#pragma once
#include <cmath>
#include <math.h>

namespace kiko
{
	constexpr float pi = 3.1415926535f;
	constexpr float twoPi = 6.283185307f;
	constexpr float halfPi = 1.57079632675f;

	constexpr float RadiansToDeg(float radians) { return radians * (180.0f / pi); }
	constexpr float DegreesToRad(float degrees) { return degrees * (pi / 180.0f); }

	constexpr int Wrap(int value, int max)
	{
		return (value % max) + ((value < 0) ? max : 0);
	}
	
	inline float Wrap(float value, float max)
	{
		return std::fmod(value , max) + ((value < 0) ? max : 0);
	}

	template <typename T>
	inline T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}
	template <typename T>
	inline T Max(T a, T b)
	{
		return (a < b) ? b : a;
	}

	template <typename T>
	inline T Clamp(T value, T min, T max)
	{
		if (min > max) std::swap(min, max);

		if (value < min) value = min;
		else if (value > max) value = max;

		return (value < min) ? min : (value > max) ? max : value;
	}

	template<typename T>
	constexpr T Lerp(const T& a, const T& b, float t)
	{
		return (a * (1.0f - t)) + (b * t);
	}
} 