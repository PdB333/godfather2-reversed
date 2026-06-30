// FUNC_NAME: updateFrame
uint updateFrame(void)
{
    // Call virtual functions at vtable offsets 0xb8 and 0xc4 on the global engine object
    (**(code **)(*(uint*)g_pEngine + 0xb8))(); // Likely pre-update (e.g., input, timing)
    (**(code **)(*(uint*)g_pEngine + 0xc4))(); // Likely post-update (e.g., render, swap)

    // Update engine subsystems
    updateNetwork();      // FUN_005e1ee0
    updateAudio(g_pAudio); // FUN_005e4d30 with global DAT_012234bc
    updateAI();           // FUN_005e43d0

    // Get frame time from timer singleton
    uint frameTime = getFrameTime(g_pTimer); // FUN_005dc2f0 with DAT_01223508
    return frameTime & 0xffffff01; // Mask out low byte and high bits (probably timing flags)
}