/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:20:17 by gemartin          #+#    #+#             */
/*   Updated: 2022/03/07 18:24:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include <limits.h>

void	ft_putchar(int c)
{
	write (1, &c, 1);
}

void	ft_putnbr(int num)
{
	if (num > 9)
	{
		ft_putnbr(num / 10);
		num = num % 10;
	}
	if (num <= 9)
		ft_putchar (('0' + num));
}

void	conv_txt(char *s)
{
	int		i;
	int		base;
	char	bit;
	int		control;
	int		result;

	i = 7;
	while (s[i])
	{
		base = 1;
		control = i;
		result = 0;
		while (base <= 128)
		{
			bit = s[control];
			if (bit == '1')
				result = result + base;
			base = base * 2;
			control--;
		}
		write(1, &result, 1);
		i = i + 8;
	}
}

void	alm_bin(int sig)
{
	static int	i = 0;
	static char	c[8];

	if (sig == SIGUSR1)
		c[i] = '1';
	else if (sig == SIGUSR2)
		c[i] = '0';
	i++;
	if (i == 8)
	{
		i = 0;
		conv_txt(c);
	}
}

int	main(void)
{
	getpid();
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, alm_bin);
	signal(SIGUSR2, alm_bin);
	while (1)
		sleep(1);
	return (0);
}
