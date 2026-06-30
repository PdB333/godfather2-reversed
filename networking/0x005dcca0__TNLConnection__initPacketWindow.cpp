// FUNC_NAME: TNLConnection::initPacketWindow
void __thiscall TNLConnection::initPacketWindow(void)
{
    // Constants from global data
    uint32_t constVal1 = DAT_00e2b1a4; // likely initial sequence or some identifier
    uint32_t constVal2 = DAT_00e2b118;

    // Starting at offset +0x18 from this there is an array of 5 packet slots
    // Each slot size = 0x68 bytes (26 dwords)
    uint32_t* slot = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x18);

    // Initialize 5 slots (iVar4 from 4 down to 0 inclusive)
    for (int i = 4; i >= 0; --i) {
        // Relative offsets from slot pointer:
        // -0x18: magic signature? (first part of slot header)
        slot[-6] = constVal1;   // +0x00 (this+0x18-0x18 = this+0x0) but actually multiple times? This writes to the object's base fields per iteration.
        // This is likely writing to fields that are before the slot array, i.e., object header fields.
        // But careful: each iteration writes to different object offsets because slot increments.
        // We'll just mirror the decompiled assignments.

        // Write to slot[-6] through slot[-1] as object-level fields
        slot[-6] = constVal1;            // +0x00 / this+0x00 (first iteration), then +0x68, etc.
        slot[-5] = constVal1;            // +0x04
        slot[4] = constVal1;             // +0x10 (from slot start)
        slot[5] = constVal1;             // +0x14
        slot[0xb] = 96000;               // +0x2c (44 bytes)
        slot[0xd] = 96000;               // +0x34 (52 bytes)
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(slot) + 9) = 0;   // byte at +9
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(slot) + 10) = 0;  // byte at +10
        slot[-4] = 0;                    // -0x10
        slot[3] = 0;                     // +0x0c
        slot[6] = 0;                     // +0x18
        slot[7] = 0;                     // +0x1c
        slot[0xc] = 0;                   // +0x30 (48)
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(slot) + 0xb) = 0; // byte at +11
        slot[-3] = 1;                    // -0x0c
        slot[-2] = 0xbadbadba;           // -0x08
        slot[-1] = 0xbeefbeef;           // -0x04
        *slot = 0xeac15a55;              // +0x00
        slot[1] = 0x91100911;            // +0x04
        slot[8] = constVal2;             // +0x20
        slot[9] = constVal1;             // +0x24
        slot[0xe] = 0;                   // +0x38 (56)
        slot[0xf] = 0;                   // +0x3c (60)
        slot[0x10] = 0;                  // +0x40 (64)
        slot[0x11] = 0;                  // +0x44 (68)
        slot[0x12] = 0;                  // +0x48 (72)
        slot[0x13] = 0;                  // +0x4c (76)

        // Advance to next slot (0x1a dwords = 0x68 bytes)
        slot += 0x1a;
    }

    // Set additional sentinel fields at offset 0x218, 0x21c, 0x220, 0x224
    *(uint32_t*)((uintptr_t)this + 0x218) = 0xbadbadba;
    *(uint32_t*)((uintptr_t)this + 0x21c) = 0xbeefbeef;
    *(uint32_t*)((uintptr_t)this + 0x220) = 0xeac15a55;
    *(uint32_t*)((uintptr_t)this + 0x224) = 0x91100911;

    // Call sub-initializers
    uint32_t result = FUN_005dd030(); // likely returns a pointer or handle
    // Store result in multiple fields (pointer array?)
    *(uint32_t*)((uintptr_t)this + 0x270) = result;
    *(uint32_t*)((uintptr_t)this + 0x274) = result;
    *(uint32_t*)((uintptr_t)this + 0x278) = result;
    *(uint32_t*)((uintptr_t)this + 0x2a0) = result;
    *(uint32_t*)((uintptr_t)this + 0x2a4) = result;
    *(uint32_t*)((uintptr_t)this + 0x2a8) = result;
    *(uint32_t*)((uintptr_t)this + 0x2ac) = result;

    FUN_005dce60(); // further init
    FUN_005e18b0(); // final init

    return;
}