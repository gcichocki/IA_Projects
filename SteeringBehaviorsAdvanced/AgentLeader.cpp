#include "AgentLeader.h"
#include "Vehicle.h"


using std::vector;
using std::list;


AgentLeader::AgentLeader(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale,
		bool isAI):Vehicle(
						 world,
						 position,
						 rotation,
						 velocity,
						 mass,
						 max_force,
						 max_speed,
						 max_turn_rate,
						 scale) {
	
	this->isAI = isAI;
	if (isAI) {
		this->Steering()->WanderOn();
	}
	else {
		this->Steering()->MoveAgentOn();
	}
	
}

void AgentLeader::Render() {
	//a vector to hold the transformed vertices
	static std::vector<Vector2D>  m_vecVehicleVBTrans;

	//Si c'est l'IA couleur rouge, si c'est l'humain couleur verte
	if (isAI) {
		gdi->RedPen();
	}
	else {
		gdi->GreenPen();
	}

	if (isSmoothingOn())
	{
		m_vecVehicleVBTrans = WorldTransform(m_vecVehicleVB,
			Pos(),
			SmoothedHeading(),
			SmoothedHeading().Perp(),
			Scale());
	}

	else
	{
		m_vecVehicleVBTrans = WorldTransform(m_vecVehicleVB,
			Pos(),
			Heading(),
			Side(),
			Scale());
	}


	gdi->ClosedShape(m_vecVehicleVBTrans);

	//render any visual aids / and or user options
	if (m_pWorld->ViewKeys())
	{
		Steering()->RenderAids();
	}
}


