/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   vec_utils.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: eamsalem <eamsalem@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/10 17:38:24 by eamsalem		  #+#	#+#			 */
/*   Updated: 2025/03/13 15:28:10 by eamsalem		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec3	add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	scale(t_vec3 a, double t)
{
	return ((t_vec3){a.x * t, a.y * t, a.z * t});
}

double	dot(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

double	magnitude(t_vec3 a)
{
	return (sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z)));
}
