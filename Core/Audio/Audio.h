#pragma once
#include <SFML/Audio.hpp>

namespace Engine
{
    class Audio
    {
    private:
        sf::Music m_Music;
    public:
        Audio(const char* fileName);
        ~Audio();

        void play();
        void pause();
        void stop();

        float getDuration();
        float getRemainingDuration();

        float getPlayingOffset();
        void setPlayingOffset(float duration);

        float getVolume();
        void setVolume(float volume);
    };
}