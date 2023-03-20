/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixextend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassyao <ohassyao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:59:02 by ohassyao          #+#    #+#             */
/*   Updated: 2023/03/13 12:20:17 by ohassyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matrixextend(char **in, char *newstr)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	if (!newstr)
		return (in);
	len = ft_matrixlen(in);
	out = (char **)ft_calloc(len + 2, sizeof(char *));
	if (!out)
		return (NULL);
	while (++i < len)
		out[i] = ft_strdup(in[i]);
	out[len] = ft_strdup(newstr);
	out[len + 1] = NULL;
	ft_matrixfree(in);
	return (out);
}
