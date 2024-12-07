#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <SDL2/SDL_mixer.h>
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <chrono>

struct SongMetadata {
    std::string Title;
    std::string Artist;
    std::string Album;
    unsigned int Year;
    unsigned int Track;
    int Bitrate;
    int Chanel;
    int Length;
};

class Song
{
public:
    Song(const std::string &path);

    void loadMusic(const std::string &path);

    Mix_Music* getMusic() const
    {
        return this->music.get();
    }

    void printMetadata();

    const SongMetadata getMetadata();

private:
    TagLib::FileRef fileRef;
    std::string path;
    std::shared_ptr<Mix_Music> music;
};