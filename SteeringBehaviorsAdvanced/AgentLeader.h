#ifndef LEADER_H
#define LEADER_H

//------------------------------------------------------------------------
//
//  Name:   AgentPoursuiveur.h
//
//  Desc:   Definition of a simple AgentPoursuiveur that uses steering behaviors
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "Vehicle.h"
#include "2d/C2DMatrix.h"
#include "2d/Geometry.h"
#include "SteeringBehaviors.h"
#include "2d/Transformations.h"
#include "GameWorld.h"
#include "misc/CellSpacePartition.h"
#include "misc/cgdi.h"

#endif

class AgentLeader : public Vehicle
{
private:
	bool isAI;
	Vector2D MoveLeader();

public:


	AgentLeader::AgentLeader(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale,
		bool isAI);

	void AgentLeader::Render();

};


