#include "Core/Audio/Audio.h"

#include <iostream>

namespace Engine
{
    Audio::Audio(const char* fileName) {
        if (!m_Music.openFromFile(fileName)) {
            std::cerr << "Couldn't load audio file " << fileName << std::endl;
        }
    }
    
    Audio::~Audio() {
    }
    
    void Audio::play() {
        m_Music.play();
    }

    void Audio::pause() {
        m_Music.pause();
    }

    void Audio::stop() {
        m_Music.stop();
    }

    float Audio::getDuration()
    {
        return m_Music.getDuration().asSeconds();
    }
    float Audio::getRemainingDuration()
    {
        return m_Music.getDuration().asSeconds() - m_Music.getPlayingOffset().asSeconds(); 
    }

    void Audio::setPlayingOffset(float playOffset)
    {
        m_Music.setPlayingOffset(sf::seconds(playOffset));
    }

    float Audio::getVolume()
    {
        return m_Music.getVolume();
    }

    void Audio::setVolume(float volume)
    {
        m_Music.setVolume(volume);
    }
}
