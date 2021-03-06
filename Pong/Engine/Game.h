/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Paddle.h"
#include "Ball.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void DrawBall(int BallX, int BallY, int BallRed, int BallGreen, int BallBlue);
	void DrawWall(int XCoordinate, int YCoordinate);
	void DrawThePixelatedWall();
	void DrawScoreboard();
	void PongBallPhysics();
	void DoBounceCalculation();
	void Swap(int& x, int& y);
	void IsGoal();
	void MovePaddle();
	void MoveSinglePaddle();
	void IsTouchingWall();
	void DrawTitleScreen();
	void DrawTitleSingle();
	void DrawTitleMulti();
	void MoveAIPaddle();

	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables    */
	bool IsStarted = false;
	bool NewRound = true;
	bool FirstTime = true;
	bool SingleSelected = true;
	bool MultiSelected = false;
	bool SingleChosen = false;
	bool MultiChosen = false;
	Paddle Left;
	Paddle Right;
	Paddle Single;
	Paddle SingleAI;
	Ball Pong;
	bool WasPressed = false;
	/********************************/
};