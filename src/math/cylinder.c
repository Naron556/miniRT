/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arkadiusz <arkadiusz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:44:34 by arkadiusz         #+#    #+#             */
/*   Updated: 2026/03/05 15:45:10 by arkadiusz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_quad_eq	cy_quad(t_ray ray, t_object cy)
{
	t_quad_eq	eq;
	t_vec3		cp;

	cp = vec_sub(ray.pnt, cy.center);
	eq.t1 = -1.0;
	eq.t2 = -1.0;
	eq.a = vec_dot(ray.dir, ray.dir) - pow(vec_dot(ray.dir, cy.shape.cy.axis),
			2.0);
	eq.b = 2.0 * (vec_dot(ray.dir, cp) - vec_dot(ray.dir, cy.shape.cy.axis)
			* vec_dot(cp, cy.shape.cy.axis));
	eq.c = vec_dot(cp, cp) - pow(vec_dot(cp, cy.shape.cy.axis), 2.0)
		- pow(cy.shape.cy.radius, 2.0);
	eq.delta = pow(eq.b, 2) - (4.0 * (eq.a * eq.c));
	if (eq.delta == 0.0)
	{
		eq.t1 = -eq.b / (2 * eq.a);
		eq.t2 = eq.t1;
	}
	else if (eq.delta > 0.0)
	{
		eq.t1 = (-eq.b - sqrt(eq.delta)) / (2 * eq.a);
		eq.t2 = (-eq.b + sqrt(eq.delta)) / (2 * eq.a);
	}
	return (eq);
}

int	t_in_height(t_ray ray, t_object cy, double t)
{
	t_vec3	hp;
	double	dist;

	if (t <= 0.0001)
		return (0);
	hp = vec_add(ray.pnt, vec_scale(ray.dir, t));
	dist = vec_dot(cy.shape.cy.axis, vec_sub(hp, cy.center));
	if (dist >= -(cy.shape.cy.height / 2.0) && dist <= (cy.shape.cy.height
			/ 2.0))
		return (1);
	return (0);
}

t_quad_eq	cy_intsec(t_ray ray, t_object cy)
{
	t_quad_eq	eq;

	eq = cy_quad(ray, cy);
	if (eq.delta < 0.0)
		return (eq);
	if (!t_in_height(ray, cy, eq.t1))
		eq.t1 = -1.0;
	if (!t_in_height(ray, cy, eq.t2))
		eq.t2 = -1.0;
	return (eq);
}
