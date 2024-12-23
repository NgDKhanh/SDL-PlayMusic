#include <Song.h>

Song::Song(const std::string &path)
{
    this->path = path;
    std::shared_ptr<Mix_Music> gMusic = std::shared_ptr<Mix_Music>(Mix_LoadMUS(path.c_str()), Mix_FreeMusic);

    if (gMusic == nullptr)
    {
        std::cout << "Fail to load music from path " << path << "\nSDL_ERROR: " << Mix_GetError() << std::endl;
    }
    else
    {
        music = gMusic;
        TagLib::FileRef tempRef{path.c_str()};    
        fileRef = tempRef;
        std::cout << "Load music from path " << path <<  " success!" << std::endl;
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

void Song::printMetadata()
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
        std::cout << "Length: " << properties->lengthInSeconds()/60 << "min " << properties->lengthInSeconds()%60 << "s" << std::endl;
        std::cout << "Channels: " << properties->channels() << std::endl;
        std::cout << "_____________________________________________________"<< std::endl;
    }
}

const SongMetadata Song::getMetadata()
{
    SongMetadata metadata;
    if (fileRef.isNull()) {
        std::cerr << "Error opening file." << std::endl;
    }
    else
    {
        // Get the Tag (metadata) of the file
        TagLib::Tag* tag = fileRef.tag();

        // Display some metadata information
         metadata.Title =  tag->title().toCString(true);
         metadata.Artist = tag->artist().toCString(true);
         metadata.Album = tag->album().toCString(true);
         metadata.Year = tag->year();
         metadata.Track = tag->track();

        TagLib::AudioProperties *properties = fileRef.audioProperties();

        metadata.Bitrate = properties->bitrate();
        metadata.Length = properties->lengthInSeconds();
        metadata.Chanel = properties->channels();

    }
    return metadata;
}
