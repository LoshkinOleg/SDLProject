#pragma once

struct Vec2i // 64 bits, 8 bytes
{
	int x;
	int y;
};

struct Vec3f // 96 bits, 12 bytes
{
	float x;
	float y;
	float z;
};

struct Mat4f // 512 bits, 64 bytes.
{
	inline static Mat4f One()
	{
		return {	1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f};
	}

	inline static Mat4f RotationMatFrom(float angle, Vec3f axis)
	{
		const float cos = cosf(angle);
		const float sin = sinf(angle);
		const float oneMinusCos = 1 - cos;
		const float xy = axis.x * axis.y;
		const float xz = axis.x * axis.z;
		const float yz = axis.y * axis.z;
		const float xsin = axis.x * sin;
		const float ysin = axis.y * sin;

		return {	cos + axis.x * axis.x * oneMinusCos,	xy*oneMinusCos,							xz*oneMinusCos + ysin,					0.0f,
					xy*oneMinusCos + xsin,					cos + axis.y * axis.y * oneMinusCos,	yz*oneMinusCos - xsin,					0.0f,
					xz*oneMinusCos - ysin,					yz*oneMinusCos + xsin,					cos + axis.z * axis.z * oneMinusCos,	0.0f,
					0.0f,									0.0f,									0.0f,									1.0f };
	}

	float data[4][4];
};

/*
@brief: UNSAFE: Creates a circle on the function's stack and returns ptr to it. Make sure to retrieve the circle immediately after calling this function unless you want the data overwritten.
*/
template <const size_t Resolution>
Vec2i* MakeCircle(const float radius = 1.0f)
{
	Vec2i returnValue[Resolution];
	const float angleIncrement = (M_PI / (double)Resolution) << 1; // << 1 = *2

	float currentAngle = 0.0f;
	for (size_t i = 0; i < Resolution; i++)
	{
		returnValue[i] = Vec2i{ (int)(cosf(currentAngle) * radius), (int)(sinf(currentAngle) * radius) };
		currentAngle += angleIncrement;
	}
	return &returnValue;
}
