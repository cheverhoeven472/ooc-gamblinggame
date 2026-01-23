#include "app.h"
#include "player.h"
#include <cstdlib>
#include <string>
#include <vector>
#include "HitAction.h"
#include "StandAction.h"
#include "DoubleDownAction.h"
#include "dealer.h"
#include "Action.h"
#include <d3d9.h>
#include "Photo_handelig.h"
#include <ctime>  



// Data
static LPDIRECT3D9              g_pD3D = nullptr;
static LPDIRECT3DDEVICE9        g_pd3dDevice = nullptr;
static bool                     g_DeviceLost = false;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

app::app()
{
    // Make process DPI aware and obtain main monitor scale
    ImGui_ImplWin32_EnableDpiAwareness();
    float main_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));

    // Create application window
    wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    hwnd = ::CreateWindowW(wc.lpszClassName, L"blackjack", WS_OVERLAPPEDWINDOW, 100, 100, (int)(1280 * main_scale), (int)(800 * main_scale), nullptr, nullptr, wc.hInstance, nullptr);




    
    
        // ============ VOEG DIT TOE AAN HET BEGIN ============
        srand(static_cast<unsigned int>(time(nullptr)));
        // ============ EINDE ============

        // Make process DPI aware and obtain main monitor scale
        ImGui_ImplWin32_EnableDpiAwareness();
        // ... rest van je constructor ...
    
    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        std::exit(1);
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale); // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale; // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // style.FontSizeBase = 20.0f;
    // io.Fonts->AddFontDefault();
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf");
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf");
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf");
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf");
    // ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf");
    // IM_ASSERT(font != nullptr);

}

void app::run()
{
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle lost D3D9 device
        if (g_DeviceLost)
        {
            HRESULT hr = g_pd3dDevice->TestCooperativeLevel();
            if (hr == D3DERR_DEVICELOST)
            {
                ::Sleep(10);
                continue;
            }
            if (hr == D3DERR_DEVICENOTRESET)
                ResetDevice();
            g_DeviceLost = false;
        }

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            g_d3dpp.BackBufferWidth = g_ResizeWidth;
            g_d3dpp.BackBufferHeight = g_ResizeHeight;
            g_ResizeWidth = g_ResizeHeight = 0;
            ResetDevice();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // Update
        update();

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
        if (result == D3DERR_DEVICELOST)
            g_DeviceLost = true;
    }
}


void app::update()
{

    static bool reset = false;
    // Alle state variabelen MOETEN static zijn
    static bool player_init_window = true;
    static bool Player_Names_Window = false;
    static bool game_window = false;
    static bool dealer_window = false;
	static bool game_over_window = false;

    static const int max_name_length = 32;
    static const int max_players = 4;

    static int Players = 0;
    static std::vector<Player> players;
    static char name_buffers[max_players][max_name_length] = { "" };
    static int inzet_buffers[max_players] = { 0 };

    static HitAction hitAction;
    static StandAction standAction;
    static DoubleDownAction doubleDownAction;

    

    if (player_init_window) {
        static int Temp_Players = 1;
        ImGui::SetNextWindowSize(ImVec2(250, 120));
        ImGui::Begin("player selection");
        ImGui::Text("Select number of players:");
        ImGui::InputInt("##players", &Temp_Players);
        if (Temp_Players > max_players || Temp_Players < 1) {
            Temp_Players = 1;
        }
        if (ImGui::Button("confirm")) {
            Players = Temp_Players;
            player_init_window = false;
            Player_Names_Window = true;
        }
        ImGui::End();
    }

    if (Player_Names_Window) {
        ImGui::SetNextWindowSize(ImVec2(500, Players * 31 + 55));
        ImGui::Begin("Player Names");

        for (int i = 0; i < Players; i++) {
            std::string name_label = "Player " + std::to_string(i + 1) + "##name" + std::to_string(i);
            std::string inzet_label = "inzet##" + std::to_string(i);

            ImGui::SetNextItemWidth(100);
            ImGui::InputText(name_label.c_str(), name_buffers[i], max_name_length);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80);
            ImGui::InputInt(inzet_label.c_str(), &inzet_buffers[i]);
        }

        if (ImGui::Button("start")) {
            Player_Names_Window = false;
            game_window = true;
            dealer_window = true;
            players.clear();

            for (int i = 0; i < Players; i++) {
                Player newPlayer("", i + 1);
                newPlayer.set_hand_value(0);
                newPlayer.set_name(name_buffers[i]);
                newPlayer.set_inzet(inzet_buffers[i]);
                players.push_back(newPlayer);
            }
        }
        ImGui::End();
    }

    if (game_window) {
        static int starting_hand = players.size();
        for (int i = 0; i < players.size(); i++)//vervangen door itterator 
        {
            ImGui::SetNextWindowPos(ImVec2(10 + i * 475, 670));
            ImGui::SetNextWindowSize(ImVec2(465, 300));
            ImGui::Begin(("Player " + std::to_string(i + 1) + " - " + players[i].get_name()).c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus);

            if (starting_hand > 0) {
                hitAction.starting_hand(players[i]);
                starting_hand--;
            }
            if (reset) {
				starting_hand = players.size();
				reset = false;
			}


            // Speler info
            ImGui::Text("Inzet: %d slokken", players[i].get_inzet());
            ImGui::Text("Hand waarde:  %d", players[i].get_hand_value());
            ImGui::Text("Kaarten: ");
            ImGui::SameLine();

            for (int j = 0; j < players[i].kaart_index; j++) {
                ImGui::Text("%c ", players[i].Player_kaart[j]);
                ImGui::SameLine();
            }

            ImGui::NewLine();
            ImGui::Separator();

            ImGui::PushID(i);

            // Check of buttons disabled moeten zijn
            bool is_disabled = players[i].has_stood();

            ImGui::BeginDisabled(is_disabled);

            if (ImGui::Button("Hit")) {
                hitAction.execute(players[i]);
            }
            ImGui::SameLine();

            if (ImGui::Button("Stand")) {
                standAction.execute(players[i]);
            }
            ImGui::SameLine();

            if (ImGui::Button("Double Down")) {
                doubleDownAction.execute(players[i]);
            }

            ImGui::EndDisabled();

            ImGui::PopID();

			ImGui::Separator();


            if(players[i].get_hand_value() == 21 && players[i].kaart_index == 2) {
                players[i].player_blackjack = true;
                standAction.execute(players[i]);
			}

            if(players[i].get_hand_value() > 21) {
				players[i].player_busted = true;
                standAction.execute(players[i]);
            }

            if (players[i].get_hand_value() == 21) {
                standAction.execute(players[i]);
            }

            if(players[i].has_stood() && !players[i].player_busted && !players[i].player_blackjack) {
                ImGui::Text("Stood!");
			}

            if(players[i].player_busted) {
                ImGui::Text("Busted!");
				
                if (players[i].get_inzet() == 1) {
                    ImGui::Text("je moet");
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%d", players[i].get_inzet());  // ← Gebruik %d
                    ImGui::SameLine();
                    ImGui::Text("slok nemen");
                }
				else if (players[i].get_inzet() > 1) {
                    ImGui::Text("je moet");
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%d", players[i].get_inzet());  // ← Gebruik %d
                    ImGui::SameLine();
                    ImGui::Text("slokken nemen");
                }
            }

            else if (players[i].player_blackjack) {
                ImGui::Text("Blackjack!");
                int gewonnen_slokken = static_cast<int>(players[i].get_inzet() * 1.5);
                ImGui::Text("je mag");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%d", gewonnen_slokken);  // ← Gebruik %d
                ImGui::SameLine();
                ImGui::Text("slokken uitdelen");
            }


            ImGui::End();
        }
    }

    static Dealer dealer;
	static bool first_deal = true;
    if (dealer_window) {
		static bool all_players_stood = false;
	    int players_stood_count = 0;
        ImGui::SetNextWindowSize(ImVec2(465, 300));
        ImGui::SetNextWindowPos(ImVec2(727, 20));
        ImGui::Begin("dealer window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus);

        if (first_deal) {
            hitAction.starting_hand(dealer);
			first_deal = false;
        }
        ImGui::Text("Dealer's Hand: ");
        ImGui::SameLine();

        // Loop door dealer's kaarten
        for (int j = 0; j < dealer.kaart_index; j++) {
            if (j == 0 && dealer.is_kaart_verborgen()) {
                ImGui::Text("[?]");  // Eerste kaart verborgen
            }
            else {
                ImGui::Text("%c", dealer.Player_kaart[j]);  // ← Object.variabele
            }
            ImGui::SameLine();
        }
        ImGui::NewLine();


        for(int i = 0; i < players.size(); i++) {
            if (players[i].has_stood()) {
				players[i].player_done = true;
            }
		}

        for (int i = 0; i < players.size(); i++) {
            if (players[i].player_done) {
				players_stood_count++;
            }
            if (players_stood_count == players.size()) {
				all_players_stood = true;
            }
        }

        if (players_stood_count == players.size()) {
			all_players_stood = true;
        }

        if (all_players_stood && !dealer.has_stood()) {
            dealer.dealer_sequence();
            game_over_window = true;

            
		}
        if (dealer.has_stood()) {
            ImGui::Text("Hand waarde: %d", dealer.get_hand_value());
            if(dealer.Dealer_busted) {
                ImGui::Text("Dealer Busted!");
				
			}  
        }
        

        ImGui::End();

    }

    if(game_over_window) {
        ImGui::SetNextWindowSize(ImVec2(300, 500));
		ImGui::SetNextWindowPos(ImVec2(50, 150));
		ImGui::Begin("Game Over", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImGui::Text("Game Over Results:");
		ImGui::Separator();
		ImGui::Text("Dealer had: %d", dealer.get_hand_value());
		ImGui::Separator();
        for (int i = 0; i < players.size(); i++) {
            ImGui::Text(players[i].get_name().c_str());
			ImGui::SameLine();
			ImGui::Text(": ");
            if (players[i].player_busted) {
                ImGui::Text("Lost - Busted");
				ImGui::Text("je moet");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%d", players[i].get_inzet());
                ImGui::SameLine();
				ImGui::Text("slokken nemen");
            }
            else if (players[i].player_blackjack) {
                ImGui::Text("Won - Blackjack!");
                int gewonnen_slokken = static_cast<int>(players[i].get_inzet() * 1.5);
                ImGui::Text("je mag");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%d", gewonnen_slokken);
                ImGui::SameLine();
				ImGui::Text("slokken uitdelen");
            }
            else if (dealer.Dealer_busted) {
                ImGui::Text("Won - Dealer Busted");
                ImGui::Text("je mag");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%d", players[i].get_inzet());
                ImGui::SameLine();
				ImGui::Text("slokken uitdelen");
            }
            else if (players[i].get_hand_value() > dealer.get_hand_value()) {
                ImGui::Text("Won");
				ImGui::Text("je mag");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%d", players[i].get_inzet());
                ImGui::SameLine();
				ImGui::Text("slokken uitdelen");
            }
            else if (players[i].get_hand_value() < dealer.get_hand_value()) {
                ImGui::Text("Lost");
                ImGui::Text("je moet");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%d", players[i].get_inzet());
				ImGui::SameLine();
				ImGui::Text("slokken nemen");
            }
            else {
                ImGui::Text("Push (Tie)");
				ImGui::Text("geen slokken");
			}
            ImGui::Separator();
            
        }
        ImGui::Separator();
        ImGui::NewLine();

        // Button 1: Volgende ronde (zelfde spelers, nieuwe inzet)
        if (ImGui::Button("Volgende Ronde", ImVec2(280, 40))) {
            // Reset game state
            game_over_window = false;
            game_window = false;
            dealer_window = false;
            Player_Names_Window = true;  // Terug naar inzet scherm
			reset = true;

           

            // Reset dealer
            dealer.kaart_index = 0;
            dealer.set_hand_value(0);
            dealer.set_stood(false);
            dealer.Dealer_busted = false;
            dealer.verberg_kaart();
            first_deal = true;

            // Reset players (behoud namen, reset kaarten)
            for (int i = 0; i < players.size(); i++) {
                players[i].kaart_index = 0;
                players[i].set_hand_value(0);
                players[i].set_stood(false);
                players[i].player_busted = false;
                players[i].player_blackjack = false;
                players[i].player_done = false;
                // Inzet wordt opnieuw gevraagd in Player_Names_Window
            }
        }

        // Button 2: Nieuwe game (alles reset)
        if (ImGui::Button("Nieuwe Game", ImVec2(280, 40))) {
            // Reset ALLES
            game_over_window = false;
            game_window = false;
            dealer_window = false;
            Player_Names_Window = false;
            player_init_window = true;  // Terug naar aantal spelers

            // Reset dealer
            dealer.kaart_index = 0;
            dealer.set_hand_value(0);
            dealer.set_stood(false);
            dealer.Dealer_busted = false;
            dealer.verberg_kaart();
            first_deal = true;

            // Clear players
            players.clear();
            Players = 0;

            // Reset name en inzet buffers
            for (int i = 0; i < max_players; i++) {
                memset(name_buffers[i], 0, max_name_length);
                inzet_buffers[i] = 0;
            }
        }
		ImGui::End();
    }
}


app::~app()
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
}

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; // Present with vsync
    // g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice)
    {
        g_pd3dDevice->Release();
        g_pd3dDevice = nullptr;
    }
    if (g_pD3D)
    {
        g_pD3D->Release();
        g_pD3D = nullptr;
    }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
