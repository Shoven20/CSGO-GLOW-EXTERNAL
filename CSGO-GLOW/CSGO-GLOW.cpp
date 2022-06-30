#include "memory.h"
#include <windows.h>
#include <thread>
#include <iostream>


namespace offset
{
    constexpr ::std::ptrdiff_t LokalOyuncu = 0xDBF4CC;
    constexpr ::std::ptrdiff_t Takim = 0xF4;
    constexpr ::std::ptrdiff_t Bayrak = 0x104;
    constexpr ::std::ptrdiff_t GostergeObjesi = 0x5324588;
    constexpr ::std::ptrdiff_t NesneListesi = 0x4DDB92C;
    constexpr ::std::ptrdiff_t GostergeIndexi = 0x10488;
}
int main()
{
    system("cls");
    int count = 0;
    SetConsoleTitle("DEVELOPED BY Shoven#5688");
    int horizontal = 0, vertical = 0;
    int x = 520, y = 420;
    HWND hwnd = GetConsoleWindow();
    MoveWindow(hwnd, 0, 0, x, y, FALSE);
    SetWindowPos(hwnd, HWND_TOPMOST, 10, 10, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
    lStyle &= ~(WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
    SetWindowLong(hwnd, GWL_STYLE, lStyle);
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);
    COORD scrollbar = {
        csbi.srWindow.Right - csbi.srWindow.Left + 1,
        csbi.srWindow.Bottom - csbi.srWindow.Top + 1
    };
    if (console == 0)
        throw 0;
    else
        SetConsoleScreenBufferSize(console, scrollbar);
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, 0, (255 * 100) / 50, LWA_ALPHA);
    std::cout << "\n\n  [+] COUNTER STRIKE : GLOBAL OFFENSIVE - GLOW CHEAT";
    std::cout << "\n\n  [+] https://github.com/Shoven20/CSGO-GLOW-EXTERNAL";
    std::cout << "\n\n  [+] Discord: Shoven#5688";
    const auto memory = Hafiza{ "csgo.exe" };
    const auto Hafizaa = Hafiza("csgo.exe");
    const auto oyun = Hafizaa.ModulAdresiniCek("client.dll");
    while (true) {
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            const auto lokaloyuncu = Hafizaa.oku<std::uintptr_t>(oyun + offset::LokalOyuncu);
            if (!lokaloyuncu)
                continue;
            const auto LokayOyuncuTakim = Hafizaa.oku<std::uintptr_t>(lokaloyuncu + offset::Takim);
            const auto LokalOyuncuBayragi = Hafizaa.oku<std::uintptr_t>(lokaloyuncu + offset::Bayrak);
            const auto GostergeObjesi = Hafizaa.oku<std::uintptr_t>(oyun + offset::GostergeObjesi);
            for (auto i = 1; i <= 32; ++i)
            {
                const auto Nesne = Hafizaa.oku<std::uintptr_t>(oyun + offset::NesneListesi + i * 0x10);
                if (!Nesne)
                    continue;
                if (Hafizaa.oku<std::uintptr_t>(Nesne + offset::Takim) == LokayOyuncuTakim)
                    continue;
                const auto Gosterge = Hafizaa.oku<std::int32_t>(Nesne + offset::GostergeIndexi);
                Hafizaa.yaz<float>(GostergeObjesi + (Gosterge * 0x38) + 0x8, 255.f); // r
                Hafizaa.yaz<float>(GostergeObjesi + (Gosterge * 0x38) + 0xC, 255.f); // g
                Hafizaa.yaz<float>(GostergeObjesi + (Gosterge * 0x38) + 0x10, 255.f); // b
                Hafizaa.yaz<float>(GostergeObjesi + (Gosterge * 0x38) + 0x14, 255.0f); // a
                Hafizaa.yaz<bool>(GostergeObjesi + (Gosterge * 0x38) + 0x28, true);
                Hafizaa.yaz<bool>(GostergeObjesi + (Gosterge * 0x38) + 0x29, false);
            }
        }
    }
}
