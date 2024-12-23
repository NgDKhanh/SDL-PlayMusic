#pragma once

#include <iostream>
#include <list>
#include <memory>
#include "sys/stat.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Song.h"

class MusicList
{
public:
  MusicList(): 
    mMusicListName("default"),
    currentPlayingSong{listSong.begin()},
    mStartPlayTime(0),
    mOffsetTime(0.0)
  {

  } 

  MusicList(std::string name): 
    mMusicListName(name),
    currentPlayingSong{listSong.begin()},
    mStartPlayTime(0),
    mOffsetTime(0.0)
  {

  } 

  bool addSong(const std::string& path);

  void addMusicMannual();

  void removeSong(const uint8_t songIndex);

  void playSong();

  void pauseSong();

  void nextSong();

  void previousSong();

  void infoMetadata();

  void modifyMetadata();

  void setMusicListName(std::string &name) { mMusicListName = name; }

  const std::string getMusicListName() { return mMusicListName; }

  const SongMetadata getSongMetadata() { return currentPlayingSong->getMetadata(); }

  const double getCurrentSongPlayPosition();

  void jumpForward(uint32_t seconds);

  void jumpBackward(uint32_t seconds);

  void printList();

private:
  std::string mMusicListName;
  std::list<Song> listSong;
  std::list<Song>::iterator currentPlayingSong;
  uint32_t mStartPlayTime;
  double mOffsetTime;
};