/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:39:55 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/04 12:18:53 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define SIZE 64
# define MOVE SIZE/4

#include "MLX42/MLX42.h"
#include <stdbool.h>
#include "libft.h"
#include <fcntl.h> // open nd close, etc
//DELETE LATER, FOR PRINTF TESTING;
#include <stdio.h>

typedef struct s_img
{

mlx_image_t	*background;
mlx_image_t	*player;
mlx_image_t	*collectible;
mlx_image_t	*wall;
mlx_image_t	*exit;
} t_img;


typedef struct s_game
{
	char	*map_str;
	char	**map;

	size_t	length;
	size_t	height;
	size_t	collect;
	size_t	plr_x;
	size_t	plr_y;
	size_t	exit_x;
	size_t	exit_y;
	bool 	exit_found;
	mlx_t	*mlx;
	t_img	*img;
} t_game;



// DELETE LATER <-----------------------
void	print_game_object_data(t_game *game);
void	print_args(char **argv);

//main
int		main(int argc, char **argv);
char	*so_strjoin(char *s1, char *s2);
char	*get_map_str(char *file_name, t_game *game);
void	init_empty_game(t_game *game);

//check_map
void	check_extension(char *file_name);
void	check_empty_lines(t_game *game);
void	check_map_objects(t_game *game);
void	check_map_shape(t_game *game);
void	check_walls(t_game	*game);


//exit_functions
void	free_map(char **map);
void	error_exit(char *msg, t_game *game);


//check_route
void	init_game(t_game *game);
void	find_objects(t_game *game);
void	check_route(t_game *game);
void	flood_fill(t_game *copy, size_t x, size_t y);
#endif
