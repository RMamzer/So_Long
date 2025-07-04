/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:50:43 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/04 15:18:47 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


	//mlx_put_string(game->mlx, "HELLO WORLD",16,game->height* SIZE - 32); <-- Show string on screen;


// CHECK FUNCTION DELETE LATER
void print_args(char **argv)
{
	int i = 0;
	while (argv[i])
	{
		printf("argv[%d]: |%s|\n", i, argv[i]);
		i++;
	}
	printf("\n\n");
}
// CHECK FUNCTION DELETE LATER
void	print_game_object_data(t_game *game)
{
printf("--- Game Object Data ---\n");
    printf("Player Position: (x=%zu, y=%zu)\n", game->plr_x, game->plr_y);
    printf("Exit Position: (x=%zu, y=%zu)\n", game->exit_x, game->exit_y);
    printf("Total Collectibles: %zu\n", game->collect);
    printf("------------------------\n");
}


char	*so_strjoin(char *s1, char *s2)
{
	char	*joinedstr;
	size_t	str1_l;
	size_t	str2_l;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		str1_l = 0;
	else
		str1_l = ft_strlen(s1);
	str2_l = ft_strlen(s2);
	joinedstr = malloc(str1_l + str2_l + 1);
	if (!joinedstr)
	{
		free (s1);
		free (s2);
		return (NULL);
	}
	ft_memcpy(joinedstr, s1, str1_l);
	ft_memcpy(joinedstr + str1_l, s2, str2_l);
	joinedstr[str1_l + str2_l] = '\0';
	free (s1);
	free (s2);
	return (joinedstr);
}





char	*get_map_str(char *file_name, t_game *game)
{
	int		fd;
	char	*next_line;
	char	*map_str;

	map_str = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_exit("Cannot open the map 🗺️", game);
	while (1)
	{
		next_line = get_next_line(fd);
		if (!next_line)
			break;
		map_str = so_strjoin(map_str, next_line);
		if (!map_str)
		{
			close(fd);
			error_exit("Malloc function misfunction", game);
		}
	}
	close(fd);
	if (map_str == NULL)
		error_exit("Empty file", game);
	return (map_str);
}


void	init_empty_game_and_img(t_game *game)
{
	t_img	*img;

	game->map_str = NULL;
	game->map = NULL;
	game->collect = 0;
	game->mlx = NULL;
	img = malloc(sizeof(t_img));
	if (!img)
		error_exit("Malloc misfunction in game struct",game);
	game->img = img;
	img->background = NULL;
	img->collectible = NULL;
	img->exit = NULL;
	img->player = NULL;
	img->wall = NULL;

}

void	place_object(t_game *game, size_t x, size_t y)
{
	int32_t check;

	check = 0;
	if (game->map[y][x] == 'P')
		check = mlx_image_to_window(game->mlx, game->img->player, x * SIZE, y * SIZE);
	else if (game->map[y][x] == 'C')
		check = mlx_image_to_window(game->mlx, game->img->collectible, x * SIZE + SIZE / 4, y * SIZE + SIZE / 3);
	else if (game->map[y][x] == '1')
		check = mlx_image_to_window(game->mlx, game->img->wall, x * SIZE, y * SIZE);
	else if (game->map[y][x] == 'E')
		check = mlx_image_to_window(game->mlx, game->img->exit, x * SIZE, y * SIZE);
	if (check < 0)
		error_exit("Could not place the object", game);
}

void	render_map(t_game *game)
{
	size_t	x;
	size_t	y;
	int32_t	check;

	y = 0;
	while (y < game->height)
		{
			x = 0;
			while (x < game->length)
			{
				check  = 0;
				check = mlx_image_to_window(game->mlx, game->img->background, x * SIZE, y * SIZE);// check return value
				if (check < 0)
					error_exit("Could not fill the background", game);
				place_object(game, x, y);
				x++;
			}
		y++;
		}

}


void	init_background(t_img *img, t_game *game)
{
	mlx_texture_t	*png;
	png = mlx_load_png("./imgs/background.png");
	if (!png)
		error_exit("Error during loading background image", game);
	img->background = mlx_texture_to_image(game->mlx, png);
	mlx_delete_texture(png);
	if (!img->background)
		error_exit("Error during converting background image", game);
	mlx_resize_image(img->background,SIZE,SIZE);
}

void	init_player(t_img *img, t_game *game)
{
	mlx_texture_t	*png;
	png = mlx_load_png("./imgs/player.png");
	if (!png)
		error_exit("Error during loading player image", game);
	img->player = mlx_texture_to_image(game->mlx, png);
	mlx_delete_texture(png);
	if (!img->player)
		error_exit("Error during converting player image", game);
	mlx_resize_image(img->player,SIZE,SIZE);
}


void	init_collectible(t_img *img, t_game *game)
{
	mlx_texture_t	*png;
	png = mlx_load_png("./imgs/collectible.png");
	if (!png)
		error_exit("Error during loading collectible image", game);
	img->collectible = mlx_texture_to_image(game->mlx, png);
	mlx_delete_texture(png);
	if (!img->collectible)
		error_exit("Error during converting collectible image", game);
	mlx_resize_image(img->collectible,SIZE / 2 ,SIZE / 2 );
}



void	init_wall(t_img *img, t_game *game)
{
	mlx_texture_t	*png;
	png = mlx_load_png("./imgs/wall.png");
	if (!png)
		error_exit("Error during loading wall image", game);
	img->wall = mlx_texture_to_image(game->mlx, png);
	mlx_delete_texture(png);
	if (!img->wall)
		error_exit("Error during converting wall image", game);
	mlx_resize_image(img->wall,SIZE, SIZE);
}
void	init_exit(t_img *img, t_game *game)
{
	mlx_texture_t	*png;
	png = mlx_load_png("./imgs/exit.png");
	if (!png)
		error_exit("Error during loading wall./	 image", game);
	img->exit = mlx_texture_to_image(game->mlx, png);
	mlx_delete_texture(png);
	if (!img->wall)
		error_exit("Error during converting wall image", game);
	mlx_resize_image(img->exit,SIZE, SIZE);
}

void	init_images(t_img *img, t_game *game)
{
	init_background(img, game);
	init_player(img, game);
	init_collectible(img,game);
	init_wall(img, game);
	init_exit(img,game);

}


void	update_map(t_game *game, char **map)
{
	if(map[game->plr_y][game->plr_x] == 'C')
	{
		game->img->collectible->instances[1].enabled = false;
		map[game->plr_y][game->plr_x] = '0';
	}
}


void	conduct_move(t_game	*game, char **map, char c)
{
	if (c == 'w' && map[game->plr_y - 1][game->plr_x] != '1')
	{
		game->plr_y--;
		game->img->player->instances->y -= SIZE;
	}
	update_map(game, game->map);
}

/**
 * Key function callback data.
 * Data related to the mlx_key_hook function
 * 
 * @param key The key that was pressed.
 * @param action The action that was done with the key.
 * @param os_key The os_key is unique for every key, and will have a 
 * different value/keycode depending on the platform. 
 * They may be consistent on different platforms.
 * @param modifier The modifier key that was pressed, 0 if none.
 */
// typedef struct mlx_key_data
// {
// 	keys_t		key;
// 	action_t	action;
// 	int32_t		os_key;
// 	modifier_key_t	modifier;
// }	mlx_key_data_t;


 void	move_hook(mlx_key_data_t keydata, void *param)
 {
	t_game *game;

	game = param;
	// ADD EXIT

	if (mlx_is_key_down(game->mlx, MLX_KEY_UP) && keydata.action == MLX_PRESS)
		conduct_move(game, game->map, 'w');
	// else if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN) && keydata.action == MLX_PRESS)
	// 	conduct_move();
	// else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) && keydata.action == MLX_PRESS)
	// 	conduct_move();
	// if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) && keydata.action == MLX_PRESS)
	// 	conduct_move();
	
 }

 



/*
- Do max and min tiles limit
- Do resizing
*/
int main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		error_exit("Invalid number of files ༼ ▀̿̿Ĺ̯̿̿▀̿ ༼ ▀̿̿Ĺ̯̿̿▀̿༽▀̿̿Ĺ̯̿̿▀̿ ༽", NULL);
	check_extension(argv[1]);
	game = malloc(sizeof(t_game));
	if (!game)
		error_exit("Malloc misfunction in game struct",NULL);
	init_empty_game_and_img(game);
	game->map_str = get_map_str(argv[1], game);
	printf ("%s\n", game->map_str);//DELETE <---------------------------------------------------------------------------------------------
	check_map_objects(game);
	check_empty_lines(game);
	game->map = ft_split(game->map_str,'\n');
	if(!game->map)
		error_exit("Malloc misfunction in ft_split", game);
	check_map_shape(game);
	check_walls(game);
	check_route(game);
	game->mlx = mlx_init(SIZE * (game->length), SIZE * (game->height), "GAZMIAS", true);//width-height
	if (!(game->mlx))
		error_exit("MLX initialization broke", game);



	init_images(game->img, game);
	render_map(game);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);

	
	mlx_key_hook(game->mlx, move_hook, game);

	mlx_loop(game->mlx);
//	print_args(map); // DELETE <---------------------------------------------------------------------------------------------
	//FOR COMPILATION
	//  mlx_ptr = mlx_init(256,256,"POPIK", false);
	// if (!mlx_ptr)
	// 	return (1);

	//  mlx_loop(mlx_ptr);

	error_exit("DONE", game);
	return (0);
}
