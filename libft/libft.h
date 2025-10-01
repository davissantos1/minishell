/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:42:33 by dasimoes          #+#    #+#             */
/*   Updated: 2025/09/30 16:23:20 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// External includes
# include <stdlib.h>

// Macros
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define LONG_MAX 9223372036854775807
# define LONG_MIN -9223372036854775808

// Enums
typedef enum e_gc_tag
{
	GC_SHELL,
	GC_TOKEN,
	GC_AST,
	GC_CMD,
	GC_TEMP,
	GC_CUSTOM1,
	GC_CUSTOM2,
	GC_CUSTOM3,
	GC_COUNT
}	t_gc_tag;

// Structs
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_btree
{
	struct s_btree	*right;
	struct s_btree	*left;
	void			*item;
}	t_btree;

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node	*lists[GC_COUNT];
}	t_gc;

// Part 1 - Libc Functions
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s)
			__attribute__((nonnull));
void		*ft_memset(void *s, int c, size_t n)
			__attribute__((nonnull(1)));
void		ft_bzero(void *s, size_t n)
			__attribute__((nonnull(1)));
void		*ft_memcpy(void *dest, const void *src, size_t n)
			__attribute__((nonnull(1, 2)));
void		*ft_memmove(void *dest, const void *src, size_t n)
			__attribute__((nonnull(1, 2)));
size_t		ft_strlcpy(char *dst, const char *src, size_t size)
			__attribute__((nonnull(1, 2)));
size_t		ft_strlcat(char *dst, const char *src, size_t size)
			__attribute__((nonnull(1, 2)));
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c)
			__attribute__((nonnull(1)));
char		*ft_strrchr(const char *s, int c)
			__attribute__((nonnull(1)));
int			ft_strncmp(const char *s1, const char *s2, size_t n)
			__attribute__((nonnull(1, 2)));
void		*ft_memchr(const void *s, int c, size_t n)
			__attribute__((nonnull(1)));
int			ft_memcmp(const void *s1, const void *s2, size_t n)
			__attribute__((nonnull(1, 2)));
char		*ft_strnstr(const char *big, const char *little, size_t len)
			__attribute__((nonnull(1, 2)));
int			ft_atoi(const char *nptr)
			__attribute__((nonnull));
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s)
			__attribute__((nonnull));

// Part 	2 - Additional Functions
char		*ft_substr(char const *s, unsigned int start, size_t len)
			__attribute__((nonnull(1)));
char		*ft_strjoin(char const *s1, char const *s2)
			__attribute__((nonnull(1, 2)));
char		*ft_strtrim(char const *s1, char const *set)
			__attribute__((nonnull(1, 2)));
char		**ft_split(char const *s, char c)
			__attribute__((nonnull(1)));
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
			__attribute__((nonnull(1, 2)));
void		ft_striteri(char *s, void (*f)(unsigned int, char*))
			__attribute__((nonnull(1, 2)));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd)
			__attribute__((nonnull(1)));
void		ft_putendl_fd(char *s, int fd)
			__attribute__((nonnull(1)));
void		ft_putnbr_fd(int n, int fd);

// Part 3 - Bonus Functions (linked list)
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new)
			__attribute__((nonnull(1, 2)));
int			ft_lstsize(t_list *lst)
			__attribute__((nonnull(1)));
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new)
			__attribute__((nonnull(1, 2)));
void		ft_lstdelone(t_list *lst, void (*del)(void*))
			__attribute__((nonnull(1, 2)));
void		ft_lstclear(t_list **lst, void (*del)(void*))
			__attribute__((nonnull(1, 2)));
void		ft_lstiter(t_list *lst, void (*f)(void *))
			__attribute__((nonnull(1, 2)));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
			__attribute__((nonnull(1, 2, 3)));

// Part 4 - Bonus Functions (b-trees)
t_btree		*btree_create_node(void *item);
void		btree_apply_infix(t_btree *root, void (*applyf)(void *))
			__attribute__((nonnull(1, 2)));
void		btree_apply_prefix(t_btree *root, void (*applyf)(void *))
			__attribute__((nonnull(1, 2)));
void		btree_apply_suffix(t_btree *root, void (*applyf)(void *))
			__attribute__((nonnull(1, 2)));

// Part 5 - Garbage Collector Functions
t_gc_node	*gc_create_node(void *p);
t_gc		*gc_init(void);
void		*gc_free_all(t_gc *gc);
void		*gc_free_tag(t_gc *gc, t_gc_tag tag);
void		*gc_malloc(size_t size, t_gc *gc, t_gc_tag tag)
			__attribute__((nonnull(2)));
void		*gc_calloc(size_t size, t_gc *gc, t_gc_tag tag)
			__attribute__((nonnull(2)));
void		*gc_addptr(void *p, t_gc *gc, t_gc_tag tag)
			__attribute__((nonnull(2)));
void		*gc_addmtx(void *mtx, t_gc *gc, t_gc_tag tag)
			__attribute__((nonnull(1, 2)));
void		*gc_addlst(void *head, t_gc *gc, t_gc_tag tag)
			__attribute__((nonnull(1, 2)));
void		*gc_addbtree(void *root, t_gc *gc, t_gc_tag tag)
			__attribute__((nonnull(1, 2)));
void		gc_delptr(void *p, t_gc *gc, t_gc_tag tag)
			__attribute__((nonnull(1, 2)));
void		*gc_findptr(void *p, t_gc *gc)
			__attribute__((nonnull(1, 2)));
void		*gc_findptr_tag(void *p, t_gc *gc, t_gc_tag tag)
			__attribute__((nonnull(1, 2)));
void		gc_dellst(void *head, int index, t_gc *gc, t_gc_tag tag)
			__attribute__((nonnull(1, 3)));
void		gc_delbtree(void *root, t_gc *gc, t_gc_tag tag)
			__attribute__((nonnull(1, 2)));

// Part 6 - Extra Cool Functions
void		*ft_free(void *ptr);
long		ft_atol(const char *nbr)
			__attribute__((nonnull));
void		*ft_mtxfree(char **mtx);
char		**ft_mtxjoin(char **mtx1, char **mtx2)
			__attribute__((nonnull(1, 2)));
void		*ft_memdup(const void *src, size_t n)
			__attribute__((nonnull(1)));
size_t		ft_mtxlen(char **mtx)
			__attribute__((nonnull));
char		**ft_mtxdup(char **mtx)
			__attribute__((nonnull));
void		ft_putmtx_fd(char **mtx, int fd)
			__attribute__((nonnull(1)));
int			*ft_bubble_sort_int(int	*arr, int size)
			__attribute__((nonnull(1)));

#endif
