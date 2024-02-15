#include "Music.h"

void MusicList::addMusic(const std::string& path)
{
    Mix_Music* gMusic = Mix_LoadMUS(path.c_str());

    if (gMusic == nullptr)
    {
        std::cerr << "Failed to load music from " << path << ": " << Mix_GetError() << std::endl;
    }
    else
    {
        listMusic.push_back(std::shared_ptr<Mix_Music>(gMusic, Mix_FreeMusic));
    }
}

void MusicList::addMusicMannual()
{
    std::string path;
    std::cout << "Enter the path to music: ";
    std::cin >> path;
    
    Mix_Music *gMusic = Mix_LoadMUS(path.c_str());

    if(gMusic == nullptr)
    {
        std::cerr << "Failed to load music from " << path << ": " << Mix_GetError() << std::endl;
    }
    else
    {
        listMusic.push_back(std::shared_ptr<Mix_Music>(gMusic, Mix_FreeMusic));
    }
}

void MusicList::playMusicList()
{
    if (!listMusic.empty()) {
        if (currentPlaying == listMusic.end()) {
            // If at the end of the list, loop back to the beginning
            currentPlaying = listMusic.begin();
        }

        if (Mix_PlayingMusic() == 0)
        {
        //Play the music
        Mix_PlayMusic( (*currentPlaying).get(), 0 );
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
    else 
    {
        std::cout << "list empty" << std::endl;
    }
}

void MusicList::nextTrack()
{
    if (!listMusic.empty()) {
        currentPlaying++;   // Move to the next music in the list
        if (currentPlaying == listMusic.end())
        {
            currentPlaying = listMusic.begin();
        }
        

        if (Mix_PlayingMusic() == 1)
        {
            //Pause the music
            Mix_PauseMusic();
        }
        //Play the music
        Mix_PlayMusic( (*currentPlaying).get(), 0 );
    } 
    else 
    {
        std::cout << "list empty" << std::endl;
    }
}

void MusicList::previousTrack()
{
    if (!listMusic.empty()) {
        if (currentPlaying != listMusic.begin())
        {
            currentPlaying--;   // Move to the next music in the list
        }
        if (Mix_PlayingMusic() == 1)
        {
            //Pause the music
            Mix_PauseMusic();
        }
        //Play the music
        Mix_PlayMusic( (*currentPlaying).get(), 0 );
        if (currentPlaying == listMusic.end()) {
            // If at the end of the list, loop back to the beginning
            currentPlaying = listMusic.begin();
        }
        else
        {
            ++currentPlaying;  // Move to the next music in the list
        }
        
    } 
    else 
    {
        std::cout << "list empty" << std::endl;
    }
}