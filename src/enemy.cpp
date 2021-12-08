#include "ball.h"
#include "main.h"

Enemy::Enemy(float x, float y, float z, color_t color, color_t color1) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->kill = 0;

    this->box.height = 350; 
    this->box.width = 350;
    this->box.depth = 350;

    this->box2.height = 45; 
    this->box2.width = 45;
    this->box2.depth = 45;

    this->box.x = x;
    this->box.y = y;
    this->box.z = z;

    this->box2.x = x;
    this->box2.y = y;
    this->box2.z = z;
    // speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data_sq[] = {
        -15.0f,-15.0f,-15.0f, // triangle 1 : begin
        -15.0f,-15.0f, 15.0f,
        -15.0f, 15.0f, 15.0f, // triangle 1 : end
        15.0f, 15.0f,-15.0f, // triangle 2 : begin
        -15.0f,-15.0f,-15.0f,
        -15.0f, 15.0f,-15.0f, // triangle 2 : end
        15.0f,-15.0f, 15.0f,
        -15.0f,-15.0f,-15.0f,
        15.0f,-15.0f,-15.0f,
        15.0f, 15.0f,-15.0f,
        15.0f,-15.0f,-15.0f,
        -15.0f,-15.0f,-15.0f,
        -15.0f,-15.0f,-15.0f,
        -15.0f, 15.0f, 15.0f,
        -15.0f, 15.0f,-15.0f,
        15.0f,-15.0f, 15.0f,
        -15.0f,-15.0f, 15.0f,
        -15.0f,-15.0f,-15.0f,
        -15.0f, 15.0f, 15.0f,
        -15.0f,-15.0f, 15.0f,
        15.0f,-15.0f, 15.0f,
        15.0f, 15.0f, 15.0f,
        15.0f,-15.0f,-15.0f,
        15.0f, 15.0f,-15.0f,
        15.0f,-15.0f,-15.0f,
        15.0f, 15.0f, 15.0f,
        15.0f,-15.0f, 15.0f,
        15.0f, 15.0f, 15.0f,
        15.0f, 15.0f,-15.0f,
        -15.0f, 15.0f,-15.0f,
        15.0f, 15.0f, 15.0f,
        -15.0f, 15.0f,-15.0f,
        -15.0f, 15.0f, 15.0f,
        15.0f, 15.0f, 15.0f,
        -15.0f, 15.0f, 15.0f,
        15.0f,-15.0f, 15.0f
    };

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
        vertex_buffer_data1[9*i + 1] = 30.0f;
        vertex_buffer_data1[9*i + 2] = r*sin(i*2*M_PI/300);
        
        vertex_buffer_data1[9*i + 3] = r*cos((i+1)*2*M_PI/300);
        vertex_buffer_data1[9*i + 4] = 30.0f;
        vertex_buffer_data1[9*i + 5] = r*sin((i+1)*2*M_PI/300);
        
        vertex_buffer_data1[9*i + 6] = 0.0f;
        vertex_buffer_data1[9*i + 7] = 45.0f;
        vertex_buffer_data1[9*i + 8] = 0.0f;
    }

    for(int i=0; i<300; i++)
    {
        vertex_buffer_data[3*i] = r*cos(i*2*M_PI/300);
        vertex_buffer_data[3*i + 1] = 30.0f;
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
        vertex_buffer_data2[3*i + 1] = -15.0f + 30.0f;
        vertex_buffer_data2[3*i + 2] = r*sin(i*2*M_PI/300);
        
        // vertex_buffer_data2[6*i + 3] = r*cos((i+1)*2*M_PI/300);
        // vertex_buffer_data2[6*i + 4] = -15.0f + 0.0f;
        // vertex_buffer_data2[6*i + 5] = r*sin((i+1)*2*M_PI/300);
        
        // vertex_buffer_data2[9*i + 6] = 0.0f;
        // vertex_buffer_data2[9*i + 7] = -15.0f + 0.0f;
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
    this->object = create3DObject(GL_TRIANGLES, 3*300, vertex_buffer_data, color1, GL_FILL);

    this->object2 = create3DObject(GL_TRIANGLES, 3*300, vertex_buffer_data2, color1, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6*300, vertex_buffer_data3, color1, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3*300, vertex_buffer_data1, color1, GL_FILL);

    this->object0 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_sq, color, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object0);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object);
}

void Enemy::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}