// Made by Roberto Reynoso (RvRproduct)

#pragma once

#include "InputHandler.h"
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
};

class GONKAVOIDANCE_API MoveUpCommand : public Command
{
public:
	void Execute() override {};
};

class GONKAVOIDANCE_API MoveDownCommand : public Command
{
public:
	void Execute() override {};
};

class GONKAVOIDANCE_API MoveLeftCommand : public Command
{
public:
	void Execute() override {};
};

class GONKAVOIDANCE_API MoveRightCommand : public Command
{
public:
	void Execute() override {};
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
