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
	chrono::system_clock::time_point time;

public:

	AppleMusic();

	AppleMusic(string name, string url, chrono::system_clock::time_point time);

	//Getters

	string getName() 
	{
		return this->name;
	}


};

