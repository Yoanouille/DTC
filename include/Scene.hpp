#ifndef SCENE_HPP
#define SCENE_HPP

class Scene 
{

    public:
        Scene();
        virtual ~Scene();
        virtual void loop_event() = 0;
        virtual void render() = 0; 

};

#endif