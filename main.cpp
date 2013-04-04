#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glu.h>
#include <GL/gl.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <iostream>

#define ANGLE_ROTATION 0.2
#define CALL_TIMER     30
#define TEX_IMAGE_NAME "D:/workspace/Display_List/cube.jpg"

float WinWidth       = 700.0;
float WinHeight      = 700.0;

GLuint	texture[1];		// Место для одной текстуры

GLuint  box;            // Память для списка отображения box (коробка)
GLuint  top;            // Память для второго списка отображения top (крышка)
GLuint  xloop;  // Цикл для оси x
GLuint  yloop;  // Цикл для оси y

static GLfloat boxcol[5][3]=    //Массив для цветов коробки
{
//Яркие: Красный, Оранжевый, Желтый, Зеленый, Голубой
{1.0f,0.0f,0.0f},{1.0f,0.5f,0.0f},{1.0f,1.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,1.0f,1.0f}
};

static GLfloat topcol[5][3]=    //Массив для цветов верха
{
//Темные: Красный, Оранжевый, Желтый, Зеленый, Голубой
{.5f,0.0f,0.0f},{0.5f,0.25f,0.0f},{0.5f,0.5f,0.0f},{0.0f,0.5f,0.0f},{0.0f,0.5f,0.5f}
};

GLfloat	x_rotation = 50.;
GLfloat	y_rotation = 50.;
GLfloat	z_rotation = 50.;
GLfloat xrot;
GLfloat yrot;

GLvoid BuildLists()     //создаем список отображения
{
    box=glGenLists(2);      //создаем два списка
    glNewList(box,GL_COMPILE);      // Новый откомпилированный список отображения box

    glBegin(GL_QUADS);      // Начинаем рисование четырехугольников (quads)
                            // Нижняя поверхность
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);        // Верхний правый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);        // Верхний левый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f( 1.0f, -1.0f, 1.0f);        // Нижний левый угол текстуры и четырехугольник
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);        // Нижний правый угол текстуры и четырехугольник
                                // Передняя поверхность
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);        // Нижний левый угол текстуры и четырехугольник
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( 1.0f, -1.0f, 1.0f);        // Нижний правый угол текстуры и четырехугольник
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 1.0f, 1.0f, 1.0f);        // Верхний правый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);        // Верхний левый угол текстуры и четырехугольник
                                // Задняя поверхность
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);        // Нижний правый угол текстуры и четырехугольник
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);        // Верхний правый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f( 1.0f, 1.0f, -1.0f);        // Верхний левый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);        // Нижний левый угол текстуры и четырехугольник
                                // Правая поверхность
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);        // Нижний правый угол текстуры и четырехугольник
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( 1.0f, 1.0f, -1.0f);        // Верхний правый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f( 1.0f, 1.0f, 1.0f);        // Верхний левый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f( 1.0f, -1.0f, 1.0f);        // Нижний левый угол текстуры и четырехугольник
                                // Левая поверхность
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);        // Нижний левый угол текстуры и четырехугольник
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);        // Нижний правый угол текстуры и четырехугольник
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);        // Верхний правый угол текстуры и четырехугольник
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);        // Верхний левый угол текстуры и четырехугольник
    glEnd();                        // Закончили рисование четырехугольников

    glEndList(); // Закончили создание списка box

    top=box+1; // Значение top это значение box + 1

    glNewList(top,GL_COMPILE);// Новый откомпилированный список отображения 'top'
    glBegin(GL_QUADS);      // Начинаем рисование четырехугольника
                            // Верхняя поверхность
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);        // Верхний левый угол текстуры и четырехугольник
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);        // Нижний левый угол текстуры и четырехугольник
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);        // Нижний правый угол текстуры и четырехугольник
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, -1.0f);        // Верхний правый угол текстуры и четырехугольник
    glEnd();                // Заканчиваем рисование четырехугольника
    glEndList();            // Закончили создание списка отображения 'top'
}

//-----------------------------------------------------------------------------
//Таймер вращения
static void timer_rotation(int value = 0)
{
    x_rotation += ANGLE_ROTATION;
    y_rotation += ANGLE_ROTATION;
    z_rotation += ANGLE_ROTATION;

  /* send redisplay event */
  glutPostRedisplay();

  /* call this function again in 30 milliseconds */
  glutTimerFunc(CALL_TIMER, timer_rotation, 0);
}

//-----------------------------------------------------------------------------
//Функция загрузки изображения текстуры
void Load_Tex_Image()
{
    int width, height, bpp;

    ilLoad(IL_JPG, reinterpret_cast<const ILstring>(TEX_IMAGE_NAME));
    int err = ilGetError();                          // Считывание кода ошибки
    if (err != IL_NO_ERROR)
    {
        const char* strError = iluErrorString(err);  // Считываем строку ошибки
        std::cout << "Error load texture image: " << strError << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Load texture image completed!" << std::endl;
        width  = ilGetInteger(IL_IMAGE_WIDTH);
        height = ilGetInteger(IL_IMAGE_HEIGHT);
        bpp    = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
        std::cout << "width:  "<< width << std::endl << "height: "
                  << height << std::endl << "bpp:    " << bpp << std::endl;
    }

    unsigned char* data = ilGetData();
    unsigned int type;

    switch (bpp) {
    case 1:
      type  = GL_RGB8;
      break;
    case 3:
      type = GL_RGB;
      break;
    case 4:
      type = GL_RGBA;
      break;
    }
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
    GL_RGB, GL_UNSIGNED_BYTE, data);
}

//-----------------------------------------------------------------------------
//Функция инициализации
void init()
{
    //Инициализация DevIL
    ilInit();
    iluInit();
    ilutInit();

    Load_Tex_Image();

    BuildLists();

    glEnable(GL_TEXTURE_2D);
    glViewport( 0, 0, WinWidth, WinHeight );
    glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHT0); // Быстрое простое освещение
                            // (устанавливает в качестве источника освещения Light0)
   // glEnable(GL_LIGHTING);  // Включает освещение
    glEnable(GL_COLOR_MATERIAL);    // Включает раскрашивание материала

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45.0f, (GLfloat)WinWidth/(GLfloat)WinHeight, 0.1f, 100.0f );
    glMatrixMode(GL_MODELVIEW);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Изящная коррекция перспективы
    glLoadIdentity();
}


//-----------------------------------------------------------------------------
//Функция рисования сцены
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Очищаем экран и буфер глубины
    glBindTexture(GL_TEXTURE_2D, texture[0]);               // Выбираем текстуру



    for (yloop = 1;yloop < 6; yloop++)                           // Цикл по оси Y
    {
        for (xloop=0;xloop< yloop;xloop++)              // Цикл по оси X
        {
            glLoadIdentity();                       // Очистка вида
            glTranslatef(1.4f+(float(xloop)*2.8f)-(float(yloop)*1.4f),
                    ((6.0f-float(yloop))*2.4f)-7.0f,-20.0f);
            glRotatef(45.0f-(2.0f*yloop)+xrot,1.0f,0.0f,0.0f);      // Наклонять кубы вверх и вниз
            glRotatef(45.0f+yrot,0.0f,1.0f,0.0f);                   // Вращать кубы вправо и влево
            //glRotatef(x_rotation,1.0f,0.0f,0.0f);		// Вращение по оси X
            //glRotatef(y_rotation,0.0f,1.0f,0.0f);		// Вращение по оси Y
            glColor3fv(boxcol[yloop-1]);            // Выбор цвета коробки
            glCallList(box);                        // Рисуем коробку
            glColor3fv(topcol[yloop-1]);            // Выбор цвета верха
            glCallList(top);                        // Рисуем крышку
        }
    }
    glFlush();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WinWidth, WinHeight);
    glutInitWindowPosition(100, 70);
    glutCreateWindow("Texture_test");
    glutDisplayFunc(display);
    init();
    timer_rotation();
    glutMainLoop();
}
