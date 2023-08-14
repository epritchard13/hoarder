#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <string.h>  // Include the string.h header for strlen
#include <math.h>
#include <stdlib.h>

#define voxel_width 10;
#define voxel_height 10;
#define voxel_length 10;


typedef struct voxel{
    unsigned char one_x;
    unsigned char one_y;
    unsigned char one_z;

    unsigned char two_x;
    unsigned char two_y;
    unsigned char two_z;

    unsigned char thr_x;
    unsigned char thr_y;
    unsigned char thr_z;

    unsigned char fou_x;
    unsigned char fou_y;
    unsigned char fou_z;

    unsigned char fiv_x;
    unsigned char fiv_y;
    unsigned char fiv_z;

    unsigned char six_x;
    unsigned char six_y;
    unsigned char six_z;

    unsigned char sev_x;
    unsigned char sev_y;
    unsigned char sev_z;

    unsigned char eig_x;
    unsigned char eig_y;
    unsigned char eig_z;
}voxel;

typedef struct camera{
    int x;
    int y;
    int z;
    unsigned char v;
    unsigned char h;

    signed char v_adj;
    signed char h_adj_x;
    signed char h_adj_y;
    
}camera;



double arctan(int numerator, int denominator) {
    double x = (double)numerator / denominator;
    return atan(x);
}





int main() {
    Display *display;
    display = XOpenDisplay(NULL);

    Window root = DefaultRootWindow(display);
    Window window = XCreateSimpleWindow(display, root, 0, 0, 800, 600, 0, 0, 0);
    XWindowAttributes windowAttributes;
    int screen = DefaultScreen(display);
    XSelectInput(display, window, PointerMotionMask | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask);
    XMapWindow(display, window);
    Pixmap blankBitmap;
    XColor dummyColor;
    char data[1] = {0};
    blankBitmap = XCreateBitmapFromData(display, window, data, 1, 1);
    Cursor invisibleCursor = XCreatePixmapCursor(display, blankBitmap, blankBitmap, &dummyColor, &dummyColor, 0, 0); // Create a blank (invisible) cursor
    XDefineCursor(display, window, invisibleCursor); // Set the invisible cursor for the window
    GC gc;
    XGCValues values;
    gc = XCreateGC(display, window, 0, &values);
    XSetForeground(display, gc, WhitePixel(display, screen));


    int voxel_x_offset = 100;
    int voxel_y_offset = 0;
    int voxel_z_offset = 100;

    //initialize the jaunt
    void *working_ptr = NULL;
    working_ptr = malloc(sizeof(voxel));
    ((voxel*)working_ptr)->one_x = 0;
    ((voxel*)working_ptr)->one_y = 0;
    ((voxel*)working_ptr)->one_z = 0;
    ((voxel*)working_ptr)->two_x = voxel_width;
    ((voxel*)working_ptr)->two_y = 0;
    ((voxel*)working_ptr)->two_z = 0;
    ((voxel*)working_ptr)->thr_x = voxel_width;
    ((voxel*)working_ptr)->thr_y = 0;
    ((voxel*)working_ptr)->thr_z = voxel_height;
    ((voxel*)working_ptr)->fou_x = 0;
    ((voxel*)working_ptr)->fou_y = 0;
    ((voxel*)working_ptr)->fou_z = voxel_height;
    ((voxel*)working_ptr)->fiv_x = 0;
    ((voxel*)working_ptr)->fiv_y = voxel_length;
    ((voxel*)working_ptr)->fiv_z = 0;
    ((voxel*)working_ptr)->six_x = voxel_width;
    ((voxel*)working_ptr)->six_y = voxel_length;
    ((voxel*)working_ptr)->six_z = 0;
    ((voxel*)working_ptr)->sev_x = voxel_width;
    ((voxel*)working_ptr)->sev_y = voxel_length;
    ((voxel*)working_ptr)->sev_z = voxel_height;
    ((voxel*)working_ptr)->eig_x = 0;
    ((voxel*)working_ptr)->eig_y = voxel_length;
    ((voxel*)working_ptr)->eig_z = voxel_height;


    void * camera_ptr = NULL;
    camera_ptr = malloc(sizeof(camera));
    ((camera*)camera_ptr)->x = 0;
    ((camera*)camera_ptr)->y = 0;
    ((camera*)camera_ptr)->z = 0;
    ((camera*)camera_ptr)->v = 0;
    ((camera*)camera_ptr)->h = 0;
    ((camera*)camera_ptr)->v_adj = 0;
    ((camera*)camera_ptr)->h_adj_x = 0;
    ((camera*)camera_ptr)->h_adj_y = 0;



    int windowWidth = 0;
    int windowHeight = 0;

    int h_angle = 0;
    int v_angle = 0;

    int arrowVertexX;
    int arrowVertexY;

    while (1) {
        XEvent event;
        XNextEvent(display, &event);

        // Grab the keyboard input focus
        XGrabKeyboard(display, root, False, GrabModeAsync, GrabModeAsync, CurrentTime);
        
        int x = event.xmotion.x;
        int y = event.xmotion.y;
        XGetWindowAttributes(display, window, &windowAttributes);
        windowWidth = windowAttributes.width;
        windowHeight = windowAttributes.height;
                

        h_angle = 255 * x / windowWidth;
        v_angle = 255 * y / windowHeight;


        ((camera*)camera_ptr)->v = h_angle;
        ((camera*)camera_ptr)->h = v_angle;

        ((camera*)camera_ptr)->v_adj = abs(v_angle - 127);
        ((camera*)camera_ptr)->h_adj_x = abs(h_angle - 127);
        ((camera*)camera_ptr)->h_adj_y = 128 - abs(h_angle - 127);



        switch (event.type) {
            case MotionNotify: {
                
                
                
                
                

                
                
                XClearWindow(display, window);


                //front face top
                XDrawLine(display,window,gc,((voxel*)working_ptr)->one_x+voxel_x_offset,((voxel*)working_ptr)->one_z+voxel_z_offset,((voxel*)working_ptr)->two_x+voxel_x_offset,((voxel*)working_ptr)->two_z+voxel_z_offset);
                //front face bottom
                //XDrawLine(display,window,gc,((voxel*)working_ptr)->fou_x+voxel_x_offset,((voxel*)working_ptr)->fou_z+voxel_z_offset,((voxel*)working_ptr)->thr_x+voxel_x_offset,((voxel*)working_ptr)->thr_z+voxel_z_offset);
                //front face left
                XDrawLine(display,window,gc,((voxel*)working_ptr)->one_x+voxel_x_offset,((voxel*)working_ptr)->one_z+voxel_z_offset,((voxel*)working_ptr)->fou_x+voxel_x_offset,((voxel*)working_ptr)->fou_z+voxel_z_offset);
                //front face right
                //XDrawLine(display,window,gc,((voxel*)working_ptr)->two_x+voxel_x_offset,((voxel*)working_ptr)->two_z+voxel_z_offset,((voxel*)working_ptr)->thr_x+voxel_x_offset,((voxel*)working_ptr)->thr_z+voxel_z_offset);

                //origin point in point 1.
                int separation_x = abs(((camera*)camera_ptr)->x - (((voxel*)working_ptr)->one_x+voxel_x_offset));
                int separation_z = abs(((camera*)camera_ptr)->y - (((voxel*)working_ptr)->one_z+voxel_z_offset));

                double at = arctan(separation_x, separation_z);

                arrowVertexX = ((camera*)camera_ptr)->x+ (((camera*)camera_ptr)->v-128);
                arrowVertexY = ((camera*)camera_ptr)->y+(((camera*)camera_ptr)->h-128);
                //XDrawPoint(display, window, gc, ((camera*)camera_ptr)->x, ((camera*)camera_ptr)->y);


                //draw direction arrow
                XDrawLine(display, window, gc, ((camera*)camera_ptr)->x, ((camera*)camera_ptr)->y,  arrowVertexX,  arrowVertexY);
                if(((camera*)camera_ptr)->y> arrowVertexY){
                    XDrawLine(display, window, gc, arrowVertexX-5, arrowVertexY-5,  arrowVertexX+5,  arrowVertexY-5);
                }else{
                    XDrawLine(display, window, gc, arrowVertexX-5, arrowVertexY+5,  arrowVertexX+5,  arrowVertexY+5);
                }

                if(((camera*)camera_ptr)->x> arrowVertexX){
                    XDrawLine(display, window, gc, arrowVertexX-5, arrowVertexY+5,  arrowVertexX-5,  arrowVertexY-5);
                }else{
                    XDrawLine(display, window, gc, arrowVertexX+5, arrowVertexY+5,  arrowVertexX+5,  arrowVertexY-5);
                }
                

                


                
                //XDrawRectangle(display, window, gc, 2000 - x, 1000 - y, width, height);


                //XDrawLine(display,window,gc,0,0,2000 - x,1000 - y);
                //XDrawLine(display,window,gc,2510,0,2000 - x+width,1000 - y);
                //XDrawLine(display,window,gc,0,1038,2000 - x,1000 - y+height);
                //XDrawLine(display,window,gc,2510,1038,2000 - x+width,1000 - y+height);


                //printf("Arrowhead coordinates: (%d, %d)\n", arrowVertexX, arrowVertexY);
                printf("Distance to origin point: (%d, %d)\n", separation_x, separation_z);
                //printf("Cursor coordinates: (%d, %d)\n", ((camera*)camera_ptr)->h_adj_x-64, ((camera*)camera_ptr)->h_adj_y-64);
                //printf("Looking At: (%d, %d)\n", h_angle, v_angle);
                printf("camera angle x, y: (%d, %d, %f)\n", ((camera*)camera_ptr)->h_adj_x,((camera*)camera_ptr)->h_adj_y, at);
                float viewMatrix[16];

                XFlush(display);
                break;
            }
            case KeyPress: {
                char buffer[10];
                KeySym key;
                XLookupString(&event.xkey, buffer, sizeof(buffer), &key, NULL);
                

                if (key == XK_w) {
                    ((camera*)camera_ptr)->x = arrowVertexX;
                    ((camera*)camera_ptr)->y = arrowVertexY;
                    break;
                }else if (key == XK_a) {
                    //printf("The 'a' key was pressed!\n");
                    break;
                } else if (key == XK_s) {
                    ((camera*)camera_ptr)->x = ((camera*)camera_ptr)->x + (((camera*)camera_ptr)->x-arrowVertexX);
                    ((camera*)camera_ptr)->y = ((camera*)camera_ptr)->y + (((camera*)camera_ptr)->y-arrowVertexY);
                    break;
                } else if (key == XK_d) {
                    //printf("The 'd' key was pressed!\n");
                    break;
                } else if (key == XK_space) {
                    //printf("The space key was pressed!\n");
                    break;
                } else if (key == XK_Shift_L) {
                    //printf("The left shift key was pressed!\n");
                    break;
                }
                break;
            }
            case KeyRelease: {
                break;
            }
            case MapNotify:{
                break;
            }
                
            case ConfigureNotify: {
                break;
            }
        }
    }

    XFreeCursor(display, invisibleCursor);
    XCloseDisplay(display);
    return 0;
}
