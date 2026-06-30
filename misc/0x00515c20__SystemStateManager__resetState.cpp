// FUNC_NAME: SystemStateManager::resetState
#include <cstdint>

// External globals (defined elsewhere in the binary)
extern float g_someFloat; // address 0x00e2af44
extern int32_t g_someInt; // address 0x00e2b1a4
extern int32_t g_someOtherInt; // address 0x00e2eb58

// Internal static state (offsets relative to module data segment at 0x01219200)
static float s_resetEnabled;   // +0x40 (0x01219240) – enables the conditional block
static float s_thresholdA;     // +0x20 (0x01219220)
static float s_thresholdB;     // +0x2C (0x0121922C)
static float s_valueSet1[3];   // +0x00, +0x04, +0x08 (0x01219200,0x01219204,0x01219208)
static float s_valueSet2[3];   // +0x10, +0x14, +0x18 (0x01219210,0x01219214,0x01219218)
static float s_otherValue1;    // +0x24 (0x01219224)
static float s_otherValue2;    // +0x28 (0x01219228)
static int32_t s_intBlock[8];  // +0xE0..+0xFC (0x012191E0..0x012191FC)
static int32_t s_zeroInt1;     // +0x0C (0x0121920C)
static int32_t s_zeroInt2;     // +0x1C (0x0121921C)
static int32_t s_someInt;      // +0x30 (0x01219230)

// Forward declaration of sub-function called under certain conditions
void FUN_00515460(void);

void SystemStateManager::resetState()
{
    // If reset is enabled and the external float is within one of two threshold ranges,
    // call the sub-function (e.g., a "stop rain" or "reset timer" routine).
    if ((s_resetEnabled != 0.0f) &&
        ((g_someFloat <= s_thresholdA &&
          (g_someFloat <= s_valueSet1[0] ||
           g_someFloat <= s_valueSet1[1] ||
           g_someFloat <= s_valueSet1[2])) ||
         (g_someFloat <= s_thresholdB &&
          (g_someFloat <= s_valueSet2[0] ||
           g_someFloat <= s_valueSet2[1] ||
           g_someFloat <= s_valueSet2[2]))))
    {
        FUN_00515460();
    }

    // Reset value set 1 to the integer external cast to float
    s_valueSet1[0] = static_cast<float>(g_someInt); // +0x00
    s_valueSet1[1] = static_cast<float>(g_someInt); // +0x04
    s_valueSet1[2] = static_cast<float>(g_someInt); // +0x08

    // Clear integer block (8 elements)
    for (int i = 0; i < 8; ++i) {
        s_intBlock[i] = 0;
    }

    // Clear any leftover integer fields
    s_zeroInt1 = 0; // +0x0C
    s_zeroInt2 = 0; // +0x1C

    // Clear value set 2
    s_valueSet2[0] = 0.0f; // +0x10
    s_valueSet2[1] = 0.0f; // +0x14
    s_valueSet2[2] = 0.0f; // +0x18

    // Clear thresholds
    s_thresholdA = 0.0f; // +0x20
    s_thresholdB = 0.0f; // +0x2C

    // Set other values from the second external integer
    s_otherValue1 = static_cast<float>(g_someOtherInt); // +0x24
    s_otherValue2 = static_cast<float>(g_someOtherInt); // +0x28

    // Clear additional integer
    s_someInt = 0; // +0x30

    // Disable the reset flag so this block only runs once per trigger
    s_resetEnabled = 0.0f; // +0x40
}