#include <corecrt_math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int width, height;

void windowResizeCallback(GLFWwindow* window,int w,int h)
{

    height = h;
    width = w;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main()
{
    if (!glfwInit())
        return -1;
    GLFWwindow* window = glfwCreateWindow(1080, 720, "3DScene", nullptr, nullptr);
    if (!window)
        return -1;
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
        return -1;

  
    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glfwSetFramebufferSizeCallback(window, windowResizeCallback);

    float camx = 0.f, camy = 0.f, camz = 5.f;
    float camYaw = 0.f;
    float camPitch = 0.f;

    float camSpeed = 0.1f;


    float mouseSensivity = 0.05f;

    
    double* cx = new double;
    double* cy = new double;

    glfwGetCursorPos(window, cx, cy);


    while (!glfwWindowShouldClose(window))
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        float xoffset = xpos - *cx;
        float yoffset = *cy - ypos;

        *cx = xpos;
        *cy = ypos;

        xoffset *= mouseSensivity;
        yoffset *= mouseSensivity;

        camYaw += xoffset;
        camPitch -= yoffset;

        if (camPitch > 89.0f) camPitch = 89.0f;
        if (camPitch < -89.0f) camPitch = -89.0f;


        if (camYaw > 360.0f) camYaw -= 360.0f;
        if (camYaw < 0.0f) camYaw += 360.0f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();


        float forwardX = sinf(camYaw * 3.14159f / 180.0f) * cosf(camPitch * 3.14159f / 180.0f);
        float forwardY = sinf(camPitch * 3.14159f / 180.0f);
        float forwardZ = -cosf(camYaw * 3.14159f / 180.0f) * cosf(camPitch * 3.14159f / 180.0f);


        float rightX = sinf((camYaw + 90.f) * 3.14159f / 180.f);
        float rightZ = -cosf((camYaw + 90.f) * 3.14159f / 180.f);

        if (glfwGetKey(window, GLFW_KEY_W))
        {
            camx += forwardX * camSpeed;
            camz += forwardZ * camSpeed;
        }
        else  if (glfwGetKey(window, GLFW_KEY_S))
        {
            camx -= forwardX * camSpeed;
            camz -= forwardZ * camSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_A))
        {
            camx -= rightX * camSpeed;
            camz -= rightZ * camSpeed;
        }
        else  if (glfwGetKey(window, GLFW_KEY_D))
        {
            camx += rightX * camSpeed;
            camz += rightZ * camSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE))
            camy += camSpeed;
        else  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
            camy -= camSpeed;




        glRotatef(camPitch, 1.f, 0.f, 0.f);
        glRotatef(camYaw, 0.f, 1.f, 0.f);

        glTranslatef(-camx, -camy, -camz);

       //BEGIN CYLINDER 1
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 1.0f); 
        for (int i = 0; i <= 360; i += 12) {
            float radian = i * (3.14159f / 180.0f);
            if (i < 180)
                glColor3f(1.0f, 0.0f, 0.0f);
            else
                glColor3f(1.f, 0.f, 1.f);
            glVertex3f(cosf(radian), sinf(radian), 1.0f);
        }
        glEnd();

       
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, -1.0f);
        for (int i = 0; i <= 360; i += 12) {
            float radian = i * (3.14159f / 180.0f);
            glVertex3f(cosf(radian), sinf(radian), -1.0f);
        }
        glEnd();

      
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= 360; i += 12) {
            float radian = i * (3.14159f / 180.0f);
            float x = cosf(radian);
            float y = sinf(radian);
            glColor3f(0.0f, 1.0f, 1.0f);
            glVertex3f(x, y, 1.0f);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(x, y, -1.0f);
        }
        glEnd();
       //END CYLINDER 1

       //BEGIN CYLINDER 2
        glBegin(GL_TRIANGLE_FAN);
        
        glColor3f(1.f, 1.f, 1.f);
        glVertex3f(4.f, 0.f, 1.f);

        for (int i=0;i<=360;i+=12)
        {
            float radian = i * (3.14159f / 180.0f);
            glVertex3f(cosf(radian)+4.f, sinf(radian), 1.f);
        }

        glEnd();


        glBegin(GL_TRIANGLE_FAN);

        glColor3f(1.f, 0.243f, 0.3f);
        glVertex3f(4.f, 0.f, -1.f);

        for (int i = 0; i <= 360; i += 12)
        {
            float radian = i * (3.14159f / 180.0f);
            glVertex3f(cosf(radian)+4.f, sinf(radian), -1.f);
        }

        glEnd();

        glBegin(GL_QUAD_STRIP);


        for (int i = 0; i <= 360; i += 12) {
            float radian = i * (3.14159f / 180.0f);
            float x = cosf(radian);
            float y = sinf(radian);
            glColor3f(0.0f, 1.0f, 1.0f);
            glVertex3f(x+4.f, y, 1.0f);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex3f(x+4.f, y, -1.0f);
        }

        glEnd();
        //END CYLINDER 2

       //BEGIN CUBE
    	glBegin(GL_QUADS);

        glColor3f(0.442f, 0.7654f, 0.3f);

        glVertex3f(-5.f, 2.f, -1.f);
        glVertex3f(-3.f, 2.f, -1.f);
        glVertex3f(-3.f, 0.f, -1.f);
        glVertex3f(-5.f, 0.f, -1.f);

        glColor3f(0.1f, 0.2f, 0.653f);

        glVertex3f(-5.f, 2.f, 1.f);
        glVertex3f(-3.f, 2.f, 1.f);
        glVertex3f(-3.f, 0.f, 1.f);
        glVertex3f(-5.f, 0.f, 1.f);

        glColor3f(0.63f, 0.24f, 0.f);

        glVertex3f(-5.f, 2.f, 1.f);
        glVertex3f(-5.f, 2.f, -1.f);
        glVertex3f(-5.f, 0.f, -1.f);
        glVertex3f(-5.f, 0.f, 1.f);

        glColor3f(0.21f, 0.83f, 0.2f);

        glVertex3f(-3.f, 2.f, -1.f);
        glVertex3f(-3.f, 2.f, 1.f);
        glVertex3f(-3.f, 0.f, 1.f);
        glVertex3f(-3.f, 0.f, -1.f);

        glColor3f(0.21421f, 0.2f, 0.643f);

        glVertex3f(-5.f, 0.f, -1.f);
        glVertex3f(-3.f, 0.f, -1.f);
        glVertex3f(-3.f, 0.f, 1.f);
        glVertex3f(-5.f, 0.f, 1.f);

        glColor3f(0.865f, 0.64f, 0.33f);

        glVertex3f(-5.f, 2.f, -1.f);
        glVertex3f(-3.f, 2.f, -1.f);
        glVertex3f(-3.f, 2.f, 1.f);
        glVertex3f(-5.f, 2.f, 1.f);

        glEnd();
       //END CUBE


        //BEGIN CONE
        glBegin(GL_TRIANGLE_FAN);

        glColor3f(1.f, 1.f, 1.f);
        glVertex3f(0.f, 2.2f, -1.f);

        for (int i=0;i<=360;i+=12)
        {
            float rad = (float)i * (3.14f / 180.f);
            glVertex3f(cosf(rad), sinf(rad) + 2.2f , -1.f);
        }


        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 3.f, 1.f);  
        for (int i = 0; i <= 360; i += 12)
        {
            float rad = (float)i * (3.14f / 180.f);
            float x = cosf(rad);
            float y = sinf(rad) + 2.2f;
            glColor3f(0.4f, 0.2f, 0.7f);
            glVertex3f(x, y, -1.f); 
        }
        glEnd();
       //END CONE
	   

        glfwSwapBuffers(window);
        glfwPollEvents();


        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_C))
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        if (glfwGetKey(window, GLFW_KEY_Y))
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    delete cx;
    delete cy;
    return 0;
}
