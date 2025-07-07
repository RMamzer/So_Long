/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:39:55 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/07 15:21:31 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define SIZE 64

# include "MLX42/MLX42.h"
# include <stdbool.h>
# include "libft.h"
# include <fcntl.h>

typedef struct s_img
{
	mlx_image_t		*background;
	mlx_image_t		*player;
	mlx_texture_t	*player_t;
	mlx_image_t		*collectible;
	mlx_image_t		*wall;
	mlx_image_t		*exit;
}	t_img;

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
	bool	exit_found;
	mlx_t	*mlx;
	t_img	*img;
	int		steps;
}	t_game;

//main
int		main(int argc, char **argv);
void	init_empty_game_and_img(t_game *game);
void	get_images(t_img *img, t_game *game);
void	parse_map(t_game *game, char **argv);

//check_map
void	check_extension(char *file_name);
void	check_empty_lines(t_game *game);
void	check_map_objects(t_game *game);
void	check_map_shape(t_game *game);
void	check_walls(t_game	*game);

//check_map.2
char	*so_strjoin(char *s1, char *s2);
char	*get_map_str(char *file_name, t_game *game);
void	find_objects(t_game *game);
void	flood_fill(t_game *copy, size_t x, size_t y);
void	check_route(t_game *game);

//exit_functions
void	free_map(char **map);
void	free_img(t_game *game, t_img *img);
void	free_and_exit(t_game *game);
void	error_exit(char *msg, t_game *game);
void	success_exit(char *msg, t_game *game);

//get_visuals
void	get_background(t_img *img, t_game *game);
void	get_player(t_img *img, t_game *game);
void	get_collectible(t_img *img, t_game *game);
void	get_wall(t_img *img, t_game *game);
void	get_exit(t_img *img, t_game *game);

//move_functions
void	conduct_move(t_game	*game, char c);
void	move_hook(mlx_key_data_t keydata, void *param);
void	update_map(t_game *game, char **map);

//render_visuals
void	render_map(t_game *game);
void	place_object(t_game *game, size_t x, size_t y);
void	pickup_collectible(t_game *game, char **map, mlx_image_t *coll);
void	move_player_image(t_game *game, t_img *img, size_t x, size_t y);
#endif
