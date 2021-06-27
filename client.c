/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acami <acami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 00:33:19 by acami             #+#    #+#             */
/*   Updated: 2021/06/27 21:35:50 by acami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	printAcknowledgement(int signal)
{
	if (signal == SIGUSR1)
		write(1, "Acknowledgement form server recieved\n", 38);
	else
		write(1, "Error occured!\n", 16);
}

static void	sendMessge(int serv_pid, const char *message)
{
	int32_t	count;
	char	curr_bit;

	while (*message != '\0')
	{
		count = 0;
		while (count < 8)
		{
			curr_bit = ((*message) >> (7 - count)) & 1L;
			if (curr_bit == 1)
				kill(serv_pid, SIGUSR2);
			else
				kill(serv_pid, SIGUSR1);
			usleep(200);
			++count;
		}
		++message;
	}
	count = 0;
	while (count < 8)
	{
		kill(serv_pid, SIGUSR1);
		usleep(200);
		++count;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	handler;

	if (argc == 3)
	{
		handler.sa_handler = printAcknowledgement;
		sigaction(SIGUSR1, &handler, NULL);
		sigaction(SIGUSR2, &handler, NULL);
		sendMessge(ft_atoi(argv[1]), argv[2]);
		pause();
	}
	else
		write(1, "Usage: ./client [SERVER_PID] [MESSAGE]\n", 40);
	return (0);
}
