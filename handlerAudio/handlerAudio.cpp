#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.Control.h>

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

    std::wstring GetCurrentMediaDetails() {
        try {
            auto sessionManager = GlobalSystemMediaTransportControlsSessionManager::RequestAsync().get();
            auto currentSession = sessionManager.GetCurrentSession();
            if (!currentSession) {
                return L"Nenhuma mídia em reprodução no momento.";
            }

            auto mediaProperties = currentSession.TryGetMediaPropertiesAsync().get();
            std::wstring title = mediaProperties.Title().empty() ? L"(Desconhecido)" : mediaProperties.Title().c_str();
            std::wstring artist = mediaProperties.AlbumArtist().empty() ? L"(Desconhecido)" : mediaProperties.AlbumArtist().c_str();
            std::wstring album = mediaProperties.AlbumTitle().empty() ? L"(Desconhecido)" : mediaProperties.AlbumTitle().c_str();

            std::wstring details = L"Título: " + title + L"\n";
            details += L"Artista: " + artist + L"\n";
            details += L"Álbum: " + album + L"\n";

            return details;
        }
        catch (const hresult_error& ex) {
            return L"Erro ao obter informações da mídia: " + std::wstring(ex.message().c_str());
        }
    }
};
