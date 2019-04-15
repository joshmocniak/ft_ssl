/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmocniak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 03:04:07 by jmocniak          #+#    #+#             */
/*   Updated: 2019/04/04 12:45:21 by jmocniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		out(unsigned char *dst, t_u32 src)
{
	dst[0] = (unsigned char)src;
	dst[1] = (unsigned char)(src >> 8);
	dst[2] = (unsigned char)(src >> 16);
	dst[3] = (unsigned char)(src >> 24);
}
