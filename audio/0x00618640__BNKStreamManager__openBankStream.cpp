// FUNC_NAME: BNKStreamManager::openBankStream
// Address: 0x00618640
// Role: Opens a bank stream based on bank ID and flags, selects platform-specific audio format from global table, and calls the appropriate loading method on the audio manager (gAudioManager).

// Global definitions (from data section)
extern int gPlatformId;               // DAT_00f15a14: platform identifier (3=PC, 2=Xbox, 1=PS2)
extern uint gBankFormatTable[/*?*/];  // DAT_00f15860: table of format FOURCCs indexed by bank type
extern void* gAudioManager;           // DAT_01205750: pointer to the audio manager singleton
extern void (*gErrorHandler)(int);    // PTR_FUN_00f15a3c: error callback

// Platform-specific audio format FOURCCs
const uint FORMAT_FD42 = 0x34324644;  // "42FD" (possible XMA or ADPCM variant)
const uint FORMAT_INTZ = 0x5a544e49;  // "INTZ" (Xbox format)
const uint FORMAT_RAWZ = 0x5a574152;  // "RAWZ" (PS2 raw format)

bool BNKStreamManager::openBankStream(uint* outData, uint* outSize)
{
    // Offset +0x08: bank type ID (0x19=25, 0x1A=26, etc.)
    int bankType = *(int*)(this + 0x08);
    // Offset +0x0C: flags (bitmask)
    uint flags = *(uint*)(this + 0x0C);
    // Offset +0x01: byte field (subtype or additional flag)
    uchar byte1 = *(uchar*)(this + 0x01);
    // Offset +0x02: word field (e.g., resource handle or group)
    ushort word2 = *(ushort*)(this + 0x02);
    // Offset +0x04: word field (e.g., resource size or offset)
    ushort word4 = *(ushort*)(this + 0x04);
    // Offset +0x30: stream mode (written later, default 1)
    int* modePtr = (int*)(this + 0x30);
    // Offset +0x14 and +0x18: output buffer (cleared before call)
    uint* bufferPtr = (uint*)(this + 0x14);
    uint* bufferSize = (uint*)(this + 0x18);

    // Initialize output parameters
    *outData = 0;
    *outSize = 0x404; // default size: 1028 bytes (likely a buffer reservation)

    // Get initial format from global table
    uint format = gBankFormatTable[bankType];
    uint uVar7 = 0; // additional mode parameter

    // Platform-specific format override
    if (gPlatformId == 3) // PC
    {
        if (bankType == 0x19)
            format = FORMAT_FD42;
    }
    else
    {
        // Check if flags bit 0x3000000 is NOT set to 0x1000000 (maybe "override format" flag)
        if ((flags & 0x3000000) != 0x1000000)
        {
            if (gPlatformId == 2) // Xbox
            {
                if ((bankType == 0x19) || (bankType == 0x1A))
                    format = FORMAT_INTZ;
            }
            else if ((gPlatformId == 1) && ((bankType == 0x19) || (bankType == 0x1A))) // PS2
            {
                format = FORMAT_RAWZ;
            }
        }
    }

    // If no format selected, fail
    if (format == 0)
        return false;

    // Determine stream mode based on flags
    *modePtr = 1; // default mode
    if (flags & 8) // streaming from memory?
    {
        *modePtr = 0;
        // Determine uVar7 based on bank type (0x18 to 0x1D: 2; else 1)
        if ((bankType >= 0x18) && (bankType <= 0x1D))
            uVar7 = 2;
        else
            uVar7 = 1;
    }
    if (flags & 0x200) // loop or persistent?
    {
        *modePtr = 2;
        *outSize = 4; // small output? maybe a handle
    }

    // Clear internal buffer pointers
    *bufferPtr = 0;
    *bufferSize = 0;

    int result;
    if ((flags & 2) == 0)
    {
        if ((flags & 4) == 0)
        {
            // Branch A: load from file with format and mode
            if (((uVar7 & 2) == 0) || (gPlatformId == 1) || (gPlatformId == 2) || (format == FORMAT_FD42))
            {
                // Use loading method at vtable[0x5c]
                result = ((int (__thiscall*)(void*, ushort, ushort, uint, uint, uint, uint, uint*, int)) 
                    ((void**)gAudioManager)[0x5c / 4])(
                    gAudioManager, word2, word4, (uint)byte1, format, uVar7, *modePtr, bufferPtr, 0);
            }
            else
            {
                // Use loading method at vtable[0x74] with different parameters
                result = ((int (__thiscall*)(void*, ushort, ushort, uint, uint, uint, uint, uint*, int)) 
                    ((void**)gAudioManager)[0x74 / 4])(
                    gAudioManager, word2, word4, format, 0, 0, (uint)1, bufferPtr, 0);
                // Note: uVar10 = 1, uVar7=0, uVar8=0 in this path
            }
        }
        else
        {
            // Branch B: use loading method at vtable[0x60] (possibly for in-memory)
            result = ((int (__thiscall*)(void*, ushort, ushort, uchar, int, uint, uint, uint, uint*, int)) 
                ((void**)gAudioManager)[0x60 / 4])(
                gAudioManager, word2, word4, byte1, 1, uVar7, format, *modePtr, bufferPtr, 0);
        }
    }
    else
    {
        // Branch C: use loading method at vtable[100] (0x64) (simplest, only word2)
        result = ((int (__thiscall*)(void*, ushort, int, uint, uint, uint, uint*, int)) 
            ((void**)gAudioManager)[100 / 4])(
            gAudioManager, word2, 1, uVar7, format, *modePtr, bufferPtr, 0);
    }

    // Error handling: specific error code triggers error handler
    if (result == -0x7789FE84)
        gErrorHandler(2);

    return (result == 0);
}