#pragma once

#include <iostream>
#include <list>
#include <memory>
#include <SDL2/SDL_mixer.h>

class MusicList
{
public:
  MusicList(): currentPlaying{listMusic.end()}{} 

  void addMusic(const std::string& path);

  void addMusicMannual();

  void playMusicList();

  void nextTrack();

  void previousTrack();

  // void pauseMusic()
  // {

  // }
private:
  std::list<std::shared_ptr<Mix_Music>> listMusic;
  std::list<std::shared_ptr<Mix_Music>>::iterator currentPlaying;
};