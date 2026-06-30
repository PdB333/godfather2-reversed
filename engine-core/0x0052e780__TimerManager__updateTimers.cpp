// FUNC_NAME: TimerManager::updateTimers
// Function address: 0x0052e780
// Updates all timer entries with delta time. Each timer entry has a current timer (float), a flag (bool), a secondary timer (float), and a default value from a structure.
// The system is enabled by global flags g_timerSystemEnabled and g_timerSystemActive.
// Maximum number of timer entries: 768 (0x300), each entry is 24 bytes (0x18).

#include <cstdint>

// Forward declaration of callback function
void TimerManager::onTimerUpdate(); // FUN_0052e2e0

// Global arrays (static members of TimerManager or global)
// These are likely static class members or global variables.
// For reconstruction, we assume they are static members of TimerManager.

// Structure for timer entry (size 0x18)
struct TimerEntry {
    float defaultTimerValue; // +0x00: Default value for secondary timer
    // Other fields unknown, total size 0x18
    uint8_t padding[0x14]; // 20 bytes padding to reach 0x18
};

// Global flags
extern uint8_t g_timerSystemEnabled;   // DAT_01219859
extern uint8_t g_timerSystemActive;    // DAT_01219858

// Global arrays
extern float g_currentTimers[768];       // DAT_01219708
extern uint8_t g_timerFlags[768];        // DAT_01219808
extern float g_secondaryTimers[768];     // DAT_01219788
extern TimerEntry g_timerEntries[768];   // DAT_0121939c

void TimerManager::updateTimers(float deltaTime)
{
    // Check if the timer system is enabled and active
    if (g_timerSystemEnabled != '\0' && g_timerSystemActive != '\0') {
        int index = 0;
        uint32_t byteOffset = 0;
        do {
            // Safety check: maximum 768 entries
            if (byteOffset > 0x2ff) {
                return;
            }

            // Update current timer
            if (g_currentTimers[index] <= 0.0f) {
                g_currentTimers[index] = 0.0f;
            } else {
                g_currentTimers[index] -= deltaTime;
            }

            // Update secondary timer based on flag
            if (g_timerFlags[index] == '\0') {
                // Timer not active: reset secondary timer to default value from entry structure
                g_secondaryTimers[index] = *(float*)(&g_timerEntries[0] + byteOffset); // Read first 4 bytes of entry
            } else {
                // Timer active: decrement secondary timer and call update callback
                g_secondaryTimers[index] -= deltaTime;
                TimerManager::onTimerUpdate(); // Callback function
            }

            index++;
            byteOffset += 0x18; // Each entry is 24 bytes
        } while (g_timerSystemActive != '\0');
    }
}