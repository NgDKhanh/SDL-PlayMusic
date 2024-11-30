#pragma once

#include <iostream>
#include <list>
#include <memory>
#include "sys/stat.h"
#include <SDL2/SDL_mixer.h>
#include "MusicList.h"
#include "DataControl.h"

class MusicManagement : public BaseComponent
{
public:
    MusicManagement(): 
        mIsPlaying(false),
        mIsPlayed(false),
        mPlayMode(0),
        mVolume(64),
        mCurrentMusicList(mMusicLists.begin())
    {
        Mix_VolumeMusic(mVolume);
    } 

    int getVolume() { return mVolume; }

    void pauseMusic();

    void playMusic();

    void nextSong();

    void previousSong();

    void volumeUp();

    void volumeDown();

    const int getVolume() const { return mVolume; } 

    void addMusicList(const MusicList& musicList);

    void addSongToList(const std::string& path);

    void addSongToListManual();

    static void playDoneCallBack();

    bool getIsPlaying() { return mIsPlaying; }

    void setPlayMode (const uint8_t mode) { mPlayMode = mode; }

    void infoMetadata();

    void Update();

private:
    bool mIsPlaying;
    bool mIsPlayed;
    uint8_t mPlayMode;
    int mVolume;
    std::list<MusicList> mMusicLists;
    std::list<MusicList>::iterator mCurrentMusicList;
};