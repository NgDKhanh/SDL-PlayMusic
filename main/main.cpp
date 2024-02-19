#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Window.h"
#include "Layer.h"
#include "Button.h"
#include "Application.h"
#include "MusicList.h"
#include "Bar.h"
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
  if (volume <= 112)
  {
    volume += 16;
    Mix_VolumeMusic(volume);
  }
}

void volumeDown()
{
  if (volume >= 16)
  {
    volume -= 16;
    Mix_VolumeMusic(volume);
  }
}

int main() {
  /***************************    LOAD MUSIC     ***********************************/
   //Initialize SDL_mixer
  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
  {
    return -1;
  }

  //Load music
  MusicList musicList;
  musicList.addSong("./music/vinhtuyBridge.mp3");
  musicList.addSong("./music/gruppa-krovi.mp3");

  // Mix_VolumeMusic(volume);

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

  Bar VolumeBar { &App, "./img/volume_bar.png", 
                  (GameWindow.GetWindowWidth() / 2) + 250, (GameWindow.GetWindowHeight() / 2) - 80};

  Button PlayButton { &App , "./img/play.png" , [&musicList]() { musicList.playSongList(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 50, GameWindow.GetWindowHeight() / 2};
  Button PauseButton { &App , "./img/pause.png" , pauseMusic, 
                    (GameWindow.GetWindowWidth() / 2) + 50, GameWindow.GetWindowHeight() / 2};
  Button VolumeDownButton { &App , "./img/volume_down.png" , [&VolumeBar]() { volumeDown(); VolumeBar.SetValue( int((float(volume) / 128) * VolumeBar.GetBarHeght()) ); },
                    (GameWindow.GetWindowWidth() / 2) + 235, (GameWindow.GetWindowHeight() / 2) + 135};
  Button VolumeUpButton { &App , "./img/volume_up.png" , [&VolumeBar]() { volumeUp(); VolumeBar.SetValue( int((float(volume) / 128) * VolumeBar.GetBarHeght()) ); },
                    (GameWindow.GetWindowWidth() / 2) + 235, (GameWindow.GetWindowHeight() / 2) - 140};
  Button PreviousTrackButton { &App , "./img/previous_track.png" , [&musicList]() { musicList.previousTrack(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 50, (GameWindow.GetWindowHeight() / 2) + 60};                    
  Button NextTrackButton { &App , "./img/next_track.png" , [&musicList]() { musicList.nextTrack(); }, 
                    (GameWindow.GetWindowWidth() / 2) + 50, (GameWindow.GetWindowHeight() / 2) + 60};
  Button AddMusicButton { &App , "./img/add.png" , [&musicList]() { musicList.addMusicMannual(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 50, (GameWindow.GetWindowHeight() / 2) - 60};  
  Button InfoButton { &App , "./img/info.png" , [&musicList]() { musicList.infoMetadata(); }, 
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
  App.SubscribeToRender(&VolumeBar);

  SDL_SetRenderDrawColor( App.GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
  SDL_RenderClear(App.GetRenderer());
  SDL_RenderPresent(App.GetRenderer());

  SDL_Event Event;
  while(true) {
    while(SDL_PollEvent(&Event)) {
      if (Event.type == SDL_QUIT) {
        SDL_Quit();
        return 0;
      }
      if (UI.HandleEvent(&Event)) {
        continue;
      }
    }
    App.RenderObjects();
    GameWindow.RenderFrame();
  }
  Mix_CloseAudio();
}