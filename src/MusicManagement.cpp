#include "MusicManagement.h"

void MusicManagement::pauseMusic() 
{
    if (Mix_PlayingMusic() != 0)
    {
        //If the music is paused
        if( Mix_PausedMusic() != 1 )
        {
            //Pause the music
            Mix_PauseMusic();
        }
    }
}

void MusicManagement::playMusic()
{
    (*mCurrentMusicList).playSongList();
    mIsPlayed = true;
}

void MusicManagement::nextSong()
{
    (*mCurrentMusicList).nextSong();
    mIsPlayed = true;
}

void MusicManagement::previousSong()
{
    (*mCurrentMusicList).previousSong();
    mIsPlayed = true;
}

void MusicManagement::volumeUp()
{
    if (mVolume <= 112)
    {
        mVolume += 16;
        Mix_VolumeMusic(mVolume);
    }
}

void MusicManagement::volumeDown()
{
    if (mVolume >= 16)
    {
        mVolume -= 16;
        Mix_VolumeMusic(mVolume);
    }
}

void MusicManagement::addMusicList(const MusicList& MusicList)
{
    mMusicLists.push_back(MusicList);
    if (mCurrentMusicList == mMusicLists.end())
    {
        mCurrentMusicList = mMusicLists.begin();
    }
}

void MusicManagement::addSongToList(const std::string& path)
{
    (*mCurrentMusicList).addSong(path);
}

void MusicManagement::addSongToListManual()
{
    (*mCurrentMusicList).addMusicMannual();
}

void MusicManagement::Update()
{
    //If the music is not play done
    if (Mix_PlayingMusic() == 0 && mIsPlayed == true)
    {
        //If the music is not paused
        if( Mix_PausedMusic() != 1 )
        {
            (*mCurrentMusicList).nextSong();
        }
    }
}

void MusicManagement::infoMetadata()
{
    (*mCurrentMusicList).infoMetadata();
}