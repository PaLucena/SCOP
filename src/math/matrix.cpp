/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:55:03 by palucena          #+#    #+#             */
/*   Updated: 2025/01/18 19:48:22 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <aio.h>

std::vector<std::vector<double>>	multiplyMatrix(std::vector<std::vector<double>> m1, std::vector<std::vector<double>> m2) {
	std::vector<std::vector<double>>	result;

	for (size_t i = 0; i < m1.size() && i < m2.size(); i++) {
		for (size_t j = 0; j < m1[i].size() && j < m2[i].size(); j++)
			result[i][j] = m1[i][j] * m2[i][j];
	}
	return (result);
}
