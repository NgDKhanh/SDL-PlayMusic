#include "MusicList.h"

bool MusicList::addSong(const std::string& path)
{
    struct stat sb;
    if (stat(path.c_str(), &sb))
    {
        std::cout << "Path is wrong" << std::endl;
        return false;
    }
    Song newSong(path);
    bool firstInitList = false;

    // Whether is is the first time adding song into list
    if (listSong.empty())
    {
        firstInitList = true;
    }

    listSong.push_back(newSong);
    
    if (firstInitList)
    {
        currentPlayingSong = listSong.begin();
    }

    return true;
}

void MusicList::addMusicMannual()
{
    std::string path;
    std::cout << "Enter the path to music: ";
    std::cin >> path;
    struct stat sb;
    if (stat(path.c_str(), &sb))
    {
        std::cout << "Path is wrong" << std::endl;
        return;
    }
    
    addSong(path);
}

void MusicList::removeSong(const uint8_t songIndex)
{
    if (listSong.empty() || songIndex > listSong.size()) 
    {
        std::cout << "Invalid remove song." << std::endl;
        return;
    }

    auto it = listSong.begin();
    std::advance(it, (songIndex-1));
    listSong.erase(it);
}

void MusicList::playSong()
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
            mStartPlayTime = SDL_GetTicks();
            mOffsetTime = 0.0;
        }
        else
        {
            //If the music is paused
            if( Mix_PausedMusic() == 1 )
            {
                //Resume the music
                Mix_ResumeMusic();
                mStartPlayTime = SDL_GetTicks();
            }
        }
    } 
    else 
    {
        std::cout << "list empty" << std::endl;
    }
}

void MusicList::pauseSong()
{
    if (Mix_PlayingMusic() != 0)
    {
        //If the music is paused
        if( Mix_PausedMusic() != 1 )
        {
            //Pause the music
            Mix_PauseMusic();
            mOffsetTime += ((double)(SDL_GetTicks() - mStartPlayTime) / 1000.0);
        }
    }
}

void MusicList::nextSong()
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
        mStartPlayTime = SDL_GetTicks();
        mOffsetTime = 0.0;
    } 
    else 
    {
        std::cout << "list empty" << std::endl;
    }
}

void MusicList::previousSong()
{
    if (!listSong.empty()) {
        if (currentPlayingSong == listSong.begin()) {
            currentPlayingSong = listSong.end();
        }
        else {
        
        }
        currentPlayingSong--;   // Move to the next music in the list

        if (Mix_PlayingMusic() == 1)
        {
            //Pause the music
            Mix_PauseMusic();
        }
        //Play the music
        Mix_PlayMusic( (*currentPlayingSong).getMusic(), 0 );
        mStartPlayTime = SDL_GetTicks();
        mOffsetTime = 0.0;
    } 
    else 
    {
        std::cout << "list empty" << std::endl;
    }
}

void MusicList::jumpBackward(uint32_t seconds)
{
    double currentTime = getCurrentSongPlayPosition();
    double targetTime; 
    if (0 < ((int)currentTime - (int)seconds) && ((int)currentTime - (int)seconds) < (double)(*currentPlayingSong).getMetadata().Length) {
        targetTime = (currentTime - (double)seconds);
    }
    else {
        targetTime = 1.0;
    }
    mOffsetTime = targetTime;
    mStartPlayTime = SDL_GetTicks();
    Mix_SetMusicPosition(targetTime);
}

void MusicList::jumpForward(uint32_t seconds)
{
    double currentTime = getCurrentSongPlayPosition();
    double targetTime; 
    if ((*currentPlayingSong).getMetadata().Length > ((int)currentTime + (int)seconds) && ((int)currentTime + (int)seconds) > 0) {
        targetTime = (currentTime + (double)seconds);
    }
    else {
        // I don't know why Mix_SetMusicPosition can't set music to the last second of the song (it's weird)
        // So I add offset 7s                                                                                    
        targetTime = (double)(*currentPlayingSong).getMetadata().Length - 1.0 + (7.0); 
    }
    mOffsetTime = targetTime;
    mStartPlayTime = SDL_GetTicks();
    Mix_SetMusicPosition(targetTime);
}

void MusicList::infoMetadata()
{
    (*currentPlayingSong).printMetadata();
}

void MusicList::modifyMetadata()
{
    
}

void MusicList::printList()
{
    int index = 1;
    std::cout << "_____________________________________________________"<< std::endl;
    std::cout << "              " << mMusicListName << "              " << std::endl;
    std::cout << "_____________________________________________________"<< std::endl;
    for (auto Song : listSong) {
        if (Song.getMetadata().Title == (*currentPlayingSong).getMetadata().Title) 
        {
            std::cout << "|-->";
        }
        else 
        {
            std::cout << "    ";
        }
        std::cout << index << ". " << Song.getMetadata().Title << " (" << Song.getMetadata().Artist << ")";
        std::cout << std::endl;
        index++;
    }
    std::cout << "_____________________________________________________"<< std::endl;
}

const double MusicList::getCurrentSongPlayPosition() { 
    if ( Mix_PausedMusic() != 1 && Mix_PlayingMusic() == 1)
    {
        return (mOffsetTime + (SDL_GetTicks() - mStartPlayTime) / 1000.0); 
    }
    else {
        return (mOffsetTime);
    }
}