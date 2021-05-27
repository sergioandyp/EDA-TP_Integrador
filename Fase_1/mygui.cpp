#include "mygui.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_allegro5.h"

#include <vector>
#include <boost/filesystem.hpp>
#include <iostream>


#define WIDTH 1024
#define HEIGH 576

#define BACKGD_COLOR_R	7
#define BACKGD_COLOR_G	210
#define BACKGD_COLOR_B	170
#define FONT_COLOR		"black"

#define HEIGHT_DIV_PERC	0.1
#define WIDTH_DIV_PERC	0.2


using namespace std;

Gui::Gui() : bufPath("blockchain_sample_0.json"), display(NULL), background(NULL), treeBMP(NULL) {

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    //al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(WIDTH, HEIGH);
    treeBMP = al_create_bitmap(WIDTH, HEIGH);
    al_set_window_title(display, "TPF - Grupo 2 - Fase 1");
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
    al_destroy_bitmap(treeBMP);
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

    al_set_target_backbuffer(display);

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

    switch (state) {
    case WAITING:
        break;
    case MENU:
        ImGui::Begin("Menu");
        progress = 0.0f;
        if (ImGui::BeginMenu("Select Block")) {


            for (Block& block : chain.getChain()) {
                string temp;
                temp = "Block " + to_string(block.getBlockHeight());
                if (ImGui::MenuItem(temp.c_str())) {
                    enabled = true;
                    this->block = block;    // Guardo el bloque
                    merkleTree = block.getMerkleTree(); // Y el tree completo
                    validRoot = merkleTree[0][0] == block.getMerkleRoot();
                    state = CALCULATEMERKLE;
                }
            }
            ImGui::EndMenu();

        }

        if (ImGui::MenuItem("View Block", (const char*)0, false, enabled))
        {
            state = DRAWTREE;
            drawTreeToBMP(WIDTH, HEIGH);

        }
        ImGui::End();

        break;
    case FILESELECT:
        ImGui::Begin("File Selector");
        ImGui::InputText("", bufPath, MAXIMUM_PATH_LENGTH + 1);
        ImGui::Text(pathtext.c_str());
        if (ImGui::Button("Done")) {    // Buttons return true when clicked (most widgets return true when edited/activated)
            path = string(bufPath);
            if (boost::filesystem::exists(path)) {
                pathtext = "Enter the path";
                if (!chain.buildFromPath(path))
                    state = MENU;
                else
                    pathtext = "The file does not contain a valid Blockchain";
            }
            else
                pathtext = "The path does not exist. Please try again.";
        }
        ImGui::End();

        break;
    case DRAWTREE:
    {
        static float c = 60.0;
        ImGui::Begin("Tree", 0, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::DragFloat("Size", &c, 0.2f, 1.0f, 100.0f, "%.0f");
        ImGui::Image(((void*)treeBMP), ImVec2(WIDTH * c / 100.0, HEIGH * c / 100.0));
        ImGui::End();
    }
        ImGui::Begin("Menu");
        if (validRoot)
            ImGui::MenuItem("Markle Root is validated", NULL, true);
        else
            ImGui::MenuItem("Markle Root does not match", NULL, false);
        
        {
            string temp = "ID: " + block.getBlockId();
            ImGui::MenuItem(temp.c_str());
            temp = "Previous Block ID: " + block.getPrevBlockId();
            ImGui::MenuItem(temp.c_str());
            temp = "Transaction count: " + to_string(block.getBlockNTx());
            ImGui::MenuItem(temp.c_str());
            temp = "Block Number: " + to_string(block.getBlockHeight());
            ImGui::MenuItem(temp.c_str());
            temp = "Nonce: " + to_string(block.getBlockNonce());
            ImGui::MenuItem(temp.c_str());
            temp = "Merkle Root: " + block.getMerkleRoot();
            ImGui::MenuItem(temp.c_str());
        }

        ImGui::MenuItem("");
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
        string temp = "Caluclating Block " + to_string(block.getBlockHeight()) + "\n";
        ImGui::Text(temp.c_str());
        ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
        ImGui::End();

#ifdef DEBUG
        cout << progress << endl;
#endif

        if (progress >= 1.0f)
            state = MENU;

        break;
    }

    // Rendering
    ImGui::Render();
    ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
    al_flip_display();

    return state;
}

void Gui::drawTreeToBMP(double dispWidth, double dispHeight) {      //Dibujo del arbol

    al_set_target_bitmap(treeBMP);

    al_clear_to_color(al_map_rgba(0,0,0,0));

    unsigned int h = merkleTree.getHeight() + 1;

    for (unsigned int i = 0; i < h; i++) {
        
        double bros = exp2(i);
        double dividerX = dispWidth * WIDTH_DIV_PERC / (double)(bros + 1.0);
        double dividerY = dispHeight * HEIGHT_DIV_PERC / (double)(h + 1.0);
        int fontSize = 60 - 12 * i;
        ALLEGRO_FONT* font = al_load_font("Sans.ttf", fontSize, 0);

        for (unsigned int j = 0; j < merkleTree[i].size(); j++) {


            double height = (dispHeight - dividerY * (h + 1.0)) / h;
            double width = (dispWidth - dividerX * (bros + 1.0)) / bros;
            double xVert1 = j * (width + dividerX) + dividerX;
            double yVert1 = i * (height + dividerY) + dividerY;
            double r = height / 10.0;

            al_draw_filled_rounded_rectangle(xVert1, yVert1, xVert1 + width, yVert1 + height, r, r, al_map_rgb(BACKGD_COLOR_R, BACKGD_COLOR_G, BACKGD_COLOR_B));

            double centerX = xVert1 + width / 2.0;
            double centerY = yVert1 + height / 2.0;

            al_draw_text(font, al_color_name(FONT_COLOR), centerX, centerY-3*fontSize/4.0, ALLEGRO_ALIGN_CENTRE, merkleTree[i][j].c_str());

        }
        al_destroy_font(font);
    }

    al_set_target_backbuffer(display);

}