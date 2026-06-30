// FUNC_NAME: InputManager::processControllerRumble
// Address: 0x00618c40
// Returns 1 if rumble state changed, 0 otherwise.
// Takes eventData pointer (ecx) and slot index in esi (0-15).
// Checks event type 0x19 (rumble trigger?) and state byte 0x02 (motor index?).
// Uses global arrays for per-slot rumble flags and two rumble manager objects.

#include <stdint.h>

// Global state: possibly platform/mode flag.
extern int32_t g_rumbleMode; // 0x00f15a14

// Per-slot active rumble flag (0 or 1). Indexed by slot.
extern uint8_t g_controllerRumbleActive[16]; // 0x011f7440

// Per-slot per-motor rumble flags (3 motors: left, right, trigger?).
// Each slot has 3 consecutive bytes starting at g_perMotorRumbleFlags[slot * 3].
extern uint8_t g_perMotorRumbleFlags[]; // 0x011f7450

// Rumble manager objects (virtual class with vtable+0x114 as SetMotorState).
extern class RumbleManager* g_rumbleManager1; // 0x0120595c
extern class RumbleManager* g_rumbleManager2; // 0x01205750

// Assume RumbleManager has a method SetMotorState(uint slot, uint motorIndex) at vtable offset 0x114.
// This would be called as: (*(void(__thiscall**)(class RumbleManager*, uint, uint)) (*(uint32_t*)obj + 0x114))(obj, slot, motorIndex);

bool __fastcall processControllerRumble(void* eventData, uint slotIndex)
{
    // eventData structure: +0x08 = event type (int), +0x21 = state byte (char)
    int eventType = *(int*)((uint8_t*)eventData + 8);
    char stateByte = *(char*)((uint8_t*)eventData + 0x21);

    if (slotIndex < 16 && g_rumbleMode == 3)
    {
        if (eventType == 0x19 && stateByte == 0x02)
        {
            // Start rumble: set controller active flag if not already.
            if (g_controllerRumbleActive[slotIndex] == 0)
            {
                // Call rumbleManager1 to activate rumble? (vtable+0x114 takes two params: slot and motor?)
                (*(void(__thiscall**)(class RumbleManager*, uint, uint))(*(uint32_t*)g_rumbleManager1 + 0x114))(g_rumbleManager1, slotIndex, 0);
                g_controllerRumbleActive[slotIndex] = 1;
            }

            // For each of three motor flags (at offset slot*3 + 0,1,2), ensure they are set.
            uint baseIndex = slotIndex * 3;
            if (g_perMotorRumbleFlags[baseIndex] != 1)
            {
                (*(void(__thiscall**)(class RumbleManager*, uint, uint))(*(uint32_t*)g_rumbleManager2 + 0x114))(g_rumbleManager2, slotIndex, 0);
                g_perMotorRumbleFlags[baseIndex] = 1;
            }
            if (g_perMotorRumbleFlags[baseIndex + 1] != 1)
            {
                (*(void(__thiscall**)(class RumbleManager*, uint, uint))(*(uint32_t*)g_rumbleManager2 + 0x114))(g_rumbleManager2, slotIndex, 1);
                g_perMotorRumbleFlags[baseIndex + 1] = 1;
            }
            if (g_perMotorRumbleFlags[baseIndex + 2] != 1)
            {
                (*(void(__thiscall**)(class RumbleManager*, uint, uint))(*(uint32_t*)g_rumbleManager2 + 0x114))(g_rumbleManager2, slotIndex, 2);
                g_perMotorRumbleFlags[baseIndex + 2] = 1;
            }
            return true;
        }

        // If rumble was active but event is not a start rumble, or if event type is 0x19 (but state != 2), stop rumble.
        if (g_controllerRumbleActive[slotIndex] != 0 || eventType == 0x19)
        {
            // Call rumbleManager1 to deactivate rumble? (pass 0 or 1?)
            (*(void(__thiscall**)(class RumbleManager*, uint, uint))(*(uint32_t*)g_rumbleManager1 + 0x114))(g_rumbleManager1, slotIndex, 0);
            g_controllerRumbleActive[slotIndex] = 0;
        }
    }
    return false;
}