/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 20:32:35 by yamohamm          #+#    #+#             */
/*   Updated: 2026/03/15 20:37:12 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	free_scene(t_scene *scene)
{
	t_object	*obj;
	t_object	*tmp_obj;

	obj = scene->objects;
	while (obj)
	{
		tmp_obj = obj->next;
		free(obj);
		obj = tmp_obj;
	}
	if (scene->lights)
		free(scene->lights);
}

void	error_exit_parse(t_scene *scene, char **tokens, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (tokens)
		free_tokens(tokens);
	if (scene)
		free_scene(scene);
	exit(1);
}
