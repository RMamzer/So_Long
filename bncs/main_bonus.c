/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:50:43 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/10 15:15:47 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	init_empty_game_and_img(t_game *game)
{
	t_img	*img;

	game->map_str = NULL;
	game->map = NULL;
	game->collect = 0;
	game->steps = 0;
	game->mlx = NULL;
	img = malloc(sizeof(t_img));
	if (!img)
		error_exit("Malloc misfunction in image struct", game);
	game->img = img;
	img->background = NULL;
	img->collectible = NULL;
	img->exit = NULL;
	img->player_left = NULL;
	img->player_right = NULL;
	img->player_t_l = NULL;
	img->player_t_r = NULL;
	img->wall = NULL;
	init_bonus(img);
}

void	init_bonus(t_img *img)
{
	img->enemy[0] = NULL;
	img->enemy[1] = NULL;
	img->enemy[2] = NULL;
	img->text_str = NULL;
	img->text_num = NULL;
	img->direction = 'd';
	img->pickup_right = NULL;
	img->pickup_left = NULL;
	img->pickup_t_right = NULL;
	img->pickup_t_left = NULL;
	img->pickup_needed = false;
	img->exit_closed = NULL;
	img->last_enemy_time = 0;
	img->enemy_frame = 0;
}

void	get_images(t_img *img, t_game *game)
{
	get_background(img, game);
	get_player(img, game);
	get_collectible(img, game);
	get_wall(img, game);
	get_exit(img, game);
	get_enemy(img, game);
	get_pickup(img, game);
}

void	parse_map(t_game *game, char **argv)
{
	game->map_str = get_map_str(argv[1], game);
	check_map_objects(game);
	check_empty_lines(game);
	game->map = ft_split(game->map_str, '\n');
	if (!game->map)
		error_exit("Malloc misfunction in ft_split", game);
	check_map_shape(game);
	check_walls(game);
	check_route(game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		error_exit("Invalid number of files", NULL);
	check_extension(argv[1]);
	game = malloc(sizeof(t_game));
	if (!game)
		error_exit("Malloc misfunction in game struct", NULL);
	init_empty_game_and_img(game);
	parse_map(game, argv);
	game->mlx = mlx_init(SIZE * (game->length),
			SIZE * (game->height + 1), "SO_LONG", true);
	if (!(game->mlx))
		error_exit("MLX initialization broke", game);
	get_images(game->img, game);
	render_map(game);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_key_hook(game->mlx, move_hook, game);
	mlx_loop_hook(game->mlx, enemy_hook, game);
	mlx_loop(game->mlx);
	success_exit(NULL, game);
}
