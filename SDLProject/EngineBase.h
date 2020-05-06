#pragma once
#include <SDL.h>

#include "Color.h"

class EngineBase
{
private:
	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnShutdown() = 0;

public:
	void Run()
	{
		Init();

		SDL_Event evnt;
		for (;;)
		{
			while (SDL_PollEvent(&evnt) != 0)
			{
				if (evnt.type == SDL_QUIT) goto SHUTDOWN;
			}
			Update();
			SDL_Delay(1);
		}

		SHUTDOWN:
		Shutdown();
	}

private:
	void Init(const unsigned width = 300, const unsigned height = 300, const char* title = "My app")
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		window_ = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			width, height, SDL_WINDOW_SHOWN);
		surface_ = SDL_GetWindowSurface(window_);
		renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

		SDL_SetRenderDrawColor(renderer_, BLACK.r, BLACK.g, BLACK.b, BLACK.a);

		OnInit();
	}

	void Update()
	{
		SDL_RenderClear(renderer_);

		OnUpdate();

		SDL_RenderPresent(renderer_);
	}

	void Shutdown()
	{
		OnShutdown();

		SDL_FreeSurface(surface_);
		SDL_DestroyRenderer(renderer_);
		SDL_DestroyWindow(window_);
		SDL_Quit();
	}

protected:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	SDL_Surface* surface_ = nullptr;
};
