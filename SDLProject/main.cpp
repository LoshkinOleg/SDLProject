#pragma once
#include <cassert>

#include "EngineBase.h"
#include "Utility.h"

#ifdef main // Remove SDL's main.
#undef main
#endif
#ifndef VIEW_RESOLUTION
#define VIEW_RESOLUTION Vec2i{300, 300};
#endif // !VIEW_RESOLUTION

struct Triangle
{
public:
	inline Triangle(	const float ax, const float ay, const float az,
						const float bx, const float by, const float bz,
						const float cx, const float cy, const float cz)
	{
		points_[0].x = ax;
		points_[0].y = ay;
		points_[0].z = az;
		points_[1].x = bx;
		points_[1].y = by;
		points_[1].z = bz;
		points_[2].x = cx;
		points_[2].y = cy;
		points_[2].z = cz;
	}
private:
	Vec3f points_[3] = {0}; // Defined in trigonometric order.
};

template <const size_t Resolution>
class Shape3D
{
private:
	Triangle triangles_[Resolution] = { 0 };
};

Triangle obj = { 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 1.0f, 2.0f };

class Camera // 80 bytes
{
public:
	inline float GetResolution()
	{
		return float(height_) / float(width_);
	}

private:
	unsigned width_ = 0;
	unsigned height_ = 0;
	unsigned front_ = 0;
	unsigned back_ = 0;
	Mat4f transform_ = Mat4f::One(); // 64 bytes
};

bool RayTriangleIntersection(const Vec3f origin, const Vec3f direction, const Triangle tri)
{

}

class Engine final : public EngineBase
{
private:
	void DrawPixel(int x, int y, Color c)
	{
		assert(x >= 0 && y >= 0 && x <= surface_->w && y <= surface_->h);
		SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
		SDL_RenderDrawPoint(renderer_, x, y);
	}
	void DrawLine(int x0, int y0, int x1, int y1, Color c)
	{
		assert(x0 >= 0 && y0 >= 0 && x0 <= surface_->w && y0 <= surface_->h && x1 >= 0 && y1 >= 0 && x1 <= surface_->w && y1 <= surface_->h);
		SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
		SDL_RenderDrawLine(renderer_, x0, y0, x1, y1);
	}

	void OnInit() override
	{

	}

	void OnUpdate() override
	{

	}

	void OnShutdown() override
	{

	}
};

int main()
{
	Engine engine{};
	engine.Run();
	return 0;
}
