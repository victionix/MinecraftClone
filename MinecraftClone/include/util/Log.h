#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <glm/glm.hpp>


namespace glm {
	template<typename T, length_t N>
	std::ostream& operator<<(std::ostream& os, vec<N, T> const& v) {
		os << "vec" << N << " : ";
		for (length_t i = 0; i < N - 1; i++)
			os << v[i] << ", ";
		os << v[N - 1];
		return os;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, tmat4x4<T> const& mat) {
		os << "mat: ";
		for (length_t i = 0; i < 4; i += 1) {
			os << mat[i] << std::endl << "     ";
		}
		return os;
	}
}

namespace util {	
	template<typename T>
	void Log(const T& data, const std::string message)
	{
		std::cout << message << " " << data << "\n";
	}
	
	template<typename T, std::size_t N>
	void Log(const std::array<T, N>& data, const std::string message)
	{
		std::cout << message << " ";
		for (auto& x : data)
		{
			std::cout << x << " ";
		}
		std::cout << "\n";
	
	}

	
	template<typename T, std::size_t N>
	void Log(const std::vector<T>& data, const std::string message)
	{
		std::cout << message << " ";
		for (auto& x : data)
		{
			std::cout << x << " ";
		}
		std::cout << "\n";
	
	}

	void Log(const std::string message);
};


#endif