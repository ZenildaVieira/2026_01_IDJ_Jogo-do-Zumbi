#pragma once

#include <string>
#include <SDL_mixer.h>

class Music {
    
public:
    Music();
    Music(const std::string& file);
    ~Music();

    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(const std::string& file);
    bool IsOpen() const;

private:
    Mix_Music* music;
};
