// FUNC_NAME: PlayerCCTVariables::serialize
#include <cstddef>
#include <cstring>

// This function serializes the PlayerCCTVariables object into a buffer.
// The buffer layout is:
//   +0x00: Type tag (0x203)
//   +0x04: Size (0xC0)
//   +0x08: 2 bytes (short) = 2
//   +0x0A: 2 bytes (short) = 0? (actually from param_1+2)
//   +0x14: 8 bytes packed flags
//   +0x1C: 64 bytes (0x40) from source +0x24
//   +0x5C: 4 bytes from source +0x28
//   +0x60: 4 bytes from source +0x30
//   +0x64: 4 bytes from source +0x34
//   +0x68: 4 bytes from source +0x40
//   +0x6C: 64 bytes (0x40) from source +0x44
//   +0xAC: 4 bytes from source +0x48
//   +0xB0: 4 bytes from source +0x50
//   +0xB4: 4 bytes from source +0x54
//   +0xB8: 4 bytes from source +0x60
//   +0xBC: 4 bytes from source +0x64

typedef void (*WriteFunc)(void* dest, const void* src, int size);
// Global function table for serialization (from DAT_01205590)
extern WriteFunc g_writeFuncTable[0x10]; // offset 0x10 corresponds to index 4

int __fastcall PlayerCCTVariables::serialize(void* thisPtr, void* outBuffer)
{
    // Debug/logging calls (not essential for serialization)
    // First log: format string at 0x59797e, writes some header
    {
        int local_10 = 0x203;          // type tag
        int local_c = 0xC0;           // size
        int uStack_28 = 0x59797e;     // "Serializing PlayerCCTVariables"
        int iStack_24 = (int)outBuffer;
        g_writeFuncTable[0x4](outBuffer); // writes header? Actually no parameters in call
    }

    // Second log: format string at 0x597996
    {
        int uStack_28 = 2;
        int iStack_30 = (int)outBuffer + 2;
        int uStack_34 = 0x597996;     // another format string
        g_writeFuncTable[0x4]();      // call without explicit params
    }

    // Now actual serialization
    // Write 4 bytes at outBuffer+4 from this+0x20
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 4), (void*)((int)thisPtr + 0x20), 4);
    // Write 4 bytes at outBuffer+8 from this+0x24? Actually call with only one arg
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 8));

    // Pack flags from various offsets into a 8-byte structure
    unsigned int flags1 = 0;
    flags1 |= ((*(int*)((int)thisPtr + 0x2C) != 0) ? 0x01 : 0x00);
    flags1 |= (*(unsigned char*)((int)thisPtr + 0x38) << 8);
    flags1 |= (*(unsigned char*)((int)thisPtr + 0x3C) << 16);
    flags1 |= (*(int*)((int)thisPtr + 0x4C) != 0) ? (0x01000000) : 0;

    unsigned int flags2 = 0;
    flags2 |= (*(unsigned char*)((int)thisPtr + 0x58) << 0);
    flags2 |= (*(unsigned char*)((int)thisPtr + 0x5C) << 8);
    flags2 |= (*(int*)((int)thisPtr + 0x68) != 0) ? 0x00010000 : 0;
    flags2 |= (*(int*)((int)thisPtr + 0x6C) != 0) ? 0x01000000 : 0;

    // Write 8 bytes of flags at outBuffer+0x14
    unsigned int flagBuffer[2] = { flags1, flags2 };
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 0x14), flagBuffer, 8);

    // Copy 64-byte block from source+0x24 to destination+0x1C
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 0x1C), *(void**)((int)thisPtr + 0x24), 0x40);

    // Copy individual 4-byte values
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 0x5C), (void*)((int)thisPtr + 0x28), 4);
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 0x60), (void*)((int)thisPtr + 0x30), 4);
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 0x64), (void*)((int)thisPtr + 0x34), 4);
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 0x68), (void*)((int)thisPtr + 0x40), 4);

    // Copy 64-byte block from source+0x44 to destination+0x6C
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 0x6C), *(void**)((int)thisPtr + 0x44), 0x40);

    // Copy remaining 4-byte values
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 0xAC), (void*)((int)thisPtr + 0x48), 4);
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 0xB0), (void*)((int)thisPtr + 0x50), 4);
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 0xB4), (void*)((int)thisPtr + 0x54), 4);
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 0xB8), (void*)((int)thisPtr + 0x60), 4);
    g_writeFuncTable[0x4]((void*)((int)outBuffer + 0xBC), (void*)((int)thisPtr + 0x64), 4);

    // Return the total size written (0xC0)
    return 0xC0;
}