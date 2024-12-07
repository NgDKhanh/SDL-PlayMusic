#pragma once

#include "DataControl.h"
#include "PlayPauseButton.h"
#include "MusicManagement.h"
#include "SongTitle.h"

class MusicController : public Mediator {
public:
    MusicController(PlayPauseButton *playPauseButton, SongTitle *songTitle, SongTitle *artist, MusicManagement *musicManagement) :
        mPlayPauseButton(playPauseButton), mMusicManagement(musicManagement), mSongTitle(songTitle), mArtist(artist)
    {
        mPlayPauseButton->set_mediator(this);
        mMusicManagement->set_mediator(this);
        mSongTitle->set_mediator(this);
        mArtist->set_mediator(this);
    }

    void Notify(BaseComponent *sender, std::string event) const override;

private:
    PlayPauseButton *mPlayPauseButton;
    MusicManagement *mMusicManagement;
    SongTitle *mSongTitle;
    SongTitle *mArtist;
};