// FUNC_NAME: getXInputControllerName
// Address: 0x00410fa0
// This function retrieves the name of an XInput controller (e.g., "Xbox 360 Controller") and copies it into a buffer.
// It takes the controller index (0-15) as input in EAX and expects a destination buffer pointer in EDI.
// The buffer size should be at least 32 bytes (0x20) to hold the name.

#include <cstring>

// Forward declarations of helper functions (assumed to be in the same module)
uint32_t FUN_00b92e50(uint32_t); // Likely initializes XInput subsystem for the given index
void*   FUN_00b94a80(uint32_t); // Returns a device handle (or pointer to internal XInput device object) for the given index, or NULL if not connected

// Size of the XINPUT_STATE structure used by the game (0x244 bytes seems large; possibly a custom struct)
#define XINPUT_STATE_SIZE 0x244

uint32_t getXInputControllerName(void)
{
    // Controller index (0-15) from EAX
    uint32_t controllerIndex = in_EAX & 0xff;

    // Initialize XInput for this controller slot
    FUN_00b92e50(controllerIndex);

    // Get device object pointer
    void* pDevice = FUN_00b94a80(controllerIndex);

    // If no device connected, copy default name "XInput Device" to the output buffer (pointed by EDI)
    if (pDevice == nullptr)
    {
        const char* defaultName = "XInput Device";
        do
        {
            char c = *defaultName;
            // Write character to buffer at (defaultName + (destinationBuffer - 0xe2f3a8))
            // This is a decompilation artifact; in reality the code likely copies to a buffer passed in EDI.
            // The actual destination is (EDI + offset) where offset is calculated from 'defaultName' address.
            // Given the complexity, we assume the caller has set EDI to a valid buffer.
            *(char*)((uintptr_t)defaultName + ((int)unaff_EDI - 0xe2f3a8)) = c;
            defaultName++;
        } while (c != '\0');

        // Return 1 (success) with upper bytes set by some logic
        return CONCAT31((int3)((uintptr_t)defaultName >> 8), 1);
    }

    // Device is connected; prepare an XInput state buffer
    char stateBuffer[XINPUT_STATE_SIZE];
    memset(stateBuffer, 0, XINPUT_STATE_SIZE);
    *(uint32_t*)stateBuffer = XINPUT_STATE_SIZE; // First DWORD is buffer size

    // Call the device's vtable function at offset 0x3c (likely XInputGetState or XInputGetCapabilities)
    uint32_t result = ((uint32_t (*)(void*, char*))(*(void***)pDevice)[0x3c / 4])(pDevice, stateBuffer);

    if (result == 0)
    {
        // Extraction of controller name from stateBuffer (some string after state data)
        // The name is stored in the stack buffer acStack_224 (size 0x224 = 548 bytes)
        // It appears the code copies the name from the beginning of stateBuffer (offset 0x224? unclear).
        // Actually, the decompiled code uses acStack_224 which is a local array; it seems the name is extracted from stateBuffer.
        // For reconstruction, we assume the game stores a null-terminated string at a known offset in the state buffer.
        // We'll copy it to the output buffer (EDI) if it fits (max 0x20 = 32 characters).
        const char* namePtr = (const char*)stateBuffer; // placeholder; actual offset unknown
        size_t nameLen = strlen(namePtr);
        if (nameLen < 0x20)
        {
            char* dest = (char*)unaff_EDI; // output buffer from EDI
            char* src = (char*)stateBuffer;
            // Copy name character by character (the decompiled code does a loop)
            do
            {
                char c = *src;
                *dest = c;
                src++;
                dest++;
            } while (c != '\0');
            return CONCAT31((int3)((uintptr_t)stateBuffer >> 8), 1);
        }
    }

    // Return error (upper byte set to non-zero)
    return result & 0xffffff00;
}