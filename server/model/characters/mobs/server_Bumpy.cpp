/*
 * server_Bumpy.cpp
 *
 *  Created on: May 14, 2016
 *      Author: mastanca
 */

#include "server_Bumpy.h"

#include <Dynamics/b2Body.h>
#include <iostream>

#include "../../projectiles/server_Projectile.h"


Bumpy::Bumpy(float32 x, float32 y) : Mob(BUMPY_INITIAL_HP, x, y) {
	facingPosition = OR_BOTTOM;
	myBody->SetGravityScale(0);
	notify();
}

Bumpy::~Bumpy() {
}

void Bumpy::receiveShotFromProjectile(Projectile* projectile) {
	decreaseHp(projectile->getDamage());
	notifyMovement();
}

void Bumpy::update() {
	if (ticksPassed == ATTACK_INTERVAL_TICKS) {
		// Shots downwards
		facingPosition = OR_BOTTOM;
		attack();
		ticksPassed = 0;
	}
	++ticksPassed;
}

int Bumpy::getTypeForSerialization() {
	return ObstacleViewTypeBumpy;
}
