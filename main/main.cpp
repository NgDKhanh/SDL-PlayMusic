#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Window.h"
#include "Layer.h"
#include "Button.h"
#include "StateButton.h"
#include "Application.h"
#include "MusicList.h"
#include "Vertical_Bar.h"
#include "TimeBar.h"
#include "MusicManagement.h"
#include "Background.h"
#include "PlayPauseButton.h"
#include "MusicController.h"
#include "Text.h"
#include "FrameControl.h"
#include "PopUpBox.h"
#include <thread>
#include <chrono>

int main() {
  std::cout << "-------------\tMusic Player\t-------------" << std::endl;

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

  if (TTF_Init() < 0) {
    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    return -1;
  }

  SetFPS(static_cast<Uint16>(APP_FPS));

  std::cout << "-------------\tFPS:" << APP_FPS <<  "\t\t-------------" << std::endl;

  //Load music
  MusicList musicList;

  MusicManagement musicPlayer;
  musicPlayer.addMusicList(musicList);
  musicPlayer.addSongToList("../music/vinhtuyBridge.mp3");
  musicPlayer.addSongToList("../music/gruppa-krovi.mp3");

  /***********************************************************************************/
  Window GameWindow{"Music Player from KhanhND", SDL_WINDOW_SHOWN};
  GameWindow.SetBackgroundColor(0x40, 0x40, 0x40);
  GameWindow.Update();
  Application App { &GameWindow };
  Layer UI;

  bool AddSongPopUp = false;

  Background Background { &App, "../img/background.png" };

  Vertical_Bar VolumeVertical_Bar { &App, "../img/volume_bar.png", 
                  GameWindow.GetWindowWidth() - 75, (GameWindow.GetWindowHeight() / 2) - 80}; 

  TimeBar Time_Bar { &App, nullptr, "../img/time_bar.png", 
                  (GameWindow.GetWindowWidth() / 2 - 280), (GameWindow.GetWindowHeight() / 2) + 140};

  const char* PlayModeButtonTexturePaths[2] = {"../img/general_loop.png", "../img/single_loop.png"}; 
  std::function<void()> PlayModeButtonFunctions[2] = {[&musicPlayer]() { musicPlayer.setPlayMode(1); }, [&musicPlayer]() { musicPlayer.setPlayMode(0); }};

  StateButton PlayModeButton { &App, 2, PlayModeButtonTexturePaths, PlayModeButtonFunctions,  
                    (GameWindow.GetWindowWidth() / 2), (GameWindow.GetWindowHeight() / 2) + 60};

  const char* PlayPauseButtonTexturePaths[2] = {"../img/play.png", "../img/pause.png"}; 
  PlayPauseButton PlayPauseButton { &App, nullptr, 2, PlayPauseButtonTexturePaths, (GameWindow.GetWindowWidth() / 2), GameWindow.GetWindowHeight() / 2};
  PlayPauseButton.Init();

  SongTitle Title { &App, nullptr, ((GameWindow.GetWindowWidth() / 2) + 25), ((GameWindow.GetWindowHeight() / 2) + 200)};
  SongTitle Artist { &App, nullptr, ((GameWindow.GetWindowWidth() / 2) + 25), ((GameWindow.GetWindowHeight() / 2) + 250), 18};

  MusicController MusicControl { &PlayPauseButton, &Title, &Artist, &Time_Bar ,&musicPlayer };

  Button VolumeDownButton { &App , "../img/volume_down.png" , [&VolumeVertical_Bar, &musicPlayer]() { musicPlayer.volumeDown(); VolumeVertical_Bar.SetValue( int((float(musicPlayer.getVolume()) / 128) * VolumeVertical_Bar.GetVertical_BarHeght()) ); },
                    GameWindow.GetWindowWidth() - 90, (GameWindow.GetWindowHeight() / 2) + 135};
  Button VolumeUpButton { &App , "../img/volume_up.png" , [&VolumeVertical_Bar, &musicPlayer]() { musicPlayer.volumeUp(); VolumeVertical_Bar.SetValue( int((float(musicPlayer.getVolume()) / 128) * VolumeVertical_Bar.GetVertical_BarHeght()) ); },
                    GameWindow.GetWindowWidth() - 90, (GameWindow.GetWindowHeight() / 2) - 140};
  Button PreviousTrackButton { &App , "../img/previous_track.png" , [&musicPlayer]() { musicPlayer.previousSong(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 100, (GameWindow.GetWindowHeight() / 2)};                    
  Button NextTrackButton { &App , "../img/next_track.png" , [&musicPlayer]() { musicPlayer.nextSong(); }, 
                    (GameWindow.GetWindowWidth() / 2) + 100, (GameWindow.GetWindowHeight() / 2)};
  // Button AddMusicButton { &App , "../img/add.png" , [&musicPlayer]() { SDL_CreateThread(MusicManagement::AddSongToListManualWrapper, "AddSongThread", static_cast<void*>(&musicPlayer)); }, 
  Button AddMusicButton { &App , "../img/add.png" , [&AddSongPopUp]() { AddSongPopUp = true; }, 
                    (GameWindow.GetWindowWidth() / 2) + 100, (GameWindow.GetWindowHeight() / 2) - 60};  
  Button RemoveMusicButton { &App , "../img/minus.png" , [&musicPlayer]() { musicPlayer.removeSongFromList(); }, 
                    (GameWindow.GetWindowWidth() / 2) - 100, (GameWindow.GetWindowHeight() / 2) - 60};
  Button InfoButton { &App , "../img/info.png" , [&musicPlayer]() { musicPlayer.infoMetadata(); }, 
                    (GameWindow.GetWindowWidth() / 2), (GameWindow.GetWindowHeight() / 2) - 60}; 
  Button Forward_10SecondsButton { &App , "../img/forward_ten.png" , [&musicPlayer]() { musicPlayer.jumpForwardSeconds(10); }, 
                    (GameWindow.GetWindowWidth() / 2) + 200, (GameWindow.GetWindowHeight() / 2)};
  Button Backward_10SecondsButton { &App , "../img/backward_ten.png" , [&musicPlayer]() { musicPlayer.jumpBackwardSeconds(10); }, 
                    (GameWindow.GetWindowWidth() / 2) -200, (GameWindow.GetWindowHeight() / 2)};
  Button ListSongButton { &App , "../img/list.png" , [&musicPlayer]() { musicPlayer.printList(); }, 
                    50, 50};

  UI.SubscribeToEvents(&VolumeUpButton);
  UI.SubscribeToEvents(&VolumeDownButton);
  UI.SubscribeToEvents(&NextTrackButton);
  UI.SubscribeToEvents(&PreviousTrackButton);
  UI.SubscribeToEvents(&AddMusicButton);
  UI.SubscribeToEvents(&RemoveMusicButton);
  UI.SubscribeToEvents(&InfoButton);
  UI.SubscribeToEvents(&PlayPauseButton);
  UI.SubscribeToEvents(&PlayModeButton);
  UI.SubscribeToEvents(&Forward_10SecondsButton);
  UI.SubscribeToEvents(&Backward_10SecondsButton);
  UI.SubscribeToEvents(&ListSongButton);

  App.SubscribeToRender(&Background);
  App.SubscribeToRender(&VolumeUpButton);
  App.SubscribeToRender(&VolumeDownButton);
  App.SubscribeToRender(&NextTrackButton);
  App.SubscribeToRender(&PreviousTrackButton);
  App.SubscribeToRender(&AddMusicButton);
  App.SubscribeToRender(&RemoveMusicButton);
  App.SubscribeToRender(&InfoButton);
  App.SubscribeToRender(&VolumeVertical_Bar);
  App.SubscribeToRender(&Time_Bar);
  App.SubscribeToRender(&PlayPauseButton);
  App.SubscribeToRender(&PlayModeButton);
  App.SubscribeToRender(&Forward_10SecondsButton);
  App.SubscribeToRender(&Backward_10SecondsButton);
  App.SubscribeToRender(&ListSongButton);
  App.SubscribeToRender(&Title);
  App.SubscribeToRender(&Artist);

  SDL_Event Event;

  while (true) {
    GetFrameStart(SDL_GetTicks());

    // Handle events
    while (SDL_PollEvent(&Event)) {
        if (Event.type == SDL_QUIT) {
            SDL_Quit();
            return 0;
        }
        else if (UI.HandleEvent(&Event)) {
            continue;
        }
    }

    if (AddSongPopUp == true) {
      PopUpBox AddMusicBox(&App, PopUpBox::POP_UP_BOX_KIND::INPUT,
                            GameWindow.GetWindowWidth(), GameWindow.GetWindowHeight());
      std::string path = AddMusicBox.showPopUp("Enter song's path");
      PopUpBox AddMusicResultBox(&App, PopUpBox::POP_UP_BOX_KIND::INFO,
                            GameWindow.GetWindowWidth(), GameWindow.GetWindowHeight());
      if (path != "Default" && path != " ") {
        if (musicPlayer.addSongToList(path)) {
          AddMusicResultBox.showPopUp("Add song OK");
        }
        else {
          AddMusicResultBox.showPopUp("Add song fail");
        }
      }
      else {
        std::cout << "Cancel" << std::endl;
      }
      AddSongPopUp = false;
    }

    // Update objects, render, and handle music
    App.RenderObjects();
    GameWindow.RenderFrame();
    musicPlayer.Update();

    FrameDelayControl();
  }
}
