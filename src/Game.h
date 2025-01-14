#pragma once
#include "structs.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "GameFiles/Pong.h"

class Game
{
public:
	explicit Game( const Window& window );
	Game( const Game& other ) = delete;
	Game& operator=( const Game& other ) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;

	~Game();

	void Run( );

	void Update(float elapsedSec);

	void Draw() const;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
	{

	}
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
	{

	}
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
	{
		
	}
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
	{
		switch (e.button)
		{
		case SDL_BUTTON_LEFT:
		{
			m_Pong.LeftMouseClick(e.x, e.y);
			break;
		}
		case SDL_BUTTON_RIGHT:
		{
			m_Pong.RightMouseClick(e.x, e.y);
			break;
		}
		default: ;
		}
		
	}
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
	{



	}

	const Rectf& GetViewPort() const
	{
		return m_Viewport;
	}

private:
	// DATA MEMBERS
	// The window properties
	const Window m_Window;
	const Rectf m_Viewport;
	// The window we render to
	SDL_Window* m_pWindow;
	// OpenGL context
	SDL_GLContext m_pContext;
	// Init info
	bool m_Initialized;
	// Prevent timing jumps when debugging
	const float m_MaxElapsedSeconds;


	// PROJECT
	Pong m_Pong;
	
	// FUNCTIONS
	void InitializeGameEngine( );
	void CleanupGameEngine( );
};
