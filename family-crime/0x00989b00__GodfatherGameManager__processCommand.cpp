// FUNC_NAME: GodfatherGameManager::processCommand

#include <cstdint>

// Function at 0x00989b00
// Handles various debug commands and messages for the Godfather game manager.
int __thiscall GodfatherGameManager::processCommand(GodfatherGameManager* thisPtr, int messageId)
{
    int result;
    int idA;
    // crString or similar structure composed of pointer, length, capacity?
    struct {
        void* data; // +0x00 local_c
        int length; // +0x04 local_8
        char flags; // +0x08 local_4
    } tempString;

    // Check if message matches a specific debug command ID (e.g., "enableDebug")
    idA = getMessageIdA(); // 0x00466840
    if (messageId == idA) {
        // Set a flag at offset 0x16 to 1 (enable something)
        *((uint8_t*)thisPtr + 0x16) = 1;

        // Initialize a temporary string with a global constant and call reset/init
        tempString.data = (void*)DAT_011302c8; // global constant string
        tempString.length = 0;
        tempString.flags = 0;
        stringInit(&tempString, 0); // 0x00408a00

        // Call virtual function at vtable offset 0x2c (likely "onDebugEnabled")
        (thisPtr->vtable[0x2c])();

        return 0;
    }

    // Check another specific command ID (maybe "toggleDebug")
    idA = getMessageIdB(); // 0x00466860
    if (messageId == idA) {
        toggleDebug(); // 0x00989150
        return 0;
    }

    // Handle numeric message IDs directly
    if (messageId == 8) {
        processCommand8(); // 0x009894e0
    }
    else if (messageId == 9) {
        processCommand9(); // 0x00989500
        return 0;
    }
    else if (messageId == 0xC) {
        // "ToggleOption" debug command
        debugPrint("ToggleOption", 0, &DAT_00d9158c, 0); // 0x005a04a0
        return 0;
    }

    return 0;
}