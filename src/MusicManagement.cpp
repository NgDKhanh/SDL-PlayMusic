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
            mIsPlaying = false;
        }
    }
}

void MusicManagement::playMusic()
{
    (*mCurrentMusicList).playSongList();
    mIsPlaying = true;
    mIsPlayed = true;
}

void MusicManagement::nextSong()
{
    (*mCurrentMusicList).nextSong();
    mIsPlaying = true;
    mIsPlayed = true;
    mediator_->Notify(this, "nextSong");
}

void MusicManagement::previousSong()
{
    (*mCurrentMusicList).previousSong();
    mIsPlaying = true;
    mIsPlayed = true;
    mediator_->Notify(this, "previousSong");
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
    //If the music is play done
    if (Mix_PlayingMusic() == 0 && mIsPlayed == true)
    {
        if (mPlayMode == 0) {
            //If the music is not paused
            if( Mix_PausedMusic() != 1 )
            {
                (*mCurrentMusicList).nextSong();
            }
        }
        else if (mPlayMode == 1) {
            //If the music is not paused
            if( Mix_PausedMusic() != 1 )
            {
                (*mCurrentMusicList).playSongList();
            }
        }
    }
}

void MusicManagement::infoMetadata()
{
    (*mCurrentMusicList).infoMetadata();
}