#pragma once
#include <string>
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

class AppleMusic
{
private:

	string name;
	string url;
	string artista;
	string album;
	chrono::system_clock::time_point time;

public:

	AppleMusic();

	AppleMusic(string name, string url, chrono::system_clock::time_point time);

	//Getters

	string getName();

	string getUrl();

	chrono::system_clock::time_point getTime();

	string getArtista();

	string getAlbum();

	//Setters

	void setName(string name);

	void setUrl(string url);

	void setTime(chrono::system_clock::time_point time);

	void setArtista(string artista);

	void setAlbum(string album);

	//Métodos

	void setActualTime();

	static string convertWStringToString(std::wstring wtext);
};

