// FUNC_NAME: game_initialize
// Address: 0x00439f30
// Role: Dispatches initialization for three core subsystems (graphics, input, audio)

void game_initialize(void)
{
    // Initialize graphics/rendering subsystem (0x004c9390)
    initGraphics();

    // Initialize input subsystem (0x00452b90)
    initInput();

    // Initialize audio subsystem (0x005e3cd0)
    initAudio();
}