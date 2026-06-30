// FUNC_NAME: StreamManager::initStreamSlots
void __thiscall StreamManager::initStreamSlots(void)
{
    // offset 0x214 in this
    *(int *)((char *)this + 0x214) = -1;

    // uVar1 and uVar2 are some global constants (likely initialization values)
    int constA = DAT_00e2b118;   // Example: could be 0 or some handle
    int constB = DAT_00e2b1a4;   // Example: unknown, maybe -1 or 0

    // Array of 5 stream slots, each 0x68 bytes (26 dwords), starting at offset 0x18
    int *slot = (int *)((char *)this + 0x18);
    for (int i = 0; i < 5; i++)
    {
        // Offset 0x00: some flags/state
        slot[-6] = constB;       // +0x00
        slot[-5] = constB;       // +0x04
        slot[4] = constB;        // +0x28
        slot[5] = constB;        // +0x2c

        // Offset 0x44: sample rate (96 kHz)
        slot[0xb] = 96000;
        // Offset 0x4c: another sample rate
        slot[0xd] = 96000;

        // Bytes at +0x21, +0x22, +0x23 set to zero
        ((char *)slot)[9] = 0;    // +0x21
        ((char *)slot)[10] = 0;   // +0x22
        ((char *)slot)[0xb] = 0;  // +0x23

        // Various zero fields
        slot[-4] = 0;   // +0x08
        slot[3] = 0;    // +0x24
        slot[6] = 0;    // +0x30
        slot[7] = 0;    // +0x34
        slot[0xc] = 0;  // +0x48

        // Debug magic numbers for uninitialized memory detection
        slot[-3] = 1;             // +0x0c, later overwritten
        slot[-2] = 0xbadbadba;    // +0x10
        slot[-1] = 0xbeefbeef;    // +0x14
        slot[0]  = 0xeac15a55;    // +0x18
        slot[1]  = 0x91100911;    // +0x1c

        // Store constants
        slot[8] = constA;         // +0x38
        slot[9] = constB;         // +0x3c

        // Additional zero fields at end
        slot[0xe] = 0;   // +0x50
        slot[0xf] = 0;   // +0x54
        slot[0x10] = 0;  // +0x58
        slot[0x11] = 0;  // +0x5c
        slot[0x12] = 0;  // +0x60
        slot[0x13] = 0;  // +0x64

        // Overwrite the earlier slot[-3] with -1 (invalid index)
        slot[-3] = -1;   // +0x0c

        // Advance to next slot (0x1a dwords = 0x68 bytes)
        slot += 0x1a;
    }

    // After initialization of all slots, set additional fields in the main struct
    // Offset 0x27c - 0x29c: likely default values for some global state
    *(int *)((char *)this + 0x27c) = constA;
    *(int *)((char *)this + 0x280) = constB;
    *(int *)((char *)this + 0x284) = constB;
    *(int *)((char *)this + 0x288) = constB;
    *(int *)((char *)this + 0x28c) = constB;
    *(int *)((char *)this + 0x290) = constB;
    *(int *)((char *)this + 0x29c) = constB;

    // Bytes at +0x298 and +0x299 zeroed
    ((char *)this)[0x298] = 0;
    ((char *)this)[0x299] = 0;

    // Offset 0x2b8 zeroed and 700 (0x2bc) set to -1
    *(int *)((char *)this + 0x2b8) = 0;
    *(int *)((char *)this + 700) = -1;  // 700 = 0x2bc
}