/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 17:18:58 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/04 03:29:58 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			set_k(const t_u32 **k)
{
	const t_u32	*tmp;

	tmp = (const t_u32[64]){ \
		0x428a2f98UL, 0x71374491UL, 0xb5c0fbcfUL, 0xe9b5dba5UL, \
		0x3956c25bUL, 0x59f111f1UL, 0x923f82a4UL, 0xab1c5ed5UL, \
		0xd807aa98UL, 0x12835b01UL, 0x243185beUL, 0x550c7dc3UL, \
		0x72be5d74UL, 0x80deb1feUL, 0x9bdc06a7UL, 0xc19bf174UL, \
		0xe49b69c1UL, 0xefbe4786UL, 0x0fc19dc6UL, 0x240ca1ccUL, \
		0x2de92c6fUL, 0x4a7484aaUL, 0x5cb0a9dcUL, 0x76f988daUL, \
		0x983e5152UL, 0xa831c66dUL, 0xb00327c8UL, 0xbf597fc7UL, \
		0xc6e00bf3UL, 0xd5a79147UL, 0x06ca6351UL, 0x14292967UL, \
		0x27b70a85UL, 0x2e1b2138UL, 0x4d2c6dfcUL, 0x53380d13UL, \
		0x650a7354UL, 0x766a0abbUL, 0x81c2c92eUL, 0x92722c85UL, \
		0xa2bfe8a1UL, 0xa81a664bUL, 0xc24b8b70UL, 0xc76c51a3UL, \
		0xd192e819UL, 0xd6990624UL, 0xf40e3585UL, 0x106aa070UL, \
		0x19a4c116UL, 0x1e376c08UL, 0x2748774cUL, 0x34b0bcb5UL, \
		0x391c0cb3UL, 0x4ed8aa4aUL, 0x5b9cca4fUL, 0x682e6ff3UL, \
		0x748f82eeUL, 0x78a5636fUL, 0x84c87814UL, 0x8cc70208UL, \
		0x90befffaUL, 0xa4506cebUL, 0xbef9a3f7UL, 0xc67178f2UL \
	};
	*k = (const t_u32 *)ft_memalloc(sizeof(const t_u32) * 64);
	ft_memcpy((void *)*k, tmp, sizeof(const t_u32) * 64);
}

void			set_sha256_state(t_u32 **sha256_state)
{
	const t_u32	*tmp;

	tmp = (t_u32[8]){ \
		0x6A09E667UL, 0xBB67AE85UL, 0x3C6EF372UL, 0xA54FF53AUL, \
		0x510E527FUL, 0x9B05688CUL, 0x1F83D9ABUL, 0x5BE0CD19UL \
	};
	*sha256_state = (t_u32 *)ft_memalloc(sizeof(t_u32) * 8);
	ft_memcpy((void *)*sha256_state, tmp, sizeof(t_u32) * 8);
}

static void		sha256_2(unsigned char out[32], size_t len, t_sha256 *z)
{
	int		i;

	if (len > 56)
	{
		while (len < 64)
			z->sha256_buf[len++] = 0;
		sha256_compress(z, z->sha256_buf);
		len = 0;
	}
	while (len < 56)
		z->sha256_buf[len++] = 0;
	store64h(z->sha256_length, z->sha256_buf + 56);
	sha256_compress(z, z->sha256_buf);
	i = 0;
	while (i < 8)
	{
		store32h(z->sha256_state[i], out + 4 * i);
		i++;
	}
	free((void *)z->k);
	free(z->sha256_state);
	free(z);
}

static void		sha256_1(unsigned char out[32], const unsigned char *in, \
		size_t len)
{
	t_sha256	*z;

	z = (t_sha256 *)ft_memalloc(sizeof(t_sha256));
	set_k(&z->k);
	set_sha256_state(&z->sha256_state);
	z->sha256_length = 0;
	while (len >= 64)
	{
		sha256_compress(z, in);
		z->sha256_length += 64 * 8;
		in += 64;
		len -= 64;
	}
	ft_memcpy(z->sha256_buf, in, len);
	z->sha256_length += len * 8;
	z->sha256_buf[len++] = 0x80;
	sha256_2(out, len, z);
}

void			sha256(t_flags *f)
{
	f->hash = (unsigned char *)ft_memalloc(32);
	sha256_1(f->hash, (const unsigned char *)f->str, f->size);
	output(f);
	free(f->hash);
}
