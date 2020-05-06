#pragma once
#include <cassert>
#include <cmath>

#include "Utility.h"

#ifndef VIEW_RESOLUTION
#define VIEW_RESOLUTION Vec2i{300,300}
#endif

namespace
{
	float Fx_xx(const float x)
	{
		return x * x;
	}
}

class Spring
{
public:
	Spring(Vec2i points[2], float rigidityMult)
	{
		assert(points[0].x >= 0 && points[0].x <= VIEW_RESOLUTION.x &&
				points[0].y >= 0 && points[0].y <= VIEW_RESOLUTION.y &&
				points[1].x >= 0 && points[1].x <= VIEW_RESOLUTION.x &&
				points[1].y >= 0 && points[1].y <= VIEW_RESOLUTION.y &&
				rigidityMult >= 0.0f);

		rigidityFunc_ = Fx_xx;
		points_[0] = points[0];
		points_[1] = points[1];
		rigidityMult_ = rigidityMult;
	}

	static bool IsValid(Spring& s)
	{
		return	s.rigidityFunc_ != nullptr &&
			s.rigidityMult_ > 0.0f &&
			s.points_[0].x >= 0 && s.points_[0].x <= VIEW_RESOLUTION.x &&
			s.points_[0].y >= 0 && s.points_[0].y <= VIEW_RESOLUTION.y &&
			s.points_[1].x >= 0 && s.points_[1].x <= VIEW_RESOLUTION.x &&
			s.points_[1].y >= 0 && s.points_[1].y <= VIEW_RESOLUTION.y;
	}

private:
	float (*rigidityFunc_)(float) = nullptr;
	float rigidityMult_ = 1.0f;
	Vec2i points_[2] = {0};
};

template <size_t Resolution>
class SoftBody
{
public:
	void Update()
	{
		// TODO
	}

	void SetSpring(Spring s, int index)
	{
		assert(index >= 0 && index < Resolution&& Spring::IsValid(s));
		points_[index] = s;
	}

private:
	Spring points_[Resolution];
};
