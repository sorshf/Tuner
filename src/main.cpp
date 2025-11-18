#include "App.h"
#include "Config.h"

int main() {

    App app {"Tuner", WINDOW_WIDTH, WINDOW_HEIGHT, SAMPLE_RATE, BUFFER_DURATION_ms, FONT_PATH, FONT_SIZE};

    app.run();

}