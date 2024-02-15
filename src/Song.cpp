#include <Song.h>

Song::Song(const std::string &path)
{
    this->path = path;
    std::shared_ptr<Mix_Music> gMusic = std::shared_ptr<Mix_Music>(Mix_LoadMUS(path.c_str()), Mix_FreeMusic);

    if (gMusic == nullptr)
    {
        std::cout << "Fail to load music from path " << path << "SDL_ERROR: " << Mix_GetError() << std::endl;
    }
    else
    {
        music = gMusic;
        TagLib::FileRef tempRef{path.c_str()};    
        fileRef = tempRef;
        std::cout << "Load music from path success!" << std::endl;
    }
}

void Song::loadMusic(const std::string &path)
{
    this->path = path;
    std::shared_ptr<Mix_Music> gMusic = std::shared_ptr<Mix_Music>(Mix_LoadMUS(path.c_str()), Mix_FreeMusic);

    music = gMusic;

    TagLib::FileRef tempRef{path.c_str()};    
    fileRef = tempRef;
}

void Song::getMetadata()
{
    if (fileRef.isNull()) {
        std::cerr << "Error opening file." << std::endl;
    }
    else
    {
        // Get the Tag (metadata) of the file
        TagLib::Tag* tag = fileRef.tag();

        // Display some metadata information
        std::cout << "_____________________________________________________"<< std::endl;
        std::cout << "Title: " << tag->title().toCString(true) << std::endl;
        std::cout << "Artist: " << tag->artist().toCString(true) << std::endl;
        std::cout << "Album: " << tag->album().toCString(true) << std::endl;
        std::cout << "Year: " << tag->year() << std::endl;
        std::cout << "Track: " << tag->track() << std::endl;

        TagLib::AudioProperties *properties = fileRef.audioProperties();
        std::cout << "Bitrate: " << properties->bitrate() << std::endl;
        std::cout << "Length: " << properties->lengthInSeconds()/60.0f << " min" << std::endl;
        std::cout << "Channels: " << properties->channels() << std::endl;
        std::cout << "_____________________________________________________"<< std::endl;
    }
}
