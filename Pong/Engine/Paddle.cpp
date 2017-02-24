#include "Paddle.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Game.h"
#include "MainWindow.h"

void Paddle::WallInsideBorder()
{
	if (y + 50 >= Graphics::ScreenHeight)
	{
		y = Graphics::ScreenHeight - 51;
	}
	if (y - 50 < 0)
	{
		y = 51;
	}
	
}

