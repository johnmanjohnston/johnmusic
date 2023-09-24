#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <conio.h>
#include <vector>
#include <filesystem>
#include <fstream>

#pragma comment (lib, "winmm.lib")

std::string CURRENT_SONGS_DIR;
std::vector<std::string> SONGS_DIRS_CHOICES;
std::vector<std::string> SONGS_LIST;
bool IS_PLAYING = false;
LPCWSTR CURRENT_SONG_PATH;
int curentSongIndex = 0;

void Set_SONGS_LIST() 
{
    SONGS_LIST.clear();
    std::cout << "Loading songs from " << CURRENT_SONGS_DIR << std::endl;
    std::filesystem::directory_iterator directoryScanner(CURRENT_SONGS_DIR);
    for (auto& entry : directoryScanner) {
        if (entry.is_regular_file()) {
            std::string fname = entry.path().filename().string();
            SONGS_LIST.push_back(fname);
        }   
    }

    std::cout << "Loaded " << SONGS_LIST.size() << " songs\n";
}

void Set_SONGS_DIRS_CHOICES() 
{
    std::ifstream songsDirPathFile("songs_dir.txt");
    if (songsDirPathFile.fail()) {
        std::cout << "Couldn't locate songs_dir.txt\n";
        exit(1);
    }

    std::string currentLine;

    while (std::getline(songsDirPathFile, currentLine)) {
        SONGS_DIRS_CHOICES.push_back(currentLine);
        if (CURRENT_SONGS_DIR == "") {
            CURRENT_SONGS_DIR = currentLine;
        }
    }

    songsDirPathFile.close();
}

void LogTutorial() 
{
    std::cout << "\nUsage:\np - toggle play/pause\nlist - list songs\ns<index: int> - plays song from index\ncd<index: int> - loads songs from different directory specified by index\nkill/abort/exit - terminate\nhelp - launches an atomic bomb at your house\n\n";
}

void ListSongsAndSongDirectories() {
    std::cout << "Songs: \n";
    for (int i = 0; i < SONGS_LIST.size(); ++i) {
        std::cout << i << " " << SONGS_LIST[i] << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Directories: \n";
    for (int i = 0; i < SONGS_DIRS_CHOICES.size(); ++i) {
        std::cout << i << " " << SONGS_DIRS_CHOICES[i] << std::endl;
    }
}

int main()
{
    Set_SONGS_DIRS_CHOICES();
    Set_SONGS_LIST();

    LogTutorial();

    while (true) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "kill" || cmd == "abort" || cmd == "exit") {
            std::cout << "Terminating...\n";
            return 0;
        }

        if (cmd == "list") {
            ListSongsAndSongDirectories();
        }

        if (cmd == "p") {
            IS_PLAYING = !IS_PLAYING;

            if (!IS_PLAYING) {
                PlaySound(NULL, NULL, 0);
            }
            else {
                std::string songName = SONGS_LIST[curentSongIndex];
                std::string songPath = CURRENT_SONGS_DIR + songName;
                std::wstring temp = std::wstring(songPath.begin(), songPath.end());
                CURRENT_SONG_PATH = temp.c_str();
                PlaySound(CURRENT_SONG_PATH, NULL, SND_FILENAME | SND_ASYNC);
            }

        }

        if (cmd.rfind("s", 0) == 0) {
            curentSongIndex = std::stoi(cmd.substr(1));
            std::string songName = SONGS_LIST[curentSongIndex];
            std::string songPath = CURRENT_SONGS_DIR + songName;
            std::wstring temp = std::wstring(songPath.begin(), songPath.end());
            CURRENT_SONG_PATH = temp.c_str();

            std::cout << songPath;

            auto b = PlaySound(CURRENT_SONG_PATH, NULL, SND_FILENAME | SND_ASYNC);
            std::cout << b;
            IS_PLAYING = true;
        }

        if (cmd.rfind("cd", 0) == 0) {
            int dirIndex = std::stoi(cmd.substr(2));
            CURRENT_SONGS_DIR = SONGS_DIRS_CHOICES[dirIndex];
            Set_SONGS_LIST();
        }

        if (cmd == "help") {
            LogTutorial();
        }

        std::cout << std::endl;
    }

    return 0;
}