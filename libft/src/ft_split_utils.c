/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:16:02 by avillar           #+#    #+#             */
/*   Updated: 2022/06/22 13:36:21 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	init_split(t_split *split, const char *s, char c)
{
	split->i = skipc(s, c, 0);
	split->j = 0;
	split->len = 0;
}
