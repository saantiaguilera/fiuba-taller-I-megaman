/*
 * EditorObstacle.h
 *
 *  Created on: May 29, 2016
 *      Author: santi
 */

#ifndef EDITOR_MODELS_OBSTACLES_EDITOR_EDITOROBSTACLE_H_
#define EDITOR_MODELS_OBSTACLES_EDITOR_EDITOROBSTACLE_H_

#include "../../../common/common_Point.h"

class EditorObstacle {
public:
	EditorObstacle(unsigned int aX, unsigned int aY, unsigned int aHeight, unsigned int aWidth);
	EditorObstacle();
	virtual ~EditorObstacle();

	unsigned int getHeight();
	unsigned int getWidth();
	Point getPoint();

protected:
		Point point;
		unsigned int height;
		unsigned int width;
};

//Tiene que haber bloques puas escaleras y presipicios

#endif /* EDITOR_MODELS_OBSTACLES_EDITOR_EDITOROBSTACLE_H_ */
