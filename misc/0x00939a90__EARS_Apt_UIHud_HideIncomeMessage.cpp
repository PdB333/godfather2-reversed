// Xbox PDB: EARS_Apt_UIHud_HideIncomeMessage
// FUNC_NAME: UIManager::setIncomeMessageHidden
// Function address: 0x00939a90
// Role: Toggles the visibility of income messages (likely HUD alerts)
// Called from FUN_0093e330 (some UI initialization routine)

#include <cstdint>

// Forward declarations for callees (hypothetical EA EARS UI functions)
static void registerUIEvent(const char* eventName, int flags, void* callbackData, int size, void* handlerData);
static void applyUIEffect(void* effectParams, int flags);

// Global data referenced by this function
extern uint32_t DAT_01130440;               // Template/initializer for effect params
extern void* DAT_00d8a64c;                  // Callback or data pointer for event
extern void* DAT_00e36d94;                  // Handler data for hiding effect
extern void* DAT_00e36da0;                  // Handler data for showing effect

// Internal struct for effect parameters (size derived from stack: 4+4+1 = 9 bytes)
struct UIEffectParams {
    uint32_t field0;    // +0x00 (local_c, initialized from DAT_01130440)
    uint32_t field4;    // +0x04 (local_8, set to 0)
    uint8_t  field8;    // +0x08 (local_4, set to 0)
} __attribute__((packed));

void UIManager::setIncomeMessageHidden(char hidden) {
    void* handlerData = (hidden != 0) ? &DAT_00e36d94 : &DAT_00e36da0;

    // Register the hide/show income message event in the UI system
    registerUIEvent("HideIncomeMessage", 0, &DAT_00d8a64c, 1, handlerData);

    // Prepare effect parameters from global template and apply/play them
    UIEffectParams effectParams;
    effectParams.field0 = DAT_01130440;   // Copy global defaults
    effectParams.field4 = 0;              // Zero out remaining fields
    effectParams.field8 = 0;

    applyUIEffect(&effectParams, 0);
}