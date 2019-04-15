/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 22:52:52 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/04 03:38:50 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		sha256_rnd(t_sha256 *z, int i)
{
	z->t0 = z->s[7] + (ss(z->s[4], 6) ^ ss(z->s[4], 11) ^ ss(z->s[4], 25)) + \
			(z->s[6] ^ (z->s[4] & (z->s[5] ^ z->s[6]))) + z->k[i] + z->w[i];
	z->t1 = (ss(z->s[0], 2) ^ ss(z->s[0], 13) ^ ss(z->s[0], 22)) + \
			(((z->s[0] | z->s[1]) & z->s[2]) | (z->s[0] & z->s[1]));
	z->s[3] += z->t0;
	z->s[7] = z->t0 + z->t1;
}

static t_u32	gamma0(t_u32 x)
{
	return (ss(x, 7) ^ ss(x, 18) ^ rr(x, 3));
}

static t_u32	gamma1(t_u32 x)
{
	return (ss(x, 17) ^ ss(x, 19) ^ rr(x, 10));
}

static void		sha256_compress_2(t_sha256 *z)
{
	int		i;

	i = 0;
	while (i < 64)
	{
		sha256_rnd(z, i);
		z->t = z->s[7];
		z->s[7] = z->s[6];
		z->s[6] = z->s[5];
		z->s[5] = z->s[4];
		z->s[4] = z->s[3];
		z->s[3] = z->s[2];
		z->s[2] = z->s[1];
		z->s[1] = z->s[0];
		z->s[0] = z->t;
		i++;
	}
	i = 0;
	while (i < 8)
	{
		z->sha256_state[i] = z->sha256_state[i] + z->s[i];
		i++;
	}
}

void			sha256_compress(t_sha256 *z, const unsigned char *buff)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		z->s[i] = z->sha256_state[i];
		i++;
	}
	i = 0;
	while (i < 16)
	{
		load32h(&z->w[i], buff + (4 * i));
		i++;
	}
	i = 16;
	while (i < 64)
	{
		z->w[i] = gamma1(z->w[i - 2]) + z->w[i - 7] + gamma0(z->w[i - 15]) + \
			z->w[i - 16];
		i++;
	}
	sha256_compress_2(z);
}
