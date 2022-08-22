/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_split.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2022/06/23 15:11:38 by safoh        /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2022/07/20 20:12:40 by saladuit     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countchar(char const *s, char c)
{
	size_t	count;
	size_t	len;
	size_t	i;

	count = 0;
	len = 0;
	i = 0;
	while (i < ft_strlen(s) + 1)
	{
		if (s[i] == c || s[i] == '\0')
		{
			if (len != 0)
				count++;
			len = 0;
		}
		if (s[i] != c)
			len++;
		i++;
	}
	return (count);
}

static char	**ft_createarrray(char **array, char *s, char c, size_t arraycount)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	while (i < ft_strlen(s) + 1 && j < arraycount)
	{
		if (s[i] == c || s[i] == '\0')
		{
			if (len != 0)
			{
				array[j] = ft_substr(s, i - len, len);
				j++;
			}
			len = 0;
		}
		if (s[i] != c)
			len++;
		i++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	arraycount;

	if (!s)
		return (NULL);
	arraycount = ft_countchar(s, c);
	split = (char **)ft_calloc(arraycount + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split = ft_createarrray(split, (char *)s, c, arraycount);
	return (split);
}
