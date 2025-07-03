#include <iostream>
#include<GLFW/glfw3.h>
#include<VkMainComponent.h>

int main()
{

    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* Window = glfwCreateWindow(800, 800, "NullptrEngine", nullptr, nullptr);
    
    VkMain Main = VkMain();
    Main.VkInitialization(Window);
    
    while (!glfwWindowShouldClose(Window)) 
    {
        glfwPollEvents();
    }

}

