#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "handlerAudio/HandlerAudio.h"  
#include "discord/cpp/discord.h"
#include "AppleMusic.h"
#include <activity_manager.h>
#include <types.h>

discord::Core* discordCore = nullptr;
discord::Activity discordActivity;

void InitializeDiscord() {
    auto result = discord::Core::Create(1309058326822256661, DiscordCreateFlags_Default, &discordCore);
    if (result != discord::Result::Ok || !discordCore) {
        throw std::runtime_error("Erro ao inicializar o Discord Core.");
    }
    discordActivity.SetType(discord::ActivityType::Listening);
    discordActivity.SetState("Ouvindo no Apple Music");
    discordActivity.SetDetails("Sem Mídia");

    discordCore->ActivityManager().UpdateActivity(discordActivity, [](discord::Result result) {
        if (result != discord::Result::Ok) {
            std::cerr << "Erro ao atualizar o Discord Activity!" << std::endl;
        }
        });
}

void UpdateDiscordActivity(Music music) {
    music.name = "Listening: " + music.name;
    discordActivity.SetDetails(music.name.c_str());
    discordActivity.SetState(music.artist.c_str());
    discordActivity.GetAssets().SetLargeImage("apple-music"); 
    discordActivity.GetAssets().SetLargeText("Apple Music RPC Wrapper");
    discordActivity.SetType(discord::ActivityType::Listening);

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
    try {
        HandlerAudio audioHandler;
        InitializeDiscord();

        while (true) {
            try {
                Music currentMusic = audioHandler.GetCurrentMediaDetails();
                //Music parsedMusic = audioHandler.ParseAlbumInfo(currentMusic);
                //arrumar o nome das variáveis e referencias
                if (currentMusic.name.empty()) {
                    std::cout << "Nenhuma mídia em execução no momento." << std::endl;
                    //parsedMusic.name = "Sem Mídia";
                    //parsedMusic.artist = "Desconhecido";
                    //parsedMusic.album = "Desconhecido";
                }
                else {
                    std::cout << "===========================\n";
                    std::cout << "Música Atual:\n";
                    std::cout << "Título: " << currentMusic.name << "\n";
                    std::cout << "Artista: " << currentMusic.artist << "\n";
                    std::cout << "Álbum: " << currentMusic.album << "\n";
                    std::cout << "===========================\n";
                }

                UpdateDiscordActivity(currentMusic);
            }
            catch (const std::exception& e) {
                std::cerr << "Erro ao obter detalhes da mídia: " << e.what() << std::endl;
            }

            RunDiscordRPC();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erro na aplicação: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
