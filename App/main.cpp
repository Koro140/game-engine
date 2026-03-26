#include "Core/Application.h"

#include "App/AppLayer.h"
#include "App/PauseLayer.h"

#include <iostream>

int main(void) {
    Engine::ApplicationSettings settings;

    settings.appName = "Game";
    settings.windowHeight = 720;
    settings.windowWidth = 1280;
    Engine::Application app(settings);

    app.PushLayer<AppLayer>();
    app.PushLayer<PauseLayer>();

    app.PopLayer();

    app.run();
}