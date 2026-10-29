#ifndef __SONG_H__
#define __SONG_H__
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class Song{
    private:
        std::string songName;
        std::string authorName;
        std::string singerName;
        std::string mp3FileName;
        int rankingPos;

    public:
    Song();
    Song(const Song&);

    std::string getSongName() const;
    std::string getAuthorName() const;
    std::string getSingerName() const;
    int getRankingPos() const;
    std::string getMp3FileName() const;

    std::string toString() const;

    void setSongName(const std::string&);
    void setAuthorName(const std::string&);
    void setSingerName(const std::string&);
    void setRankingPos(const int&);
    void setMp3FileName(const std::string&);

    Song& operator = (const Song&);

    bool operator == (const Song&) const;
    bool operator != (const Song&) const;
    bool operator < (const Song&) const;
    bool operator <= (const Song&) const;
    bool operator > (const Song&) const;
    bool operator >= (const Song&) const;

    static int compareByName(const Song&, const Song&); 
    static int compareBySinger(const Song&, const Song&); 

    friend std::ostream& operator << (std::ostream&, const Song&);
    friend std::istream& operator >> (std::istream&, Song&);
};

#endif