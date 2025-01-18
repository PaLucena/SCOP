/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:54:59 by palucena          #+#    #+#             */
/*   Updated: 2025/01/18 17:56:46 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <cmath>

std::vector<std::vector<double>>	perspective(double fovy, double aspect, double zNear, double zFar) {
	std::vector<std::vector<double>>	result;

	result[0][0] = 1 / (tan(fovy / 2) * aspect);
	result[1][1] = 1 / tan(fovy / 2);
	result[2][2] = -((zFar + zNear) / (zFar - zNear));
	result[2][3] = -((2 * zFar * zNear) / (zFar - zNear));

	return (result);
}
