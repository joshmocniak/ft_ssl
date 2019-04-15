/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 17:18:19 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/04 03:17:27 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const void	*body(t_md5_ctx *ctx, const void *data, unsigned long size)
{
	t_md5_abcd			z;

	z.ptr = (const unsigned char *)data;
	z.a = ctx->a;
	z.b = ctx->b;
	z.c = ctx->c;
	z.d = ctx->d;
	while (1)
	{
		md5_make_rounds(&z, ctx);
		if (!(size -= 64))
			break ;
	}
	ctx->a = z.a;
	ctx->b = z.b;
	ctx->c = z.c;
	ctx->d = z.d;
	return (z.ptr);
}

static void			md5_init(t_md5_ctx *ctx)
{
	ctx->a = 0x67452301;
	ctx->b = 0xefcdab89;
	ctx->c = 0x98badcfe;
	ctx->d = 0x10325476;
	ctx->lo = 0;
	ctx->hi = 0;
}

static void			md5_update(t_md5_ctx *ctx, const void *data, \
		unsigned long size)
{
	t_u32			saved_lo;
	unsigned long	used;
	unsigned long	available;

	saved_lo = ctx->lo;
	if ((ctx->lo = (saved_lo + size) & 0x1fffffff) < saved_lo)
		ctx->hi++;
	ctx->hi += size >> 29;
	used = saved_lo & 0x3f;
	if (used)
	{
		available = 64 - used;
		if (size < available && (ft_memcpy(&ctx->buffer[used], data, size)))
			return ;
		ft_memcpy(&ctx->buffer[used], data, available);
		data = (const unsigned char *)data + available;
		size -= available;
		body(ctx, ctx->buffer, 64);
	}
	if (size >= 64 && (data = body(ctx, data, size & ~(unsigned long)0x3f)))
		size &= 0x3f;
	ft_memcpy(ctx->buffer, data, size);
}

void				md5_final(unsigned char *result, t_md5_ctx *ctx)
{
	unsigned long	used;
	unsigned long	available;

	used = ctx->lo & 0x3f;
	ctx->buffer[used++] = 0x80;
	available = 64 - used;
	if (available < 8)
	{
		ft_bzero(&ctx->buffer[used], available);
		body(ctx, ctx->buffer, 64);
		used = 0;
		available = 64;
	}
	ft_bzero(&ctx->buffer[used], available - 8);
	ctx->lo <<= 3;
	out(&ctx->buffer[56], ctx->lo);
	out(&ctx->buffer[60], ctx->hi);
	body(ctx, ctx->buffer, 64);
	out(&result[0], ctx->a);
	out(&result[4], ctx->b);
	out(&result[8], ctx->c);
	out(&result[12], ctx->d);
}

void				md5(t_flags *f)
{
	t_md5_ctx		ctx;

	md5_init(&ctx);
	md5_update(&ctx, (const void *)f->str, f->size);
	f->hash = (unsigned char *)ft_memalloc(16);
	md5_final(f->hash, &ctx);
	output(f);
	free(f->hash);
}
