#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Window.h"
#include "Layer.h"
#include "Button.h"
#include "Application.h"
#include "MusicList.h"
#include "Vertical_Bar.h"
#include "MusicManagement.h"
#include <thread>
#include <chrono>

int main() {
  /***************************    LOAD MUSIC     ***********************************/
   //Initialize SDL_mixer
  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
  {
    return -1;
  }

  //Load music
  MusicList musicList;
  // musicList.addSong("music/vinhtuyBridge.mp3");
  // musicList.addSong("music/gruppa-krovi.mp3");

  MusicManagement musicPlayer;
  musicPlayer.addMusicList(musicList);
  musicPlayer.addSongToList("music/vinhtuyBridge.mp3");
  musicPlayer.addSongToList("music/gruppa-krovi.mp3");

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

  Vertical_Bar VolumeVertical_Bar { &App, "img/volume_bar.png", 
                  (GameWindow.GetWindowWidth() / 2) + 250, (GameWindow.GetWindowHeight() / 2) - 80}; 

  Button PlayButton { &App , "img/play.png" , [&musicPlayer]() { musicPlayer.playMusic(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 50, GameWindow.GetWindowHeight() / 2};
  Button PauseButton { &App , "img/pause.png" , [&musicPlayer]() { musicPlayer.pauseMusic(); }, 
                    (GameWindow.GetWindowWidth() / 2) + 50, GameWindow.GetWindowHeight() / 2};
  Button VolumeDownButton { &App , "img/volume_down.png" , [&VolumeVertical_Bar, &musicPlayer]() { musicPlayer.volumeDown(); VolumeVertical_Bar.SetValue( int((float(musicPlayer.getVolume()) / 128) * VolumeVertical_Bar.GetVertical_BarHeght()) ); },
                    (GameWindow.GetWindowWidth() / 2) + 235, (GameWindow.GetWindowHeight() / 2) + 135};
  Button VolumeUpButton { &App , "img/volume_up.png" , [&VolumeVertical_Bar, &musicPlayer]() { musicPlayer.volumeUp(); VolumeVertical_Bar.SetValue( int((float(musicPlayer.getVolume()) / 128) * VolumeVertical_Bar.GetVertical_BarHeght()) ); },
                    (GameWindow.GetWindowWidth() / 2) + 235, (GameWindow.GetWindowHeight() / 2) - 140};
  Button PreviousTrackButton { &App , "img/previous_track.png" , [&musicPlayer]() { musicPlayer.previousSong(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 50, (GameWindow.GetWindowHeight() / 2) + 60};                    
  Button NextTrackButton { &App , "img/next_track.png" , [&musicPlayer]() { musicPlayer.nextSong(); }, 
                    (GameWindow.GetWindowWidth() / 2) + 50, (GameWindow.GetWindowHeight() / 2) + 60};
  Button AddMusicButton { &App , "img/add.png" , [&musicPlayer]() { musicPlayer.addSongToListManual(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 50, (GameWindow.GetWindowHeight() / 2) - 60};  
  Button InfoButton { &App , "img/info.png" , [&musicPlayer]() { musicPlayer.infoMetadata(); }, 
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
  App.SubscribeToRender(&VolumeVertical_Bar);

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
    musicPlayer.Update();
  }
  Mix_CloseAudio();
}
