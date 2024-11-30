#pragma once

#include "DataControl.h"
#include "PlayPauseButton.h"
#include "MusicManagement.h"

class MusicController : public Mediator {
public:
    MusicController(PlayPauseButton *playPauseButton, MusicManagement *musicManagement) :
        mPlayPauseButton(playPauseButton), mMusicManagement(musicManagement) 
    {
        mPlayPauseButton->set_mediator(this);
        mMusicManagement->set_mediator(this);
    }

    void Notify(BaseComponent *sender, std::string event) const override;

private:
    PlayPauseButton *mPlayPauseButton;
    MusicManagement *mMusicManagement;
};