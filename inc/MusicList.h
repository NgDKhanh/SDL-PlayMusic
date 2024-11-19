#pragma once

#include <iostream>
#include <list>
#include <memory>
#include "sys/stat.h"
#include <SDL2/SDL_mixer.h>
#include "Song.h"

class MusicList
{
public:
  MusicList(): 
    mMusicListName("default"),
    currentPlayingSong{listSong.begin()}
  {

  } 

  MusicList(std::string name): 
    mMusicListName(name),
    currentPlayingSong{listSong.begin()}
  {

  } 

  void addSong(const std::string& path);

  void addMusicMannual();

  void playSongList();

  void nextSong();

  void previousSong();

  void infoMetadata();

  void modifyMetadata();

  void setMusicListName(std::string &name) { mMusicListName = name; }

  const std::string getMusicListName() { return mMusicListName; }

private:
  std::string mMusicListName;
  std::list<Song> listSong;
  std::list<Song>::iterator currentPlayingSong;
};