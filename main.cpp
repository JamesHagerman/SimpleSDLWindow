#include "SDL.h"

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/glu.h>
	#include <GL/gl.h>
    #include <GL/glext.h>
    #include <GL/glx.h>
    #include <GL/glxext.h>
    #define glXGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)x)
#endif

#include <iostream>
#include <math.h>
#include <time.h>
#include <unistd.h>

SDL_Surface *screen;
SDL_Event event;

// Set up some global variables to point to GLSL in Linux:
#if !defined(__APPLE__) && !defined(_WIN32)
	PFNGLCREATEPROGRAMOBJECTARBPROC     glCreateProgramObjectARB = NULL;
	PFNGLCREATESHADEROBJECTARBPROC      glCreateShaderObjectARB = NULL;
	PFNGLSHADERSOURCEARBPROC            glShaderSourceARB = NULL;
	PFNGLCOMPILESHADERARBPROC           glCompileShaderARB = NULL;
	PFNGLGETOBJECTPARAMETERIVARBPROC    glGetObjectParameterivARB = NULL;
	PFNGLATTACHOBJECTARBPROC            glAttachObjectARB = NULL;
	PFNGLGETINFOLOGARBPROC              glGetInfoLogARB = NULL;
	PFNGLLINKPROGRAMARBPROC             glLinkProgramARB = NULL;
	PFNGLUSEPROGRAMOBJECTARBPROC        glUseProgramObjectARB = NULL;
	PFNGLGETUNIFORMLOCATIONARBPROC      glGetUniformLocationARB = NULL;
	PFNGLUNIFORM1FARBPROC               glUniform1f = NULL;
#endif

using namespace std;

// Some usefull settings and functions for OpenGL work:
static GLboolean should_rotate = GL_TRUE;
static void quit_tutorial( int code )
{
    /*
     * Quit SDL so we can release the fullscreen
     * mode and restore the previous video settings,
     * etc.
     */
    SDL_Quit( );

    /* Exit program. */
    exit( code );
}

// Break the keyboard input handeling out into a function call:
static void handle_key_down( SDL_keysym* keysym )
{

	cout << "Keydown!" << endl;

	/* 
	 * We're only interested if 'Esc' has
	 * been presssed.
	 *
	 * EXERCISE: 
	 * Handle the arrow keys and have that change the
	 * viewing position/angle.
	 */
	switch( keysym->sym ) {
		case SDLK_ESCAPE:
			cout << "Quitting the app!" << endl;
			quit_tutorial( 0 );
			break;
		case SDLK_SPACE:
			should_rotate = !should_rotate;
			break;
		default:
			break;
	}

}

// Handle all SDL events in a function:
static void process_events( void )
{
    /* Our SDL event placeholder. */
    SDL_Event event;

    /* Grab all the events off the queue. */
    while( SDL_PollEvent( &event ) ) {
        switch( event.type ) {
			case SDL_KEYDOWN:
				/* Handle key presses. */
				handle_key_down( &event.key.keysym );
				break;
			case SDL_KEYUP:
				cout << "Keyup!" << endl;
				break;
			case SDL_QUIT:
				/* Handle quit requests (like Ctrl-c). */
				quit_tutorial( 0 );
				break;
        }

    }

}

static void draw_screen( void )
{
	/* Our angle of rotation. */
	static float angle = 0.0f;

	/*
	 * EXERCISE:
	 * Replace this awful mess with vertex
	 * arrays and a call to glDrawElements.
	 *
	 * EXERCISE:
	 * After completing the above, change
	 * it to use compiled vertex arrays.
	 *
	 * EXERCISE:
	 * Verify my windings are correct here ;).
	 */
	static GLfloat v0[] = { -1.0f, -1.0f,  1.0f };
	static GLfloat v1[] = {  1.0f, -1.0f,  1.0f };
	static GLfloat v2[] = {  1.0f,  1.0f,  1.0f };
	static GLfloat v3[] = { -1.0f,  1.0f,  1.0f };
	static GLfloat v4[] = { -1.0f, -1.0f, -1.0f };
	static GLfloat v5[] = {  1.0f, -1.0f, -1.0f };
	static GLfloat v6[] = {  1.0f,  1.0f, -1.0f };
	static GLfloat v7[] = { -1.0f,  1.0f, -1.0f };
	static GLubyte red[]    = { 255,   0,   0, 255 };
	static GLubyte green[]  = {   0, 255,   0, 255 };
	static GLubyte blue[]   = {   0,   0, 255, 255 };
	static GLubyte white[]  = { 255, 255, 255, 255 };
	static GLubyte yellow[] = {   0, 255, 255, 255 };
	static GLubyte black[]  = {   0,   0,   0, 255 };
	static GLubyte orange[] = { 255, 255,   0, 255 };
	static GLubyte purple[] = { 255,   0, 255,   0 };

	/* Clear the color and depth buffers. */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	/* We don't want to modify the projection matrix. */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	/* Move down the z-axis. */
	glTranslatef( 0.0, 0.0, -5.0 );

	/* Rotate. */
	glRotatef( angle, 0.0, 1.0, 0.0 );

	if( should_rotate ) {

		if( ++angle > 360.0f ) {
			angle = 0.0f;
		}

	}

	/* Send our triangle data to the pipeline. */
	glBegin( GL_TRIANGLES );

	glColor4ubv( red );
	glVertex3fv( v0 );
	glColor4ubv( green );
	glVertex3fv( v1 );
	glColor4ubv( blue );
	glVertex3fv( v2 );

	glColor4ubv( red );
	glVertex3fv( v0 );
	glColor4ubv( blue );
	glVertex3fv( v2 );
	glColor4ubv( white );
	glVertex3fv( v3 );

	glColor4ubv( green );
	glVertex3fv( v1 );
	glColor4ubv( black );
	glVertex3fv( v5 );
	glColor4ubv( orange );
	glVertex3fv( v6 );

	glColor4ubv( green );
	glVertex3fv( v1 );
	glColor4ubv( orange );
	glVertex3fv( v6 );
	glColor4ubv( blue );
	glVertex3fv( v2 );

	glColor4ubv( black );
	glVertex3fv( v5 );
	glColor4ubv( yellow );
	glVertex3fv( v4 );
	glColor4ubv( purple );
	glVertex3fv( v7 );

	glColor4ubv( black );
	glVertex3fv( v5 );
	glColor4ubv( purple );
	glVertex3fv( v7 );
	glColor4ubv( orange );
	glVertex3fv( v6 );

	glColor4ubv( yellow );
	glVertex3fv( v4 );
	glColor4ubv( red );
	glVertex3fv( v0 );
	glColor4ubv( white );
	glVertex3fv( v3 );

	glColor4ubv( yellow );
	glVertex3fv( v4 );
	glColor4ubv( white );
	glVertex3fv( v3 );
	glColor4ubv( purple );
	glVertex3fv( v7 );

	glColor4ubv( white );
	glVertex3fv( v3 );
	glColor4ubv( blue );
	glVertex3fv( v2 );
	glColor4ubv( orange );
	glVertex3fv( v6 );

	glColor4ubv( white );
	glVertex3fv( v3 );
	glColor4ubv( orange );
	glVertex3fv( v6 );
	glColor4ubv( purple );
	glVertex3fv( v7 );

	glColor4ubv( green );
	glVertex3fv( v1 );
	glColor4ubv( red );
	glVertex3fv( v0 );
	glColor4ubv( yellow );
	glVertex3fv( v4 );

	glColor4ubv( green );
	glVertex3fv( v1 );
	glColor4ubv( yellow );
	glVertex3fv( v4 );
	glColor4ubv( black );
	glVertex3fv( v5 );

	glEnd( );

	/*
	 * EXERCISE:
	 * Draw text telling the user that 'Spc'
	 * pauses the rotation and 'Esc' quits.
	 * Do it using vetors and textured quads.
	 */

	/*
	 * Swap the buffers. This this tells the driver to
	 * render the next frame from the contents of the
	 * back-buffer, and to set all rendering operations
	 * to occur on what was the front-buffer.
	 *
	 * Double buffering prevents nasty visual tearing
	 * from the application drawing on areas of the
	 * screen that are being updated at the same time.
	 */
	SDL_GL_SwapBuffers( );
}

static void setup_opengl( int width, int height )
{

	/* Our shading model--Gouraud (smooth). */
	glShadeModel( GL_SMOOTH );

	/* Culling. */
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );
	glEnable( GL_CULL_FACE );

	/* Set the clear color. */
	glClearColor( 0, 0, 0, 0 );

	/* Setup our viewport. */
	glViewport(0, 0, width, height);

	/*
	 * Change to the projection matrix and set
	 * our viewing volume.
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Ratio is not used now but it will probably be used when we start using shaders to get
	// the screen to look right:
	// float ratio = (float) width / (float) height;

	/*
	* EXERCISE:
	* Replace this with a call to glFrustum.
	*/
	// Actually, forget that. Because gluPerspective is no longer available in new versions
	// of OpenGL
	// gluPerspective( 60.0, ratio, 1.0, 1024.0 );
	// gluPerspective( 120, 4.0f / 3.0f, .00001, 100);
	// gluPerspective( 120, ratio, .00001, 100);
	glMatrixMode(GL_MODELVIEW);
}

// Main Entry point:
int main(int argc, char* argv[]) {
	/* Information about the current video settings. */
    const SDL_VideoInfo* info = NULL;
    /* Dimensions of our window. */
    int width = 0;
    int height = 0;
    /* Color depth in bits of our window. */
    int bpp = 0;

    /* First, initialize SDL's video subsystem. */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        /* Failed, exit. */
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError() );
        quit_tutorial(1);
    }

    /* Let's get some video information. */
    info = SDL_GetVideoInfo( );

    if( !info ) {
        /* This should probably never happen. */
        fprintf( stderr, "Video query failed: %s\n",
             SDL_GetError( ) );
        quit_tutorial(1);
    }

    /*
     * Set our width/height to 640/480 (you would
     * of course let the user decide this in a normal
     * app). We get the bpp we will request from
     * the display. On X11, VidMode can't change
     * resolution, so this is probably being overly
     * safe. Under Win32, ChangeDisplaySettings
     * can change the bpp.
     */
    // Just to test at a smaller size:
    width = 640;
    height = 480;

    // Macbook Pro Retina 15" is: 2880 × 1800
    // width = 2880;
    // height = 1800;
    bpp = info->vfmt->BitsPerPixel;

    // Set up some OpenGL Color sizes:
	/*
     * Now, we want to setup our requested
     * window attributes for our OpenGL window.
     * We want *at least* 5 bits of red, green
     * and blue. We also want at least a 16-bit
     * depth buffer.
     *
     * The last thing we do is request a double
     * buffered window. '1' turns on double
     * buffering, '0' turns it off.
     *
     * Note that we do not use SDL_DOUBLEBUF in
     * the flags to SDL_SetVideoMode. That does
     * not affect the GL attribute state, only
     * the standard 2D blitting setup.
     */
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );

	#ifdef __APPLE__
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      32);
	#else
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
	#endif

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    // Set the video mode: | SDL_FULLSCREEN
	if (SDL_SetVideoMode(width, height, bpp, SDL_OPENGL ) == 0) {
		cout << "Could not initialize SDL: " << SDL_GetError() << endl;
		quit_tutorial( 1 );
	}
	SDL_WM_SetCaption("Simple Window", "Simple Window");


	// Set up OpenGL:
	/*
     * At this point, we should have a properly setup
     * double-buffered window for use with OpenGL.
     */
    setup_opengl( width, height );

    // Old Draw Loop:
	// bool done = false;
	// while (!done) {
	// 	while (SDL_PollEvent(&event)) {
	// 		if (event.type == SDL_QUIT) {
	// 			done = true;
	// 		}

	// 		switch (event.type) {
	// 			case SDL_KEYDOWN:
	// 				cout << "Keydown!" << endl;
	// 				cout << "Quitting the app!" << endl;
	// 				done = true;
	// 			case SDL_KEYUP:
	// 				cout << "Keyup!" << endl;
	// 			// case SDL_QUIT:
	// 			// 	done = true;
	// 			default:
	// 				break;
	// 		}

	// 	}
	// 	if (screen != NULL) {
	// 		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 0, 0));
	// 		SDL_Flip(screen);
	// 	} 
	// }

    // New Draw Loop:
	/*
     * Now we want to begin our normal app process--
     * an event loop with a lot of redrawing.
     */
    while( 1 ) {
        /* Process incoming events. */
        process_events( );
        /* Draw the screen. */
        draw_screen( );
    }

    // Some notes on framerate:
    /*
     * EXERCISE:
     * Record timings using SDL_GetTicks() and
     * and print out frames per second at program
     * end.
     */

	return 0;
}