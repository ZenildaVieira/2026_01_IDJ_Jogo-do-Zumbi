#pragma once

class State {
public:
    State();
    bool QuitRequested() const;
    void LoadAssets();
    void Update(float dt);
    void Render();
private:
    Sprite bg;
    Music music;
    bool quitRequested;
};