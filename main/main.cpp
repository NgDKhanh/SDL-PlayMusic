#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Window.h"
#include "Layer.h"
#include "Button.h"
#include "Application.h"

//The music that will be played
Mix_Music *gMusic = NULL;

void printGoodbye()
{
  std::cout << "Goodbye" << std::endl;
}

void playMusic()
{
  if (Mix_PlayingMusic() == 0)
  {
    //Play the music
    Mix_PlayMusic( gMusic, -1 );
    
  }
  else
  {
    //If the music is paused
    if( Mix_PausedMusic() == 1 )
    {
      //Resume the music
      Mix_ResumeMusic();
    }
  }
}

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
	gMusic = Mix_LoadMUS( "./music/vinhtuyBridge.mp3");
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		return -1;
	}
  Mix_VolumeMusic(volume);

  /***********************************************************************************/
  Window GameWindow{"Button", 0};
  GameWindow.SetBackgroundColor(155, 155, 155);
  GameWindow.Update();
  Application App { &GameWindow };
  int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) )
  {
    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    return -1;
  }
  Layer UI;
  Button PlayButton { &App , "./img/play.png" , playMusic, 
                    (GameWindow.GetWindowWidth() / 2) - 150, GameWindow.GetWindowHeight() / 2};
  Button PauseButton { &App , "./img/pause.png" , pauseMusic, 
                    (GameWindow.GetWindowWidth() / 2) - 50, GameWindow.GetWindowHeight() / 2};
  Button VolumeUpButton { &App , "./img/volume_up.png" , volumeUp, 
                    (GameWindow.GetWindowWidth() / 2) + 50, GameWindow.GetWindowHeight() / 2};
  Button VolumeDownButton { &App , "./img/volume_down.png" , volumeDown, 
                    (GameWindow.GetWindowWidth() / 2) + 150, GameWindow.GetWindowHeight() / 2};
  UI.SubscribeToEvents(&PlayButton);
  UI.SubscribeToEvents(&PauseButton);
  UI.SubscribeToEvents(&VolumeUpButton);
  UI.SubscribeToEvents(&VolumeDownButton);
  SDL_RenderPresent(App.GetRenderer());

  SDL_Event Event;
  while(true) {
    while(SDL_PollEvent(&Event)) {
      if (Event.type == SDL_QUIT) {
        Mix_FreeMusic( gMusic );
        gMusic = NULL;
        SDL_Quit();
        return 0;
      }
      if (UI.HandleEvent(&Event)) {
        // SDL_SetRenderDrawColor( App.GetRenderer(), 0x40, 0x40, 0x40, 0xFF );
        // SDL_RenderClear(App.GetRenderer());
        SDL_RenderPresent(App.GetRenderer());
        continue;
      }
    }
    GameWindow.RenderFrame();
  }
}