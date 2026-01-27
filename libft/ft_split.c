/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: edi-maio <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/10/15 16:34:31 by edi-maio		  #+#	#+#			 */
/*   Updated: 2025/10/22 15:37:48 by edi-maio         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

static void	ft_freeall(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		++i;
	}
	free(strs);
	strs = NULL;
}

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	k;
	int	is_word;

	i = 0;
	k = 0;
	is_word = 1;
	while (s[i])
	{
		if (s[i] != c && is_word)
		{
			++k;
			is_word = 0;
		}
		else if (s[i] == c)
			is_word = 1;
		++i;
	}
	return (k);
}

static int	ft_strlen_to_c(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		++i;
	return (i);
}

static char	*ft_strdup_to_n(const char *s, int n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = malloc(sizeof(char) * (n + 1));
	if (!ptr)
		return (NULL);
	ptr[0] = '\0';
	while (s[i] && i < (size_t)n)
	{
		ptr[i] = s[i];
		++i;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**strs;
	int		k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	strs = ft_calloc(1, (ft_count_words(s, c) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (k < ft_count_words(s, c))
	{
		while (s[i] == c)
			++i;
		strs[k] = ft_strdup_to_n(&s[i], ft_strlen_to_c(&s[i], c));
		if (!strs[k])
		{
			ft_freeall(strs);
			return (NULL);
		}
		++k;
		i += ft_strlen_to_c(&s[i], c);
	}
	return (strs);
}
