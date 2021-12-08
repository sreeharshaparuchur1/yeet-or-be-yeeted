#include "ball.h"
#include "main.h"

Bullet::Bullet(float x, float y, float z, color_t color, int i) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->kill = 0;
    this->enemy_no = i;
    this->enemy_x = x;
    this->enemy_y = y;
    this->enemy_z = z;

    this->box.x = x;
    this->box.y = y;
    this->box.z = z;

    this->box.height = 25; 
    this->box.width = 25;
    this->box.depth = 25;
    
    static const GLfloat vertex_buffer_data_sq[] = {
        -5.0f,-5.0f,-5.0f, // triangle 1 : begin
        -5.0f,-5.0f, 5.0f,
        -5.0f, 5.0f, 5.0f, // triangle 1 : end
        5.0f, 5.0f,-5.0f, // triangle 2 : begin
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f,-5.0f, // triangle 2 : end
        5.0f,-5.0f, 5.0f,
        -5.0f,-5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f, 5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f, 5.0f,
        -5.0f, 5.0f,-5.0f,
        5.0f,-5.0f, 5.0f,
        -5.0f,-5.0f, 5.0f,
        -5.0f,-5.0f,-5.0f,
        -5.0f, 5.0f, 5.0f,
        -5.0f,-5.0f, 5.0f,
        5.0f,-5.0f, 5.0f,
        5.0f, 5.0f, 5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f, 5.0f,-5.0f,
        5.0f,-5.0f,-5.0f,
        5.0f, 5.0f, 5.0f,
        5.0f,-5.0f, 5.0f,
        5.0f, 5.0f, 5.0f,
        5.0f, 5.0f,-5.0f,
        -5.0f, 5.0f,-5.0f,
        5.0f, 5.0f, 5.0f,
        -5.0f, 5.0f,-5.0f,
        -5.0f, 5.0f, 5.0f,
        5.0f, 5.0f, 5.0f,
        -5.0f, 5.0f, 5.0f,
        5.0f,-5.0f, 5.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_sq, color, GL_FILL);

    
}

void Bullet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotatez    = glm::rotate((float) (this->rotation_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    
    // glm::mat4 rotatey    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // glm::mat4 rotatex    = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->object2);
    // draw3DObject(this->object3);
}   

void Bullet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bullet::tick(Ball plane) {
    // this->rotation += speed;
    this->position.y += (plane.position.y - this->enemy_y)/50.0f;
    this->position.x += (plane.position.x - this->enemy_x)/50.0f;
    this->position.z += (plane.position.z - this->enemy_z)/50.0f;

    this->box.x = this->position.x;
    this->box.y = this->position.y;
    this->box.z = this->position.z;
    
}

