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
    std::cout << "\nUsage:\np - toggle play/pause\nlist - list songs\ns<index: int> - plays song from index\nkill/abort/exit - terminate\n\n";
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
            std::cout << "Toggle pause/play\n";
            IS_PLAYING = !IS_PLAYING;
        }

        if (cmd.rfind("s", 0) == 0) {
            int songIndex = std::stoi(cmd.substr(1));
            std::string songName = SONGS_LIST[songIndex];

            std::string songPath = SONGS_DIR + songName;
            std::wstring tmp = std::wstring(songPath.begin(), songPath.end());
            LPCWSTR wideString = tmp.c_str();

            std::cout << songName;

            PlaySound(wideString, NULL, SND_FILENAME | SND_ASYNC);
        }

        std::cout << std::endl;
    }

    for (auto& e : SONGS_LIST) {
        std::cout << e << std::endl;
    }
    return 0;
    std::cout << "1\n";
    PlaySound(L"beans.wav", NULL, SND_FILENAME | SND_ASYNC);

    std::cout << "asdf\n";

    std::string a;
    std::cin >> a;
}