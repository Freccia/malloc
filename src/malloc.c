
#include "malloc.h"

#include "libft.h" //norme
#include <stdio.h> //norme

/*
 **  initialize the new page and the first chunk of memory allocated
 */

t_page		*new_page(size_t page_size, size_t chunk_size)
{
    t_page			*new_page;
    t_chunk			*chunk;

    ft_printf("TINY: %ld\n", TINY);
    ft_printf("SMALL: %ld\n", SMALL);
    ft_printf("PAGE_TINY: %ld\n", PAGE_TINY);
    ft_printf("PAGE_SMALL: %ld\n", PAGE_SMALL);
    new_page = mmap(NULL, page_size,
            PROT_READ | PROT_WRITE,
            MAP_ANON | MAP_PRIVATE, -1, 0);
    if (new_page == MAP_FAILED)
        return ((t_page *)-1);
    ft_bzero(new_page, page_size);
    new_page->full = FALSE;
    new_page->size = page_size;
    new_page->size_left = page_size - PAGE_META - CHUNK_META;
    new_page->next = NULL;
    chunk = (t_chunk*)(new_page + PAGE_META);
    chunk->free = TRUE;
    chunk->size = chunk_size;
    ft_printf("NEW_PAGE_SIZE: %ld\n", new_page->size);
    return (new_page);
}

t_page		*get_new_page(size_t size)
{
    t_page	*page;

    page = NULL;
    if (size + PAGE_META + CHUNK_META <= TINY)
        page = new_page(PAGE_TINY, size);
    else if (size + PAGE_META + CHUNK_META <= SMALL)
        page = new_page(PAGE_SMALL, size);
    else
        page = new_page(size, size);
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

void			*find_free_chunk(size_t size, t_page *page)
{
    t_chunk		*chunk;
    t_chunk     *tmp;

    chunk = (t_chunk*)(page + PAGE_META);
    if (chunk->free == TRUE && chunk->size >= size)
    {
        chunk->free = FALSE;
        chunk->size = size;
        tmp = (t_chunk*)(chunk + CHUNK_META + size);
        tmp->free = TRUE;
        tmp->size = page->size_left - CHUNK_META - size;
        return ((void*)(chunk + CHUNK_META));
    }
    while(chunk->free != TRUE)
    {
        chunk = (t_chunk*)(chunk + chunk->size);
    }
    chunk->free = FALSE;
    chunk->size = size;
    tmp = (t_chunk*)(chunk + CHUNK_META + size);
    tmp->free = TRUE;
    tmp->size = page->size_left - CHUNK_META - size;
    return ((void*)chunk + CHUNK_META);
}

void			*get_chunk(size_t size)
{
    t_page  *page;
    void    *memo;

    page = g_mem;
    memo = NULL;
    while (page && (page->full == TRUE || page->size_left < size))
        page = page->next;
    if (page == NULL)
        return ((void*)-1);
    if ((memo = find_free_chunk(size, page)))
    {
        page->size_left -= size + CHUNK_META;
        return (memo);
    }
    return ((void*)-1);
}

void			*mymalloc(size_t size)
{
    void	*memo;

    memo = NULL;
    if (g_mem)
    {
        if ((memo = get_chunk(size)) != (void*)-1)
            return (memo);
        if (add_new_page(size) == -1)
            return ((void*)-1);
        if ((memo = get_chunk(size)) == (void*)-1)
            return ((void*)-1);
    }
    else
    {
        g_mem = get_new_page(size); 
        if ((memo = get_chunk(size)) == (void*)-1)
            return ((void*)-1);
    }
    return (memo);
}

int				myfree(void* addr)
{
    if (addr != NULL)
        return (munmap(addr - PAGE_META - CHUNK_META, (size_t) addr));
    return (munmap(addr - PAGE_META - CHUNK_META, (size_t) addr));
}

/*
 **	this implementation is shitty. must implement padding and
 **		for god's sake clean it!
 */

void      print_mem_chunks(t_page *page)
{
    t_chunk   *chunk;

    chunk = (t_chunk*)(page + PAGE_META);
    while (chunk->free == FALSE && chunk->size != 0)
    {
        ft_printf("%p - %p : %ld octets\n", chunk, (chunk + chunk->size), ((chunk + chunk->size) - chunk));
        chunk += chunk->size;
    }
}

void			show_alloc_mem()
{
    t_page	*page;

    page = g_mem;
    while (page)
    {
        if (page->size <= PAGE_TINY)
        {
            ft_printf("TINY: %p\n", page);
            print_mem_chunks(page);
        }
        else if (page->size <= PAGE_SMALL)
        {
            ft_printf("SMALL: %p\n", page);
            print_mem_chunks(page);
        }
        else
        {
            ft_printf("LARGE: %p\n", page);
            print_mem_chunks(page);
        }
        page = page->next;
    }
}


