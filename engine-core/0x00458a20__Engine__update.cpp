// FUNC_NAME: Engine::update
void Engine::update()
{
    // Update engine timer with global timer data (DAT_00e2e4c8)
    Timer::update(&g_timerData); // FUN_00ab4db0
    // Process pending events (e.g. input, network, animation)
    Events::process();           // FUN_00ab4e70
}