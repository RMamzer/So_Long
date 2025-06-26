/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:13:20 by rmamzer           #+#    #+#             */
/*   Updated: 2025/06/26 15:56:42 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void check_extension(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	if (len <=4 || ft_strncmp(file_name + len - 4, ".ber", 4)!= 0)
		error_exit("Only .bers ʕ•ᴥ•ʔ can pass");

}
