#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.Control.h>
#include <AppleMusic.h>
#include <AppleMusic.cpp>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Media::Control;

class HandlerAudio {
public:
    HandlerAudio() {
        init_apartment(); 
    }

    ~HandlerAudio() {

    }
    
    AppleMusic music = AppleMusic::AppleMusic();

    AppleMusic GetCurrentMediaDetails() {
        try {
            auto sessionManager = GlobalSystemMediaTransportControlsSessionManager::RequestAsync().get();
            auto currentSession = sessionManager.GetCurrentSession();
            if (!currentSession) {
                music.setName("Nenhuma Midia em reprodução no momento.");
                return music;
            }

            auto mediaProperties = currentSession.TryGetMediaPropertiesAsync().get();
            std::wstring title = mediaProperties.Title().empty() ? L"(Desconhecido)" : mediaProperties.Title().c_str();
            std::wstring artist = mediaProperties.AlbumArtist().empty() ? L"(Desconhecido)" : mediaProperties.AlbumArtist().c_str();
            std::wstring album = mediaProperties.AlbumTitle().empty() ? L"(Desconhecido)" : mediaProperties.AlbumTitle().c_str();

            std::string titleMusic = music.convertWStringToString(title);
            std::string artistMusic = music.convertWStringToString(artist);
            std::string albumArtist = music.convertWStringToString(album);

            music.setName(titleMusic);
            music.setArtista(artistMusic);
            music.setAlbum(albumArtist);

            std::wstring details = L"Titulo: " + title + L"\n";
            details += L"Artista: " + artist + L"\n";
            details += L"Album: " + album + L"\n";

            return music;
        }
        catch (const hresult_error& ex) {
            music.setName("Erro ao obter informações da mídia : ");
            return music;
        }
    }
};
