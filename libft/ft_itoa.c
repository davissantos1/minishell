/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:43:56 by dasimoes          #+#    #+#             */
/*   Updated: 2025/07/22 23:02:11 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digitlen(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*ft_itoa_aux(int digit_size, char *result, long n, int is_negative)
{
	result[digit_size] = '\0';
	while (digit_size)
	{
		digit_size--;
		result[digit_size] = '0' + (n % 10);
		n /= 10;
	}
	if (is_negative)
		result[0] = '-';
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		digit_size;
	long	nbr;
	int		is_negative;

	nbr = (long)n;
	is_negative = 0;
	if (n < 0)
	{
		is_negative = 1;
		nbr = -nbr;
		digit_size = ft_digitlen(nbr) + 1;
	}
	else
		digit_size = ft_digitlen(nbr);
	result = (char *)malloc((digit_size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result = ft_itoa_aux(digit_size, result, nbr, is_negative);
	return (result);
}
