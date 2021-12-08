#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color, color_t color1);
    glm::vec3 position;

    float rotation_x;
    float rotation_y;
    float rotation_z;

    int kill;
    bounding_box_t plane_box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void go_left();
    void go_right();
    void tilt_left();
    void tilt_right();
    void go_forward();
    void go_back();
    void go_down();
    void go_up();
    // void drop_bomb();
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
};

#endif // BALL_H

#ifndef GROUND_H
#define GROUND_H


class Ground {
public:
    Ground() {}
    Ground(float x, float y, float z, color_t color);
    glm::vec3 position;

    float rotation;
    // float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    // VAO *object2;
    // VAO *object3;
    // VAO *object4;
};

#endif // GROUND_H

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z, color_t color);
    glm::vec3 position;

    float rotation;
    bounding_box_t box;
    // float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    // VAO *object2;
    // VAO *object3;
    // VAO *object4;
};

#endif // GROUND_H

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z, color_t color);
    glm::vec3 position;

    float rotation;
    // float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    // VAO *object4;
};

#endif // GROUND_H

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z, color_t color, color_t color1);
    glm::vec3 position;

    float rotation;
    int kill;
    bounding_box_t para_box;
    // float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    // VAO *object4;
};

#endif // GROUND_H


#ifndef ALTITUDE_H
#define ALTITUDE_H

class Altitude {
public:
    Altitude() {}
    Altitude(float x, float y, float z, color_t color, color_t color1);
    glm::vec3 position;

    float rotation;
    float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP, Ball plane);
    void set_position(float x, float y);
    void tick(Ball plane);
    double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // GROUND_H

#ifndef BOMB_H
#define BOMB_H

class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, color_t color);
    glm::vec3 position;

    float rotation;
    float kill;
    // float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    // VAO *object2;
    // VAO *object3;
    // VAO *object4;
};

#endif // GROUND_H

#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, color_t color, color_t color1, Ball plane);
    glm::vec3 position;

    float rotation_x;
    float rotation_y;
    float rotation_z;

    int kill;
    bounding_box_t missile_box;
    // float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(Ball plane);
    double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // GROUND_H

#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float z, color_t color, color_t color1);
    glm::vec3 position;
    float rotation;
    int kill;
    bounding_box_t box;
    bounding_box_t box2;
    // float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
	VAO *object0;
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // GROUND_H

#ifndef ARROW_H
#define ARROW_H

class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation_x;
    float rotation;
    int cur_enemy;
    // float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(Ball plane, Enemy current);
    double speed;
private:
    VAO *object;
    VAO *object1;
    // VAO *object3;
    // VAO *object4;
};
#endif // GROUND_H

#ifndef FUEL_H
#define FUEL_H

class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y, float z, color_t color);
    glm::vec3 position;
    int kill;
    bounding_box_t fuel_box;

    float rotation;
    // float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1;
    // VAO *object3;
    // VAO *object4;
};
#endif // GROUND_H

#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y, float z, color_t color, int i);
    glm::vec3 position;
    float enemy_no;
    float rotation;
    int kill;
    float enemy_x;
    float enemy_y;
    float enemy_z;

    bounding_box_t box;
    // float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(Ball plane);
    double speed;
private:
    VAO *object;
    // VAO *object2;
    // VAO *object3;
    // VAO *object4;
};

#endif // GROUND_H

#ifndef LIFE_H
#define LIFE_H

class Life {
public:
    Life() {}
    Life(float x, float y, float z, color_t color, color_t color1);
    glm::vec3 position;

    float rotation;
    float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP, long long lives);
    void set_position(float x, float y);
    void tick(Ball plane);
    double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // GROUND_H

#ifndef COMPASS_H
#define COMPASS_H

class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z, color_t color, color_t color1);
    glm::vec3 position;

    float rotation;
    float rotation_y;
    // float rotation_z;
    void draw(glm::mat4 VP, Ball plane);
    void set_position(float x, float y);
    void tick(Ball plane);
    double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // GROUND_H
