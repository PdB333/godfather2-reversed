// FUNC_NAME: InputManager::updateControllerState

// Per-controller state (16 bytes per entry)
struct ControllerState {
    uint32_t flags;      // +0x00
    uint32_t prevFlags;  // +0x04
    int32_t posX;        // +0x08
    int32_t posY;        // +0x0C
};

// Global arrays – each is the base address of a field in the ControllerState array
static uint32_t* gControllerFlags     = (uint32_t*)0x011da7f0;   // &ControllerState[0].flags
static uint32_t* gControllerPrevFlags = (uint32_t*)0x011da7f4;   // &ControllerState[0].prevFlags
static int32_t*  gControllerPosX      = (int32_t*)0x011da7f8;    // &ControllerState[0].posX
static int32_t*  gControllerPosY      = (int32_t*)0x011da7fc;    // &ControllerState[0].posY

// Global input manager (has vtbl)
static InputManager* gInputManager = (InputManager*)0x01205750;

// Function at 0x0060c820
// Updates controller state for a given index and notifies the global manager.
// Parameters:
//   controllerIndex   – param_2
//   rawInputFlags     – passed in EAX register (e.g., bitmask from analog sticks/buttons)
//   newPrevFlags      – param_3 (pointer to new previous flags, may be null)
//                      When non‑null, also expects posX and posY (param_5, param_4).
//   newPosX           – param_5
//   newPosY           – param_4
//   esiPrevFlagsPtr   – unaff_ESI (register parameter, pointer to the value to store in prevFlags)
void InputManager::updateControllerState(
    int controllerIndex,
    uint32_t rawInputFlags,          // in_EAX
    uint32_t* newPrevFlags,          // param_3
    int32_t newPosX,                 // param_5
    int32_t newPosY,                 // param_4
    uint32_t* esiPrevFlagsPtr)       // unaff_ESI
{
    int byteOffset = controllerIndex * 0x10;   // stride of ControllerState

    // Build new flags value: if rawInputFlags does not have a specific bit (0x40000000),
    // force bit 0, then OR with rawInputFlags.
    uint32_t newFlags;
    if (rawInputFlags != 0x40000000) {
        newFlags = 1;                // set bit 0
    } else {
        newFlags = 0;                // original param_1 value, but here we use zero
    }
    newFlags |= rawInputFlags;

    // Update flags if changed, and notify manager via vtbl+0x198
    if (gControllerFlags[controllerIndex] != newFlags) {
        (*(void (__thiscall**)(InputManager*, int, uint32_t))((int*)*gInputManager + 0x198))(
            gInputManager, controllerIndex, newFlags);
        gControllerFlags[controllerIndex] = newFlags;
    }

    // Optional update of position/prevFlags fields
    if (newPrevFlags == nullptr) {
        // Reset prevFlags to zero if it was non‑zero
        if (gControllerPrevFlags[controllerIndex] != 0) {
            (*(void (__thiscall**)(InputManager*, int, uint32_t, int32_t, int32_t))((int*)*gInputManager + 0x190))(
                gInputManager, controllerIndex, 0, 0, newPosY);   // note: param_4 used as newPosY
            gControllerPrevFlags[controllerIndex] = 0;
            return;
        }
    } else {
        // Update if differences exist
        bool changed = (gControllerPrevFlags[controllerIndex] != *newPrevFlags) ||
                       (*(int32_t*)((int)gControllerPosX + byteOffset) != newPosX) ||
                       (*(int32_t*)((int)gControllerPosY + byteOffset) != newPosY);
        if (changed) {
            (*(void (__thiscall**)(InputManager*, int, uint32_t, int32_t, int32_t))((int*)*gInputManager + 0x190))(
                gInputManager, controllerIndex, *newPrevFlags, newPosX, newPosY);
            // Note: the original code stores *unaff_ESI (esiPrevFlagsPtr) into prevFlags
            gControllerPrevFlags[controllerIndex] = *esiPrevFlagsPtr;
            *(int32_t*)((int)gControllerPosX + byteOffset) = newPosX;
            *(int32_t*)((int)gControllerPosY + byteOffset) = newPosY;
        }
    }
    return;
}