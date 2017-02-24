/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <time.h>





Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	Left.x = 100;
	Right.x = 700;
}
///Calls the game functions
void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}
///Calls to update the model
void Game::UpdateModel()
{
		
		///Moves player paddles
		MovePaddle();
		///Checks if player paddles are inside the given parameters.
		Left.WallInsideBorder();
		Right.WallInsideBorder();
		///Reactions of Pongball
		PongBallPhysics();
		IsGoal();
	
}
///Composes frame
void Game::ComposeFrame()
{
	
	
		DrawBall(Pong.x, Pong.y, Pong.red, Pong.green, Pong.blue);
		DrawWall(Left.x, Left.y);
		DrawWall(Right.x, Right.y);
		DrawThePixelatedWall();
		DrawScoreboard();
	

}
///Draws the Pongball
void Game::DrawBall(int BallX, int BallY, int BallRed, int BallGreen, int BallBlue)
{
	///Middle layer of pixels
	gfx.PutPixel(BallX, BallY, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 1, BallY, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 2, BallY, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 3, BallY, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX - 1, BallY, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX - 2, BallY, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX - 3, BallY, BallRed, BallGreen, BallBlue);
	///Layer of Pixels above middle layer
	gfx.PutPixel(BallX - 3, BallY - 1, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX - 2, BallY - 1, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX - 1, BallY - 1, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX, BallY - 1, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 1, BallY - 1, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 2, BallY - 1, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 3, BallY - 1, BallRed, BallGreen, BallBlue);
	///Layer of Pixels beneath top layer
	gfx.PutPixel(BallX - 2, BallY - 2, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX - 1, BallY - 2, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX, BallY - 2, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 1, BallY - 2, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 2, BallY - 2, BallRed, BallGreen, BallBlue);
	///Top Layer
	gfx.PutPixel(BallX - 1, BallY - 3, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX, BallY - 3, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 1, BallY - 3, BallRed, BallGreen, BallBlue);
	///Layer beneath middle layer
	gfx.PutPixel(BallX - 3, BallY + 1, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX - 2, BallY + 1, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX - 1, BallY + 1, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX, BallY + 1, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 1, BallY + 1, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 2, BallY + 1, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 3, BallY + 1, BallRed, BallGreen, BallBlue);
	///Layer above bottom layer
	gfx.PutPixel(BallX - 2, BallY + 2, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX - 1, BallY + 2, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX, BallY + 2, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 1, BallY + 2, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 2, BallY + 2, BallRed, BallGreen, BallBlue);
	///Bottom layer
	gfx.PutPixel(BallX - 1, BallY + 3, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX, BallY + 3, BallRed, BallGreen, BallBlue);
	gfx.PutPixel(BallX + 1, BallY + 3, BallRed, BallGreen, BallBlue);



}
///Draws the walls for the players (100 pixels tall)
void Game::DrawWall(int XCoordinate, int YCoordinate)
{
	if (XCoordinate == Left.x)
	{
		for (int i = -50; i <= 50; ++i)
		{
			gfx.PutPixel(XCoordinate, YCoordinate + i, 255, 255, 255);
			gfx.PutPixel(XCoordinate - 1, YCoordinate + i, 255, 255, 255);
			gfx.PutPixel(XCoordinate - 2, YCoordinate + i, 255, 255, 255);
			gfx.PutPixel(XCoordinate - 3, YCoordinate + i, 255, 255, 255);
		}
	}

	if (XCoordinate == Right.x)
	{
		for (int i = -50; i <= 50; ++i)
		{
			gfx.PutPixel(XCoordinate, YCoordinate + i, 255, 255, 255);
			gfx.PutPixel(XCoordinate + 1, YCoordinate + i, 255, 255, 255);
			gfx.PutPixel(XCoordinate + 2, YCoordinate + i, 255, 255, 255);
			gfx.PutPixel(XCoordinate + 3, YCoordinate + i, 255, 255, 255);
		}
	}
}
///Draws the boundary between the player fields
void Game::DrawThePixelatedWall()
{
	for (int i = 0; i <= 597; i = i + 3)
	{
		gfx.PutPixel(399, i, 255, 255, 255);
	}
}
///Draws the scoreboard.
void Game::DrawScoreboard()
{
	{
		int x = 320;
		int y = 6;
		switch (Left.Score) {
		case 0:
			for (int i = 6; i <= 50; ++i)
			{
				gfx.PutPixel(320 + 6, i, 255, 255, 255);
				gfx.PutPixel(320 + 5, i, 255, 255, 255);
				gfx.PutPixel(320 - 5, i, 255, 255, 255);
				gfx.PutPixel(320 - 6, i, 255, 255, 255);
				gfx.PutPixel(320 + 7, i, 255, 255, 255);
				gfx.PutPixel(320 - 7, i, 255, 255, 255);
			}
			for (int i = -4; i <= 6; ++i)
			{
				gfx.PutPixel(320 + i, 6, 255, 255, 255);
				gfx.PutPixel(320 + i, 7, 255, 255, 255);
				gfx.PutPixel(320 + i, 8, 255, 255, 255);
				gfx.PutPixel(320 + i, 50, 255, 255, 255);
				gfx.PutPixel(320 + i, 49, 255, 255, 255);
				gfx.PutPixel(320 + i, 48, 255, 255, 255);
			}


			break;

		case 1:
			for (int i = 6; i <= 50; ++i)
			{
				gfx.PutPixel(320, i, 255, 255, 255);
				gfx.PutPixel(320 + 1, i, 255, 255, 255);
				gfx.PutPixel(320 - 1, i, 255, 255, 255);
			}
			break;

		case 2:
			gfx.PutPixel(9 + x, 2 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 2 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 2 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 2 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 2 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 2 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 43 + y, 255, 255, 255);

			break;

		case 3:
			gfx.PutPixel(11 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 43 + y, 255, 255, 255);

			break;

		case 4:
			gfx.PutPixel(3 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 46 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 47 + y, 255, 255, 255);

			break;

		case 5:
			gfx.PutPixel(4 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 45 + y, 255, 255, 255);

			break;

		case 6:
			gfx.PutPixel(15 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 46 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 46 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 46 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 46 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 46 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 46 + y, 255, 255, 255);

			break;

		case 7:
			gfx.PutPixel(3 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 46 + y, 255, 255, 255);

			break;

		case 8:
			for (int i = 6; i <= 50; ++i)
			{
				gfx.PutPixel(320 + 6, i, 255, 255, 255);
				gfx.PutPixel(320 + 5, i, 255, 255, 255);
				gfx.PutPixel(320 - 5, i, 255, 255, 255);
				gfx.PutPixel(320 - 6, i, 255, 255, 255);
				gfx.PutPixel(320 + 7, i, 255, 255, 255);
				gfx.PutPixel(320 - 7, i, 255, 255, 255);
			}
			for (int i = -4; i <= 6; ++i)
			{
				gfx.PutPixel(320 + i, 6, 255, 255, 255);
				gfx.PutPixel(320 + i, 7, 255, 255, 255);
				gfx.PutPixel(320 + i, 8, 255, 255, 255);
				gfx.PutPixel(320 + i, 50, 255, 255, 255);
				gfx.PutPixel(320 + i, 49, 255, 255, 255);
				gfx.PutPixel(320 + i, 48, 255, 255, 255);
				gfx.PutPixel(320 + i, 27, 255, 255, 255);
				gfx.PutPixel(320 + i, 28, 255, 255, 255);
			}

			break;

		case 9:
			gfx.PutPixel(13 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 45 + y, 255, 255, 255);

			break;

		case 10:
			break;

		}
	}

	{
		int x = 478;
		int y = 6;
		switch (Right.Score) {
		case 0:
			for (int i = 6; i <= 50; ++i)
			{
				gfx.PutPixel(478 + 6, i, 255, 255, 255);
				gfx.PutPixel(478 + 5, i, 255, 255, 255);
				gfx.PutPixel(478 - 5, i, 255, 255, 255);
				gfx.PutPixel(478 - 6, i, 255, 255, 255);
				gfx.PutPixel(478 + 7, i, 255, 255, 255);
				gfx.PutPixel(478 - 7, i, 255, 255, 255);
			}
			for (int i = -4; i <= 6; ++i)
			{
				gfx.PutPixel(478 + i, 6, 255, 255, 255);
				gfx.PutPixel(478 + i, 7, 255, 255, 255);
				gfx.PutPixel(478 + i, 8, 255, 255, 255);
				gfx.PutPixel(478 + i, 50, 255, 255, 255);
				gfx.PutPixel(478 + i, 49, 255, 255, 255);
				gfx.PutPixel(478 + i, 48, 255, 255, 255);
			}
			break;

		case 1:
			for (int i = 6; i <= 50; ++i)
			{
				gfx.PutPixel(478, i, 255, 255, 255);
				gfx.PutPixel(478 + 1, i, 255, 255, 255);
				gfx.PutPixel(478 - 1, i, 255, 255, 255);
			}
			break;

		case 2:

			gfx.PutPixel(9 + 478, 2 + 6, 255, 255, 255);
			gfx.PutPixel(10 + 478, 2 + 6, 255, 255, 255);
			gfx.PutPixel(11 + 478, 2 + 6, 255, 255, 255);
			gfx.PutPixel(12 + 478, 2 + 6, 255, 255, 255);
			gfx.PutPixel(13 + 478, 2 + 6, 255, 255, 255);
			gfx.PutPixel(14 + 478, 2 + 6, 255, 255, 255);
			gfx.PutPixel(6 + 478, 3 + 6, 255, 255, 255);
			gfx.PutPixel(7 + 478, 3 + 6, 255, 255, 255);
			gfx.PutPixel(8 + 478, 3 + 6, 255, 255, 255);
			gfx.PutPixel(9 + 478, 3 + 6, 255, 255, 255);
			gfx.PutPixel(10 + 478, 3 + 6, 255, 255, 255);
			gfx.PutPixel(11 + 478, 3 + 6, 255, 255, 255);
			gfx.PutPixel(12 + 478, 3 + 6, 255, 255, 255);
			gfx.PutPixel(13 + 478, 3 + 6, 255, 255, 255);
			gfx.PutPixel(14 + 478, 3 + 6, 255, 255, 255);
			gfx.PutPixel(15 + 478, 3 + 6, 255, 255, 255);
			gfx.PutPixel(16 + 478, 3 + 6, 255, 255, 255);
			gfx.PutPixel(5 + 478, 4 + 6, 255, 255, 255);
			gfx.PutPixel(6 + 478, 4 + 6, 255, 255, 255);
			gfx.PutPixel(7 + 478, 4 + 6, 255, 255, 255);
			gfx.PutPixel(8 + 478, 4 + 6, 255, 255, 255);
			gfx.PutPixel(9 + 478, 4 + 6, 255, 255, 255);
			gfx.PutPixel(14 + 478, 4 + 6, 255, 255, 255);
			gfx.PutPixel(15 + 478, 4 + 6, 255, 255, 255);
			gfx.PutPixel(16 + 478, 4 + 6, 255, 255, 255);
			gfx.PutPixel(17 + 478, 4 + 6, 255, 255, 255);
			gfx.PutPixel(18 + 478, 4 + 6, 255, 255, 255);
			gfx.PutPixel(4 + 478, 5 + 6, 255, 255, 255);
			gfx.PutPixel(5 + 478, 5 + 6, 255, 255, 255);
			gfx.PutPixel(6 + 478, 5 + 6, 255, 255, 255);
			gfx.PutPixel(7 + 478, 5 + 6, 255, 255, 255);
			gfx.PutPixel(16 + 478, 5 + 6, 255, 255, 255);
			gfx.PutPixel(17 + 478, 5 + 6, 255, 255, 255);
			gfx.PutPixel(18 + 478, 5 + 6, 255, 255, 255);
			gfx.PutPixel(19 + 478, 5 + 6, 255, 255, 255);
			gfx.PutPixel(3 + 478, 6 + 6, 255, 255, 255);
			gfx.PutPixel(4 + 478, 6 + 6, 255, 255, 255);
			gfx.PutPixel(5 + 478, 6 + 6, 255, 255, 255);
			gfx.PutPixel(18 + 478, 6 + 6, 255, 255, 255);
			gfx.PutPixel(19 + 478, 6 + 6, 255, 255, 255);
			gfx.PutPixel(20 + 478, 6 + 6, 255, 255, 255);
			gfx.PutPixel(3 + 478, 7 + 6, 255, 255, 255);
			gfx.PutPixel(4 + 478, 7 + 6, 255, 255, 255);
			gfx.PutPixel(20 + 478, 7 + 6, 255, 255, 255);
			gfx.PutPixel(21 + 478, 7 + 6, 255, 255, 255);
			gfx.PutPixel(3 + 478, 8 + 6, 255, 255, 255);
			gfx.PutPixel(4 + 478, 8 + 6, 255, 255, 255);
			gfx.PutPixel(21 + 478, 8 + 6, 255, 255, 255);
			gfx.PutPixel(22 + 478, 8 + 6, 255, 255, 255);
			gfx.PutPixel(2 + 478, 9 + 6, 255, 255, 255);
			gfx.PutPixel(3 + 478, 9 + 6, 255, 255, 255);
			gfx.PutPixel(4 + 478, 9 + 6, 255, 255, 255);
			gfx.PutPixel(22 + 478, 9 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 9 + 6, 255, 255, 255);
			gfx.PutPixel(2 + 478, 10 + 6, 255, 255, 255);
			gfx.PutPixel(3 + 478, 10 + 6, 255, 255, 255);
			gfx.PutPixel(4 + 478, 10 + 6, 255, 255, 255);
			gfx.PutPixel(22 + 478, 10 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 10 + 6, 255, 255, 255);
			gfx.PutPixel(2 + 478, 11 + 6, 255, 255, 255);
			gfx.PutPixel(3 + 478, 11 + 6, 255, 255, 255);
			gfx.PutPixel(22 + 478, 11 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 11 + 6, 255, 255, 255);
			gfx.PutPixel(24 + 478, 11 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 12 + 6, 255, 255, 255);
			gfx.PutPixel(24 + 478, 12 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 13 + 6, 255, 255, 255);
			gfx.PutPixel(24 + 478, 13 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 14 + 6, 255, 255, 255);
			gfx.PutPixel(24 + 478, 14 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 15 + 6, 255, 255, 255);
			gfx.PutPixel(24 + 478, 15 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 16 + 6, 255, 255, 255);
			gfx.PutPixel(24 + 478, 16 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 17 + 6, 255, 255, 255);
			gfx.PutPixel(24 + 478, 17 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 18 + 6, 255, 255, 255);
			gfx.PutPixel(24 + 478, 18 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 19 + 6, 255, 255, 255);
			gfx.PutPixel(24 + 478, 19 + 6, 255, 255, 255);
			gfx.PutPixel(22 + 478, 20 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 20 + 6, 255, 255, 255);
			gfx.PutPixel(24 + 478, 20 + 6, 255, 255, 255);
			gfx.PutPixel(22 + 478, 21 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 21 + 6, 255, 255, 255);
			gfx.PutPixel(21 + 478, 22 + 6, 255, 255, 255);
			gfx.PutPixel(22 + 478, 22 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 22 + 6, 255, 255, 255);
			gfx.PutPixel(20 + 478, 23 + 6, 255, 255, 255);
			gfx.PutPixel(21 + 478, 23 + 6, 255, 255, 255);
			gfx.PutPixel(22 + 478, 23 + 6, 255, 255, 255);
			gfx.PutPixel(20 + 478, 24 + 6, 255, 255, 255);
			gfx.PutPixel(21 + 478, 24 + 6, 255, 255, 255);
			gfx.PutPixel(22 + 478, 24 + 6, 255, 255, 255);
			gfx.PutPixel(19 + 478, 25 + 6, 255, 255, 255);
			gfx.PutPixel(20 + 478, 25 + 6, 255, 255, 255);
			gfx.PutPixel(21 + 478, 25 + 6, 255, 255, 255);
			gfx.PutPixel(18 + 478, 26 + 6, 255, 255, 255);
			gfx.PutPixel(19 + 478, 26 + 6, 255, 255, 255);
			gfx.PutPixel(20 + 478, 26 + 6, 255, 255, 255);
			gfx.PutPixel(21 + 478, 26 + 6, 255, 255, 255);
			gfx.PutPixel(17 + 478, 27 + 6, 255, 255, 255);
			gfx.PutPixel(18 + 478, 27 + 6, 255, 255, 255);
			gfx.PutPixel(19 + 478, 27 + 6, 255, 255, 255);
			gfx.PutPixel(20 + 478, 27 + 6, 255, 255, 255);
			gfx.PutPixel(17 + 478, 28 + 6, 255, 255, 255);
			gfx.PutPixel(18 + 478, 28 + 6, 255, 255, 255);
			gfx.PutPixel(19 + 478, 28 + 6, 255, 255, 255);
			gfx.PutPixel(16 + 478, 29 + 6, 255, 255, 255);
			gfx.PutPixel(17 + 478, 29 + 6, 255, 255, 255);
			gfx.PutPixel(18 + 478, 29 + 6, 255, 255, 255);
			gfx.PutPixel(15 + 478, 30 + 6, 255, 255, 255);
			gfx.PutPixel(16 + 478, 30 + 6, 255, 255, 255);
			gfx.PutPixel(17 + 478, 30 + 6, 255, 255, 255);
			gfx.PutPixel(18 + 478, 30 + 6, 255, 255, 255);
			gfx.PutPixel(14 + 478, 31 + 6, 255, 255, 255);
			gfx.PutPixel(15 + 478, 31 + 6, 255, 255, 255);
			gfx.PutPixel(16 + 478, 31 + 6, 255, 255, 255);
			gfx.PutPixel(17 + 478, 31 + 6, 255, 255, 255);
			gfx.PutPixel(14 + 478, 32 + 6, 255, 255, 255);
			gfx.PutPixel(15 + 478, 32 + 6, 255, 255, 255);
			gfx.PutPixel(16 + 478, 32 + 6, 255, 255, 255);
			gfx.PutPixel(13 + 478, 33 + 6, 255, 255, 255);
			gfx.PutPixel(14 + 478, 33 + 6, 255, 255, 255);
			gfx.PutPixel(15 + 478, 33 + 6, 255, 255, 255);
			gfx.PutPixel(12 + 478, 34 + 6, 255, 255, 255);
			gfx.PutPixel(13 + 478, 34 + 6, 255, 255, 255);
			gfx.PutPixel(14 + 478, 34 + 6, 255, 255, 255);
			gfx.PutPixel(11 + 478, 35 + 6, 255, 255, 255);
			gfx.PutPixel(12 + 478, 35 + 6, 255, 255, 255);
			gfx.PutPixel(13 + 478, 35 + 6, 255, 255, 255);
			gfx.PutPixel(10 + 478, 36 + 6, 255, 255, 255);
			gfx.PutPixel(11 + 478, 36 + 6, 255, 255, 255);
			gfx.PutPixel(12 + 478, 36 + 6, 255, 255, 255);
			gfx.PutPixel(13 + 478, 36 + 6, 255, 255, 255);
			gfx.PutPixel(9 + 478, 37 + 6, 255, 255, 255);
			gfx.PutPixel(10 + 478, 37 + 6, 255, 255, 255);
			gfx.PutPixel(11 + 478, 37 + 6, 255, 255, 255);
			gfx.PutPixel(12 + 478, 37 + 6, 255, 255, 255);
			gfx.PutPixel(8 + 478, 38 + 6, 255, 255, 255);
			gfx.PutPixel(9 + 478, 38 + 6, 255, 255, 255);
			gfx.PutPixel(10 + 478, 38 + 6, 255, 255, 255);
			gfx.PutPixel(11 + 478, 38 + 6, 255, 255, 255);
			gfx.PutPixel(7 + 478, 39 + 6, 255, 255, 255);
			gfx.PutPixel(8 + 478, 39 + 6, 255, 255, 255);
			gfx.PutPixel(9 + 478, 39 + 6, 255, 255, 255);
			gfx.PutPixel(10 + 478, 39 + 6, 255, 255, 255);
			gfx.PutPixel(5 + 478, 40 + 6, 255, 255, 255);
			gfx.PutPixel(6 + 478, 40 + 6, 255, 255, 255);
			gfx.PutPixel(7 + 478, 40 + 6, 255, 255, 255);
			gfx.PutPixel(8 + 478, 40 + 6, 255, 255, 255);
			gfx.PutPixel(9 + 478, 40 + 6, 255, 255, 255);
			gfx.PutPixel(4 + 478, 41 + 6, 255, 255, 255);
			gfx.PutPixel(5 + 478, 41 + 6, 255, 255, 255);
			gfx.PutPixel(6 + 478, 41 + 6, 255, 255, 255);
			gfx.PutPixel(7 + 478, 41 + 6, 255, 255, 255);
			gfx.PutPixel(8 + 478, 41 + 6, 255, 255, 255);
			gfx.PutPixel(3 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(4 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(5 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(6 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(7 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(8 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(9 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(10 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(11 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(12 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(13 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(14 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(15 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(16 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(17 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(18 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(19 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(20 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(21 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(22 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(24 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(25 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(26 + 478, 42 + 6, 255, 255, 255);
			gfx.PutPixel(3 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(4 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(5 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(6 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(7 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(8 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(9 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(10 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(11 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(12 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(13 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(14 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(15 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(16 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(17 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(18 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(19 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(20 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(21 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(22 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(23 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(24 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(25 + 478, 43 + 6, 255, 255, 255);
			gfx.PutPixel(26 + 478, 43 + 6, 255, 255, 255);

			break;

		case 3:
			gfx.PutPixel(11 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 3 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 43 + y, 255, 255, 255);
			break;

		case 4:
			gfx.PutPixel(3 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 4 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 46 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 47 + y, 255, 255, 255);
			break;

		case 5:
			gfx.PutPixel(4 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(26 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 45 + y, 255, 255, 255);
			break;

		case 6:
			gfx.PutPixel(15 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(2 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(3 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 46 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 46 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 46 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 46 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 46 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 46 + y, 255, 255, 255);
			break;

		case 7:
			gfx.PutPixel(3 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(4 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 46 + y, 255, 255, 255);
			break;

		case 8:
			for (int i = 6; i <= 50; ++i)
			{
				gfx.PutPixel(478 + 6, i, 255, 255, 255);
				gfx.PutPixel(478 + 5, i, 255, 255, 255);
				gfx.PutPixel(478 - 5, i, 255, 255, 255);
				gfx.PutPixel(478 - 6, i, 255, 255, 255);
				gfx.PutPixel(479 + 7, i, 255, 255, 255);
				gfx.PutPixel(478 - 7, i, 255, 255, 255);
			}
			for (int i = -4; i <= 6; ++i)
			{
				gfx.PutPixel(478 + i, 6, 255, 255, 255);
				gfx.PutPixel(478 + i, 7, 255, 255, 255);
				gfx.PutPixel(478 + i, 8, 255, 255, 255);
				gfx.PutPixel(478 + i, 50, 255, 255, 255);
				gfx.PutPixel(478 + i, 49, 255, 255, 255);
				gfx.PutPixel(478 + i, 48, 255, 255, 255);
				gfx.PutPixel(478 + i, 27, 255, 255, 255);
				gfx.PutPixel(478 + i, 28, 255, 255, 255);
			}
			break;

		case 9:
			gfx.PutPixel(13 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 5 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 6 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 7 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 8 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 9 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 10 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 11 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 12 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 13 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 14 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 15 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 16 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 17 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 18 + y, 255, 255, 255);
			gfx.PutPixel(5 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 19 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 20 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 21 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 22 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 23 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(25 + x, 24 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 25 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 26 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 27 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 28 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 29 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 30 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 31 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 32 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 33 + y, 255, 255, 255);
			gfx.PutPixel(24 + x, 34 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 35 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 36 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 37 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 38 + y, 255, 255, 255);
			gfx.PutPixel(6 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(23 + x, 39 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 40 + y, 255, 255, 255);
			gfx.PutPixel(7 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(22 + x, 41 + y, 255, 255, 255);
			gfx.PutPixel(8 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(21 + x, 42 + y, 255, 255, 255);
			gfx.PutPixel(9 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(20 + x, 43 + y, 255, 255, 255);
			gfx.PutPixel(10 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(11 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(17 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(18 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(19 + x, 44 + y, 255, 255, 255);
			gfx.PutPixel(12 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(13 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(14 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(15 + x, 45 + y, 255, 255, 255);
			gfx.PutPixel(16 + x, 45 + y, 255, 255, 255);
			break;

		case 10:

			break;

		}
	}
}
///Pong Ball physics :D
void Game::PongBallPhysics()
{
	Pong.x = Pong.x + Pong.vx;
	Pong.y = Pong.y + Pong.vy;
	///Sets initial VX and VY
	
	if (NewRound)
	{
		srand(time(NULL));
		Pong.y = rand() % 599;
		Pong.vx = rand() % 6 + 5;
		srand(time(NULL));
		Pong.vy = rand() % 9;
		int Random = rand() % 2;
		if (Random == 1)
		{
			Pong.vx = -Pong.vx;
		}
		NewRound = false;
	}
	IsTouchingWall();
	/// Touching top or bottom?
	if (Pong.y - 3 < 0)
	{
		DoBounceCalculation();
		Pong.y = 3;
	}
	if (Pong.y + 3 > 599)
	{
		DoBounceCalculation();
		Pong.y = 595;
	}
	///Touching a wall?
	/// ERROR, BallVX goes PAST LeftPlayerX/RightPlayerX!
	
}
///Makes the angle be the same as when it hit the wall/boundary.Looked at and is working
void Game::DoBounceCalculation()
{
	Pong.vy = -Pong.vy;
} 
///Swaps two variables, looked at and should be working
void Game::Swap(int &x, int &y)
{
	int SwapVariable = x;
	x = y;
	y = SwapVariable;
}
///Checks if ball is in opponent's goal, looked at and is working
void Game::IsGoal()
{
	if (Pong.x - 3 <= 0)
	{
		Right.Score++;
		Pong.x = 399;
		FirstTime = true;
	}
	if (Pong.x + 3 >= gfx.ScreenWidth)
	{
		Left.Score++;
		Pong.x = 399;
		FirstTime = true;
	}
}
///Moves player walls, looked at and is working
void Game::MovePaddle()
{
	if (wnd.kbd.KeyIsPressed(0x57))
	{
		Left.y = Left.y - 10;
	}
	if (wnd.kbd.KeyIsPressed(0x53))
	{
		Left.y = Left.y + 10;
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		Right.y = Right.y - 10;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		Right.y = Right.y + 10;
	}
}
///Checks if Ball is touching Player paddles and changes velocity accordingly, works
void Game::IsTouchingWall()
{
	// if-statement that checks if the ball is going to hit the paddle in the next frame.
	// The problem is, that VX skips the pixels the wall's at, (when they're set to anything higher than 1)
	// So that it jumps over the paddle.
	///Handles Leftplayer paddle
	if (Pong.x - Left.x - 3 < -Pong.vx && !(Pong.x - Left.x - 3 < 0))
	{
		int XGap = Pong.x - Left.x - 3;
		double BallVelocity = Pong.vy / Pong.vx;
		int YGap = XGap*BallVelocity;
		int TheoreticalX = Left.x;
		int TheoreticalY = Pong.y - YGap;
		if (TheoreticalX == Left.x && TheoreticalY - 3 <= Left.y + 50 && TheoreticalY + 3 >= Left.y - 50)
		{
			Pong.x = 104;
			Pong.y = TheoreticalY - 3;
			srand(time(NULL));
			Pong.vy = rand() % 9;
			srand(time(NULL));
			int Random = rand() % 2;
			if (Random == 1)
				Pong.vy = -Pong.vy;
			Pong.vx = rand() % 6 + 5;
		}
	}
	///Handles rightplayer paddle
	if (Right.x - Pong.x - 3 < Pong.vx && !(Right.x - Pong.x - 3 < 0))
	{
		int XGap = Right.x - Pong.x - 3;
		double BallVelocity = Pong.vy / Pong.vx;
		int YGap = XGap*BallVelocity;
		int TheoreticalX = Right.x;
		int TheoreticalY = Pong.y + YGap;
		if (TheoreticalX == Right.x && TheoreticalY - 3 <= Right.y + 50 && TheoreticalY + 3 >= Right.y - 50)																																																																																																																																					///Hi
		{
			Pong.x = 696;
			Pong.y = TheoreticalY;
			srand(time(NULL));
			Pong.vy = rand() % 9;
			int Random = rand() % 2;
			if (Random == 1)
				Pong.vy = -Pong.vy;
			srand(time(NULL));
			Pong.vx = rand() % 6 + 5;
			Pong.vx = -Pong.vx;
		}
	}
}

