// FUNC_NAME: TimeManager::updateFrame
#include <cstdint>

// Global constants
extern const float kTwoPow32;          // DAT_00e44578 - 4294967296.0f for unsigned wrap
extern const float kTicksToSeconds;    // DAT_00e2e210 - conversion factor (e.g., 1/1000.0f)
extern const float kDeltaAbsConstant;  // DAT_00e44564 - likely 0.0f for absolute value

// Global singleton pointers
extern void* g_pSubsystem1;            // DAT_01223508
extern void* g_pSubsystem2;            // DAT_012234bc
extern uint8_t* g_pGameState;          // DAT_0122350c

// Forward declarations of called functions
bool updateSubsystem1(void* manager, float deltaSeconds); // FUN_005dc9b0
bool updateSubsystem2(void* manager, float deltaSeconds); // FUN_005e4700
void yieldToOtherThreads();                               // FUN_005e86e0

class TimeManager {
public:
    uint32_t lastTimestamp; // offset +0x08

    bool updateFrame(uint32_t currentTime) {
        int32_t deltaTicks = currentTime - this->lastTimestamp;
        float deltaSeconds = static_cast<float>(deltaTicks