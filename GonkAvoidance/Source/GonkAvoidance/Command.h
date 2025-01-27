// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "InputHandler.h"
#include "GameManager.h"
#include "CoreMinimal.h"

/**
 *
 */
class GONKAVOIDANCE_API Command
{
public:
	Command();
	virtual ~Command();
	virtual void Execute() = 0;
	ATileSelector* tileSelector;
	AGameManager* gameManager;
};

class GONKAVOIDANCE_API MoveUpCommand : public Command
{
public:
	void Execute() override 
	{
		if (gameManager->currentMode == Mode::SelectUnit)
		{

		}
		else if (gameManager->currentMode == Mode::Move)
		{
			tileSelector->UnitMovement(Movement::Up);
		}
	};
};

class GONKAVOIDANCE_API MoveDownCommand : public Command
{
public:
	void Execute() override 
	{
		if (gameManager->currentMode == Mode::SelectUnit)
		{

		}
		else if (gameManager->currentMode == Mode::Move)
		{
			tileSelector->UnitMovement(Movement::Down);
		}
	};
};

class GONKAVOIDANCE_API MoveLeftCommand : public Command
{
public:
	void Execute() override 
	{
		if (gameManager->currentMode == Mode::SelectUnit)
		{
			tileSelector->SelectUnit(Movement::Left);
		}
		else if (gameManager->currentMode == Mode::Move)
		{
			tileSelector->UnitMovement(Movement::Left);
		}
	};
};

class GONKAVOIDANCE_API MoveRightCommand : public Command
{
public:
	void Execute() override 
	{
		if (gameManager->currentMode == Mode::SelectUnit)
		{
			tileSelector->SelectUnit(Movement::Right);
		}
		else if (gameManager->currentMode == Mode::Move)
		{
			tileSelector->UnitMovement(Movement::Right);
		}
	};
};

class GONKAVOIDANCE_API SelectCommand : public Command
{
public:
	void Execute() override 
	{
		if (gameManager->currentMode == Mode::SelectUnit)
		{
			tileSelector->SelectionUnit();
		}
		else if (gameManager->currentMode == Mode::Move)
		{
			tileSelector->SelectMovement();
		}
	};
};
