#include "AgentPoursuiveur.h"
#include "Vehicle.h"


using std::vector;
using std::list;


AgentPoursuiveur::AgentPoursuiveur(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale, Vehicle * toFollow):Vehicle(
						 world,
						 position,
						 rotation,
						 velocity,
						 mass,
						 max_force,
						 max_speed,
						 max_turn_rate,
						 scale) {
		this->Steering()->OffsetPursuitOn(toFollow,  Vector2D(-40, 0));
		this->Steering()->SeparationOn();
}


