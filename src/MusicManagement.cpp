#include "MusicManagement.h"

void MusicManagement::pauseMusic() 
{
    (*mCurrentMusicList).pauseSong();
    mIsPlaying = false;
}

void MusicManagement::playMusic()
{
    (*mCurrentMusicList).playSong();
    mIsPlaying = true;
    mIsPlayed = true;
}

void MusicManagement::nextSong()
{
    (*mCurrentMusicList).nextSong();
    mIsPlaying = true;
    mIsPlayed = true;
    mediator_->Notify(this, "nextSong");
    mediator_->Notify(this, "SongName:" + (*mCurrentMusicList).getSongMetadata().Title);
    mediator_->Notify(this, "Artist:" + (*mCurrentMusicList).getSongMetadata().Artist);
}

void MusicManagement::previousSong()
{
    (*mCurrentMusicList).previousSong();
    mIsPlaying = true;
    mIsPlayed = true;
    mediator_->Notify(this, "previousSong");
    mediator_->Notify(this, "SongName:" + (*mCurrentMusicList).getSongMetadata().Title);
    mediator_->Notify(this, "Artist:" + (*mCurrentMusicList).getSongMetadata().Artist);
}

void MusicManagement::jumpForwardSeconds(uint32_t seconds)
{
    (*mCurrentMusicList).jumpForward(seconds);
}

void MusicManagement::jumpBackwardSeconds(uint32_t seconds)
{
    (*mCurrentMusicList).jumpBackward(seconds);
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
    if (!mFirstUpdate) {
        // Send info about initial metadata of music to UI components
        mediator_->Notify(this, "SongName:" + (*mCurrentMusicList).getSongMetadata().Title);
        mediator_->Notify(this, "Artist:" + (*mCurrentMusicList).getSongMetadata().Artist);
        mFirstUpdate = true;
    }
    //If the music is play done
    if (Mix_PlayingMusic() == 0 && mIsPlayed == true)
    {
        if (mPlayMode == 0) {
            //If the music is not paused
            if( Mix_PausedMusic() != 1 )
            {
                nextSong();
            }
        }
        else if (mPlayMode == 1) {
            //If the music is not paused
            if( Mix_PausedMusic() != 1 )
            {
                (*mCurrentMusicList).playSong();
            }
        }
    }
}

void MusicManagement::infoMetadata()
{
    (*mCurrentMusicList).infoMetadata();
}