// FUNC_NAME: Player::updateCullingState (0x00741d60)
// Role: Updates culling visibility state based on distance, timer, and component flags.
void __fastcall Player::updateCullingState(int this) {
    char cVar1;
    int timeInfo;

    // If the culling/visibility helper component at this+0x50 exists, call its virtual update method (vtable+0x164)
    if (*(int **)(this + 0x50) != (int *)0x0) {
        (**(code **)(**(int **)(this + 0x50) + 0x164))();
    }

    if (*(int *)(this + 0x50) != 0) {
        timeInfo = FUN_005552b0(); // Get current time info (likely a struct with two floats)
        // Check if the game is in a paused/negative time state and if a global time range is valid
        if ((*(float *)(timeInfo + 4) < 0.0) && (g_cullMinTime < g_cullMaxTime - *(float *)(timeInfo + 4))) {
            // Reset the timeout to global game time and clear the culling flag (bit 0 of this+0x60)
            *(int *)(this + 0x54) = g_gameTime;
            *(uint *)(this + 0x60) = *(uint *)(this + 0x60) & 0xfffffffe;
        }
    }

    // Check bit 11 (0x800) of the component's state at this + 0x8e4
    if ((*(uint *)(*(int *)(this + 0x50) + 0x8e4) >> 0xb & 1) == 0) {
        // If component bit is clear, check distance from this+0x30 or recent timeout
        if ((*(float *)(this + 0x30) <= g_cullDistance) ||
            (*(int *)(this + 0x54) == g_gameTime) ||
            ((uint)(g_gameTime - *(int *)(this + 0x54)) < 0xb)) {
            goto LAB_00741dea;
        }
    }

    // Mark as culled (bit 0 set)
    *(uint *)(this + 0x60) = *(uint *)(this + 0x60) | 1;

LAB_00741dea:
    cVar1 = FUN_007f8f10(); // Check if debug/dev mode forces all objects to be culled
    if (cVar1 != '\0') {
        *(uint *)(this + 0x60) = *(uint *)(this + 0x60) | 1;
    }
    return;
}