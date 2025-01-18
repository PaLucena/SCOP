/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:19:37 by palucena          #+#    #+#             */
/*   Updated: 2025/01/18 19:47:14 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <cmath>
#include <string>

void	throwError(const std::string &str);

std::vector<double> operator+(const std::vector<double>& a, const std::vector<double>& b) {
	if (a.size() != b.size())
		throwError("Vectors must have same size");

	std::vector<double> result(a.size());
	for (size_t i = 0; i < a.size(); ++i)
		result[i] = a[i] + b[i];
	return result;
}

std::vector<double> operator-(const std::vector<double>& a, const std::vector<double>& b) {
	if (a.size() != b.size())
		throwError("Vectors must have same size");

	std::vector<double> result(a.size());
	for (size_t i = 0; i < a.size(); ++i)
		result[i] = a[i] - b[i];
	return result;
}

std::vector<double> operator*(const std::vector<double>& a, const std::vector<double>& b) {
	if (a.size() != b.size())
		throwError("Vectors must have same size");

	std::vector<double> result(a.size());
	for (size_t i = 0; i < a.size(); ++i)
		result[i] = a[i] * b[i];
	return result;
}

std::vector<double> operator*(const std::vector<double>& v, const double& n) {
	std::vector<double> result(v.size());
	for (size_t i = 0; i < v.size(); ++i)
		result[i] = v[i] * n;
	return result;
}

std::vector<double> operator/(const std::vector<double>& a, const std::vector<double>& b) {
	if (a.size() != b.size())
		throwError("Vectors must have same size");

	std::vector<double> result(a.size());
	for (size_t i = 0; i < a.size(); ++i)
		result[i] = a[i] / b[i];
	return result;
}

std::vector<double> operator/(const std::vector<double>& v, const double n) {
	std::vector<double> result(v.size());
	for (size_t i = 0; i < v.size(); ++i)
		result[i] = v[i] / n;
	return result;
}

std::vector<double>	crossProduct(std::vector<double> v1, std::vector<double> v2) {
	std::vector<double>	result;

	result[0] = v1[1] * v2[2] - v1[2] * v2[1];
	result[1] = v1[2] * v2[0] - v1[0] * v2[2];
	result[2] = v1[0] * v2[1] - v1[1] * v2[0];

	return (result);
}

std::vector<double>	fabs(std::vector<double> v) {
	std::vector<double> result;

	for (size_t i = 0; i < v.size(); i++)
		result[i] = fabs(v[i]);
	return (result);
}
