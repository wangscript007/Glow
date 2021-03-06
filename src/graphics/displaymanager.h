#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

//TODO: maybe implement multiple windows (most games don't need that)

namespace Glow { namespace graphics {

    class DisplayManager {
        private:
            int width_ = 0;
            int height_ = 0;
            std::string title_;
            GLFWwindow* window_ = nullptr; //only one window supported for now
        public:
            ~DisplayManager();
            void createWindow(int width, int height, std::string title);
            void destroyWindow();
            void clearWindow() const;
            void swapWindow() const;

            void (*window_focus_handler)(bool focused);
            //Getters and setters
            GLFWwindow* getWindow() const;
            bool windowShouldClose();
            void setWindowShouldClose(bool close);
            void setWindowTitle(std::string title);
            void setWindowSize(int width, int height);
            void setWindowFocusHandler(void (*handler)(bool focused));
        private:
            friend void framebuffer_resized(GLFWwindow* window, int width, int height);
            friend void window_focused(GLFWwindow* window, int focused);
            //to be implemented (callbacks)
            //friend void window_iconified(GLFWwindow* window, int iconified);
            
            void initGLFW();
            void initGL();

    };

}}
