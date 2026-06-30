// FUNC_NAME: updateWithDelta
// Function address: 0x00598f50
// Role: Updates game logic with delta time, capping large deltas and optionally running a debug update.

#include <cstdint>

// Global variables (likely defined elsewhere)
extern float g_maxDeltaTime;          // 0x00e2fc44 - threshold for delta time cap
extern uint8_t g_debugUpdateEnabled;  // 0x012055a1 - flag to enable debug update path

// Forward declarations of called functions
void debugUpdate(float deltaTime);    // 0x00597070 - special update (debug/physics)
void mainUpdate(float deltaTime);     // 0x00596b90 - core game update

void updateWithDelta(float deltaTime)
{
    if (deltaTime > g_maxDeltaTime) {
        // Delta time exceeds threshold, optionally run debug update then main update.
        if (g_debugUpdateEnabled != 0) {
            debugUpdate(deltaTime);
        }
        mainUpdate(deltaTime);
    } else {
        // Small delta time: skip debug update, run main update with zero delta (pause?).
        mainUpdate(0.0f);
    }
}