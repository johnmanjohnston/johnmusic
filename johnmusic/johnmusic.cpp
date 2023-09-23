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

int main()
{
    Set_SONGS_LIST();

    for (auto e : SONGS_LIST) {
        std::cout << e << std::endl;
    }
    return 0;
    std::cout << "1\n";
    PlaySound(L"beans.wav", NULL, SND_FILENAME | SND_ASYNC);

    std::cout << "asdf\n";

    std::string a;
    std::cin >> a;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
