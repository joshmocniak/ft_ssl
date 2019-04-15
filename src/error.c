/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 01:27:21 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/04 01:31:12 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			usage(t_flags *f)
{
	if (f->alg == MD5)
		ft_putstr("usage: md5 [-pqr] [-s string] [files ...]\n");
	else if (f->alg == SHA256)
		ft_putstr("usage: sha256 [-pqr] [-s string] [files ...]\n");
	exit(0);
}

void			illegal_option(char c, t_flags *f)
{
	ft_putstr(f->alg_str);
	ft_putstr(": illegal option -- ");
	ft_putchar(c);
	ft_putchar('\n');
	usage(f);
}
