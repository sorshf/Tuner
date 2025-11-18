
#include "App.h"


App::App(const char* title, int width, int height, int sampleRate, int bufferDuration_ms, const char* fontPath, float fontSize):
    m_windowWidth(width),
    m_windowHeight(height),
    m_recorder(sampleRate, bufferDuration_ms),
    m_text({255, 255, 255, 255})//White text color
{
    
    //Create Audio Recording stream
    if (m_recorder.failed) {
        SDL_DestroyWindow(m_window);
        SDL_DestroyRenderer(m_renderer);
        SDL_Quit();
    }
    
    if(!SDL_Init(SDL_INIT_VIDEO)){
        std::cerr << "Couldn't initialize SDL video library: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    TTF_Init();

    //Create window
    m_window = SDL_CreateWindow("Tuner", width, height, SDL_WINDOW_ALWAYS_ON_TOP);
    if (m_window == NULL) {
        std::cerr << "Couldn't create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    //Create Renderer
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (m_renderer == NULL) {
        std::cerr << "Couldn't initiate the renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    //Text Engine
    m_textEngine = TTF_CreateRendererTextEngine(m_renderer);
    if (!m_textEngine) {
        std::cerr << "Text Engine Error: " << SDL_GetError() << std::endl;
    }

    m_font = TTF_OpenFont(fontPath, fontSize);
    if (!m_font) {
        std::cerr << "Font Load Error: " << SDL_GetError() << std::endl;
    }

    //Adjust the dimension and anchor of the graph
    float graphWidth = 70.0/100.0*width;
    float graphHeight = 60.0/100.0*height;
    float xG = (width - graphWidth)/2;
    float yG = height / 4;

    m_graph.changeDimension(graphWidth, graphHeight);
    m_graph.changeAnchor({xG, yG});

}

App::~App() {
    TTF_DestroyRendererTextEngine(m_textEngine);
    TTF_CloseFont(m_font);
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    TTF_Quit();
    SDL_Quit();
}

void App::run() {

    //Controling the main loop of the app
    bool quit = false;
    SDL_Event e;

    //Main loop of the app
    while (!quit) {

       while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        update();
        render();

    }
}


void App::update() {

    // If recorder recorded enough data
    if(m_recorder.record()){
        m_graph.update(m_recorder.getSound());
        m_text.update(m_recorder.getSound().getFreqStr(), m_textEngine, m_font);
    }

}

void App::render() {

    //Background is black
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    //Draw the graph with white
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    m_graph.display(m_renderer);

    //Draw frequency number
    float xT = (m_windowWidth - 200) / 2.0; //200 is arbitrary
    float yT = m_windowHeight/10.0;
    m_text.display(xT, yT);
    
    //Present everything
    SDL_RenderPresent(m_renderer);

    SDL_Delay(40);

}