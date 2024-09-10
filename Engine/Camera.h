#ifndef CAMERA_H
#define CAMERA_H

#include "Vector2D.h"

#include "stdafx.h"

enum CAM_DIRECTION{

    FREEZE = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    DOWN = 4
};

enum AXIS{

    X_AXIS = 0,
    Y_AXIS = 1
};


class Camera{


public:


    //Camera();
    Camera(int x, int y, int w, int h, int maxSize);

    void setVelocity(int vel);
    int getVelocity();

    void setPosition(int x, int y){ camera.x = x; camera.y = y; }


    void setCameraDimensions(int x = 0, int y = 0, int w = 0, int h = 0);
    SDL_Rect getCamera();

    void moveCamera(int direction, int axis);

    void moveCam2(int direction, float time);
    void stopCam2(int dir, float time);

    void update(float deltaTime);


private:

    SDL_Rect camera;

    Vector2D vel;

    int velocityX;
    int velocityY;
    float camSpeed;
    int mDirection;
    int maxGridSize;
    bool camMoved;
};

#endif // CAMERA_H
