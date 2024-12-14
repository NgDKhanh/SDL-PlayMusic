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
    else if (event.find("SongName") == 0) {
        size_t pos = event.find(':');

        if (pos != std::string::npos) {
            std::string SongName = event.substr(pos+1);

            mSongTitle->SetText(SongName);
        }
    }
    else if (event.find("Artist") == 0) {
        size_t pos = event.find(':');

        if (pos != std::string::npos) {
            std::string Artist = event.substr(pos+1);

            mArtist->SetText(Artist);
        }
    }
    else if (event.find("Time" == 0)) {
        size_t pos = event.find(':');

        if (pos != std::string::npos) {
            double currentTimeRatio = std::stod(event.substr(pos+1));

            mTimeBar->SetRatio(currentTimeRatio);
        }
    }
}