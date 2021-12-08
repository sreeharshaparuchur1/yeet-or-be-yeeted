#include "ball.h"
#include "main.h"

Missile::Missile(float x, float y, float z, color_t color, color_t color1, Ball plane) {
    this->position = glm::vec3(x, y, z);
    this->rotation_x = -90;
    this->rotation_y = plane.rotation_y;
    this->rotation_z = 0;
    speed = 1;

    this->kill = 0;

    this->missile_box.x = x;
    this->missile_box.y = y;
    this->missile_box.z = z;

    this->missile_box.height = 6; 
    this->missile_box.width = 6;
    this->missile_box.depth = 14;

    static GLfloat vertex_buffer_data[2700]; // circle 1
    static GLfloat vertex_buffer_data1[2700]; // cone
    static GLfloat vertex_buffer_data2[2700]; // circle 2
    static GLfloat vertex_buffer_data3[32400]; //cylinder joining

    float a,r;
    a=100;
    r=3.0f;

    for(int i=0; i<300; i++)
    {
        vertex_buffer_data1[9*i] = r*cos(i*2*M_PI/300);
        vertex_buffer_data1[9*i + 1] = 0.0f;
        vertex_buffer_data1[9*i + 2] = r*sin(i*2*M_PI/300);
        
        vertex_buffer_data1[9*i + 3] = r*cos((i+1)*2*M_PI/300);
        vertex_buffer_data1[9*i + 4] = 0.0f;
        vertex_buffer_data1[9*i + 5] = r*sin((i+1)*2*M_PI/300);
        
        vertex_buffer_data1[9*i + 6] = 0.0f;
        vertex_buffer_data1[9*i + 7] = 6.0f;
        vertex_buffer_data1[9*i + 8] = 0.0f;
    }

    for(int i=0; i<300; i++)
    {
        vertex_buffer_data[3*i] = r*cos(i*2*M_PI/300);
        vertex_buffer_data[3*i + 1] = 0.0f;
        vertex_buffer_data[3*i + 2] = r*sin(i*2*M_PI/300);
        
        // vertex_buffer_data[6*i + 3] = r*cos((i+1)*2*M_PI/300);
        // vertex_buffer_data[6*i + 4] = 0.0f;
        // vertex_buffer_data[6*i + 5] = r*sin((i+1)*2*M_PI/300);
        
        // vertex_buffer_data[9*i + 6] = 0.0f;
        // vertex_buffer_data[9*i + 7] = 0.0f;
        // vertex_buffer_data[9*i + 8] = 0.0f;
    }

    for(int i=0; i<300; i++)
    {
        vertex_buffer_data2[3*i] = r*cos(i*2*M_PI/300);
        vertex_buffer_data2[3*i + 1] = -8.0f + 0.0f;
        vertex_buffer_data2[3*i + 2] = r*sin(i*2*M_PI/300);
        
        // vertex_buffer_data2[6*i + 3] = r*cos((i+1)*2*M_PI/300);
        // vertex_buffer_data2[6*i + 4] = -10.0f + 0.0f;
        // vertex_buffer_data2[6*i + 5] = r*sin((i+1)*2*M_PI/300);
        
        // vertex_buffer_data2[9*i + 6] = 0.0f;
        // vertex_buffer_data2[9*i + 7] = -10.0f + 0.0f;
        // vertex_buffer_data2[9*i + 8] = 0.0f;
    }

    int k = 0;
    for ( int i =0; i<900; i+=3)
    {
        // if(i%9 == 1 || i%9 == 2 || i%9 == 3)
        //  continue;

        vertex_buffer_data3[k] = vertex_buffer_data[i];
        vertex_buffer_data3[k+1] = vertex_buffer_data[i+1];
        vertex_buffer_data3[k+2] = vertex_buffer_data[i+2];

        vertex_buffer_data3[k+3] = vertex_buffer_data2[i];
        vertex_buffer_data3[k+4] = vertex_buffer_data2[i+1];
        vertex_buffer_data3[k+5] = vertex_buffer_data2[i+2];

        vertex_buffer_data3[k+6] = vertex_buffer_data[i+3];
        vertex_buffer_data3[k+7] = vertex_buffer_data[i+4];
        vertex_buffer_data3[k+8] = vertex_buffer_data[i+5];

        vertex_buffer_data3[k+9] = vertex_buffer_data[i+3];
        vertex_buffer_data3[k+10] = vertex_buffer_data[i+4];
        vertex_buffer_data3[k+11] = vertex_buffer_data[i+5];
        
        vertex_buffer_data3[k+12] = vertex_buffer_data2[i];
        vertex_buffer_data3[k+13] = vertex_buffer_data2[i+1];
        vertex_buffer_data3[k+14] = vertex_buffer_data2[i+2];

        vertex_buffer_data3[k+15] = vertex_buffer_data2[i+3];
        vertex_buffer_data3[k+16] = vertex_buffer_data2[i+4];
        vertex_buffer_data3[k+17] = vertex_buffer_data2[i+5];

        k+=18;
    }
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->object = create3DObject(GL_TRIANGLES, 3*300, vertex_buffer_data, color, GL_FILL);

    this->object2 = create3DObject(GL_TRIANGLES, 3*300, vertex_buffer_data2, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6*300, vertex_buffer_data3, color1, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3*300, vertex_buffer_data1, color, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatez    = glm::rotate((float) (this->rotation_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    
    glm::mat4 rotatey    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatex    = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotatez * rotatey * rotatex);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    // draw3DObject(this->object5);
    // draw3DObject(this->object6);
}

void Missile::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Missile::tick(Ball plane) {
    this->position.z = this->position.z - 3*cos(this->rotation_y*M_PI/180.0f);
    this->position.x = this->position.x - 3*sin(this->rotation_y*M_PI/180.0f);

    this->missile_box.x = this->position.x;
    this->missile_box.y = this->position.y;
    this->missile_box.z = this->position.z;
}




