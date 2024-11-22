#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include "AppleMusic.h"
#include <chrono>
#include <locale>
#include <codecvt>

using namespace std;
using namespace chrono;

AppleMusic::AppleMusic() 
{
	AppleMusic::setActualTime();
}

AppleMusic::AppleMusic(string name, string url, chrono::system_clock::time_point time) : name(name), url(url), time(time) 
{
	AppleMusic::setActualTime();
}

//Getters

string AppleMusic::getName()
{
	return name;
}

string AppleMusic::getUrl()
{
	return url;
}

chrono::system_clock::time_point AppleMusic::getTime()
{
	return time;
}

string AppleMusic::getAlbum()
{
	return album;
}

string AppleMusic::getArtista()
{
	return artista;
}

//Setters

void AppleMusic::setName(string name)
{
	this->name = name;
}

void AppleMusic::setUrl(string url)
{
	this->url = url;
}

void AppleMusic::setTime(chrono::system_clock::time_point time)
{
	this->time = time;
}

void AppleMusic::setAlbum(string album)
{
	this->album = album;
}

void AppleMusic::setArtista(string artista)
{
	this->artista = artista;
}

//Métodos

void AppleMusic::setActualTime()
{
	auto now = chrono::system_clock::now();

	this->time = now;
}

string AppleMusic::convertWStringToString(std::wstring wtext)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	string str = converter.to_bytes(wtext);

	return str;
}
