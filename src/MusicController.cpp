#include "MusicController.h"

void MusicController::Notify(BaseComponent *sender, std::string event) const {
    if (event == "Play") {
        this->mMusicManagement->playMusic();
    }
    else if (event == "Pause") {
        this->mMusicManagement->pauseMusic();
    }
    else if (event == "nextSong" || event == "previousSong") {
        this->mPlayPauseButton->SetState(PlayPauseButton::PlayingMode::PAUSE);
    }
}