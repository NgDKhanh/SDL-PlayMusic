#pragma once

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include "sys/stat.h"
#include <SDL2/SDL_mixer.h>
#include "MusicList.h"
#include "DataControl.h"
#include <chrono>

class MusicManagement : public BaseComponent
{
public:
    MusicManagement(): 
        mFirstUpdate(false),
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

    void jumpForwardSeconds(uint32_t seconds);

    void jumpBackwardSeconds(uint32_t seconds);

    void volumeUp();

    void volumeDown();

    const int getVolume() const { return mVolume; } 

    void addMusicList(const MusicList& musicList);

    bool addSongToList(const std::string& path);

    void addSongToListManual();

    void removeSongFromList();

    static void playDoneCallBack();

    bool getIsPlaying() { return mIsPlaying; }

    void setPlayMode (const uint8_t mode) { mPlayMode = mode; }

    void infoMetadata();

    void printList();

    void Update();

    static int AddSongToListManualWrapper(void* data) {
        MusicManagement* musicManagement = static_cast<MusicManagement*>(data);

        musicManagement->addSongToListManual();

        return 0;
    }

private:
    bool mFirstUpdate;
    bool mIsPlaying;
    bool mIsPlayed;
    uint8_t mPlayMode;
    int mVolume;
    std::list<MusicList> mMusicLists;
    std::list<MusicList>::iterator mCurrentMusicList;
};

