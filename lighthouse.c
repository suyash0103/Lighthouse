#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>

int horizon_x1, horizon_y1, horizon_x2, horizon_y2, horizon_x3, horizon_y3, horizon_x4, horizon_y4;
int sea_x1, sea_y1, sea_x2, sea_y2, sea_x3, sea_y3, sea_x4, sea_y4;
int beach_x1, beach_y1, beach_x2, beach_y2, beach_x3, beach_y3, beach_x4, beach_y4;

void myInit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500,0, 500);
}

void draw_pixel(int x, int y, float r, float g, float b)
{
    glColor3f(r, g, b);
	glBegin(GL_POINTS);
	glVertex3f(x, y,0);
	glEnd();
}

/*void draw_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}*/

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

void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b)
{
    int le[500],re[500];
    int i,y;
    for(i=0;i<500;i++)
    {
        le[i]=1000;
        re[i]=0;
    }
    edgedetect(x1,y1,x2,y2,le,re);
    edgedetect(x2,y2,x3,y3,le,re);
    edgedetect(x3,y3,x4,y4,le,re);
    edgedetect(x4,y4,x1,y1,le,re);
    for(y=0;y<500;y++)        // for every scan line with value y
    {
        if(le[y]<=re[y])
        {
            for(i=le[y]+1;i<re[y];i++)
            {
                draw_pixel(i, y, r, g, b);
            }
        }
    }
}

void draw_line(int x1, int x2, int y1, int y2, float r, float g, float b)
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
		draw_pixel(x, y, r, g, b);
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
			draw_pixel(x, y, r, g, b);
		}
	}
	else
    {
		draw_pixel(x, y, r, g, b);
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
			draw_pixel(x, y, r, g, b);
		}
	}
}

void myDisplay()
{
	scanfill(horizon_x1, horizon_y1, horizon_x2, horizon_y2, horizon_x4, horizon_y4, horizon_x3, horizon_y3, 0.0, 99, 1);
    scanfill(sea_x1, sea_y1, sea_x2, sea_y2, sea_x3, sea_y3, sea_x4, sea_y4, 0.0, 0.0, 100.0);
    scanfill(beach_x1, beach_y1, beach_x2, beach_y2, beach_x3, beach_y3, beach_x4, beach_y4, .9, .33, .19);

	glFlush();
}

void main(int argc, char **argv)
{
	horizon_x1 = 0;
	horizon_y1 = 500;
	horizon_x2 = 500;
	horizon_y2 = 500;
	horizon_x3 = 0;
	horizon_y3 = 440;
	horizon_x4 = 500;
	horizon_y4 = 435;

    sea_x1 = 0;
    sea_y1 = 0;
    sea_x2 = 0;
    sea_y2 = 440;
    sea_x3 = 250;
    sea_y3 = 437.5;
    sea_x4 = 200;
    sea_y4 = 0;

    beach_x1 = 250;
    beach_y1 = 437.5;
    beach_x2 = 270;
    beach_y2 = 437.5;
    beach_x3 = 250;
    beach_y3 = 0;
    beach_x4 = 200;
    beach_y4 = 0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's Line Drawing");
    glutFullScreen();
    myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}
