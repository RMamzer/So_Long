/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:50:43 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/01 14:00:30 by rmamzer          ###   ########.fr       */
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
			error_exit("Malloc function misfunction", game);
	}
	close(fd);
	if (map_str == NULL)
		error_exit("Empty file", game);
	return (map_str);
}



void	init_game(t_game *game)
{
	game->map_str = NULL;
	game->map = NULL;
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

	init_game(game);
	game->map_str = get_map_str(argv[1], game);
	printf ("%s\n", game->map_str);
	check_empty_lines(game);  //DELETE <---------------------------------------------------------------------------------------------
	check_map_objects(game);
	 game->map = ft_split(game->map_str,'\n');
	 if(!game->map)
	 	error_exit("Malloc misfunction in ft_split", game);
	 check_map_shape(game);
	 check_walls(game);
//	print_args(map); // DELETE <---------------------------------------------------------------------------------------------
	//FOR COMPILATION
	//  mlx_ptr = mlx_init(256,256,"POPIK", false);
	// if (!mlx_ptr)
	// 	return (1);

	//  mlx_loop(mlx_ptr);

	error_exit("DONE", game);
	return (0);
}
