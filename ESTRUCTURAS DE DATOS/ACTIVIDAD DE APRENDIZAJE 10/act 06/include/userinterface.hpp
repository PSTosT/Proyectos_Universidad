#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#include <iostream>
#include <string>
#include "list.hpp"
#include "song.hpp"
#include <fstream>
#include <sstream>

class UserInterface{
    private:
        List<Song>* myListRef;
    void cleanAndPauseScreen();
    void addNewSong();
    void deleteSong();
    void writeToDisk();
    void readFromDisk();
    void searchSong();
    void orderSongList();
    public:
        UserInterface(List<Song>&);
        
};

#endif