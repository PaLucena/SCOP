/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 23:00:18 by palucena          #+#    #+#             */
/*   Updated: 2025/01/18 23:58:27 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>
#include <cmath>

void	throwError(const std::string &str);

struct vec2 {
	double	x, y, z;

	// Constructors
	vec2(): x(0), y(0), z(0) {}
	vec2(double val): x(val), y(val), z(val) {}
	vec2(double v1, double v2, double v3): x(v1), y(v2), z(v3) {}

	// Basic operators
	vec2	&operator+(const vec2 &other) const {
		vec2 result(vec2(x + other.x, y + other.y, z + other.z));
		return (result);
	}
	vec2	&operator-(const vec2 &other) const {
		vec2 result(vec2(x - other.x, y - other.y, z - other.z));
		return (result);
	}
	vec2	&operator*(const vec2 &other) const {
		vec2 result(vec2(x * other.x, y * other.y, z * other.z));
		return (result);
	}
	vec2	&operator/(const vec2 &other) const {
		vec2 result(vec2(x / other.x, y / other.y, z / other.z));
		return (result);
	}
	vec2	&operator*(double scalar) const {
		vec2 result(vec2(x * scalar, y * scalar, z * scalar));
		return (result);
	}
	vec2	&operator/(double scalar) const {
		vec2 result(vec2(x / scalar, y / scalar, z / scalar));
		return (result);
	}

	double	&operator[](int index) {
		if (index < 0 || index > 1)
			throwError("Index out of range");
		return (index == 0) ? x : (index == 1) ? y : z;
	}
};
