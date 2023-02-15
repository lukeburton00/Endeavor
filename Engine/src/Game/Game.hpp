#pragma once
#include "Scene.hpp"

class Game
{
public:
    virtual ~Game(){}
    virtual void start() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void stop() = 0;

    int getWidth() const { return mWidth; }
    int getHeight() const { return mHeight; }
    const char * getTitle() const { return mTitle; }
    std::shared_ptr<Scene> getActiveScene() const { return activeScene; }
    void setActiveScene(Scene scene) { activeScene = std::make_shared<Scene>(scene); }

protected:
    std::shared_ptr<Scene> activeScene;
    void setWidth(int w) { mWidth = w; }
    void setHeight(int h) { mHeight = h; }
    void setTitle(const char * title) { mTitle = title; }

private:
    int mWidth, mHeight, mFlags;
    const char * mTitle;

};