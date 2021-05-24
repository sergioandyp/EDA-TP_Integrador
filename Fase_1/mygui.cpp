#include "mygui.h"

#include "fileborowser.h"
#include <allegro5/allegro_image.h>
#include <vector>
//#include <Windows.h>
#include <iostream>
#include <string>

#include <boost/filesystem.hpp>

#define WIDTH 1024
#define HEIGH 576

using namespace std;



Gui::Gui() {

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(WIDTH, HEIGH);
    al_set_window_title(display, "Tree Reader");
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    if (!al_init_font_addon()) {

        std::cout << "failed to initialize allegro fonts!\n" << std::endl;
    }
    if (!al_init_ttf_addon()) {

        std::cout << "failed to initialize allegro ttf!\n" << std::endl;
    }
    if (!al_init_image_addon()) {       // ADDON necesario para manejo de imagenes 
        std::cout << "Failed to initialize image addon!" << std::endl;
    }
    if (!(background = al_load_bitmap("background.jpg"))) {
        std::cout << "Failed to initialize image addon!" << std::endl;
    }
    state = WAITING;
    pathtext = "Enter the Path";
}

Gui::~Gui() {

    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();
    al_destroy_event_queue(queue);
    al_destroy_bitmap(background);
    al_destroy_display(display);
}

void Gui::setup() {

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplAllegro5_Init(display);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

}

void Gui::setstate(DisplayState state) {
    this->state = state;
}
DisplayState Gui::getstate() {
    return state;
}

string Gui::getpath() {
    return path;
}

DisplayState Gui::functions() {
  
   // cout << background << endl;
   // al_clear_to_color(al_map_rgb(100, 100, 100));   //Clearing of the display is made before LCD are written
    al_draw_bitmap(background, 0, 0, 0);
    ALLEGRO_EVENT ev;

    while (al_get_next_event(queue, &ev))
    {
        ImGui_ImplAllegro5_ProcessEvent(&ev);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            state = STOP_RUNNING;

        if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
        {
            ImGui_ImplAllegro5_InvalidateDeviceObjects();
            al_acknowledge_resize(display);
            ImGui_ImplAllegro5_CreateDeviceObjects();
        }
    }

    // Start the Dear ImGui frame
    ImGui_ImplAllegro5_NewFrame();
    ImGui::NewFrame();
    ImGui::FileBrowser fileDialog;
    static bool enabled = false; // For menu options
    static float progress = 0.0f; // For progress bar


    if (ImGui::BeginMainMenuBar())
    {
        
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open")) {
                state = FILESELECT;
                enabled = false;
                progress = 0.0f;
            }
            
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    switch (state){
        case WAITING:
            break;
        case MENU:
            ImGui::Begin("Menu");
            progress = 0.0f;
            if (ImGui::BeginMenu("Calculate Mrarkletree")) {
                for (int i = 1; i < n+1; i++) {
                    string temp = "Block " + to_string(i);
                    if (ImGui::MenuItem(temp.c_str())) {
                        enabled = true;
                        state = CALCULATEMERKLE;
                        curr = i;
                    }
                }
                ImGui::EndMenu();
              
            }

            if (ImGui::MenuItem("Draw Tree", (const char*)0, false, enabled))
            {
                state = DRAWTREE;
            }
            ImGui::End();

            break;
        case FILESELECT:
            //static imgui_ext::file_browser_modal fileBrowser("Import");


            // (optional) set browser properties
            //fileDialog.SetTitle("Files");
            //fileDialog.SetTypeFilters({ ".json"});

            // mainloop
            // while ()
            // {
                //...do other stuff like ImGui::NewFrame();

                //fileDialog.Open();
                //fileDialog.Display();

                //if (fileDialog.HasSelected())
                //{
                //    std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
                //    fileDialog.ClearSelected();
                //    state = MENU;
                //}
            ImGui::Begin("File Selector");
            ImGui::InputText("", bufPath, MAXIMUM_PATH_LENGTH + 1);
            ImGui::Text(pathtext.c_str());
            if (ImGui::Button("Done")) {    // Buttons return true when clicked (most widgets return true when edited/activated)
                path = string(bufPath);
                if (boost::filesystem::exists(path)) {
                    state = MENU;
                    pathtext = "Enter the path";
                }
                else {
                    pathtext = "The path doesn't exist. Please try again.";
                }
            }
            ImGui::End();

            //Seteo el vector
            n = 5;
            break;
        case DRAWTREE:

            al_draw_circle(WIDTH / 2-200, HEIGH-200, 50, al_map_rgb(100, 200, 200), 20);
            al_draw_circle(WIDTH / 2+0, HEIGH-200, 50, al_map_rgb(100, 200, 200), 20);
            al_draw_circle(WIDTH / 2+200, HEIGH-200, 50, al_map_rgb(100, 200, 200), 20);
            al_draw_circle(WIDTH / 2+400, HEIGH-200, 50, al_map_rgb(100, 200, 200), 20);
            al_draw_circle(WIDTH / 2-100, HEIGH-400, 50, al_map_rgb(100, 200, 200), 20);
            al_draw_circle(WIDTH / 2+300, HEIGH-400, 50, al_map_rgb(100, 200, 200), 20);
            al_draw_circle(WIDTH / 2+100, HEIGH-500, 50, al_map_rgb(100, 200, 200), 20);

            ImGui::Begin("Menu");
            if (ImGui::MenuItem("Go back"))
            {
                state = MENU;
                enabled = false;
            }
            ImGui::End();
            break;
        case CALCULATEMERKLE:
            //Do sth

            
            ImGui::Begin("Menu");
            progress += 0.4f * ImGui::GetIO().DeltaTime;
            // Typically we would use ImVec2(-1.0f,0.0f) or ImVec2(-FLT_MIN,0.0f) to use all available width,
            // or ImVec2(width,0.0f) for a specified width. ImVec2(0.0f,0.0f) uses ItemWidth.
            string temp = "Caluclating Block" + to_string(curr) + "\n";
            ImGui::Text(temp.c_str());
            ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            ImGui::End();
            //cout << progress << endl;
            if (progress >= 1.0f) {
                state = MENU;
            }




            
            break;
        }

    // Rendering
    ImGui::Render();
    ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
    al_flip_display();

    return state;
}
