/*
 * editor_main.cpp
 *
 *  Created on: May 14, 2016
 *      Author: santi
 */

#include <gtkmm.h>

#include "views/editor_MainWindow.h"
#include <iostream>
#include <exception>
#include "models/editor_EditorMapParser.h"
#include "models/editor_EditorMap.h"
#include "controllers/editor_EditorController.h"

int main(int argc, char *argv[]) {

	std::cout<<argc<<argv[0]<<std::endl;

	EditorController editorController = EditorController(argc, argv);

	editorController.begin();

	return EXIT_SUCCESS;
}

