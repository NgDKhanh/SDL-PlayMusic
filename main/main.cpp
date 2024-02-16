#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Window.h"
#include "Layer.h"
#include "Button.h"
#include "Application.h"
#include "MusicList.h"
#include <thread>
#include <chrono>

void pauseMusic()
{
  if (Mix_PlayingMusic() != 0)
  {
    //If the music is paused
    if( Mix_PausedMusic() != 1 )
    {
      //Pause the music
      Mix_PauseMusic();
    }
  }
}

int volume = 64;

void volumeUp()
{
  if (volume <= 116)
  {
    volume += 12;
    Mix_VolumeMusic(volume);
  }
}

void volumeDown()
{
  if (volume >= 12)
  {
    volume -= 12;
    Mix_VolumeMusic(volume);
  }
}

int main() {
  /***************************    LOAD MUSIC     ***********************************/
   //Initialize SDL_mixer
  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
  {
    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    return -1;
  }

  //Load music
  MusicList musicList;
  musicList.addSong("./music/vinhtuyBridge.mp3");
  musicList.addSong("./music/gruppa-krovi.mp3");

  Mix_VolumeMusic(volume);

  /***********************************************************************************/
  Window GameWindow{"Music Player", SDL_WINDOW_SHOWN};
  GameWindow.SetBackgroundColor(0x40, 0x40, 0x40);
  GameWindow.Update();
  Application App { &GameWindow };
  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) )
  {
    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    return -1;
  }
  Layer UI;

  Button PlayButton { App.GetRenderer() , "./img/play.png" , [&musicList]() { musicList.playSongList(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 150, GameWindow.GetWindowHeight() / 2};
  Button PauseButton { App.GetRenderer() , "./img/pause.png" , pauseMusic, 
                    (GameWindow.GetWindowWidth() / 2) - 50, GameWindow.GetWindowHeight() / 2};
  Button VolumeDownButton { App.GetRenderer() , "./img/volume_down.png" , volumeDown, 
                    (GameWindow.GetWindowWidth() / 2) + 50, GameWindow.GetWindowHeight() / 2};
  Button VolumeUpButton { App.GetRenderer() , "./img/volume_up.png" , volumeUp, 
                    (GameWindow.GetWindowWidth() / 2) + 150, GameWindow.GetWindowHeight() / 2};
  Button PreviousTrackButton { App.GetRenderer() , "./img/previous_track.png" , [&musicList]() { musicList.previousTrack(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 50, (GameWindow.GetWindowHeight() / 2) + 60};                    
  Button NextTrackButton { App.GetRenderer() , "./img/next_track.png" , [&musicList]() { musicList.nextTrack(); }, 
                    (GameWindow.GetWindowWidth() / 2) + 50, (GameWindow.GetWindowHeight() / 2) + 60};
  Button AddMusicButton { App.GetRenderer() , "./img/add.png" , [&musicList]() { musicList.addMusicMannual(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 50, (GameWindow.GetWindowHeight() / 2) - 60};  
  Button InfoButton { App.GetRenderer() , "./img/info.png" , [&musicList]() { musicList.infoMetadata(); }, 
                    (GameWindow.GetWindowWidth() / 2) + 50, (GameWindow.GetWindowHeight() / 2) - 60};                    

  UI.SubscribeToEvents(&PlayButton);
  UI.SubscribeToEvents(&PauseButton);
  UI.SubscribeToEvents(&VolumeUpButton);
  UI.SubscribeToEvents(&VolumeDownButton);
  UI.SubscribeToEvents(&NextTrackButton);
  UI.SubscribeToEvents(&PreviousTrackButton);
  UI.SubscribeToEvents(&AddMusicButton);
  UI.SubscribeToEvents(&InfoButton);

  App.SubscribeToRender(&PlayButton);
  App.SubscribeToRender(&PauseButton);
  App.SubscribeToRender(&VolumeUpButton);
  App.SubscribeToRender(&VolumeDownButton);
  App.SubscribeToRender(&NextTrackButton);
  App.SubscribeToRender(&PreviousTrackButton);
  App.SubscribeToRender(&AddMusicButton);
  App.SubscribeToRender(&InfoButton);

  App.RenderObjects();

  SDL_Event Event;
  while(true) {
    while(SDL_PollEvent(&Event)) {
      if (Event.type == SDL_QUIT) {
        SDL_Quit();
        return 0;
      }
      if (UI.HandleEvent(&Event)) {
        App.RenderObjects();
        continue;
      }
    }
    GameWindow.RenderFrame();
  }
}