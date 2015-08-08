#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "displaymanager.h"
#include "renderer.h"
#include "time.h"
#include "log.h"

#include "vec3.h"

//the size of the window, defaulted to HD, which should be the minimum size of a monitor nowadays
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Glow3D - Pascal Riesinger"

namespace Glow {

//set to true when the game should exit
bool quit = false;

//important objects, such as the renderer
Renderer renderer;
DisplayManager displayManager;

//TODO: TEMP
float vertices[] = {
    -1.0, -1.0, 0.0,
     1.0, -1.0, 0.0,
     0.0,  1.0, 0.0
};

GLuint vboID;
GLuint vaoID;

//function prototypes
void start();
void loadup();
void gameloop();
void update();
void cleanup();

void start() {
    displayManager.createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    //TODO:create proper resource management system   
    loadup();
    gameloop();
    cleanup();
}


void loadup() {
	renderer.init();
    
    //initialize the timing subsystem
    Time::init();
    
    //TODO: TEMP
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void gameloop(){
	SDL_Event event;
	while (!quit) {
		//update the delta time
		Time::update();
		//get all SDL_Events and handle them
		while (SDL_PollEvent (&event)) {
			switch (event.type) {
				case SDL_QUIT: //SDL_Quit = close window
					quit = true;
				    break;
			}
		}
		update();
		//swap framebuffers
		SDL_GL_SwapWindow(displayManager.getWindow());
	}
}

void update(){
    //TODO: update the input
    renderer.prepare();
    renderer.renderVAO(vaoID);
    //after everything is done updating render every element
    renderer.renderAll();
}


void cleanup(){
    displayManager.destroyWindow();
	
	SDL_Quit();
}


}


int main(int argc, char *argv[]){
    Glow::start();
	return 0;
}
