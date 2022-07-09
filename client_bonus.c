/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:05:57 by gemartin          #+#    #+#             */
/*   Updated: 2022/03/10 14:50:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<limits.h>
#include<stdlib.h>

int	ft_atoi(const char *str)
{
	int				i;
	long long int	nbr;

	nbr = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
		if (nbr > INT_MAX)
			return (-1);
	}
	return (nbr);
}

void	conv_int_bin(unsigned int c, int pidserv)
{
	unsigned int		base;
	unsigned int		cont;

	cont = 0;
	base = 2147483648;
	if (cont < 32)
	{
		while (base > 0)
		{
			if (c >= base)
			{
				kill(pidserv, SIGUSR1);
				c = c - base;
			}
			else
			{
				kill(pidserv, SIGUSR2);
			}
			base = base / 2;
			usleep(300);
		}
	}
	usleep(500);
	cont++;
}

void	conv_bin(unsigned char c, int pidserv)
{
	int		base;

	base = 128;
	while (base > 0)
	{
		if (c >= base)
		{
			kill(pidserv, SIGUSR1);
			c = c - base;
		}
		else
		{
			kill(pidserv, SIGUSR2);
		}
		base = base / 2;
		usleep(300);
	}
	usleep(500);
}

void	confirm(int sig)
{
	if (sig == SIGUSR1)
		write (1, "Received bit\n", 13);
}

int	main(int argc, char **argv)
{
	int	pidserv;
	int	i;

	i = 0;
	if (argc != 3)
		return (-1);
	signal(SIGUSR1, confirm);
	pidserv = ft_atoi(argv[1]);
	conv_int_bin(getpid(), pidserv);
	while (argv[2][i])
	{
		conv_bin(argv[2][i], pidserv);
		i++;
	}
	conv_bin('\0', pidserv);
	return (0);
}
