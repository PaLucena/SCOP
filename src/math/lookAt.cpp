/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookAt.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:37:30 by palucena          #+#    #+#             */
/*   Updated: 2025/01/18 19:45:44 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <cmath>

std::vector<double> operator-(const std::vector<double>& a, const std::vector<double>& b);
std::vector<double> operator/(const std::vector<double>& a, const std::vector<double>& b);
std::vector<double>	crossProduct(std::vector<double> v1, std::vector<double> v2);
std::vector<double>	fabs(std::vector<double> v);

std::vector<std::vector<double>>	lookAt(std::vector<double> position, std::vector<double> center, std::vector<double> up) {
	std::vector<std::vector<double>>	result;
	std::vector<double>					forward;
	std::vector<double>					right;

	forward = (center - position) / fabs(center - position);
	right = crossProduct(up, forward) / fabs(crossProduct(up, forward));
	result[0][0] = right[0];
	result[1][0] = right[1];
	result[2][0] = right[2];
	result[0][1] = up[0];
	result[1][1] = up[1];
	result[2][1] = up[2];
	result[0][2] = forward[0];
	result[1][2] = forward[1];
	result[2][2] = forward[2];
	result[0][3] = position[0];
	result[1][3] = position[1];
	result[2][3] = position[2];
	result[3][3] = 1;

	return (result);
}