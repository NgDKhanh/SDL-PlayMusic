#include "MusicList.h"

void MusicList::addSong(const std::string& path)
{
    Song newSong(path);
    listSong.push_back(newSong);
}

void MusicList::addMusicMannual()
{
    std::string path;
    std::cout << "Enter the path to music: ";
    std::cin >> path;
    
    addSong(path);
}

void MusicList::playSongList()
{
    if (!listSong.empty()) {
        if (currentPlayingSong == listSong.end()) {
            // If at the end of the list, loop back to the beginning
            currentPlayingSong = listSong.begin();
        }

        if (Mix_PlayingMusic() == 0)
        {
        //Play the music
        Mix_PlayMusic( (*currentPlayingSong).getMusic(), 0 );
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
    if (!listSong.empty()) {
        currentPlayingSong++;   // Move to the next music in the list
        if (currentPlayingSong == listSong.end())
        {
            currentPlayingSong = listSong.begin();
        }
        

        if (Mix_PlayingMusic() == 1)
        {
            //Pause the music
            Mix_PauseMusic();
        }
        //Play the music
        Mix_PlayMusic( (*currentPlayingSong).getMusic(), 0 );
    } 
    else 
    {
        std::cout << "list empty" << std::endl;
    }
}

void MusicList::previousTrack()
{
    if (!listSong.empty()) {
        if (currentPlayingSong != listSong.begin())
        {
            currentPlayingSong--;   // Move to the next music in the list
        }
        if (Mix_PlayingMusic() == 1)
        {
            //Pause the music
            Mix_PauseMusic();
        }
        //Play the music
        Mix_PlayMusic( (*currentPlayingSong).getMusic(), 0 );
        if (currentPlayingSong == listSong.end()) {
            // If at the end of the list, loop back to the beginning
            currentPlayingSong = listSong.begin();
        }
        else
        {
            ++currentPlayingSong;  // Move to the next music in the list
        }
        
    } 
    else 
    {
        std::cout << "list empty" << std::endl;
    }
}

void MusicList::infoMetadata()
{
    (*currentPlayingSong).getMetadata();
}

void MusicList::modifyMetadata()
{
    
}