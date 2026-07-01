// FUNC_NAME: Mission::onMissionQuit
// Address: 0x008d1a70
// Role: Logs mission quit event with elapsed time and resets active flag

void __fastcall Mission::onMissionQuit()
{
    // Log mission quit with elapsed time (float at +0x14)
    logMessage(this, "%.1f,Mission Quit\n", (double)(*(float*)((uint8_t*)this + 0x14)));

    // Reset mission state (likely timer/cleanup)
    resetMissionState();

    // Clear active flag at +0x1f (0x1F = 31, byte offset)
    *(uint8_t*)((uint8_t*)this + 0x1F) = 0;
}