/*
 * server_Powerup.cpp
 *
 *  Created on: May 10, 2016
 *      Author: mastanca
 */

#include "server_Powerup.h"

#include <Collision/Shapes/b2PolygonShape.h>
#include <Common/b2Math.h>
#include <Dynamics/b2Body.h>
#include <Dynamics/b2Fixture.h>
#include <Dynamics/b2World.h>

#include "../../game_engine/server_Engine.h"


Powerup::Powerup(unsigned int effectAmount, float32 x, float32 y) :
		effectAmount(effectAmount) {
	// TODO: Use sensors for powerups field of view
	b2BodyDef powerupBodyDef;
	powerupBodyDef.type = b2_staticBody;
	powerupBodyDef.position.Set(x,y);
	// TODO: Maybe add it from the outside? when its created
	myBody = Engine::getInstance().getMyWorld()->CreateBody(&powerupBodyDef);

	// Assign user data for callbacks
	myBody->SetUserData( this );

	// Add shape to body
	b2PolygonShape boxShape;
	boxShape.SetAsBox(getWidth(),getHeight());

	// Add fixture
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	myBody->CreateFixture(&boxFixtureDef);
	myBody->GetFixtureList()->SetSensor(true);
}

float32 Powerup::getWidth() {
	return BODIES_SIZE / 4;
}

float32 Powerup::getHeight() {
	return BODIES_SIZE / 4;
}

Powerup::~Powerup() {
	myBody->GetWorld()->DestroyBody(myBody);
}

int Powerup::getObjectType() {
	return OT_POWERUP;
}
