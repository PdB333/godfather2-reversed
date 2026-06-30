// FUNC_NAME: processMissionPairing

#include <cstdint>

// Global array of entity structures (size 0x38 each, offset 0x2 for short match)
extern uint8_t g_entityArray[]; // at 0x011a0f28
extern uint32_t g_currentEntityIndex; // DAT_011f38f0
extern uint32_t g_targetEntityIndex; // DAT_012058a4
extern uint32_t g_expectedEntityIndex; // DAT_01206a88
extern uint32_t g_earlyExitValue; // DAT_01206b14
extern uint32_t g_currentState; // DAT_01205958
extern int32_t g_currentPhase; // DAT_01206aec, modulo 3
extern int32_t g_minThreshold; // DAT_012058d0
extern int32_t g_maxThreshold; // DAT_00f15988
extern int32_t g_missionFlag1; // _DAT_011f3a30
extern int32_t g_missionFlag2; // _DAT_011f3a3c
extern int32_t g_missionFlag3; // _DAT_011f3a38
extern int32_t g_missionFlag4; // _DAT_011f3a14
extern uint32_t g_missionCompletionCount; // DAT_01206a78

// Forward declarations of called functions (with guessed names)
bool isMissionInProgress(); // FUN_0041ddf0
uint64_t getEntityHandle64(uint32_t index); // FUN_00606370 - returns packed 64-bit value with two 32-bit pointers
void updateMissionState(); // FUN_0041d7d0
void setMissionPhase(int32_t phase); // FUN_0041d310
void finalizePhaseTransition(); // FUN_0041dd00
void setMissionFlag1(int32_t value); // FUN_00412f50
void setMissionFlag2(int32_t value); // FUN_00412f10
void initializeMission(int32_t param); // FUN_00417fe0
void setupMissionParameters(int32_t a, int32_t b, int32_t c); // FUN_00417cf0

void processMissionPairing(int32_t param1)
{
    // Check if any mission is currently active; if so, just update state and exit.
    if (isMissionInProgress())
    {
        g_currentState = g_earlyExitValue;
        return;
    }

    // Validate the incoming parameter against expected entity index.
    if (param1 == g_expectedEntityIndex && g_currentEntityIndex < 0x1000)
    {
        // Access entity at g_currentEntityIndex
        uint8_t* currentEntity = &g_entityArray[g_currentEntityIndex * 0x38];
        if (currentEntity != nullptr && *currentEntity > 2) // byte at offset 0
        {
            uint8_t* targetEntity = (g_targetEntityIndex < 0x1000) ? &g_entityArray[g_targetEntityIndex * 0x38] : nullptr;

            // Compare short at offset 0x2 of both entities
            if (*(int16_t*)(currentEntity + 0x2) == *(int16_t*)(targetEntity + 0x2))
            {
                // Retrieve packed 64-bit handle for current entity (side effect? return value ignored)
                getEntityHandle64(g_currentEntityIndex);

                // Get packed handle for target entity; its value contains two 32-bit pointers.
                uint64_t packedHandles = getEntityHandle64(g_targetEntityIndex);

                // The 64-bit value is assumed to hold two pointers (low 32 bits = first, high 32 bits = second).
                // Compare the int16_t at offset +4 from each of those pointers.
                int32_t lowPtr = static_cast<int32_t>(packedHandles & 0xFFFFFFFF);
                int32_t highPtr = static_cast<int32_t>(packedHandles >> 32);
                if (*(int16_t*)(lowPtr + 4) == *(int16_t*)(highPtr + 4))
                {
                    // Advance the phase modulo 3
                    g_currentPhase = (g_currentPhase + 1) % 3;

                    updateMissionState();
                    setMissionPhase(g_currentPhase);
                    finalizePhaseTransition();

                    // Clamp thresholds
                    if (g_minThreshold < 0x16) g_minThreshold = 0x16;
                    if (g_maxThreshold > 0x16) g_maxThreshold = 0x16;
                    g_missionFlag1 = 1;
                    setMissionFlag1(1);
                    setMissionFlag2(1);

                    if (g_minThreshold < 0x19) g_minThreshold = 0x19;
                    if (g_maxThreshold > 0x19) g_maxThreshold = 0x19;
                    g_missionFlag2 = 7;

                    if (g_minThreshold < 0x18) g_minThreshold = 0x18;
                    if (g_maxThreshold > 0x18) g_maxThreshold = 0x18;
                    g_missionFlag3 = 0;

                    if (g_minThreshold < 0xF) g_minThreshold = 0xF;
                    if (g_maxThreshold > 0xF) g_maxThreshold = 0xF;
                    g_missionFlag4 = 0;

                    initializeMission(0);
                    setupMissionParameters(1, 5, 6);

                    g_missionCompletionCount++;
                }
            }
        }
    }
}