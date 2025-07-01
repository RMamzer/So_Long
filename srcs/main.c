/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:50:43 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/01 19:59:47 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// CHECK FUNCTION DELE
void print_args(char **argv)
{
	int i = 0;
	while (argv[i])
	{
		printf("argv[%d]: |%s|\n", i, argv[i]);
		i++;
	}
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
}
void	init_game(t_game *game)
{
	find_objects (game);
}


void	find_objects(t_game *game)
{
	size_t x;
	size_t y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while(game->map[y][x])
		{
			if (game->map[y][x] == 'P' )
			{
				game->plr_x = x;
				game->plr_y = y;
			}
			else if (game->map[y][x] == 'E' )
			{
				game->exit_x = x;
				game->exit_y = y;
			}
			else if (game->map[y][x]== "C")
				game->collect++;
			x++;
		}
		y++;
	}
}
void	flood_fill(t_game *copy, size_t plr_x, size_t plr_y)
{

}


void	check_route(t_game *game)
{
	t_game	copy;

	copy.map = ft_split(game->map_str,'\n');
	if (!copy.map)
		error_exit("ft_slit malloc broke during map  copying", game);
	copy.height = game->height;
	copy.length = game->length;
	copy.collect= game->collect;
	copy.plr_x = game->plr_x;
	copy.plr_y = game->plr_y;
	copy.exit_found = false;

	flood_fill(&copy, copy.plr_x, copy.plr_y);
}

int main(int argc, char **argv)
{
	// mlx_t	*mlx_ptr;
	t_game	*game;

	if (argc != 2)
		error_exit("Invalid number of files ༼ ▀̿̿Ĺ̯̿̿▀̿ ༼ ▀̿̿Ĺ̯̿̿▀̿༽▀̿̿Ĺ̯̿̿▀̿ ༽", NULL);
	check_extension(argv[1]);
	game = malloc(sizeof(t_game));
	if (!game)
		error_exit("Malloc misfunction in game struct",NULL);
	init_empty_game(game);
	game->map_str = get_map_str(argv[1], game);
	printf ("%s\n", game->map_str);
	check_empty_lines(game);  //DELETE <---------------------------------------------------------------------------------------------
	check_map_objects(game);
	game->map = ft_split(game->map_str,'\n');
	if(!game->map)
		error_exit("Malloc misfunction in ft_split", game);
	check_map_shape(game);
	check_walls(game);
	check_route(game);
//	print_args(map); // DELETE <---------------------------------------------------------------------------------------------
	//FOR COMPILATION
	//  mlx_ptr = mlx_init(256,256,"POPIK", false);
	// if (!mlx_ptr)
	// 	return (1);

	//  mlx_loop(mlx_ptr);

	error_exit("DONE", game);
	return (0);
}
