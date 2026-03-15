/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:32:09 by yamohamm          #+#    #+#             */
/*   Updated: 2026/03/15 20:32:09 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static void	replace_whitespace_with_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\n' || line[i] == '\r'
			|| line[i] == '\v')
			line[i] = ' ';
		i++;
	}
}

static void	dispatch_object(t_scene *scene, char **tokens)
{
	if (ft_strncmp(tokens[0], "A", 2) == 0)
		parse_ambient(scene, tokens);
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
		parse_camera(scene, tokens);
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
		parse_light(scene, tokens);
	else if (ft_strncmp(tokens[0], "sp", 3) == 0)
		parse_sphere(scene, tokens);
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
		parse_plane(scene, tokens);
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
		parse_cylinder(scene, tokens);
	else
		error_exit_parse(scene, tokens, "Unknown identifier in file");
}

void	parse_line(t_scene *scene, char *line)
{
	char	**tokens;

	replace_whitespace_with_space(line);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || tokens[0][0] == '#')
	{
		free_tokens(tokens);
		return ;
	}
	dispatch_object(scene, tokens);
	free_tokens(tokens);
}

void	init_scene(t_scene *scene)
{
	scene->amb_count = 0;
	scene->light_count = 0;
	scene->lights = NULL;
	scene->objects = NULL;
}

void	parse_file(t_data *data, char *filename)
{
	int		fd;
	char	*line;
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strncmp(ext, ".rt", 4) != 0)
	{
		printf("Error\nFile must be a .rt file\n");
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("%s", ERR_FILE);
		exit(1);
	}
	init_scene(&data->scene);
	line = get_next_line(fd);
	while (line != NULL)
	{
		parse_line(&data->scene, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
