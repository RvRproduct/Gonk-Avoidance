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

	};
};

class GONKAVOIDANCE_API MoveDownCommand : public Command
{
public:
	void Execute() override {};
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
	};
};

class GONKAVOIDANCE_API GeneralSelectCommand : public Command
{
public:
	void Execute() override {};
};

class GONKAVOIDANCE_API CombatSelectCommand : public Command
{
public:
	void Execute() override {};
};
