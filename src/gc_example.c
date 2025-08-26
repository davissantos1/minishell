#include "setup.h"

int	main(void)
{
	t_gc	*gc;
	char	*ptr;
	char	*dup;

	gc = gc_init();
	if (!gc)
		return (1);
	ptr = gc_malloc( 12 * sizeof(char), gc, GC_DEFAULT);	
	if (!ptr)
	{	
		gc = gc_free_all(gc);
		return (1);
	}
	ft_strlcpy(ptr, "Weird stuff", 12);
	ft_putstr_fd("ptr is: \n", 1);
	ft_putstr_fd(ptr, 1);
	ft_putstr_fd("\n", 1);
	dup = ft_strdup(ptr);
	ft_putstr_fd("dup is: \n", 1);
	ft_putstr_fd(dup, 1);
	ft_putstr_fd("\n", 1);
	if (!gc_addptr(dup, gc, GC_TEMP))
	{	
		gc = gc_free_all(gc);
		return (1);
	}
	dup = gc_free_tag(gc, GC_TEMP);
	ft_putstr_fd("dup after free is: \n", 1);
	if (!dup)
		ft_putstr_fd("NULL", 1);
	ft_putstr_fd("\n", 1);
	gc = gc_free_all(gc);
	ft_putstr_fd("ptr after free is: \n", 1);
	ft_putstr_fd(ptr, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
	
