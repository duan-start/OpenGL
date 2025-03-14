#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
   
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window); 
    glewInit();
     float position[6] = {
        -0.5,0.5,
        0.0,-0.5,
        - 0.5, -0.5
    };
     //创建buffer ,绑定编号，绑定buffer和显存的缓冲区，输入数据和模式
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
   
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);//现代的openGL的绘图
        /* glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f,0.5f);
        glVertex2f(0.0f, -0.5f);
        glVertex2f(-0.5f, -0.5f);

        glEnd();
        Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}