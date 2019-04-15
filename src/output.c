/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:42:14 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/05 20:18:49 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			print_hash(t_flags *f)
{
	int			i;
	int			len;

	i = -1;
	len = 16;
	if (f->alg == SHA256)
		len = 32;
	while (++i < len)
		ft_printf("%.2x", f->hash[i]);
}

static void		handle_stdin(t_flags *f)
{
	if (!f->p)
	{
		print_hash(f);
		ft_printf("\n");
	}
	else
	{
		ft_printf("%s", f->str);
		print_hash(f);
		ft_printf("\n");
	}
}

static void		handle_reverse(t_flags *f)
{
	print_hash(f);
	ft_putchar(' ');
	if (f->filename)
		ft_printf("%s\n", f->filename);
	else
		ft_printf("\"%s\"\n", f->str);
}

static void		handle_file_or_string(t_flags *f)
{
	if (f->filename)
		ft_printf("%s (%s) = ", f->alg_str, f->filename);
	else
		ft_printf("%s (\"%s\") = ", f->alg_str, f->str);
	print_hash(f);
	ft_putchar('\n');
}

void			output(t_flags *f)
{
	if (f->q && !f->p)
	{
		print_hash(f);
		ft_printf("\n");
	}
	else if (!f->filename && !f->s)
		handle_stdin(f);
	else if (f->r)
		handle_reverse(f);
	else
		handle_file_or_string(f);
	f->filename = 0;
	if (f->free_str)
	{
		free(f->str);
		f->free_str = 0;
	}
}
