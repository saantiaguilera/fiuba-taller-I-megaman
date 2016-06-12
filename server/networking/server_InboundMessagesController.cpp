/*
 * server_iinboundMessageInterpreter.cpp
 *
 *  Created on: May 21, 2016
 *      Author: mastanca
 */

#include "server_InboundMessagesController.h"

#include <Common/b2Math.h>
#include <Dynamics/b2Body.h>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

#include "../../common/common_MessageProtocol.h"
#include "../game_engine/physics/server_PhysicObject.h"
#include "../game_engine/server_Engine.h"
#include "../game_engine/server_EventContext.h"
#include "../game_engine/server_Player.h"
#include "../model/characters/humanoids/server_Megaman.h"
#include "../parsers/server_JsonMapParser.h"
#include "../serializers/server_NewPlayerSerializer.h"
#include "../serializers/server_StartGameSerializer.h"

#define MAX_PLAYERS_COUNT 4
#define MAX_MOVE_STATES 5

InboundMessagesController::InboundMessagesController(int messageCode,
		unsigned int clientId, const std::string& inboundMessage) {
	analizeMessageCode(messageCode, clientId, inboundMessage);
}

void InboundMessagesController::analizeMessageCode(int messageCode,
		unsigned int clientId, const std::string& inboundMessage) {
	// CHECK MESSAGE PROTOCOL IN common_MessageProtocol.h
	std::list<Player*> playerList = Engine::getInstance().getPlayersList();
	Player* desiredPlayer;
	switch (messageCode) {
	case PLAYER_CONNECTED:
		if (Engine::getInstance().getPlayersList().size() <= MAX_PLAYERS_COUNT) {
			Engine::getInstance().addNewPlayer(clientId, inboundMessage);
			NewPlayerSerializer* newPlayerSerializer = new NewPlayerSerializer(
					inboundMessage);
			Engine::getInstance().getContext()->dispatchEvent(
					newPlayerSerializer);
		}
		break;
	case START_GAME:
		if (Engine::getInstance().getPlayersList().size() <= MAX_PLAYERS_COUNT && !Engine::getInstance().isRunning()) {
			// Set the flag of the engine to ready to start
			desiredPlayer = getDesiredPlayer(clientId);
			if (desiredPlayer->isAdmin()) {
				StartGameSerializer* startGameSerializer =
						new StartGameSerializer(inboundMessage);
				Engine::getInstance().getContext()->dispatchEvent(
						startGameSerializer);
				JsonMapParser mapParser;
				mapParser.parseDocument("level" + inboundMessage + ".json");
				int selectedMapId;
				std::stringstream inboundMessageStream(inboundMessage);
				inboundMessageStream >> selectedMapId;
				Engine::getInstance().setCurrentMapId(selectedMapId);
				Engine::getInstance().setReadyToStart(true);
			}
		}
		break;
	case KEY_PRESSED:
		// Here inbound message is a map of keys-boolean
		// According to the pressed key we should do something
		// We should get the player id, the key pressed
		desiredPlayer = getDesiredPlayer(clientId);
		processMovement(inboundMessage, desiredPlayer);
		break;
		desiredPlayer->getMegaman()->getMyBody()->SetLinearVelocity(b2Vec2(50, 100));
	case WEAPON_CHANGE:
		std::cout << "Weapon change!" << std::endl;
		desiredPlayer = getDesiredPlayer(clientId);
		desiredPlayer->getMegaman()->changeWeaponTo(
				processWeaponType(inboundMessage));
		break;
	default:
		break;
	}
}

Player* InboundMessagesController::getDesiredPlayer(unsigned int playerId) {
	std::list<Player*> playerList = Engine::getInstance().getPlayersList();
	for (std::list<Player*>::iterator it = playerList.begin();
			it != playerList.end(); ++it) {
		if ((*it)->getId() == playerId)
			return *it;
	}
	return NULL;
}

void InboundMessagesController::processMovement(const std::string& keyMap,
		Player* player) {
	std::stringstream ss;
	ss.str(keyMap);
//	bool jump, down, left, right, shoot;
	std::vector<bool> keysVector;
	bool aux;
	for (int i = 0; i < MAX_MOVE_STATES; ++i) {
		ss >> aux;
		keysVector.push_back(aux);
	}

	if (keysVector[0] == true) {
		player->getMegaman()->move(PhysicObject::_moveState::MS_JUMP);
	}
	if (keysVector[1] == true) {
		player->getMegaman()->move(PhysicObject::_moveState::MS_DOWN);
	}
	if (keysVector[2] == true) {
		player->getMegaman()->move(PhysicObject::_moveState::MS_LEFT);
	}
	if (keysVector[3] == true) {
		player->getMegaman()->move(PhysicObject::_moveState::MS_RIGHT);
	}
	if (keysVector[4] == true) {
		player->getMegaman()->attack();
	}

}

int InboundMessagesController::processWeaponType(
		const std::string& weaponType) {
	std::stringstream ss(weaponType);
	int incomingWeaponType;
	ss >> incomingWeaponType;
	return incomingWeaponType;
}

InboundMessagesController::~InboundMessagesController() {
}

