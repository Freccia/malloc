#include "malloc.h"

#include "libft.h" //norme
#include <stdio.h> //norme

t_page		*new_page(size_t size)
{
	t_page			*new_page;
	t_chunk			*chunk;

	new_page = mmap(NULL, size,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new_page == MAP_FAILED)
		return ((t_page *)-1);
	ft_bzero(new_page, size);
	new_page->full = FALSE;
	new_page->size = size;
	new_page->size_left = size - sizeof(t_page) - sizeof(t_chunk);
	new_page->next = NULL;
	chunk = (t_chunk*)(new_page + sizeof(t_page));
	chunk->free = TRUE;
	chunk->size = size;
	return (new_page);
}

t_page		*get_new_page(size_t size)
{
	t_page	*page;

	page = NULL;
	if (size + sizeof(t_page) + sizeof(t_chunk) <= TINY)
		page = new_page(TINY);
	else if (size + sizeof(t_page) + sizeof(t_chunk) <= SMALL)
		page = new_page(SMALL);
	else
		page = new_page(size);
	return (page);
}

int				add_new_page(size_t size)
{
	t_page	*tmp;

	tmp = g_mem;
	if ((g_mem = get_new_page(size)) == (void*)-1)
			return (-1);
	g_mem->next = tmp;
	return (0);
}

void			*check_and_choose_chunk(size_t size, t_page *page)
{
	t_chunk		*chunk;

	chunk = (t_chunk*)(page + sizeof(t_page));
	if (chunk->free == TRUE && chunk->size >= size)
		return ((void*)(chunk + sizeof(t_chunk)));
	while(chunk->free != TRUE)
	{
		chunk = (t_chunk*)(chunk + chunk->size);
	}
	return ((void*)chunk + sizeof(t_chunk));
}

void			*find_chunk_space(size_t size)
{
	t_page	*page;
	void		*memo;

	memo = NULL;
	page = g_mem;
	while (page && (page->full == TRUE || page->size_left < size))
		page = page->next;
	if (page == NULL)
		return ((void*)-1);
	if ((memo = check_and_choose_chunk(size, page)))
		return (memo);
	return ((void*)-1);
}

void			*mymalloc(size_t size)
{
	void	*memo;

	memo = NULL;
	if (g_mem)
	{
		if ((memo = find_chunk_space(size)) != (void*)-1)
			return (memo);
		if (add_new_page(size) == -1)
				return ((void*)-1);
		if ((memo = find_chunk_space(size)) == (void*)-1)
			return ((void*)-1);
	}
	else
	{
		g_mem = get_new_page(size); 
		memo = (void*)(g_mem + sizeof(t_page) + sizeof(t_chunk));
	}
	return (memo);
}

int				myfree(void* addr)
{
	if (addr != NULL)
		return (munmap(addr - sizeof(size_t), (size_t) addr));
	return (munmap(addr - sizeof(size_t), (size_t) addr));
}

/*
**	this implementation is shitty. must implement padding and
**		for god's sake clean it!
*/

void			show_alloc_mem()
{
		t_page	*page;

		page = g_mem;
		printf("TINY: %p\n", page);
		while (page)
		{
				if (page->size <= TINY)
					printf("%p - %p\n", page + sizeof(t_page), (page + page->size));
				page = page->next;
		}
		page = g_mem;
		printf("SMALL: %p\n", page);
		while (page)
		{
				if (page->size > TINY && page->size <= SMALL)
					printf("%p - %p\n", page + sizeof(t_page), (page + page->size));
				page = page->next;
		}
		page = g_mem;
		printf("LARGE: %p\n", page);
		while (page)
		{
				if (page->size > SMALL)
					printf("%p - %p\n", page + sizeof(t_page), (page + page->size));
				page = page->next;
		}
}


