/*
 * server_NormalSniper.cpp
 *
 *  Created on: May 14, 2016
 *      Author: mastanca
 */

#include "server_NormalSniper.h"

#include <iostream>

NormalSniper::NormalSniper(float32 x, float32 y) : Sniper(x, y) {
	notify();
	facingPosition = OR_LEFT;
}

NormalSniper::~NormalSniper() {
}

void NormalSniper::update() {
	// Apparently he doesn't move
	if (ticksPassed == ATTACK_INTERVAL_TICKS) {
		// Makes itself vulnerable and shots
		vulnerable = true;
		attack();
		ticksPassed = 0;
	}
	++ticksPassed;
	if (ticksPassed == ATTACK_INTERVAL_TICKS / 4) {
		vulnerable = false;
	}
}

int NormalSniper::getTypeForSerialization() {
	return ObstacleViewTypeNormalSnyper;
}
