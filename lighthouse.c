#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>

int horizon_x1, horizon_y1, horizon_x2, horizon_y2, horizon_x3, horizon_y3, horizon_x4, horizon_y4;
int sea_x1, sea_y1, sea_x2, sea_y2, sea_x3, sea_y3, sea_x4, sea_y4;
int beach_x1, beach_y1, beach_x2, beach_y2, beach_x3, beach_y3, beach_x4, beach_y4;
int green1_x1, green1_y1, green1_x2, green1_y2, green1_x3, green1_y3, green1_x4, green1_y4;
int green2_x1, green2_y1, green2_x2, green2_y2, green2_x3, green2_y3, green2_x4, green2_y4;
int road_x1, road_y1, road_x2, road_y2, road_x3, road_y3, road_x4, road_y4;
int l1_x, l1_y, l2_x, l2_y, l3_x, l3_y, l4_x, l4_y, l5_x, l5_y, l6_x, l6_y;
int p1_x, p1_y, p2_x, p2_y, p3_x, p3_y, p4_x, p4_y;

float scale_x=2.736;
float scale_y=1.44;

void myInit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1368, 0, 720);
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
    if((y2 - y1) < 0)    // if second point is below first point interchange them
    {
        temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
    }
    if((y2 - y1) != 0)      // if denominator is zero we can't find slope
        mx = (x2 - x1)/(y2 - y1);
    else
        mx = x2 - x1;    // y2-y1=0 implies line is horizontal
    x = x1;
    for(i = y1; i < y2; i++)        // starting from x1,y1 add slope mx to x
    {                                  // and round it to find the next point on the                                        // line. For that particular scan line i
        if(x < le[i])         // insert the x value into either le or re.
            le[i] = x; // Initially both le and re will contain same value...
        if(x > re[i])         // in the next time for the other edge
            re[i] = x; // either le or re will change
        x += mx;            // NOTE: le and re are integer arrays and x
    }                          // is float so automatic type conversion.
}

void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b)
{
    int le[1080],re[1080];
    int i, y;
    for(i=0;i<1080;i++)
    {
        le[i]=1000;
        re[i]=0;
    }

    edgedetect(x1,y1,x2,y2,le,re);
    edgedetect(x2,y2,x3,y3,le,re);
    edgedetect(x3,y3,x4,y4,le,re);
    edgedetect(x4,y4,x1,y1,le,re);
    for(y=0;y<1080;y++)
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
	scanfill(horizon_x1, horizon_y1, horizon_x2, horizon_y2, horizon_x4, horizon_y4, horizon_x3, horizon_y3, 0.0, 0.75, 1.0);
    scanfill(sea_x1, sea_y1, sea_x2, sea_y2, sea_x3, sea_y3, sea_x4, sea_y4, 0.0, 0.0, 1.0);
    scanfill(beach_x1, beach_y1, beach_x2, beach_y2, beach_x3,  beach_y3, beach_x4, beach_y4, .661, .598, .302);
    scanfill(green1_x1, green1_y1, green1_x2, green1_y2, green1_x3, green1_y3, green1_x4, green1_y4, 0.0, 0.49, 0.0);
    scanfill(green2_x1, green2_y1, green2_x2, green2_y2, green2_x3, green2_y3, green2_x4, green2_y4, 0.0, 0.49, 0.0);
    scanfill(road_x1, road_y1, road_x2, road_y2, road_x3, road_y3, road_x4, road_y4, 0.41, 0.41, 0.41);

    // Block 1
    scanfill(l1_x, l1_y, l2_x, l2_y, l3_x, l3_y, l4_x, l4_y, 1.0, 0.0, 0.0);
    scanfill(l5_x, l5_y, l1_x, l1_y, l4_x, l4_y, l6_x, l6_y, 1.0, 0.0, 0.0);

    // Block 2
    l4_y = l1_y;
    l3_y = l2_y;
    l6_y = l5_y;
    l1_y += 80;
    l2_y += 80;
    l5_y += 80;
    scanfill(l1_x, l1_y, l2_x, l2_y, l3_x, l3_y, l4_x, l4_y, 1.0, 1.0, 1.0);
    scanfill(l5_x, l5_y, l1_x, l1_y, l4_x, l4_y, l6_x, l6_y, 1.0, 1.0, 1.0);

    // Block 3
    l4_y = l1_y;
    l3_y = l2_y;
    l6_y = l5_y;
    l1_y += 80;
    l2_y += 80;
    l5_y += 80;
    scanfill(l1_x, l1_y, l2_x, l2_y, l3_x, l3_y, l4_x, l4_y, 1.0, 0.0, 0.0);
    scanfill(l5_x, l5_y, l1_x, l1_y, l4_x, l4_y, l6_x, l6_y, 1.0, 0.0, 0.0);

    // Block 4
    l4_y = l1_y;
    l3_y = l2_y;
    l6_y = l5_y;
    l1_y += 80;
    l2_y += 80;
    l5_y += 80;
    scanfill(l1_x, l1_y, l2_x, l2_y, l3_x, l3_y, l4_x, l4_y, 1.0, 1.0, 1.0);
    scanfill(l5_x, l5_y, l1_x, l1_y, l4_x, l4_y, l6_x, l6_y, 1.0, 1.0, 1.0);

    // Block 5
    l4_y = l1_y;
    l3_y = l2_y;
    l6_y = l5_y;
    l1_y += 80;
    l2_y += 80;
    l5_y += 80;
    scanfill(l1_x, l1_y, l2_x, l2_y, l3_x, l3_y, l4_x, l4_y, 1.0, 0.0, 0.0);
    scanfill(l5_x, l5_y, l1_x, l1_y, l4_x, l4_y, l6_x, l6_y, 1.0, 0.0, 0.0);

    // Line for 3D Effect
    draw_line(l1_x, l1_x, l1_y, 0, 0.41, 0.41, 0.41);

    // Ceiling
    l4_y = l1_y;
    l3_y = l2_y;
    l6_y = l5_y;
    l1_x -= 5;
    l1_y += 10;
    l5_x -= 5;
    l5_y += 10;
    l4_x -= 5;
    l2_x += 5;
    l2_y += 10;
    l3_x += 5;
    l6_x -= 5;
    scanfill(l1_x, l1_y, l2_x, l2_y, l3_x, l3_y, l4_x, l4_y, 1.0, 1.0, 1.0);
    scanfill(l5_x, l5_y, l1_x, l1_y, l4_x, l4_y, l6_x, l6_y, 1.0, 1.0, 1.0);
    scanfill(l5_x, l5_y, l5_x + 85, l5_y + 10, l2_x, l2_y, l1_x, l1_y, 1.0, 1.0, 1.0);

    // Pillar
    scanfill(p1_x, p1_y, p2_x, p2_y, p3_x, p3_y, p4_x, p4_y, 0.0, 0.75, 1.0);

	glFlush();
}

void main(int argc, char **argv)
{
	horizon_x1 = 0;
	horizon_y1 = 500*scale_y;
	horizon_x2 = 500*scale_x;
	horizon_y2 = 500*scale_y;
	horizon_x3 = 0;
	horizon_y3 = 440*scale_y;
	horizon_x4 = 500*scale_x;
	horizon_y4 = 435*scale_y;

    sea_x1 = 0;
    sea_y1 = 0;
    sea_x2 = 0;
    sea_y2 = 440*scale_y;
    sea_x3 = 260*scale_x;
    sea_y3 = 437.5*scale_y;
    sea_x4 = 210*scale_x;
    sea_y4 = 0;

    beach_x1 = 259*scale_x;
    beach_y1 = 437.5*scale_y;
    beach_x2 = 272.5*scale_x;
    beach_y2 = 437.5*scale_y;
    beach_x3 = 260*scale_x;
    beach_y3 = 0;
    beach_x4 = 209*scale_x;
    beach_y4 = 0;

    green1_x1 = 271.5*scale_x;
    green1_y1 = 437.5*scale_y;
    green1_x2 = 335*scale_x;
    green1_y2 = 437.5*scale_y;
    green1_x3 = 322.5*scale_x;
    green1_y3 = 0;
    green1_x4 = 259*scale_x;
    green1_y4 = 0;


    road_x1 = 314*scale_x;
    road_y1 = 437.5*scale_y;
    road_x2 = 320*scale_x;
    road_y2 = 437.5*scale_y;
    road_x3 = 325*scale_x;
    road_y3 = 0;
    road_x4 = 301.5*scale_x;
    road_y4 = 0;

    green2_x1 = 319*scale_x;
    green2_y1 = 437.5*scale_y;
    green2_x2 = 510*scale_x;
    green2_y2 = 437.5*scale_y;
    green2_x3 = 510*scale_x;
    green2_y3 = 0;
    green2_x4 = 300.5*scale_x;
    green2_y4 = 0;

    l1_x = 380 + 600;
    l1_y = 10;
    l2_x = (470 - 5) + 600;
    l2_y = 20;
    l3_x = (470 - 5) + 600;
    l3_y = 0;
    l4_x = 380 + 600;
    l4_y = 0;
    l5_x = (370 - 10) + 600;
    l5_y = 25;
    l6_x = (370 - 10) + 600;
    l6_y = 0;

    p1_x = 985;
    p1_y = 410;
    p2_x = 1035;
    p2_y = 410;
    p3_x = 1035;
    p3_y = 350;
    p4_x = 985;
    p4_y = 350;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(1368, 720);
	glutInitWindowPosition(0, 0);
    glutCreateWindow("Lighthouse");
    glutFullScreen();
    myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}
