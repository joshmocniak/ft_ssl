/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_body.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:02:38 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/04 01:14:23 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		round_1(t_md5_abcd *z, t_md5_ctx *c)
{
	step(&(t_step){md5_f, set(c, z, 0), 0xd76aa478, 7}, z);
	step(&(t_step){md5_f, set(c, z, 1), 0xe8c7b756, 12}, z);
	step(&(t_step){md5_f, set(c, z, 2), 0x242070db, 17}, z);
	step(&(t_step){md5_f, set(c, z, 3), 0xc1bdceee, 22}, z);
	step(&(t_step){md5_f, set(c, z, 4), 0xf57c0faf, 7}, z);
	step(&(t_step){md5_f, set(c, z, 5), 0x4787c62a, 12}, z);
	step(&(t_step){md5_f, set(c, z, 6), 0xa8304613, 17}, z);
	step(&(t_step){md5_f, set(c, z, 7), 0xfd469501, 22}, z);
	step(&(t_step){md5_f, set(c, z, 8), 0x698098d8, 7}, z);
	step(&(t_step){md5_f, set(c, z, 9), 0x8b44f7af, 12}, z);
	step(&(t_step){md5_f, set(c, z, 10), 0xffff5bb1, 17}, z);
	step(&(t_step){md5_f, set(c, z, 11), 0x895cd7be, 22}, z);
	step(&(t_step){md5_f, set(c, z, 12), 0x6b901122, 7}, z);
	step(&(t_step){md5_f, set(c, z, 13), 0xfd987193, 12}, z);
	step(&(t_step){md5_f, set(c, z, 14), 0xa679438e, 17}, z);
	step(&(t_step){md5_f, set(c, z, 15), 0x49b40821, 22}, z);
}

static void		round_2(t_md5_abcd *z, t_md5_ctx *c)
{
	step(&(t_step){md5_g, get(c, 1), 0xf61e2562, 5}, z);
	step(&(t_step){md5_g, get(c, 6), 0xc040b340, 9}, z);
	step(&(t_step){md5_g, get(c, 11), 0x265e5a51, 14}, z);
	step(&(t_step){md5_g, get(c, 0), 0xe9b6c7aa, 20}, z);
	step(&(t_step){md5_g, get(c, 5), 0xd62f105d, 5}, z);
	step(&(t_step){md5_g, get(c, 10), 0x02441453, 9}, z);
	step(&(t_step){md5_g, get(c, 15), 0xd8a1e681, 14}, z);
	step(&(t_step){md5_g, get(c, 4), 0xe7d3fbc8, 20}, z);
	step(&(t_step){md5_g, get(c, 9), 0x21e1cde6, 5}, z);
	step(&(t_step){md5_g, get(c, 14), 0xc33707d6, 9}, z);
	step(&(t_step){md5_g, get(c, 3), 0xf4d50d87, 14}, z);
	step(&(t_step){md5_g, get(c, 8), 0x455a14ed, 20}, z);
	step(&(t_step){md5_g, get(c, 13), 0xa9e3e905, 5}, z);
	step(&(t_step){md5_g, get(c, 2), 0xfcefa3f8, 9}, z);
	step(&(t_step){md5_g, get(c, 7), 0x676f02d9, 14}, z);
	step(&(t_step){md5_g, get(c, 12), 0x8d2a4c8a, 20}, z);
}

static void		round_3(t_md5_abcd *z, t_md5_ctx *c)
{
	step(&(t_step){md5_h, get(c, 5), 0xfffa3942, 4}, z);
	step(&(t_step){md5_h2, get(c, 8), 0x8771f681, 11}, z);
	step(&(t_step){md5_h, get(c, 11), 0x6d9d6122, 16}, z);
	step(&(t_step){md5_h2, get(c, 14), 0xfde5380c, 23}, z);
	step(&(t_step){md5_h, get(c, 1), 0xa4beea44, 4}, z);
	step(&(t_step){md5_h2, get(c, 4), 0x4bdecfa9, 11}, z);
	step(&(t_step){md5_h, get(c, 7), 0xf6bb4b60, 16}, z);
	step(&(t_step){md5_h2, get(c, 10), 0xbebfbc70, 23}, z);
	step(&(t_step){md5_h, get(c, 13), 0x289b7ec6, 4}, z);
	step(&(t_step){md5_h2, get(c, 0), 0xeaa127fa, 11}, z);
	step(&(t_step){md5_h, get(c, 3), 0xd4ef3085, 16}, z);
	step(&(t_step){md5_h2, get(c, 6), 0x04881d05, 23}, z);
	step(&(t_step){md5_h, get(c, 9), 0xd9d4d039, 4}, z);
	step(&(t_step){md5_h2, get(c, 12), 0xe6db99e5, 11}, z);
	step(&(t_step){md5_h, get(c, 15), 0x1fa27cf8, 16}, z);
	step(&(t_step){md5_h2, get(c, 2), 0xc4ac5665, 23}, z);
}

static void		round_4(t_md5_abcd *z, t_md5_ctx *c)
{
	step(&(t_step){md5_i, get(c, 0), 0xf4292244, 6}, z);
	step(&(t_step){md5_i, get(c, 7), 0x432aff97, 10}, z);
	step(&(t_step){md5_i, get(c, 14), 0xab9423a7, 15}, z);
	step(&(t_step){md5_i, get(c, 5), 0xfc93a039, 21}, z);
	step(&(t_step){md5_i, get(c, 12), 0x655b59c3, 6}, z);
	step(&(t_step){md5_i, get(c, 3), 0x8f0ccc92, 10}, z);
	step(&(t_step){md5_i, get(c, 10), 0xffeff47d, 15}, z);
	step(&(t_step){md5_i, get(c, 1), 0x85845dd1, 21}, z);
	step(&(t_step){md5_i, get(c, 8), 0x6fa87e4f, 6}, z);
	step(&(t_step){md5_i, get(c, 15), 0xfe2ce6e0, 10}, z);
	step(&(t_step){md5_i, get(c, 6), 0xa3014314, 15}, z);
	step(&(t_step){md5_i, get(c, 13), 0x4e0811a1, 21}, z);
	step(&(t_step){md5_i, get(c, 4), 0xf7537e82, 6}, z);
	step(&(t_step){md5_i, get(c, 11), 0xbd3af235, 10}, z);
	step(&(t_step){md5_i, get(c, 2), 0x2ad7d2bb, 15}, z);
	step(&(t_step){md5_i, get(c, 9), 0xeb86d391, 21}, z);
}

void			md5_make_rounds(t_md5_abcd *z, t_md5_ctx *ctx)
{
	z->saved_a = z->a;
	z->saved_b = z->b;
	z->saved_c = z->c;
	z->saved_d = z->d;
	round_1(z, ctx);
	round_2(z, ctx);
	round_3(z, ctx);
	round_4(z, ctx);
	z->a += z->saved_a;
	z->b += z->saved_b;
	z->c += z->saved_c;
	z->d += z->saved_d;
	z->ptr += 64;
}
