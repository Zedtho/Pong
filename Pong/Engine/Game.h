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
	int WallInsideBorder(int YCoordinate);
	void PongBallPhysics();
	void DoBounceCalculation();
	void Swap(int& x, int& y);
	void IsGoal();
	void MovePaddle();
	void IsTouchingWall();

	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	double BallVX = 0;
	double BallVY = 0;
	int BallX = 399;
	int BallY = 0;
	int BallRed = 255;
	int BallGreen = 255;
	int BallBlue = 255;
	const int LeftPlayerX = 100;
	int LeftPlayerY = 299;
	const int RightPlayerX = 700;
	int RightPlayerY = 299;
	int LeftPlayerScore = 0;
	int RightPlayerScore = 0;
	bool NewRound = true;
	bool IsStarted = false;
	bool FirstTime = true;
	
	/********************************/
};