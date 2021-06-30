/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 00:33:19 by acami             #+#    #+#             */
/*   Updated: 2021/06/30 16:00:18 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_message	g_message;

static void	sendBit(int signal, siginfo_t *info, void *context)
{
	int32_t	bit;

	(void)context;
	if (signal == SIGUSR2)
	{
		write(1, "Everything was successfully sent to the server\n", 48);
		exit (EXIT_SUCCESS);
	}
	bit = ((g_message.str[g_message.str_pos]) >> (7 - g_message.bit_pos)) & 1L;
	usleep(30);
	if (bit == 0)
		kill(info->si_pid, SIGUSR1);
	else
		kill(info->si_pid, SIGUSR2);
	++(g_message.bit_pos);
	if (g_message.bit_pos == 8)
	{
		g_message.bit_pos = 0;
		++(g_message.str_pos);
	}
}

static void	sendMessage(int serv_pid)
{
	struct sigaction	handler;
	siginfo_t			info;

	handler.sa_sigaction = sendBit;
	handler.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &handler, NULL);
	sigaction(SIGUSR2, &handler, NULL);
	info.si_pid = serv_pid;
	sendBit(SIGUSR1, &info, NULL);
	while (1)
	{
		pause();
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		g_message.str = argv[2];
		sendMessage(ft_atoi(argv[1]));
	}
	else
		write(1, "Usage: ./client [SERVER_PID] [MESSAGE]\n", 40);
	return (0);
}
