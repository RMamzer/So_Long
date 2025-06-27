/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:39:55 by rmamzer           #+#    #+#             */
/*   Updated: 2025/06/27 16:51:42 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H


#include "MLX42/MLX42.h"
#include <stdbool.h>
#include "libft.h"
#include <fcntl.h> // open nd close, etc
//DELETE LATER, FOR PRINTF TESTING;
#include <stdio.h>

typedef struct s_game
{
	char *map_str;
	char **map;
} t_game;


int main(int argc, char **argv);
void error_exit (char *msg);
char	*so_strjoin(char *s1, char *s2);
char	*get_map_str(char *file_name);
char	*so_strjoin(char *s1, char *s2);

void check_extension(char *file_name);
bool	check_map_objects(char *map_str);
#endif
