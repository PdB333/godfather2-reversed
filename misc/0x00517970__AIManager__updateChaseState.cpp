// FUNC_NAME: AIManager::updateChaseState
// Function at 0x00517970
// Evaluates chase conditions for AI; returns 1 if chase initiation criteria are met.

#include <cstdint>

// Forward declarations for helper functions
bool checkChasePersistence();  // FUN_00517040
void debugPrint(int level);    // FUN_00609890

// Global structures and variables (offsets relative to 0x01219250)
struct ChaseTarget {
    float someTime;          // +0x00 (0x01219250)
    float posX;              // +0x04
    float posY;              // +0x08
    float posZ;              // +0x0C
    float unknown_10;        // +0x10
    float unknown_14;        // +0x14
    float unknown_18;        // +0x18
    float unknown_1C;        // +0x1C
    float unknown_20;        // +0x20
    float unknown_24;        // +0x24
    float unknown_28;        // +0x28
    float timer;             // +0x2C (0x0121927c)
    float unknown_30;        // +0x30 (0x01219280)
    float unknown_34;        // +0x34 (0x01219284)
    float threshold2;        // +0x38 (0x01219288)
    float threshold3;        // +0x3C (0x0121928c)
    float unknown_40;        // +0x40 (0x01219290)
    float unknown_44;        // +0x44 (0x01219294)
    float unknown_48;        // +0x48 (0x01219298)
}; // sizeof = 0x4C

extern ChaseTarget g_chaseTargetA;  // at 0x01219250
extern ChaseTarget g_chaseTargetB;  // at 0x012192b0

extern float g_currentTime;        // DAT_00e2af44
extern float g_maxActivationTime;  // DAT_00e448ec
extern float g_defaultPos;         // DAT_00e2b1a4 (first component of a zero/default vector)

extern uint8_t* g_debugPtr;        // PTR_DAT_00f17650

uint8_t AIManager::updateChaseState()
{
    // Initial condition: if the primary target has no valid timer or any threshold is below current time
    if (g_chaseTargetA.someTime == 0.0f ||
        g_chaseTargetA.timer < g_currentTime ||
        (g_chaseTargetA.threshold2 < g_currentTime && g_chaseTargetA.threshold3 < g_currentTime))
    {
        g_chaseTargetB.timer = 0.0f;
    }
    else
    {
        if (!checkChasePersistence())
        {
            // Copy target A data into B (struct copy)
            g_chaseTargetB = g_chaseTargetA;
        }
    }

    uint8_t result = 0;
    // Check if the copied timer and one of the thresholds are at or above current time
    if (g_currentTime <= g_chaseTargetB.timer &&
        (g_currentTime <= g_chaseTargetB.threshold2 || g_currentTime <= g_chaseTargetB.threshold3))
    {
        if (g_debugPtr[3] != 0)
        {
            debugPrint(2);
        }

        // Check whether the activation distance fields are within valid range
        bool hasMinDist = (g_chaseTargetB.unknown_30 > 0.0f && g_chaseTargetB.unknown_30 <= g_maxActivationTime);
        bool hasMaxDist = (g_chaseTargetB.unknown_34 > 0.0f && g_chaseTargetB.unknown_34 <= g_maxActivationTime);

        if (g_chaseTargetB.unknown_40 == 4 || g_chaseTargetB.unknown_40 == 0x4000000)
        {
            // All three position components must equal the default, and no distance flags.
            if (g_chaseTargetB.posX == g_defaultPos &&
                g_chaseTargetB.posY == g_defaultPos &&
                g_chaseTargetB.posZ == g_defaultPos &&
                !hasMinDist && !hasMaxDist)
            {
                result = 1;
            }
        }
    }

    // Mark debug system as active
    g_debugPtr[3] = 1;
    return result;
}