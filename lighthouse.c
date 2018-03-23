#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>

int x1, y1, x2, y2, x3, y3, x4, y4;

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

void edgedetect(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,int *le,int *re)
{
            float mx,x,temp;
            int i;
            if((y2-y1)<0)    // if second point is below first point interchange them
            {
              temp=x1;x1=x2;x2=temp;
              temp=y1;y1=y2;y2=temp;
            }
              if((y2-y1)!=0)      // if denominator is zero we can't find slope
                        mx=(x2-x1)/(y2-y1);
            else
                        mx=x2-x1;    // y2-y1=0 implies line is horizontal
            x=x1;
            for(i=y1;i<y2;i++)        // starting from x1,y1 add slope mx to x
            {                                  // and round it to find the next point on the
                                                // line. For that particular scan line i
                        if(x<le[i])         // insert the x value into either le or re.
                                    le[i]=x; // Initially both le and re will contain same
                                                // value...
                        if(x>re[i])         // in the next time for the other edge
                                    re[i]=x; // either le or re will change
                        x+=mx;            // NOTE: le and re are integer arrays and x
            }                                  // is float so automatic type conversion.
}

void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
            int le[500],re[500];
            int i,y;
            for(i=0;i<500;i++)   // initialize le and re array values
            {
                        le[i]=500;
                        re[i]=0;
            }
            edgedetect(x1,y1,x2,y2,le,re);    // call edge detect four times
            edgedetect(x2,y2,x3,y3,le,re);    // once for each edge.
            edgedetect(x3,y3,x4,y4,le,re);
            edgedetect(x4,y4,x1,y1,le,re);
for(y=0;y<500;y++)        // for every scan line with value y
{
           if(le[y]<=re[y])            // refer to le and re arrays to see if a part
                        for(i=le[y]+1;i<re[y];i++) // of the scanline is inside polygon
                                    draw_pixel(i,y);       // if so draw a horizontal line from
}                                                              // left edge to right edge
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

void myDisplay()
{
	draw_line(x1, x2, y1, y2);
	draw_line(x1, x3, y1, y3);
	draw_line(x3, x4, y3, y4);
	draw_line(x2, x4, y2, y4);
	glFlush();
}

void main(int argc, char **argv)
{
	x1 = -260;
	y1 = 250;
	x2 = 250;
	y2 = 250;
	x3 = -260;
	y3 = 210;
	x4 = 250;
	y4 = 200;

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
