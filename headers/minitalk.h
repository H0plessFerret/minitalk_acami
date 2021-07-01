/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 12:59:23 by acami             #+#    #+#             */
/*   Updated: 2021/07/01 13:49:02 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <inttypes.h>
# include <stdbool.h>
# include <stdlib.h>
# define BUFF_SIZE 1024
# define USLEEP_TIME 40

typedef struct s_message	t_message;

struct	s_message
{
	int32_t	str_pos;
	int32_t	bit_pos;
	char	*str;
	bool	trnasaction_pending;
};

size_t	ft_strlen(const char *str);
int32_t	ft_atoi(const char *str);
char	*ft_itoa(int n);

#endif