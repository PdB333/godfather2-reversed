// FUNC_NAME: InputManager::handleControllerMessage
// Address: 0x00618c40
// Handles controller vibration enable/disable based on received message type.
// Uses global controller state arrays: g_controllerVibrationActive[16] (byte),
// g_controllerMotorFlags[16*3] (bytes, stride 12), and two manager singletons:
// g_vibrationManager (DAT_0120595c) and g_motorManager (DAT_01205750).
// message+8 is type (0x19 = vibration command), message+0x21 is subtype (0x02 = enable vibration).

#include <cstdint>

// Forward declarations of globals (from other translation units)
extern uint8_t g_controllerVibrationActive[16];           // 0x011f7440
extern uint8_t g_controllerMotorFlags[16 * 12];           // 0x011f7450 (stride 12 per slot, only first 3 bytes used)
extern int32_t g_controllerMode;                          // 0x00f15a14, expected value 3

// Manager instances with vtable methods
extern void* g_vibrationManager;                          // 0x0120595c
extern void* g_motorManager;                              // 0x01205750

// Helper macro for calling vtable method at offset 0x114 (276)
#define CALL_VTABLE_0x114(obj) \
    ((void (*)(void*))(*(uint32_t*)(*(uint32_t*)(obj) + 0x114)))(obj)

uint32_t __fastcall InputManager::handleControllerMessage(
    void* thisPtr,
    uint32_t controllerSlot,        // passed in EDX (unaff_ESI)
    ControllerMessage* message)      // passed as first parameter (param_1)
{
    if (controllerSlot >= 16 || g_controllerMode != 3)
        return 0;

    if (message->type == 0x19 && message->subtype == 0x02)
    {
        // Enable vibration for this slot
        if (g_controllerVibrationActive[controllerSlot] == 0)
        {
            CALL_VTABLE_0x114(g_vibrationManager);
            g_controllerVibrationActive[controllerSlot] = 1;
        }

        uint32_t baseIdx = controllerSlot * 12;
        // Enable all three motor flags (left, right, ?)
        if (g_controllerMotorFlags[baseIdx] != 1)
        {
            CALL_VTABLE_0x114(g_motorManager);
            g_controllerMotorFlags[baseIdx] = 1;
        }
        if (g_controllerMotorFlags[baseIdx + 1] != 1)
        {
            CALL_VTABLE_0x114(g_motorManager);
            g_controllerMotorFlags[baseIdx + 1] = 1;
        }
        if (g_controllerMotorFlags[baseIdx + 2] != 1)
        {
            CALL_VTABLE_0x114(g_motorManager);
            g_controllerMotorFlags[baseIdx + 2] = 1;
        }

        return 1;
    }

    // Disable vibration if active or if the message is type 0x19 without enable subtype
    if (g_controllerVibrationActive[controllerSlot] != 0 || message->type == 0x19)
    {
        CALL_VTABLE_0x114(g_vibrationManager);
        g_controllerVibrationActive[controllerSlot] = 0;
    }

    return 0;
}

// Structure assumed for the controller message (message+8, +0x21)
struct ControllerMessage
{
    uint32_t type;          // +0x08 (0x19 = vibration)
    uint8_t  subtype;       // +0x21 (0x02 = enable, other = disable)
};