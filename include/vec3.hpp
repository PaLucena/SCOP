/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:20:20 by palucena          #+#    #+#             */
/*   Updated: 2025/01/18 23:58:06 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>
#include <cmath>

void	throwError(const std::string &str);

struct vec3 {
	double	x, y, z;

	// Constructors
	vec3(): x(0), y(0), z(0) {}
	vec3(double val): x(val), y(val), z(val) {}
	vec3(double v1, double v2, double v3): x(v1), y(v2), z(v3) {}

	// Basic operators
	vec3	&operator+(const vec3 &other) const {
		vec3 result(vec3(x + other.x, y + other.y, z + other.z));
		return (result);
	}
	vec3	&operator-(const vec3 &other) const {
		vec3 result(vec3(x - other.x, y - other.y, z - other.z));
		return (result);
	}
	vec3	&operator*(const vec3 &other) const {
		vec3 result(vec3(x * other.x, y * other.y, z * other.z));
		return (result);
	}
	vec3	&operator/(const vec3 &other) const {
		vec3 result(vec3(x / other.x, y / other.y, z / other.z));
		return (result);
	}
	vec3	&operator*(double scalar) const {
		vec3 result(vec3(x * scalar, y * scalar, z * scalar));
		return (result);
	}
	vec3	&operator/(double scalar) const {
		vec3 result(vec3(x / scalar, y / scalar, z / scalar));
		return (result);
	}

	double	&operator[](int index) {
		if (index < 0 || index > 2)
			throwError("Index out of range");
		return (index == 0) ? x : (index == 1) ? y : z;
	}
};
