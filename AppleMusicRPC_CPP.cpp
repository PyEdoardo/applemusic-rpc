#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "handlerAudio/HandlerAudio.cpp"  
#include "discord/cpp/achievement_manager.cpp"
#include "discord/cpp/activity_manager.cpp"
#include "discord/cpp/application_manager.cpp"
#include "discord/cpp/core.cpp"
#include "discord/cpp/discord.h"
#include "discord/cpp/event.h"
#include "discord/cpp/ffi.h"
#include "discord/cpp/image_manager.cpp"
#include "discord/cpp/lobby_manager.cpp"
#include "discord/cpp/network_manager.cpp"
#include "discord/cpp/overlay_manager.cpp"
#include "discord/cpp/relationship_manager.cpp"
#include "discord/cpp/storage_manager.cpp"
#include "discord/cpp/store_manager.cpp"
#include "discord/cpp/types.cpp"
#include "discord/cpp/user_manager.cpp"
#include "discord/cpp/voice_manager.cpp"

discord::Core* discordCore = nullptr;
discord::Activity discordActivity;

void InitializeDiscord() {
    discord::Core::Create(1309058326822256661, DiscordCreateFlags_Default, &discordCore);

    discordActivity.SetState("Ouvindo no Apple Music");
    discordActivity.SetDetails("Sem Mídia");

    discordCore->ActivityManager().UpdateActivity(discordActivity, [](discord::Result result) {
        if (result != discord::Result::Ok) {
            std::cerr << "Erro ao atualizar o Discord Activity!" << std::endl;
        }
        });
}

void UpdateDiscordActivity(const std::wstring& mediaDetails) {
    std::string mediaDetailsStr(mediaDetails.begin(), mediaDetails.end());

    discordActivity.SetDetails(mediaDetailsStr.c_str());
    discordCore->ActivityManager().UpdateActivity(discordActivity, [](discord::Result result) {
        if (result != discord::Result::Ok) {
            std::cerr << "Erro ao atualizar o Discord Activity!" << std::endl;
        }
        });
}

void RunDiscordRPC() {
    if (discordCore) {
        discordCore->RunCallbacks();
    }
}

int main() {
    HandlerAudio audioHandler;

    InitializeDiscord();

    while (true) {
        try {

            std::wstring mediaDetails = audioHandler.GetCurrentMediaDetails();

            if (mediaDetails.empty()) {
                std::wcout << L"Sem detalhes da mídia no momento." << std::endl;
                UpdateDiscordActivity(L"Sem Mídia");
            }
            else {
                std::wcout << L"\n===========================" << std::endl;
                std::wcout << L"Detalhes da Mídia Atual:" << std::endl;
                std::wcout << mediaDetails << std::endl;
                std::wcout << L"===========================" << std::endl;

                UpdateDiscordActivity(mediaDetails);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Erro ao obter detalhes da mídia: " << e.what() << std::endl;
        }

        RunDiscordRPC();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (discordCore) {
        discordCore->ApplicationManager();
    }

    return 0;
}
