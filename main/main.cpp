#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Window.h"
#include "Layer.h"
#include "Button.h"
#include "StateButton.h"
#include "Application.h"
#include "MusicList.h"
#include "Vertical_Bar.h"
#include "MusicManagement.h"
#include "Background.h"
#include "PlayPauseButton.h"
#include "MusicController.h"
#include <thread>
#include <chrono>

int main() {
  /***************************    LOAD MUSIC     ***********************************/
   //Initialize SDL_mixer
  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
  {
    return -1;
  }

  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) )
  {
    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
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

  /***********************************************************************************/
  Window GameWindow{"Music Player from KhanhND", SDL_WINDOW_SHOWN};
  GameWindow.SetBackgroundColor(0x40, 0x40, 0x40);
  GameWindow.Update();
  Application App { &GameWindow };
  Layer UI;

  Background Background { &App, "img/background.png" };

  Vertical_Bar VolumeVertical_Bar { &App, "img/volume_bar.png", 
                  (GameWindow.GetWindowWidth() / 2) + 250, (GameWindow.GetWindowHeight() / 2) - 80}; 

  const char* PlayModeButtonTexturePaths[2] = {"img/general_loop.png", "img/single_loop.png"}; 
  std::function<void()> PlayModeButtonFunctions[2] = {[&musicPlayer]() { musicPlayer.setPlayMode(1); }, [&musicPlayer]() { musicPlayer.setPlayMode(0); }};

  StateButton PlayModeButton { &App, 2, PlayModeButtonTexturePaths, PlayModeButtonFunctions,  
                    (GameWindow.GetWindowWidth() / 2), (GameWindow.GetWindowHeight() / 2) + 60};

  const char* PlayPauseButtonTexturePaths[2] = {"img/play.png", "img/pause.png"}; 
  PlayPauseButton PlayPauseButton { &App, nullptr, 2, PlayPauseButtonTexturePaths, (GameWindow.GetWindowWidth() / 2), GameWindow.GetWindowHeight() / 2};
  PlayPauseButton.Init();

  MusicController MusicControl { &PlayPauseButton, &musicPlayer };

  Button VolumeDownButton { &App , "img/volume_down.png" , [&VolumeVertical_Bar, &musicPlayer]() { musicPlayer.volumeDown(); VolumeVertical_Bar.SetValue( int((float(musicPlayer.getVolume()) / 128) * VolumeVertical_Bar.GetVertical_BarHeght()) ); },
                    (GameWindow.GetWindowWidth() / 2) + 235, (GameWindow.GetWindowHeight() / 2) + 135};
  Button VolumeUpButton { &App , "img/volume_up.png" , [&VolumeVertical_Bar, &musicPlayer]() { musicPlayer.volumeUp(); VolumeVertical_Bar.SetValue( int((float(musicPlayer.getVolume()) / 128) * VolumeVertical_Bar.GetVertical_BarHeght()) ); },
                    (GameWindow.GetWindowWidth() / 2) + 235, (GameWindow.GetWindowHeight() / 2) - 140};
  Button PreviousTrackButton { &App , "img/previous_track.png" , [&musicPlayer]() { musicPlayer.previousSong(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 100, (GameWindow.GetWindowHeight() / 2)};                    
  Button NextTrackButton { &App , "img/next_track.png" , [&musicPlayer]() { musicPlayer.nextSong(); }, 
                    (GameWindow.GetWindowWidth() / 2) + 100, (GameWindow.GetWindowHeight() / 2)};
  Button AddMusicButton { &App , "img/add.png" , [&musicPlayer]() { musicPlayer.addSongToListManual(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 50, (GameWindow.GetWindowHeight() / 2) - 60};  
  Button InfoButton { &App , "img/info.png" , [&musicPlayer]() { musicPlayer.infoMetadata(); }, 
                    (GameWindow.GetWindowWidth() / 2) + 50, (GameWindow.GetWindowHeight() / 2) - 60}; 

  UI.SubscribeToEvents(&VolumeUpButton);
  UI.SubscribeToEvents(&VolumeDownButton);
  UI.SubscribeToEvents(&NextTrackButton);
  UI.SubscribeToEvents(&PreviousTrackButton);
  UI.SubscribeToEvents(&AddMusicButton);
  UI.SubscribeToEvents(&InfoButton);
  UI.SubscribeToEvents(&PlayPauseButton);
  UI.SubscribeToEvents(&PlayModeButton);

  App.SubscribeToRender(&Background);
  App.SubscribeToRender(&VolumeUpButton);
  App.SubscribeToRender(&VolumeDownButton);
  App.SubscribeToRender(&NextTrackButton);
  App.SubscribeToRender(&PreviousTrackButton);
  App.SubscribeToRender(&AddMusicButton);
  App.SubscribeToRender(&InfoButton);
  App.SubscribeToRender(&VolumeVertical_Bar);
  App.SubscribeToRender(&PlayPauseButton);
  App.SubscribeToRender(&PlayModeButton);

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
    App.RenderObjects();
    GameWindow.RenderFrame();
    musicPlayer.Update();
  }
  Mix_CloseAudio();
}
