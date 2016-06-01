/*
 * server_MovementSerializer.cpp
 *
 *  Created on: May 30, 2016
 *      Author: mastanca
 */

#include "server_PositionSerializer.h"

#include <sstream>

PositionSerializer::PositionSerializer(unsigned int objectId, float x, float y) : Serializer(objectId), x(x), y(y) {
}

PositionSerializer::~PositionSerializer() {
}

std::string PositionSerializer::serializePosition() {
	std::stringstream ss;
	ss << x;
	ss << y;
	return ss.str();
}