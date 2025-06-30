/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:50:43 by rmamzer           #+#    #+#             */
/*   Updated: 2025/06/30 13:05:21 by rmamzer          ###   ########.fr       */
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

 void	free_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}
void error_exit(char *msg, t_game *game)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);

	if (game != NULL)
	{
		if (game->map_str != NULL)
			free (game->map_str);
		if (game->map != NULL);
			free_map (game->map);
	}
	exit (1);
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

char	*get_map_str(char *file_name)
{
	int		fd;
	char	*next_line;
	char	*map_str;

	map_str = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_exit("Cannot open the map 🗺️", NULL);
	while (1)
	{
		next_line = get_next_line(fd);
		if (!next_line)
			break;
		map_str = so_strjoin(map_str, next_line);
		if (!map_str)
			error_exit("Malloc function misfunction", NULL);
	}
	close(fd);
	if (map_str == NULL)
		error_exit("Empty file", NULL);
	return (map_str);
}


bool	check_map_shape(char **map)
{
	int length;
	int height;

	length = ft_strlen(map[0]);
	
	height = 0;
	while(map[height] != NULL)
	{
		if (length != ft_strlen(map[height]))
			return (false);
		height ++;
	}
}
	/*
	- calculate strlen of first (length)
	- move between str and compare their length with first  line. if not same -> exit
	- increment width
	- --> not necessary, previous checks mitigate it width and lengh more that 3 and 5 (one of the  ways ) 
	*/

void	init_game(t_game *game)
{
	game->map_str = NULL;
	game->map = NULL;
}


int main(int argc, char **argv)
{
	// mlx_t	*mlx_ptr;
	t_game	*game;
	char	*map_str;
	char 	**map;
	if (argc != 2)
		error_exit("Invalid number of files ༼ ▀̿̿Ĺ̯̿̿▀̿ ༼ ▀̿̿Ĺ̯̿̿▀̿༽▀̿̿Ĺ̯̿̿▀̿ ༽", NULL);
	check_extension(argv[1]);
	init_game(game);
	game->map_str = get_map_str(argv[1]);
	printf ("%s\n", map_str);  //DELETE <---------------------------------------------------------------------------------------------
	if (!check_map_objects(map_str))
			error_exit("Invalid map objects", game);
	 map = ft_split(map_str,'\n');
	 if(!map)
	 	error_exit("Malloc misfunction in ft_split", game);
	 check_map_shape(map);
//	print_args(map); // DELETE <---------------------------------------------------------------------------------------------
	// check_shape_and_walls(map);
	//FOR COMPILATION
	//  mlx_ptr = mlx_init(256,256,"POPIK", false);
	// if (!mlx_ptr)
	// 	return (1);

	//  mlx_loop(mlx_ptr);

	return (0);
}
