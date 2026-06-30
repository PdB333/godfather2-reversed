// FUNC_NAME: updateGameLoop
// Function address: 0x004acf70
// Role: Simple wrapper function that delegates to the actual update routine at 0x004ae6f0.
// Called from many locations across the game (e.g., 0x00872d90, 0x00739530, etc.),
// suggesting it's the main per-frame update or tick function for the EARS engine.

void updateGameLoop(void)
{
    // Delegate the actual update processing to the internal function.
    FUN_004ae6f0();
    return;
}