#include "ball.h"
#include "main.h"

Parachute::Parachute(float x, float y, float z, color_t color, color_t color1) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    this->kill = 0;

    this->para_box.x = x;
    this->para_box.y = y;
    this->para_box.z = z;

    this->para_box.height = 25; 
    this->para_box.width = 25;
    this->para_box.depth = 25;
    speed = 1;

    static const GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f, // triangle 1 : begin
        0.0f, 25.0f, 0.0f,
        25.0f, 0.0f, 0.0f, // triangle 1 : end
        0.0f, 25.0f, 0.0f,
        25.0f, 0.0f, 0.0f,
        25.0f, 25.0f, 0.0f,
    }; 

    static const GLfloat vertex_buffer_data2[] = {
        12.5f, 12.5f, 15.0f,
        0.0f, 0.0f, 0.0f, // triangle 1 : begin
        
        12.5f, 12.5f, 15.0f, // triangle 1 : end
        0.0f, 25.0f, 0.0f,
    }; 

    static const GLfloat vertex_buffer_data3[] = {
        12.5f, 12.5f, 15.0f, 
        25.0f, 0.0f, 0.0f,
         // triangle 1 : begin
        
        12.5f, 12.5f, 15.0f, // triangle 1 : end
        25.0f, 25.0f, 0.0f,
    }; 

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->object = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_LINES, 4, vertex_buffer_data2, color1, GL_FILL);
    this->object3 = create3DObject(GL_LINES, 4, vertex_buffer_data3, color1, GL_FILL);

    // this->object2 = create3DObject(GL_TRIANGLES, 3*300, vertex_buffer_data2, color, GL_FILL);
    // this->object3 = create3DObject(GL_TRIANGLES, 6*300, vertex_buffer_data3, color, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
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
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}	

void Parachute::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Parachute::tick() {
    // this->rotation += speed;
    this->position.y -= 0.2;
    this->para_box.x = this->position.x;
    this->para_box.y = this->position.y;
    this->para_box.z = this->position.z;
    if(this->position.y < -40)
    {
    	this->position.y = 340;
    	this->para_box.y = this->position.y;
    }
}

