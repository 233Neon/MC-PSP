#include "MenuState.hpp"

namespace Minecraft::Menus{

	MenuState::MenuState(){
        elapsed = 0;
        dt = 0;
        selectRegion = selectPosY = selectPosX = 0;
        langPos = langPosMax = langPosSel = 0;
    }

    MenuState::~MenuState(){

    }

	void MenuState::Init(){
        t = Timer();
        //BGM!!!
        srand(time(0));
	    int musicChoice = rand() % 4 + 1; //1 - 4
        std::stringstream ss;
        ss << "./assets/sounds/ambient/menu/menu";
        ss << musicChoice;
        ss << ".bgm";

	    bgm = oslLoadSoundFile(ss.str().c_str(),OSL_FMT_STREAM);
        button = oslLoadSoundFile("./assets/sounds/other/button1.wav", 0);
	    g_AudioManager.PlayMusic(bgm);

        panorama = new Panorama();

        menu_states = MENU_STATE_TITLE;

        logo = TextureUtil::LoadPng("./assets/minecraft/textures/gui/title/minecraft.png");
        Minecraft1 = new Sprite(logo, 0, 0, 155, 45);
        Minecraft2 = new Sprite(logo, 0, 45, 120, 45);

        std::ifstream infile("./assets/minecraft/texts/splashes.txt");

        std::vector<std::string> splashes;

        std::string temp;
	    while(std::getline(infile, temp)){
		    splashes.push_back(temp);
	    }
	
	    srand(time(0));
	    int chosen = rand() % splashes.size();
	
	    splashText = splashes[chosen];

        selectPosY = 0;
        selectPosX = 1;

        widgets = TextureUtil::LoadPng("./assets/minecraft/textures/gui/widgets.png");
        disabled = new Sprite(widgets, 0, 46, 200, 20);
        unselected = new Sprite(widgets, 0, 66, 200, 20);
        selected = new Sprite(widgets, 0, 86, 200, 20);

        miniSel = new Sprite(widgets, 0, 86, 200, 20);
        miniSel->Scale(0.48f, 1.0f);
        miniUnSel = new Sprite(widgets, 0, 66, 200, 20);
        miniUnSel->Scale(0.48f, 1.0f);
        

        lang = new Sprite(widgets, 0, 106, 20, 20);
        hlang = new Sprite(widgets, 0, 126, 20, 20);

        options_bg = TextureUtil::LoadPng("assets/minecraft/textures/gui/options_background.png");
        options_tile = new Sprite(options_bg);
        options_tile->Scale(2.0f, 2.0f);

        Common::g_TranslationOBJ.init();
        Common::g_TranslationOBJ.setTranslation("de_de");
    }

	void MenuState::Enter(){

    }
	void MenuState::CleanUp(){
        //Sprites


        delete panorama;

        //BGM!!!
        oslDeleteSound(bgm);
    }

	void MenuState::Pause(){

    }
	void MenuState::Resume(){

    }

	void MenuState::HandleEvents(StateManager* sManager){

    }
	void MenuState::Update(StateManager* sManager){
        dt = t.GetDeltaTime();
        elapsed += dt;

        g_System.InputUpdate();
        switch(menu_states){
            case MENU_STATE_TITLE:{
                titleScreenUpdate();
                break;
            }

            case MENU_STATE_LANGUAGE:{
                languageScreenUpdate();
                break;
            }
        }

        splashSize = vfpu_sinf(elapsed * 3.14159f) * (0.618f - (1.0f - 0.618f))/4.0f + (1.0f - 0.687f)*2 ;
    }
    

	void MenuState::Draw(StateManager* sManager){
        g_RenderManager.StartFrame(0, 0, 0);

        if(menu_states == MENU_STATE_TITLE){
            g_RenderManager.SetPerspective(75, 480.0f / 272.0f, 0.3f, 1000.0f); //Into 3D Mode for panorama
            panoramaPass();
        }

        g_RenderManager.SetOrtho(0,0,0,0,0,0); //Into 2D Mode for menu pass
        menuPass();
        g_RenderManager.EndFrame();
    }

    void MenuState::menuPass(){
        switch(menu_states){
            case MENU_STATE_TITLE:{
                titleScreenDraw();
                break;
            }

            case MENU_STATE_LANGUAGE:{
                languageScreenDraw();
                break;
            }
        }   
    }


    void MenuState::panoramaPass(){
        panorama->update(dt);
        panorama->render();
    }
}