/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:58:27 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/04 13:36:10 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft_printf/includes/ft_printf.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# define MD5 0
# define SHA256 1
# define READBUF 64

typedef unsigned int	t_u32;
typedef unsigned long	t_u64;

typedef	struct			s_sha256
{
	const t_u32			*k;
	t_u64				sha256_length;
	t_u32				*sha256_state;
	t_u32				s[8];
	t_u32				w[64];
	t_u32				t0;
	t_u32				t1;
	t_u32				t;
	unsigned char		sha256_buf[64];
}						t_sha256;

typedef struct			s_md5_ctx
{
	t_u32				lo;
	t_u32				hi;
	t_u32				a;
	t_u32				b;
	t_u32				c;
	t_u32				d;
	unsigned char		buffer[64];
	t_u32				block[16];
}						t_md5_ctx;

typedef struct			s_step
{
	t_u32				(*f)(t_u32 x, t_u32 y, t_u32 z);
	t_u32				x;
	t_u32				t;
	t_u32				s;
}						t_step;

typedef struct			s_md5_abcd
{
	const unsigned char	*ptr;
	t_u32				a;
	t_u32				b;
	t_u32				c;
	t_u32				d;
	t_u32				saved_a;
	t_u32				saved_b;
	t_u32				saved_c;
	t_u32				saved_d;
}						t_md5_abcd;

typedef struct			s_flags
{
	void				(*dispatch[2])(struct s_flags *f);
	int					alg;
	int					p;
	int					q;
	int					r;
	int					s;
	char				*str;
	char				*alg_str;
	int					free_str;
	char				*filename;
	unsigned char		*hash;
	unsigned long		size;
}						t_flags;

typedef struct			s_list_
{
	struct s_list_		*next;
	char				*data;
	int					size;
}						t_list_;

typedef struct			s_get_stdin
{
	t_list_				*head;
	t_list_				*tmp;
	t_list_				*prev;
	int					buf_size;
	int					i;
}						t_get_stdin;

int						validate_flags(char **argv, int i, t_flags *f);
void					get_strings_from_files(char **argv, int i, t_flags *f);
void					populate_dispatch_table(void (*dispatch[])(t_flags *f));
void					md5(t_flags *f);
void					sha256(t_flags *f);
void					usage(t_flags *f);
void					illegal_option(char c, t_flags *f);
char					*read_to_buffer(char *filename, int fd, t_flags *f);
void					init_flags(t_flags *f);
void					modified_strerror(char *filename, t_flags *f);
void					md5_make_rounds(t_md5_abcd *z, t_md5_ctx *ctx);
void					output(t_flags *f);
void					sha256_compress(t_sha256 *z, const unsigned char *buff);
t_u32					ss(t_u32 x, t_u32 n);
t_u32					rr(t_u32 x, t_u32 n);
void					load32h(t_u32 *x, const unsigned char *y);
void					store32h(t_u32 x, unsigned char *y);
void					store64h(t_u64 x, unsigned char *y);
t_u32					md5_f(t_u32 x, t_u32 y, t_u32 z);
t_u32					md5_g(t_u32 x, t_u32 y, t_u32 z);
t_u32					md5_h(t_u32 x, t_u32 y, t_u32 z);
t_u32					md5_h2(t_u32 x, t_u32 y, t_u32 z);
t_u32					md5_i(t_u32 x, t_u32 y, t_u32 z);
void					step(t_step *y, t_md5_abcd *z);
t_u32					set(t_md5_ctx *c, t_md5_abcd *z, int n);
t_u32					get(t_md5_ctx *c, int n);
void					out(unsigned char *dst, t_u32 src);
char					*get_stdin(t_flags *f);
t_list_					*create_node(int data_size);
void					free_node(t_list_ *node);
char					*full_buffer(t_list_ *node, int buf_size);

#endif
