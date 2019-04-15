/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 20:49:09 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/04 21:36:29 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int		set_flag(char c, t_flags *f)
{
	if (c == 'p')
		f->p = 1;
	else if (c == 'q')
		f->q = 1;
	else if (c == 'r')
		f->r = 1;
	else if (c == 's')
		f->s = 1;
	else
		return (0);
	return (1);
}

static int		handle_s(char **str, int i, int j, t_flags *f)
{
	set_flag(str[i][j], f);
	if (str[i][j + 1])
		f->str = &str[i][j + 1];
	else if (str[i + 1])
	{
		f->str = str[i + 1];
		i++;
	}
	else
	{
		ft_putstr(f->alg_str);
		ft_putstr(": option requires an argument -- s\n");
		usage(f);
	}
	f->size = ft_strlen(f->str);
	f->dispatch[f->alg](f);
	f->s = 0;
	return (i);
}

static void		handle_p(t_flags *f)
{
	f->str = read_to_buffer("STDIN", 0, f);
	f->free_str = 1;
	f->dispatch[f->alg](f);
	f->p = 0;
	f->free_str = 0;
}

int				validate_flags(char **str, int i, t_flags *f)
{
	int		j;
	int		p_handled;

	if (!str[i])
		handle_p(f);
	while (str[i] && str[i][0] == '-')
	{
		p_handled = 0;
		j = 1;
		while (str[i][j] && set_flag(str[i][j], f) && str[i][j] != 's')
		{
			if (f->p && (p_handled = 1))
				handle_p(f);
			j++;
		}
		if (f->s)
			i = handle_s(str, i, j, f);
		else if (!p_handled && !str[i][j] && !str[i + 1])
			handle_p(f);
		else if (str[i][j] != '\0')
			illegal_option(str[i][j], f);
		i++;
	}
	return (i);
}
