#ifndef SCENE_H
#define SCENE_H

// Abstract Class that represents the interior of a window
class Scene
{

public:
    Scene() {};
    virtual ~Scene() {};

    // Manage event
    virtual void loop_event() = 0;

    // Manager the visual of the scene
    virtual void render() = 0;
};

#endif