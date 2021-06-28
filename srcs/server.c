/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 00:17:58 by acami             #+#    #+#             */
/*   Updated: 2021/06/28 14:59:14 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_message	g_message;

static void	initMessage(t_message *message)
{
	int	count;

	count = 0;
	message->trnasaction_pending = true;
	message->bit_pos = 0;
	message->str_pos = 0;
	while (count < BUFF_SIZE)
	{
		message->str[count] = '\0';
		++count;
	}
}

static void	printMessage(void)
{
	int32_t	 count;

	write(1, g_message.str, g_message.str_pos);
	count = 0;
	while (count < g_message.str_pos)
	{
		g_message.str[count] = '\0';
		++count;
	}
	g_message.str_pos = 0;
}

static void	recieveBit(int signal, siginfo_t *info, void *context)
{
	int32_t	bit;

	(void)context;
	if (signal == SIGUSR1)
		bit = 0;
	else
		bit = 1;
	g_message.str[g_message.str_pos] |= (bit << (7 - g_message.bit_pos));
	if (++(g_message.bit_pos) == 8)
	{
		if (g_message.str[g_message.str_pos] == '\0')
		{
			g_message.trnasaction_pending = false;
			printMessage();
			kill(info->si_pid, SIGUSR2);
			write(1, "\n", 1);
			return ;
		}
		g_message.bit_pos = 0;
		++(g_message.str_pos);
		if (g_message.str_pos == BUFF_SIZE)
			printMessage();
	}
	usleep(20);
	kill(info->si_pid, SIGUSR1);
}

static void	decodeBinary(void)
{
	struct sigaction	handler;

	handler.sa_sigaction = recieveBit;
	handler.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &handler, NULL);
	sigaction(SIGUSR2, &handler, NULL);
	while (g_message.trnasaction_pending)
		pause();
}

int	main(void)
{
	char	*pid;
	char	message[BUFF_SIZE];

	g_message.str = message;
	pid = ft_itoa(getpid());
	write(1, "I am alive! PID: ", 18);
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
	while (1)
	{
		initMessage(&g_message);
		decodeBinary();
	}
	return (0);
}
