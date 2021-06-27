/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 20:50:01 by acami             #+#    #+#             */
/*   Updated: 2021/06/27 23:43:03 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	ft_is_ignorable(char sym)
{
	if ((sym != '\n') && (sym != ' ') && (sym != '\t')
		&& (sym != '\v') && (sym != '\r') && (sym != '\f'))
		return (0);
	return (1);
}

int32_t	ft_atoi(const char *str)
{
	int32_t	sign;
	int32_t	result;

	result = 0;
	sign = 1;
	while (ft_is_ignorable(*str))
		++str;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	else if (*str == '+')
		++str;
	while ((*str >= '0') && (*str <= '9'))
	{
		result = result * 10 + (*str - '0') * sign;
		++str;
	}
	return (result);
}
