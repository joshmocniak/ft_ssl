/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:09:08 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/04 13:34:30 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			err_msg(char *str)
{
	ft_putstr(str);
	exit(1);
}

char			*invalid_command(char *str)
{
	char	*tmp;

	tmp = "ft_ssl: Error: '";
	str = ft_strjoin(tmp, str);
	tmp = "' is an invalid command.\n\nStandard commands:\n\n\
Message Digest commands:\nmd5\nsha256\n\nCipher commands:\n";
	tmp = ft_strjoin(str, tmp);
	free(str);
	ft_putstr(tmp);
	free(tmp);
	exit(1);
}

static void		check_args(int argc, char **argv, t_flags *f)
{
	int		i;

	i = 2;
	if (argc < 2)
		err_msg("usage: ft_ssl command [command opts] [command args]\n");
	else
	{
		if (!ft_strcmp("md5", argv[1]))
		{
			f->alg_str = ft_strdup("MD5");
			f->alg = MD5;
		}
		else if (!ft_strcmp("sha256", argv[1]))
		{
			f->alg_str = ft_strdup("SHA256");
			f->alg = SHA256;
		}
		else
			invalid_command(argv[1]);
	}
	i = validate_flags(argv, i, f);
	get_strings_from_files(argv, i, f);
}

void			init_flags(t_flags *f)
{
	f->p = 0;
	f->q = 0;
	f->r = 0;
	f->s = 0;
	f->alg = 0;
	f->str = 0;
	f->alg_str = 0;
	f->filename = 0;
	f->hash = 0;
	f->free_str = 0;
}

int				main(int argc, char **argv)
{
	t_flags	f;

	init_flags(&f);
	populate_dispatch_table(f.dispatch);
	check_args(argc, argv, &f);
	return (0);
}
