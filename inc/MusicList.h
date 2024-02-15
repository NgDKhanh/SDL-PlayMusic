#pragma once

#include <iostream>
#include <list>
#include <memory>
#include <SDL2/SDL_mixer.h>
#include "Song.h"

class MusicList
{
public:
  MusicList(): currentPlayingSong{listSong.end()} {} 

  void addSong(const std::string& path);

  void addMusicMannual();

  void playSongList();

  void nextTrack();

  void previousTrack();

  void infoMetadata();

  void modifyMetadata();

private:
  std::list<Song> listSong;
  std::list<Song>::iterator currentPlayingSong;
};