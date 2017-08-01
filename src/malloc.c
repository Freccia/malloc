#include "malloc.h"

t_page		*new_page(size_t size)
{
	t_page		*new_page;

	new_page = mmap(NULL, size,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new_page == MAP_FAILED)
		return ((t_page *)-1);
	ft_bzero(new_page, sizeof(t_page));
	new_page->full = FALSE;
	new_page->size = size;
	new_page->size_left = size;
	new_page->next = NULL;
	//*(new_page + sizeof(t_page)) = TRUE; // chunk->free
	//*(new_page + sizeof(t_page)) + 1 = size; // chunk->size
	new_page->first.free = TRUE;
	new_page->first.size = size;
	return (new_page);
}

t_page		*get_new_page(size_t size)
{
	t_page	*page;

	page = NULL;
	if (size + sizeof(t_page) + sizeof(t_chunk) <= SMALL)
		page = new_page(SMALL);
	else if (size + sizeof(t_page) + sizeof(t_chunk) <= TINY)
		page = new_page(TINY);
	else
		page = new_page(size);
	return (page);
}

void			add_new_page(size_t size)
{
	t_page	*tmp;

	tmp = g_mem;
	g_mem = get_new_page(size);
	g_mem->next = tmp;
}

void			*check_and_choose_chunk(size_t size, t_page *page)
{
	t_chunk	*ptr;
	void		*chunk;

	chunk = NULL;
	if (page->first.free == TRUE && page->first.size >= size)
		return (void*)(page + sizeof(t_page));
	ptr = (t_chunk*)(page + sizeof(t_page));
	while(ptr->free != TRUE)
	{
		ptr = (t_chunk*)(ptr + sizeof(t_page) + ptr->size);
	}
	return (chunk);
}

void			*find_chunk_space(size_t size)
{
	t_page	*ptr;
	void		*chunk;

	chunk = NULL;
	ptr = g_mem;
	while (ptr && ptr->full == TRUE && ptr->size_left < size)
		ptr = ptr->next;
	if (ptr == NULL)
		return ((void*)-1);
	if ((chunk = check_and_choose_chunk(size, ptr)))
		return (chunk);
	return ((void*)-1);
}

void			*mymalloc(size_t size)
{
	void	*chunk;

	chunk = NULL;
	if (g_mem)
	{
		if ((chunk = find_chunk_space(size)) != (void*)-1)
			return (chunk);
		add_new_page(size);
		if ((chunk = find_chunk_space(size)) == (void*)-1)
			return ((void*)-1);
	}
	else
	{
		g_mem = get_new_page(size); 
		chunk = (void*)(g_mem + sizeof(t_page) + sizeof(t_chunk));
	}
	return (chunk);
}

int myfree(void* addr)
{
	if (addr != NULL)
		return (munmap(addr - sizeof(size_t), (size_t) addr));
	return (munmap(addr - sizeof(size_t), (size_t) addr));
}


