#include "HandlerAudio.h"
#include <locale>
#include <codecvt>
#include <iostream>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.Control.h>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Media::Control;

std::string Music::convertHStringToString(const hstring& hstr) {
    std::wstring wstr = hstr.c_str();
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.to_bytes(wstr);
}

Music HandlerAudio::ParseAlbumInfo(Music& music) {
    size_t dashPos = music.name.find(" - ");

    if (dashPos != std::string::npos) {
       
        music.artist = music.name.substr(0, dashPos); 
        music.album = music.name.substr(dashPos + 3); 
    }
    else {
        
        music.artist = "Desconhecido";
        music.album = music.name;
    }

    return music; 
}

HandlerAudio::HandlerAudio() {
    init_apartment(); 
}

HandlerAudio::~HandlerAudio() = default;

Music HandlerAudio::GetCurrentMediaDetails() {
    Music music;
    try {
        auto sessionManager = GlobalSystemMediaTransportControlsSessionManager::RequestAsync().get();
        auto currentSession = sessionManager.GetCurrentSession();
        auto playbackStatus = currentSession.GetPlaybackInfo();
        if (!currentSession) {
            music.name = "Nenhuma mídia em execução";
            music.artist = "N/A";
            music.album = "N/A";
            return music;
        }

        auto mediaProperties = currentSession.TryGetMediaPropertiesAsync().get();
        music.name = Music::convertHStringToString(mediaProperties.Title().empty() ? L"(Desconhecido)" : mediaProperties.Title());
        music.artist = Music::convertHStringToString(mediaProperties.AlbumArtist().empty() ? L"(Desconhecido)" : mediaProperties.AlbumArtist());
        music.album = Music::convertHStringToString(mediaProperties.AlbumTitle().empty() ? L"(Desconhecido)" : mediaProperties.AlbumTitle());
    }
    catch (const hresult_error& ex) {
        music.name = "Erro ao obter informações da mídia";
        music.artist = "Erro";
        music.album = ex.message().empty() ? "Detalhes indisponíveis" : Music::convertHStringToString(ex.message());
    }   
    
    return music;
}
