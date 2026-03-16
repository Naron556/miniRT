#include "../../inc/miniRT.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

int	count_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return (0);
	while (tokens[i])
		i++;
	return (i);
}

double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	double	fraction;

	result = 0.0;
	sign = 1.0;
	fraction = 1.0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1.0;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			result = result * 10.0 + (*str++ - '0');
			fraction *= 10.0;
		}
	}
	return (sign * (result / fraction));
}

t_vec3	parse_vec3(char *str, t_scene *scene, char **tokens)
{
	t_vec3	vec;
	char	**parts;

	parts = ft_split(str, ',');
	if (count_tokens(parts) != 3)
	{
		free_tokens(parts);
		error_exit_parse(scene, tokens, "Invalid vector format");
	}
	vec.e[0] = ft_atof(parts[0]);
	vec.e[1] = ft_atof(parts[1]);
	vec.e[2] = ft_atof(parts[2]);
	free_tokens(parts);
	return (vec);
}

t_vec3	parse_color(char *str, t_scene *scene, char **tokens)
{
	t_vec3	color;

	color = parse_vec3(str, scene, tokens);
	if (color.e[0] < 0 || color.e[0] > 255 || color.e[1] < 0 || color.e[1] > 255
		|| color.e[2] < 0 || color.e[2] > 255)
		error_exit_parse(scene, tokens, "Color out of range (0-255)");
	return (color);
}
