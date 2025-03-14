
#include "LoadTextures.h"
#include "inner/Camera.h"
#include "inner/shader.h"
#include  <vector>
#include <map>

#include <glm/gtc/type_ptr.hpp>
//改一下架构，复用的vendor就放外面，省的我每次都要复制vendor在文件里面
//#include <KHR/khrplatform.h>  如果要改的话还要改好几个地方

#define SCR_WIDTH 1280
#define SCR_HEIGHT 1280

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool firstMouse = true;
float lastX=800 ,lastY=640;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
// settings

float fov = 45.0f;

static  float last_time = 0.0f;
static float deltaTime;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

  int main() {

	//set Init;
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "senior", NULL,NULL);

	if (!window) {
		std::cout << "GLFW_INITIAL_FAILED" << std::endl;
	}
	glfwMakeContextCurrent(window);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!status) {
		std::cout << "GLAD_LOADER_FAILED" << std::endl;
	}

	//glfwsetcallback
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float vertices[] = {
        // 位置          // 纹理坐标
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  // 左上
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // 左下
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // 右下
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f   // 右上
    };
 //   glEnable(GL_DEPTH_TEST);
 //   glEnable(GL_BLEND);
 //   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	////data
 //   float vertices[] = {
 //       // positions          // texture Coords
 //      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 //       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
 //       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 //      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

 //      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 //       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 //       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 //       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 //      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
 //      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

 //      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 //      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 //      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 //       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 //       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //       0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 //       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 //      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 //       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 //       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 //       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 //      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 //      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

 //      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 //       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 //       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 //       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 //      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
 //      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
 //   };

    //float planeVertices[] = {
    //    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
    //     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    //    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    //    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

    //     5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    //    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
    //     5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    //};
    //float transparentVertices[] = {
    //    // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
    //    0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
    //    0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
    //    1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

    //    0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
    //    1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
    //    1.0f,  0.5f,  0.0f,  1.0f,  0.0f
    //};

    //创建缓冲区
    int indices[] = { 0,1,2,
                      2,3,0};
    unsigned int cubeVAO, cubeVBO,cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //position attribute;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));  // 纹理坐标
   


    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glBindVertexArray(0);

    ////second
    //unsigned int planeVAO, planeVBO;
    //glGenVertexArrays(1, &planeVAO);
    //glGenBuffers(1, &planeVBO);
    //glBindVertexArray(planeVAO);
    //glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    ////position attribute;
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glBindVertexArray(0);

    //unsigned int TransPortplaneVAO, TransPortplaneVBO;
    //glGenVertexArrays(1, &TransPortplaneVAO);
    //glGenBuffers(1, &TransPortplaneVBO);
    //glBindVertexArray(TransPortplaneVAO);
    //glBindBuffer(GL_ARRAY_BUFFER,TransPortplaneVBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glBindVertexArray(0);


    //unsigned int cubeTexture = loadTexture("./vendor/get.jpg",GL_REPEAT);
    //unsigned int floorTexture = loadTexture("./vendor/get.png", GL_REPEAT);
    //unsigned int trans= loadTexture("./vendor/window.png", GL_CLAMP_TO_EDGE);

    shader Shader("./src/shaders/copy.vs","./src/shaders/copy.fs");
    //shader LineShader("./src/shaders/VertexShader.vs", "./src/shaders/line.fs");
    
 /*   std::vector<glm::vec3> vegetion{
      glm::vec3(-1.5f, 0.0f, -0.48f),
        glm::vec3(1.5f, 0.0f, 0.51f),
        glm::vec3(0.0f, 0.0f, 0.7f),
        glm::vec3(-0.3f, 0.0f, -2.3f),
        glm::vec3(0.5f, 0.0f, -0.6f)
    };*/

    //采样器可以选择多个也可以选择与i个，实际上这两者可以相互替代，知识说你要对单独的问题进行特殊的操作时，就比较麻烦
    //Shader.use();
    //Shader.setInt("texture1", 0);

    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    //glEnable(GL_STENCIL_TEST);
    //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    //copy 
    glm::vec2 isr(1600., 1280.);
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - last_time;
        last_time = currentFrame;

        ////DEPTH TEST

     

        //// input
        //// -----
        //processInput(window);
        //    
        //std::map<float, glm::vec3> sorted;
        //for (unsigned int i = 0; i < vegetion.size(); i++) {
        //    float diatance = glm::length(camera.Position - vegetion[i]);
        //    sorted[diatance] = vegetion[i];
        //}
        //// render
        //// ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        ////draw objects
        Shader.use();
        glBindVertexArray(cubeVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        Shader.setFloat("iTime", currentFrame);
        Shader.setVec2("iResolution", glm::vec2(1280, 1280));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //
        ////根据外部设置的透视投影，确实抽象起来好用了很多，比自己手写还是方便
        //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.f);
        //glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 model = glm::mat4(1.0f);
        //Shader.setMatrix4fv("projection",glm::value_ptr(projection));
        //Shader.setMatrix4fv("view", glm::value_ptr(view));

        ////bind cubes 
        //glBindVertexArray(cubeVAO);
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, cubeTexture);

        //model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        //Shader.setMatrix4fv("model",glm::value_ptr(model));
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //model = glm::translate(model, glm::vec3(4.0f, 0.0f, -3.0f));
        //Shader.setMatrix4fv("model", glm::value_ptr(model));
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        //Shader.setMatrix4fv("model", glm::value_ptr(model));
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //

        //// floor
        //glBindVertexArray(planeVAO);
        //glBindTexture(GL_TEXTURE_2D, floorTexture);
        //model = glm::mat4(1.0f);
        //Shader.setMatrix4fv("model", glm::value_ptr(model));
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        //// vegetation
        //glBindVertexArray(TransPortplaneVAO);
        //glBindTexture(GL_TEXTURE_2D, trans);
        //for (std::map<float,glm::vec3>::reverse_iterator it= sorted.rbegin();it!=sorted.rend();++it)
        //{
        //    model = glm::mat4(1.0f);
        //    model = glm::translate(model, it->second);
        //    Shader.setMatrix4fv("model", glm::value_ptr(model));
        //    glDrawArrays(GL_TRIANGLES, 0, 6);
        //}
        /*-------------------------------------------------------------------------------*/
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    //glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &cubeVBO);
    //glDeleteBuffers(1, &planeVBO);
    //
    glfwTerminate();
    return 1;

}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

