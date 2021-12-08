#include "ball.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // this->rotation_y = 0;
    // this->rotation_z = 0;
    // speed = 1;
    static GLfloat vertex_buffer_data[2700];
    float a,r;
    a=100;
    r=10.0f;

    for(int i=0; i<300; i++)
    {
        vertex_buffer_data[9*i] = r*cos(i*2*M_PI/300);
        vertex_buffer_data[9*i + 1] = 0.0f;
        vertex_buffer_data[9*i + 2] = r*sin(i*2*M_PI/300);
        
        vertex_buffer_data[9*i + 3] = r*cos((i+1)*2*M_PI/300);
        vertex_buffer_data[9*i + 4] = 0.0f;
        vertex_buffer_data[9*i + 5] = r*sin((i+1)*2*M_PI/300);
        
        vertex_buffer_data[9*i + 6] = 0.0f;
        vertex_buffer_data[9*i + 7] = 15.0f;
        vertex_buffer_data[9*i + 8] = 0.0f;
    }


    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->object = create3DObject(GL_TRIANGLES, 3*300, vertex_buffer_data, color, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bomb::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bomb::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
    this->position.y -= 5;
}










