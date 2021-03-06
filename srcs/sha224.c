/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:59:08 by vdarmaya          #+#    #+#             */
/*   Updated: 2018/07/23 17:07:53 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*get_sha224_hash(unsigned int *h)
{
	unsigned char	buff_hex[7][8];
	char			*out;
	int				i;
	int				j;
	int				l;

	i = -1;
	while (++i < 7)
	{
		ft_memset(buff_hex[i], '0', 8);
		get_hex(buff_hex[i], h[i], 0);
		strrev(buff_hex[i], 8);
	}
	if (!(out = (char*)malloc(57)))
		ft_exiterror("Malloc failed.", 1);
	i = -1;
	j = -1;
	while (++i < 56)
	{
		if (!(i % 8) && (++j + 1))
			l = -1;
		out[i] = buff_hex[j][++l];
	}
	out[i] = '\0';
	return (out);
}

char		*sha224(unsigned char *msg, unsigned long size)
{
	unsigned int	msg_len;
	unsigned int	offset;
	char			*out;
	t_sha256		*s;

	if (!(s = (t_sha256*)malloc(sizeof(struct s_sha256))))
		ft_exiterror("Malloc failed.", 1);
	init_sha2_output(s, SHA224);
	msg_len = fill_message_sha256(&msg, size);
	offset = 0;
	while (offset < msg_len)
	{
		main_loop_sha256(s, (void*)msg + offset);
		add_to_h(s);
		offset += 64;
	}
	out = get_sha224_hash(s->out);
	free(s);
	free(msg);
	return (out);
}
