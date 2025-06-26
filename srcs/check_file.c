/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:13:20 by rmamzer           #+#    #+#             */
/*   Updated: 2025/06/26 12:33:27 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool check_extension(char *file_name)
{
	int len;

	len = ft_strlen(file_name);

	if (len <=4 || ft_strncmp(file_name + len - 4, ".ber", 4)!= 0)
	{
		write (1, "false\n", 6);
		return (false);
	}
	write (1, "true\n", 5);
	return (true);
}
