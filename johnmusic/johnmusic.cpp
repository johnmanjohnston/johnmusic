#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <conio.h>
#include <vector>
#include <filesystem>

#pragma comment (lib, "winmm.lib")

std::string SONGS_DIR = "C:/Users/USER/OneDrive/Desktop/new-world/";
std::vector<std::string> SONGS_LIST;
bool IS_PLAYING = false;
LPCWSTR CURRENT_SONG_PATH;
int curentSongIndex = 0;

void Set_SONGS_LIST() 
{
    std::filesystem::directory_iterator directoryScanner(SONGS_DIR);
    for (auto& entry : directoryScanner) {
        if (entry.is_regular_file()) {
            std::string fname = entry.path().filename().string();
            SONGS_LIST.push_back(fname);
        }   
    }
}

void LogTutorial() 
{
    std::cout << "\nUsage:\np - toggle play/pause\nlist - list songs\ns<index: int> - plays song from index\nkill/abort/exit - terminate\nhelp - launches an atomic bomb at your house\n\n";
}

void ListSongs() {
    for (int i = 0; i < SONGS_LIST.size(); ++i) {
        std::cout << i << " " << SONGS_LIST[i] << std::endl;
    }
}

int main()
{
    Set_SONGS_LIST();

    std::cout << "Loading songs from " << SONGS_DIR << std::endl;
    std::cout << "Loaded " << SONGS_LIST.size() << " songs" << std::endl;

    LogTutorial();

    while (true) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "kill" || cmd == "abort" || cmd == "exit") {
            std::cout << "Terminating...\n";
            return 0;
        }

        if (cmd == "list") {
            ListSongs();
        }

        if (cmd == "p") {
            IS_PLAYING = !IS_PLAYING;

            if (!IS_PLAYING) {
                PlaySound(NULL, NULL, SND_ASYNC);
            }
            else {
                std::string songName = SONGS_LIST[curentSongIndex];
                std::string songPath = SONGS_DIR + songName;
                std::wstring temp = std::wstring(songPath.begin(), songPath.end());
                CURRENT_SONG_PATH = temp.c_str();
                PlaySound(CURRENT_SONG_PATH, NULL, SND_FILENAME | SND_ASYNC);
            }

        }

        if (cmd.rfind("s", 0) == 0) {
            int songIndex = std::stoi(cmd.substr(1));
            curentSongIndex = songIndex;
            std::string songName = SONGS_LIST[songIndex];
            std::string songPath = SONGS_DIR + songName;
            std::wstring temp = std::wstring(songPath.begin(), songPath.end());
            CURRENT_SONG_PATH = temp.c_str();

            std::cout << songPath;

            PlaySound(CURRENT_SONG_PATH, NULL, SND_FILENAME | SND_ASYNC);
            IS_PLAYING = true;
        }

        if (cmd == "help") {
            LogTutorial();
        }

        std::cout << std::endl;
    }

    return 0;
}