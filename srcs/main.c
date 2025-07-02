/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:50:43 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/02 19:23:14 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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





void	init_empty_game(t_game *game)
{
	game->map_str = NULL;
	game->map = NULL;
	game->collect = 0;
	game->mlx = NULL;
}



void	fill_backgroud(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < 8)
		{
			x = 0;
			while (x < 8)
			{
				mlx_image_to_window(game->mlx, game->img->grass, x * 64, y * 64);
				x++;
			}
		y++;
		}

}
void	init_images(t_img *img, t_game *game)
{
	mlx_texture_t	*grass;
	grass = mlx_load_png("./imgs/check.png");
	img->grass = mlx_texture_to_image(game->mlx, grass);
	mlx_resize_image(img->grass,64,64);
	mlx_delete_texture(grass);
}

int main(int argc, char **argv)
{
	t_game	*game;
	t_img	*img;

	if (argc != 2)
		error_exit("Invalid number of files ༼ ▀̿̿Ĺ̯̿̿▀̿ ༼ ▀̿̿Ĺ̯̿̿▀̿༽▀̿̿Ĺ̯̿̿▀̿ ༽", NULL);
	check_extension(argv[1]);
	game = malloc(sizeof(t_game));
	if (!game)
		error_exit("Malloc misfunction in game struct",NULL);
	init_empty_game(game);
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
	game->mlx = mlx_init(1600, 1600, "GAZMIAS", false);
	if (!(game->mlx))
		error_exit("MLX initialization broke", game);







	img = malloc(sizeof(t_img));
	init_images(img, game);
	game->img = img;
	fill_backgroud(game);




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
