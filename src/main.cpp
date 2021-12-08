#include "main.h"
#include "timer.h"
#include "ball.h"

using namespace std;

GLMatrices Matrices;
GLMatrices Ortho;
GLuint     programID;
GLFWwindow *window;

int cam;
long long cur_enemy = 0;
long long total_score = 0;
long long lives = 20;
long long no_of_bombs = 0;
long long no_of_missiles=0;
long long no_of_fuelups = 0;
long long no_of_bullets = 0;
long long shoot = 0;

Ball plane;
Ground ground;
Altitude alt;
Life life;
Arrow arrow;
Compass comp;

Volcano volcanoes[200];
Ring rings [200];
Parachute parachutes[200];
Fuel fuelups[1000];
Enemy enemies[200];

Missile missiles[1000];
Bomb bombs[1000];
Bullet bullets[5000];

float screen_zoom = 0.5, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);
Timer t1(1.0 / 10);
Timer t2(10);
Timer t3(1);
Timer t4(1);

void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 0, 0, 0);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 0, 1);

    if(cam==0)//follow cam
    {
    	// if (t1.processTick())
    	// {
    	eye = glm::vec3(plane.position.x, plane.position.y + 40 , plane.position.z);
    	eye.x += 80*sin(plane.rotation_y*M_PI/180.0f);
    	eye.z += 80*cos(plane.rotation_y*M_PI/180.0f);

    	target = glm::vec3(plane.position.x+0.01, plane.position.y+0.01, plane.position.z+0.01);
    	target.x -= 30*sin(plane.rotation_y*M_PI/180.0f);
    	target.z -= 30*cos(plane.rotation_y*M_PI/180.0f);

    	up = glm::vec3(0, 1, 0);
    	// }

    }
    else if(cam == 1) // top view
    {
    	// if (t1.processTick())
    	// {
	    	eye = glm::vec3(plane.position.x, plane.position.y + 500 , plane.position.z);
	    	target = glm::vec3(plane.position.x+0.01, plane.position.y+0.01, plane.position.z+0.01);
	    	up = glm::vec3(0, 1, 0);
	    // }

    }

    else if(cam == 2) // first person view
    {
    	eye = glm::vec3(plane.position.x, plane.position.y + 10 , plane.position.z);
    	eye.x -= 10*sin(plane.rotation_y*M_PI/180.0f);
    	eye.z -= 10*cos(plane.rotation_y*M_PI/180.0f);

    	target = glm::vec3(plane.position.x+0.01, plane.position.y+0.01, plane.position.z+0.01);
    	target.x -= 400*sin(plane.rotation_y*M_PI/180.0f);
    	target.z -= 400*cos(plane.rotation_y*M_PI/180.0f);

    	up = glm::vec3(0, 1, 0);

    }

    else if(cam == 3) // tower view
    {
    	eye = glm::vec3(0, 100, 400);

    	target = glm::vec3(plane.position.x+0.01, plane.position.y+0.01, plane.position.z+0.01);

    	up = glm::vec3(0, 1, 0);

    }

    glm::vec3 eye2 (0, 0, -20);
    glm::vec3 target2 (0, 0, 0);
    glm::vec3 up2 (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    Ortho.view = glm::lookAt( eye2, target2, up2 );
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP2 = Ortho.projection * Ortho.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    plane.draw(VP);
    ground.draw(VP);

    for(int i = 0; i<12; i++)
    {
    	if(enemies[i].kill == 0)
    		enemies[i].draw(VP);
    }
    // volcanoes[0].draw(VP);
    for(int i = 0; i<40; i++)
    	volcanoes[i].draw(VP);

    for(int i = 0; i<60; i++)
    	rings[i].draw(VP);
    for(int i = 0; i<no_of_bombs; i++)
    	bombs[i].draw(VP);
    
    for(int i = 0; i<no_of_missiles; i++)
    {
    	if(missiles[i].kill == 0)
    		missiles[i].draw(VP);
    }

    for(int i = 0; i<no_of_bullets; i++)
    {
    	if(bullets[i].kill == 0)
    		bullets[i].draw(VP);
    }
    
    for(int i = 0; i<20; i++)
    {
    	if(parachutes[i].kill==0)
    		parachutes[i].draw(VP);
    }

    arrow.draw(VP2);
    alt.draw(VP2, plane);
    life.draw(VP2, lives);
    comp.draw(VP2, plane);

    // if(t2.processTick())
    for(int i = 0; i<no_of_fuelups; i++)
    {
    	if(fuelups[i].kill == 0)
    		fuelups[i].draw(VP);
    }

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int forward = glfwGetKey(window, GLFW_KEY_W);
    int tilt_left = glfwGetKey(window, GLFW_KEY_Q);
    int tilt_right = glfwGetKey(window, GLFW_KEY_E);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int back = glfwGetKey(window, GLFW_KEY_S);
    int down = glfwGetKey(window, GLFW_KEY_X);
    int change_cam = glfwGetKey(window, GLFW_KEY_C);
    int bomb = glfwGetKey(window, GLFW_KEY_B);
    int missile = glfwGetKey(window, GLFW_KEY_M);

    if (left)
    	plane.go_left();
    else if(right)
    	plane.go_right();
    else if(forward)
    	plane.go_forward();
    else if(tilt_left)
    	plane.tilt_left();
    else if(tilt_right)
    	plane.tilt_right();
    else if(up)
    	plane.go_up();
    else if(back)
    	plane.go_back();
    else if(down)
    	plane.go_down();
    else if(change_cam)
    {
    	if (t1.processTick())
    		cam = (cam+1)%4;
    }
    else if(bomb)
    {
    	if (t1.processTick())
    		bombs[no_of_bombs++] = Bomb(plane.position.x, plane.position.y, plane.position.z, COLOR_RED);

    }
    else if(missile)
    {
    	if (t1.processTick())
    		missiles[no_of_missiles++] = Missile(plane.position.x - 30*sin(plane.rotation_y*M_PI/180.0f), plane.position.y, plane.position.z - 30*cos(plane.rotation_y*M_PI/180.0f), COLOR_NAVY, COLOR_GOLD, plane);


    }
}

void tick_elements() {
    plane.tick();

    for (int i =0; i<no_of_bombs; i++)
    	bombs[i].tick();

    alt.tick(plane);

    for (int i =0; i<no_of_missiles; i++)
    	missiles[i].tick(plane);

    for (int i =0; i<no_of_bullets; i++)
    	bullets[i].tick(plane);

    for (int i =0; i<no_of_bullets; i++)
    	missiles[i].tick(plane);

    for (int i =0; i<20; i++)
    	parachutes[i].tick();

    for (int i =0; i<30; i++)
    	fuelups[i].tick();

    if(t2.processTick())
    {
    	int n1 = rand() % 900;
        int n2 = rand() % 900;

        fuelups[no_of_fuelups++] = Fuel(n1,350,n2, COLOR_ORANGE);
    }
    arrow.tick(plane, enemies[cur_enemy]);
    comp.tick(plane);


}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane = Ball(0, 250, 300, COLOR_RED, COLOR_GREEN);
    ground = Ground(0, -50, 0, COLOR_CYAN);
    
    alt=Altitude(-190, -220, 0, COLOR_FIRE, COLOR_GOLD);
    life=Life(190, -220, 0, COLOR_FIRE, COLOR_BLACK);
    arrow=Arrow(0, 150, 0, COLOR_YELLOW);
    comp=Compass(190, 220, 0, COLOR_FIRE, COLOR_GOLD);
    // ring = Ring(50, 70, 0, COLOR_WHITE);

    // volcanoes[0] = Volcano(0, -50, 0, COLOR_TURQUOISE);

    int j;

    //enemies

    for (j = 0; j < 3; j++) 
    {
        int n1 = (rand() % 900);
        int n2 = (rand() % 900);
        enemies[j] = Enemy(n1, -50, n2, COLOR_BROWN, COLOR_PEACH);

    }
    for (j = 0; j < 3; j++) 
    {
        int n1 = (rand() % 900) - 900;
        int n2 = (rand() % 900) - 900;
        enemies[j+3] = Enemy(n1, -50, n2, COLOR_BROWN, COLOR_PEACH);

    }
    for (j = 0; j < 3; j++) 
    {
        int n1 = (rand() % 900);
        int n2 = (rand() % 900) - 900;
        enemies[j+6] = Enemy(n1, -50, n2, COLOR_BROWN, COLOR_PEACH);

    }
    for (j = 0; j < 3; j++) 
    {
        int n1 = (rand() % 900) - 900;
        int n2 = (rand() % 900);
        enemies[j+9] = Enemy(n1, -50, n2, COLOR_BROWN, COLOR_PEACH);

    }

    //volcanoes

    for (j = 0; j < 10; j++) 
    {
        int n1 = (rand() % 900);
        int n2 = (rand() % 900);
        volcanoes[j] = Volcano(n1, -50, n2, COLOR_TURQUOISE);

    }
    for (j = 0; j < 10; j++) 
    {
        int n1 = (rand() % 900);
        int n2 = (rand() % 900) - 900;
        volcanoes[j+10] = Volcano(n1, -50, n2, COLOR_TURQUOISE);

    }
    for (j = 0; j < 10; j++) 
    {
        int n1 = (rand() % 900) - 900;
        int n2 = (rand() % 900);
        volcanoes[j+20] = Volcano(n1, -50, n2, COLOR_TURQUOISE);

    }
    for (j = 0; j < 10; j++) 
    {
        int n1 = (rand() % 900) - 900;
        int n2 = (rand() % 900) - 900;
        volcanoes[j+30] = Volcano(n1, -50, n2, COLOR_TURQUOISE);

    }

    //Rings

    for (j = 0; j < 15; j++) 
    {
        int n1 = rand() % 900;
        int n2 = rand() % 350;
        int n3 = rand() % 900;
        rings[j] = Ring(n1, n2, n3, COLOR_WHITE);

    }
    for (j = 0; j < 15; j++) 
    {
        int n1 = rand() % 900;
        int n2 = rand() % 350;
        int n3 = rand() % 900;
        n1*=-1;
        n3*=-1;
        rings[j+15] = Ring(n1, n2, n3, COLOR_WHITE);

    }

    for (j = 0; j < 15; j++) 
    {
        int n1 = rand() % 900;
        int n2 = rand() % 350;
        int n3 = rand() % 900;
        // n1*=-1;
        n3*=-1;
        rings[j+30] = Ring(n1, n2, n3, COLOR_WHITE);

    }

    for (j = 0; j < 15; j++) 
    {
        int n1 = rand() % 900;
        int n2 = rand() % 350;
        int n3 = rand() % 900;
        n1*=-1;
        // n3*=-1;
        rings[j+45] = Ring(n1, n2, n3, COLOR_WHITE);

    }

    //parachutes
    
    for (j = 0; j < 30; j++) 
    {

        int n1 = (rand() % 900) - 450;
        int n2 = (rand()%(350-250))+250;
        int n3 = (rand() % 900) - 450;
        // n1*=-1;
        // n3*=-1;
        parachutes[j] = Parachute(n1, n2, n3, COLOR_FUCHSIA, COLOR_FUCHSIA);

    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    cam = 0;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) 
        {
        	if(lives<=0)
        	{
        		printf("All out of fuel!");
        		quit(window);
        	}
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);

            //Checking collisions

            for (int i = 0; i < no_of_missiles; ++i)
				for(int j =0; j<20; j++)
			    {
			        if ((detect_collision(parachutes[j].para_box, missiles[i].missile_box)==1) && (missiles[i].kill == 0) && (parachutes[j].kill == 0)) 
			        {
			            missiles[i].kill = 1;
			            parachutes[j].kill = 1;
			            total_score ++;
			            printf("TOTAL SCORE: %lld ", total_score );
			            // cout << endl;
			        }
			    }

			for (int i = 0; i < no_of_fuelups; ++i)
            {
                if ((detect_collision(plane.plane_box, fuelups[i].fuel_box)==1) && (fuelups[i].kill == 0)) 
                {
                    fuelups[i].kill = 1;
                    lives+=5;
                    printf("LIVES REMAINING: %lld ", lives );
                }
            }
            for (int i = 0; i < 12; ++i)
            {
                if ((detect_collision(plane.plane_box, enemies[i].box)==1) && (enemies[i].kill == 0)) 
                {
                    // enemies[i].kill = 1;
                    // lives++;
                    // printf("Start shooting at plane!:");
                    if (t3.processTick())
    					bullets[no_of_bullets++] = Bullet(enemies[i].position.x, enemies[i].position.y, enemies[i].position.z, COLOR_WHITE, i);
                }
            }
            for (int i = 0; i < 40; ++i)
            {
                if ((detect_collision(plane.plane_box, volcanoes[i].box)==1)) 
                	if (t4.processTick())
                		lives -= 0.1;
             
            }

            for (int i = 0; i < no_of_bullets; ++i)
            {
				if ((detect_collision(bullets[i].box, plane.plane_box)==1) && (bullets[i].kill == 0)) 
		        {
		            bullets[i].kill = 1;
		            // (bullets[i].enemy_no == cur_enemy)
		            lives -= 0.4;
		            // printf("TOTAL SCORE: %lld ", total_score );
		            // cout << endl;
		        }
		    }

		    for (int i = 0; i < no_of_missiles; ++i)
            {
				if ((detect_collision(missiles[i].missile_box, enemies[cur_enemy].box2)==1) && (missiles[i].kill == 0)) 
		        {
		            missiles[i].kill = 1;
		            
		            enemies[cur_enemy].kill = 1;
		            cur_enemy ++;
		            lives += 6;
		            // printf("TOTAL SCORE: %lld ", total_score );
		            // cout << endl;
		        }
		    }

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.depth + b.depth));
}

void reset_screen() {
    float top    = screen_center_y + 150 / screen_zoom;
    float bottom = screen_center_y - 150 / screen_zoom;
    float left   = screen_center_x - 150 / screen_zoom;
    float right  = screen_center_x + 150 / screen_zoom;
    Matrices.projection = glm::perspective(90.0f*M_PI/180, (double)1, 0.1, (double)10000.0);
    Ortho.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}


