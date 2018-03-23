#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>

int x1, y1, x2, y2;

void myInit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-250, 250,-250, 250);
}

void draw_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void draw_line(int x1, int x2, int y1, int y2)
{
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;

	dx = x2-x1;
	dy = y2-y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	if (dx > dy)
    {
		draw_pixel(x, y);
		e = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++)
		{
			if (e >= 0)
			{
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			draw_pixel(x, y);
		}
	}
	else
    {
		draw_pixel(x, y);
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++)
		{
			if (e >= 0)
			{
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}
}

void horizon()
{
    /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3d(94, 94, 94);
        glVertex2f(-250, 250);
        glColor3d(94, 94, 94);
        glVertex2f(250, 250);
        glColor3d(94, 94, 94);
        glVertex2f(-250, 210);
        glColor3d(94, 94, 94);
        glVertex2f(250, 200);
    glEnd();
    glutSwapBuffers();*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3d(94,94,94);
        glVertex2d(-100,-100);
        glColor3d(94,94,94);
        glVertex2d(-100,100);
        glColor3d(94,94,94);
        glVertex2d(100,-100);
        glColor3d(94,94,94);
        glVertex2d(100,100);
    glEnd();
    glutSwapBuffers();
}

void myDisplay()
{
	draw_line(-260, 250, 250, 250);
	draw_line(-260, -250, 250, 210);
	draw_line(-260, 250, 210, 200);
	draw_line(250, 250, 250, 210);
	//horizon();
	glFlush();
}

void main(int argc, char **argv)
{
	//printf( "Enter (x1, y1, x2, y2)\n");
	//scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    x1 = -250;
    y1 = 210;
    x2 = 250;
    y2 = 200;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's Line Drawing");
    glutFullScreen();
    myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}
