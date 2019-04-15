/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 23:53:14 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/14 17:35:15 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			modified_strerror(char *filename, t_flags *f)
{
	char	*lower;
	int		i;

	lower = ft_strdup(f->alg_str);
	i = 0;
	while (lower[i])
	{
		lower[i] = ft_tolower(lower[i]);
		i++;
	}
	ft_printf("ft_ssl: %s: %s: %s\n", lower, filename, strerror(errno));
}

static int		open_file(char *filename, t_flags *f)
{
	int fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		modified_strerror(filename, f);
	return (fd);
}

static int		read_string_from_file(char *filename, t_flags *f)
{
	int		fd;

	if ((fd = open_file(filename, f)) == -1)
		return (0);
	if ((f->str = read_to_buffer(filename, fd, f)) == 0)
		return (0);
	close(fd);
	return (1);
}

void			get_strings_from_files(char **argv, int i, t_flags *f)
{
	while (argv[i])
	{
		f->filename = argv[i];
		if (read_string_from_file(f->filename, f))
		{
			f->free_str = 1;
			f->dispatch[f->alg](f);
		}
		i++;
	}
}
