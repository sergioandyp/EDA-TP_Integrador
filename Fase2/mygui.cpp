#include "mygui.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_allegro5.h"

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

#define MAXPORT 65535
using namespace std;

struct ExampleAppLog
{
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool                AutoScroll;  // Keep scrolling if already at the bottom.

    ExampleAppLog()
    {
        AutoScroll = true;
        Clear();
    }

    void    Clear()
    {
        Buf.clear();
        LineOffsets.clear();
        LineOffsets.push_back(0);
    }

    void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size + 1);
    }

    void    Draw(const char* title, bool* p_open = NULL)
    {
        if (!ImGui::Begin(title, p_open))
        {
            ImGui::End();
            return;
        }

        // Options menu
        if (ImGui::BeginPopup("Options"))
        {
            ImGui::Checkbox("Auto-scroll", &AutoScroll);
            ImGui::EndPopup();
        }

        // Main window
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        bool clear = ImGui::Button("Clear");
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("Filter", -100.0f);

        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        if (clear)
            Clear();
        if (copy)
            ImGui::LogToClipboard();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        const char* buf = Buf.begin();
        const char* buf_end = Buf.end();
        if (Filter.IsActive())
        {
            // In this example we don't use the clipper when Filter is enabled.
            // This is because we don't have a random access on the result on our filter.
            // A real application processing logs with ten of thousands of entries may want to store the result of
            // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
            for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
            {
                const char* line_start = buf + LineOffsets[line_no];
                const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                if (Filter.PassFilter(line_start, line_end))
                    ImGui::TextUnformatted(line_start, line_end);
            }
        }
        else
        {
            // The simplest and easy way to display the entire buffer:
            //   ImGui::TextUnformatted(buf_begin, buf_end);
            // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
            // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
            // within the visible area.
            // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
            // on your side is recommended. Using ImGuiListClipper requires
            // - A) random access into your data
            // - B) items all being the  same height,
            // both of which we can handle since we an array pointing to the beginning of each line of text.
            // When using the filter (in the block of code above) we don't have random access into the data to display
            // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
            // it possible (and would be recommended if you want to search through tens of thousands of entries).
            ImGuiListClipper clipper;
            clipper.Begin(LineOffsets.Size);
            while (clipper.Step())
            {
                for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
            clipper.End();
        }
        ImGui::PopStyleVar();

        if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();
        ImGui::End();
    }
};

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
    mode = WAITING;
    pathtext = "Enter the Path";
    int octets1[4] = { 123, 123, 123, 123 };
    int octets2[4] = { 123, 123, 123, 123 };
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

DisplayMode Gui::functions() {

    al_set_target_backbuffer(display);

    al_draw_bitmap(background, 0, 0, 0);
    ALLEGRO_EVENT ev;

    while (al_get_next_event(queue, &ev))
    {
        ImGui_ImplAllegro5_ProcessEvent(&ev);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            mode = STOP_RUNNING;

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
    static bool enablesendbtn = false; // For TCP sending message
    static bool enabletransactions = false; // For TCP transactions
    static float progress = 0.0f; // For progress bar
    
    static ExampleAppLog my_log;
    my_log.Draw("log");

    if (ImGui::BeginMainMenuBar())
    {

        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open")) {
                mode = MERKLETREE;
                state = FILESELECT;
                enabled = false;
                progress = 0.0f;
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Node"))
        {
            if (ImGui::BeginMenu("Create")) {
                if (ImGui::MenuItem("Full")) {
                    //Guardo el tipo de nodo....
                    state = CREATE;
                    mode = NODE;
                }
                if (ImGui::MenuItem("SPV")) {
                    //Guardo el tipo de nodo....
                    state = CREATE;
                    mode = NODE;
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Link")) {
                state = LINK;
                mode = NODE;
            }
            if (ImGui::BeginMenu("Connect")) {
                for (int i = 0; i < 3; i++) {
                    string temp = ("Client" + to_string(i));
                    if (ImGui::BeginMenu(temp.c_str())) {
                        for (int j = 0; j < 5; j++) {
                            temp = ("Server" + to_string(j));
                            if (ImGui::MenuItem(temp.c_str())) {
                                mode = NODE;
                                state = SEND;
                                enablesendbtn = false;
                                enabletransactions = false;
                                my_log.AddLog("A TCP connection between %d and %d was stablished\n", i, j);
                            }
                        }
                        ImGui::EndMenu();
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

    }
    ImGui::EndMainMenuBar();
        
    switch (mode) {
    case WAITING:
        break;
    case MERKLETREE:
        switch (state) {

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
        break;
    case NODE:
        switch (state) {
        case CREATE:
            ImGui::Begin("Node Creator");
            ImGui::InputInt("Port", &port1, 1, 100);
            if (ImGui::Button("Create")) {    // Buttons return true when clicked (most widgets return true when edited/activated)
                if (port1 < MAXPORT) {
                    cout << port1 << endl;
                    my_log.AddLog("A new local node was created - Port: %d\n", port1);
                    mode = WAITING;
                }
            }
            ImGui::End();
            break;
        case LINK:
            ImGui::Begin("Neighbor Selector");
            ImGui::InputInt("Port1", &port1, 1, 100);
            IPinput(octets1, "IP1");
            ImGui::InputInt("Port2", &port2, 1, 100);
            IPinput(octets2, "IP2");
            
            
            if (ImGui::Button("Link")) {    // Buttons return true when clicked (most widgets return true when edited/activated)
                if (port1 < MAXPORT) {
                    cout << port1 << endl;
                    cout << octets1[0] << "." << octets1[1] << "." << octets1[2] << "." << octets1[3]<<endl;
                    cout << port2 << endl;
                    cout << octets2[0] << "." << octets2[1] << "." << octets2[2] << "." << octets2[3]<<endl;
                    mode = WAITING;
                    my_log.AddLog("The node %d.%d.%d.%d: port %d was connected with the node %d.%d.%d.%d: port %d\n", octets1[0], octets1[1], octets1[2], octets1[3], port1, octets2[0], octets2[1], octets2[2], octets2[3], port2);
                }
            }
            ImGui::End();
            break;
        case SEND:
            for(const auto& x: node1.getSendActions()) {
                for(const auto& y: node2.getReceiveActions()){
                    if (y==x){
                        //Do sth....
                    }
                }
            }
            // sizeof(ACTION_ID)/sizeof(int)
            ImGui::Begin("Connect");
            if (ImGui::BeginMenu("Select message type")) {
                for (int j = 0; j < 3; j++) {
                    string temp = ("Message" + to_string(j));
                    if (ImGui::MenuItem(temp.c_str())) {
                        enablesendbtn = true;
                        if (j == 3) {
                            enabletransactions = true;
                        }
                    }
                }
                ImGui::EndMenu();
            }
            if (enabletransactions) {
                ImGui::InputInt("Value to transfer", &valueToTransfer, 1, 100);
                ImGui::InputText("Public key", bufKey, MAXIMUM_KEY_LENGTH + 1);
            }
            if (enablesendbtn && ImGui::Button("Send")) {    // Buttons return true when clicked (most widgets return true when edited/activated)
                publicKey = string(bufKey);
                my_log.AddLog("A message was send\n");
                mode = WAITING;
                my_log.AddLog("The TCP connection ended\n");
            }
            ImGui::End();
            break;
        }
        break;
        
    }
    // Rendering
    ImGui::Render();
    ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
    al_flip_display();

    return mode;
}
void Gui::IPinput(int * octets, string ip) {
    const char * myip= ip.c_str();
    float width = ImGui::CalcItemWidth();
    ImGui::BeginGroup();
    ImGui::PushID(myip);
    ImGui::TextUnformatted(myip);
    ImGui::SameLine();
    for (int i = 0; i < 4; i++) {
        ImGui::PushItemWidth(width / 4.0f);
        ImGui::PushID(i);
        bool invalid_octet = false;
        if (octets[i] > 255) {
            // Make values over 255 red, and when focus is lost reset it to 255.
            octets[i] = 255;
            invalid_octet = true;
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        }
        if (octets[i] < 0) {
            // Make values below 0 yellow, and when focus is lost reset it to 0.
            octets[i] = 0;
            invalid_octet = true;
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
        }
        ImGui::InputInt("##v", &octets[i], 0, 0, ImGuiInputTextFlags_CharsDecimal);
        if (invalid_octet) {
            ImGui::PopStyleColor();
        }
        ImGui::SameLine();
        ImGui::PopID();
        ImGui::PopItemWidth();
    }
    ImGui::PopID();
    ImGui::EndGroup();

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

