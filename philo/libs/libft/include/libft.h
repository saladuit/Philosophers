/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   libft.h                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:15:24 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/22 16:02:00 by safoh        \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define FT_LONG_MAX 9223372036854775807

//WRITE FUNCTIONS
void		ft_putchar_fd(const char c, int fd);
void		ft_putendl_fd(const char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putuint_fd(unsigned int nb, int fd);
void		ft_put2d_fd(char **s2d, int fd, size_t len);
void		ft_error(void);
void		ft_merror(const char *function_name);

//CHECK FUNCTIONS
bool		ft_isalnum(int c);
bool		ft_isalpha(int c);
bool		ft_isascii(int c);
bool		ft_isdigit(int c);
bool		ft_isprint(int c);
bool		ft_isspace(int c);
bool		ft_isatoi(int c);
bool		ft_iszero(const char *string);
bool		ft_isempty(int c);

//MEMORY FUNCTIONS
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memalloc(size_t size);
void		*ft_memccpy(void *dest, const void *src, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memdel(void *ptr);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);

void		*ft_memint(int *arr, int d, size_t n);

//BIT FUNCTIONS
int			ft_bit_count(int num);

//STRING FUNCTIONS
char		**ft_split(char const *s, char c);
bool		ft_strbapi(char const *s, bool (*f)(int));
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
void		ft_strdel(void **ptr);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strnew(size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_strtoupper(char *string);
void		ft_strtolower(char *string);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_matrixlen(const	char **matrix, size_t count);
char		*ft_joinmatrix(const char **matrix, size_t count);

// strclr
// striter
// striteri
// strequ
// strnequ
//MISCELLANEOUS FUNCTIONS
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
size_t		ft_numlen(long long num);
size_t		ft_sgdnumlen(long long num);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_uitoa(unsigned int n);
char		*ft_uitoh(unsigned int n);
char		*ft_ultoh(unsigned long n);
const int	*ft_arrint(const int *array, const int num, const int len);
void		ft_swap(int *x, int *y);
void		ft_bubble_sort(const int len, int *integer);

//LIST FUNCTIONS
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void		ft_lstadd_back(t_list **lst, t_list *lnew);
void		ft_lstadd_front(t_list **lst, t_list *lnew);
void		ft_swap_nodes(t_list **stack);
void		ft_push_node(t_list **dest, t_list **src);
void		ft_rotate_list(t_list **lst);
void		ft_rev_rotate_list(t_list **lst);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
void		ft_free_list(t_list **stack);
//LIST IDEAS to implement
//ft_lsttravel
//ft_lstadd_after
//ft_lstsearch
//ft_lstprint

#endif
