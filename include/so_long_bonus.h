/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:39:55 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/10 18:30:48 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# define SIZE 64

# include "MLX42/MLX42.h"
# include <stdbool.h>
# include "libft.h"
# include <fcntl.h>

typedef struct s_img
{
	mlx_image_t		*background;
	mlx_image_t		*player_right;
	mlx_image_t		*player_left;
	mlx_texture_t	*player_t_r;
	mlx_texture_t	*player_t_l;
	mlx_image_t		*collectible;
	mlx_image_t		*wall;
	mlx_image_t		*exit;
	mlx_image_t		*exit_closed;
	mlx_image_t		*enemy[3];
	mlx_image_t		*text_str;
	mlx_image_t		*text_num;
	mlx_image_t		*pickup_right;
	mlx_texture_t	*pickup_t_right;
	mlx_image_t		*pickup_left;
	mlx_texture_t	*pickup_t_left;
	char			direction;
	bool			pickup_needed;
	double			last_enemy_time;
	int				enemy_frame;
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
void	init_bonus(t_img *img);
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
void	create_player_direction(t_game *game, t_img *img, size_t x, size_t y);
void	move_player_image(t_game *game, t_img *img);
void	conduct_move(t_game	*game, char c);
void	move_hook(mlx_key_data_t keydata, void *param);
void	update_map(t_game *game, char **map);

//render_visuals
void	render_map(t_game *game);
void	place_object(t_game *game, size_t x, size_t y);
void	pickup_collectible(t_game *game, char **map, mlx_image_t *coll);
void	update_exit(t_game *game, t_img *img, size_t x, size_t y);

//new_enemy
void	get_enemy(t_img *img, t_game *game);
void	enemy_hook(void *temp);
void	place_enemies(t_game *game, t_img *img, size_t x, size_t y);
void	create_pickup_image(t_game *game, t_img *img, size_t x, size_t y);

//new_visual_utilities
void	get_pickup(t_img *img, t_game *game);
void	display_moves_text(t_game *game);
void	display_moves_num(t_game *game);
void	free_bonus_img(t_game *game, t_img *img);
#endif
