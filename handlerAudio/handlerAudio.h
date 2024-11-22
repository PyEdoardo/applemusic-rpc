#ifndef HANDLERAUDIO_H
#define HANDLERAUDIO_H

#include <string>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.Control.h>

struct Music {
    std::string name;
    std::string artist;
    std::string album;

    static std::string convertHStringToString(const winrt::hstring& hstr);
};

class HandlerAudio {
public:
    HandlerAudio();
    ~HandlerAudio();
    Music GetCurrentMediaDetails();
    Music ParseAlbumInfo(Music& music);
};
#endif // HANDLERAUDIO_H
