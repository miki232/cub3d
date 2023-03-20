/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoia <mtoia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:35:08 by mtoia             #+#    #+#             */
/*   Updated: 2023/03/20 16:35:27 by mtoia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_impr(char *out, char *str)
{
	int	i;
	int	k;
	int	x;

	i = 0;
	k = 0;
	x = ft_strlen(out);
	while (x >= 0)
	{
		if (out[i] == '\'' || out[i] == '\"')
		{
			i++;
			continue ;
		}
		else if (out[i] != str[k])
			return (0);
		i++;
		k++;
		x--;
	}
	return (1);
}
