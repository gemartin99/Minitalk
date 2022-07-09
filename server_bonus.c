/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:20:17 by gemartin          #+#    #+#             */
/*   Updated: 2022/03/10 14:35:34 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include <limits.h>

static int	g_pidclient;

void	ft_putnbr(int num)
{
	int	c;

	if (num > 9)
	{
		ft_putnbr(num / 10);
		num = num % 10;
	}
	if (num <= 9)
	{
		c = (('0' + num));
		write(1, &c, 1);
	}
}

void	reset2(int *result, unsigned int *base)
{
	g_pidclient = *result;
	*result = 0;
	*base = 128;
}

void	reset(unsigned int *base, int *result, int *cont)
{
	if (*cont == 40 && *result != 0)
	{
		write(1, &*result, 1);
		*base = 128;
		*cont = 32;
		*result = 0;
	}
	else if (*cont == 40 && *result == 0)
	{
		*cont = 0;
		*base = 2147483648;
	}
}

void	conv_txt(int bit)
{
	static unsigned int		base = 2147483648;
	static int				result = 0;
	static int				cont = 0;

	if (cont < 32)
	{
		if (bit == SIGUSR1)
			result = result + base;
		base = base / 2;
	}
	if (cont == 31)
		reset2(&result, &base);
	if (cont >= 32 && cont <= 39)
	{
		if (bit == SIGUSR1)
			result = result + base;
		base = base / 2;
		kill(g_pidclient, SIGUSR1);
	}
	cont++;
	if (result == 0 && cont == 40)
		reset(&base, &result, &cont);
	if (cont == 40)
		reset(&base, &result, &cont);
}

int	main(void)
{
	int	control;

	control = 0;
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, conv_txt);
	signal(SIGUSR2, conv_txt);
	pause();
	while (1)
		sleep(1);
	return (0);
}
