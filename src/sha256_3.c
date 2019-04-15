/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 23:06:53 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/04 03:34:42 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_u32			ss(t_u32 x, t_u32 n)
{
	return (((((t_u32)(x) & 0xFFFFFFFFUL) >> (t_u32)((n) & 31)) \
			| ((t_u32)(x) << (t_u32)((32 - ((n) & 31)) & 31))) & 0xFFFFFFFFUL);
}

t_u32			rr(t_u32 x, t_u32 n)
{
	return (((x) & 0xFFFFFFFFUL) >> (n));
}

void			load32h(t_u32 *x, const unsigned char *y)
{
	*x = ((t_u32)((y)[0] & 255) << 24) | ((t_u32)((y)[1] & 255) << 16) | \
	((t_u32)((y)[2] & 255) << 8) | ((t_u32)((y)[3] & 255));
}

void			store32h(t_u32 x, unsigned char *y)
{
	(y)[0] = (unsigned char)(((x) >> 24) & 255);
	(y)[1] = (unsigned char)(((x) >> 16) & 255);
	(y)[2] = (unsigned char)(((x) >> 8) & 255);
	(y)[3] = (unsigned char)((x) & 255);
}

void			store64h(t_u64 x, unsigned char *y)
{
	(y)[0] = (unsigned char)(((x) >> 56) & 255); \
	(y)[1] = (unsigned char)(((x) >> 48) & 255); \
	(y)[2] = (unsigned char)(((x) >> 40) & 255); \
	(y)[3] = (unsigned char)(((x) >> 32) & 255); \
	(y)[4] = (unsigned char)(((x) >> 24) & 255); \
	(y)[5] = (unsigned char)(((x) >> 16) & 255); \
	(y)[6] = (unsigned char)(((x) >> 8) & 255); \
	(y)[7] = (unsigned char)((x) & 255);
}
