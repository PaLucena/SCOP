/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:17:53 by palucena          #+#    #+#             */
/*   Updated: 2025/01/18 19:38:05 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// matrix.cpp
std::vector<std::vector<double>>	multiplyMatrix(std::vector<std::vector<double>> m1, std::vector<std::vector<double>> m2);

// vector.cpp
std::vector<double> operator+(const std::vector<double>& a, const std::vector<double>& b);
std::vector<double> operator-(const std::vector<double>& a, const std::vector<double>& b);
std::vector<double> operator*(const std::vector<double>& a, const std::vector<double>& b);
std::vector<double> operator*(const std::vector<double>& v, const double& n);
std::vector<double> operator/(const std::vector<double>& a, const std::vector<double>& b);
std::vector<double> operator/(const std::vector<double>& v, const double n);
std::vector<double>	crossProduct(std::vector<double> v1, std::vector<double> v2);
std::vector<double>	fabs(std::vector<double> v);

// perspective.cpp
std::vector<std::vector<double>>	perspective(double fovy, double aspect, double zNear, double zFar);

// radians.cpp
double	toRadians(double degrees);

// lookAt.cpp
std::vector<std::vector<double>>	lookAt(std::vector<double> position, std::vector<double> center, std::vector<double> up);
