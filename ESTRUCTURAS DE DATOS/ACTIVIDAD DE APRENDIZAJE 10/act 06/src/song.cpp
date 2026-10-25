#include "song.hpp"
using namespace std;

Song::Song(){ }

Song::Song(const Song& s) : songName(s.songName), authorName(s.authorName), singerName(s.singerName), rankingPos(s.rankingPos), mp3FileName(s.mp3FileName) {  }

string Song::getSongName() const{
    return this -> songName;
}

string Song::getAuthorName() const{
    return this -> authorName;
}

string Song::getSingerName() const{
    return this -> singerName;
}

int Song::getRankingPos() const{
    return this -> rankingPos;
}

string Song::getMp3FileName() const{
    return this -> mp3FileName + ".mp3";
}

string Song::toString() const{
    string result;
    result += getSongName();
    result += " | ";
    result += getAuthorName();
    result += " | ";
    result += getSingerName();
    result += " | ";
    result += to_string(getRankingPos());
    result += " | ";
    result += getMp3FileName();
    return result;
}

void Song::setSongName(const string& son){
    this-> songName = son;
}

void Song::setAuthorName(const string& an){
    this-> authorName = an;
}

void Song::setSingerName(const string& sin){
    this -> singerName = sin;
}

void Song::setRankingPos(const int& r){
    this -> rankingPos = r;
}

void Song::setMp3FileName(const string& m){
    this -> mp3FileName = m;
}

Song& Song::operator = (const Song& s){
    this -> songName = s.songName;
    this -> authorName = s.authorName;
    this -> singerName = s.singerName;
    this -> rankingPos = s.rankingPos;
    this -> mp3FileName = s.mp3FileName;
    return *this;
}

bool Song::operator == (const Song& s) const{
    return this -> songName == s.songName;
}

bool Song::operator != (const Song& s) const{
    return !(*this == s);
}

bool Song::operator < (const Song& s) const{
    return this -> rankingPos < s.rankingPos;
}

bool Song::operator <= (const Song& s) const{
    return this -> rankingPos <= s.rankingPos;
}

bool Song::operator > (const Song& s) const{
    return this -> rankingPos > s.rankingPos;
}

bool Song::operator >= (const Song& s) const{
    return this -> rankingPos > s.rankingPos;
}

int Song::compareByName(const Song& a, const Song& b){
    return a.songName.compare(b.songName);
}

int Song::compareBySinger(const Song& a, const Song& b){
    return a.singerName.compare(b.singerName);
}

istream& operator >> (istream& is, Song& s) {
    string myStr;
    if (!getline(is, s.songName)) return is;
    getline(is, s.authorName);
    getline(is, s.singerName);
    getline(is, myStr);
    if(myStr != "") s.rankingPos = stoi(myStr);
    getline(is, s.mp3FileName);
    return is;
}

ostream& operator << (ostream& os, const Song& s) {
    os << s.songName << endl;
    os << s.authorName << endl;
    os << s.singerName << endl;
    os << s.rankingPos << endl;
    os << s.mp3FileName;
    return os;
}