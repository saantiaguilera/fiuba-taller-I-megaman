/*
 * server_JumpingSniper.cpp
 *
 *  Created on: May 14, 2016
 *      Author: mastanca
 */

#include "server_JumpingSniper.h"

#include <iostream>

JumpingSniper::JumpingSniper(float32 x, float32 y) : Sniper(x, y) {
	notify();
}

JumpingSniper::~JumpingSniper() {
}

void JumpingSniper::update() {
	// Jumps between shots
	if (ticksPassed == ATTACK_INTERVAL_TICKS) {
		// Makes itself vulnerable and shots
		vulnerable = true;
		attack();
		ticksPassed = 0;
	} else {
		move(MS_JUMP);
	}

	if (ticksPassed == ATTACK_INTERVAL_TICKS / 4)
		vulnerable = false;

	++ticksPassed;
}

int JumpingSniper::getTypeForSerialization() {
	return ObstacleViewTypeJumpingSnyper;
}
