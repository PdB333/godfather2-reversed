// FUNC_NAME: CrewLeaderComponent::init
#include <cstdint>

class CrewLeaderComponent {
public:
    void init();
};

// Global data references (unknown exact types)
extern uint32_t DAT_01223510; // pointer to some global object with vtable
extern uint32_t DAT_00e2b1a4; // default VecX or config value
extern uint32_t DAT_00e2b04c; // default VecY or config value
extern uint32_t DAT_00e2b050; // default VecZ or config value

void CrewLeaderComponent::init() {
    // Assume 'this' is accessed via register ESI (unaff_ESI)
    int* thisPtr = reinterpret_cast<int*>(this);
    int* globalObj = reinterpret_cast<int*>(DAT_01223510);

    // Set various fields to default values
    thisPtr[8] = DAT_00e2b1a4;               // +0x20
    thisPtr[0] = 0;                           // +0x00
    thisPtr[1] = 0;                           // +0x04
    thisPtr[2] = 0;                           // +0x08
    thisPtr[6] = -1;                          // +0x18
    thisPtr[7] = -1;                          // +0x1C
    thisPtr[9] = 0;                           // +0x24
    thisPtr[10] = 0;                          // +0x28
    thisPtr[0xC] = 0x1000;                    // +0x30 (4096, maybe max health/ammo)
    thisPtr[0xB] = 96000;                     // +0x2C (maybe max money/XP)
    thisPtr[0xE] = 0;                         // +0x38

    // Call virtual function on global object to get some initial value (e.g., random seed)
    typedef int (*GetFunc)(int*);
    GetFunc getter = *reinterpret_cast<GetFunc*>(*globalObj + 0x5c);
    int seedVal = getter(globalObj);
    thisPtr[0xF] = seedVal;                   // +0x3C

    uint32_t uVar2 = DAT_00e2b1a4;
    uint32_t uVar4 = DAT_00e2b04c;
    uint32_t uVar1 = DAT_00e2b050;

    thisPtr[0x10] = 0;                        // +0x40
    thisPtr[0x12] = 0;                        // +0x48
    thisPtr[0x13] = 0;                        // +0x4C
    thisPtr[0x14] = 0;                        // +0x50
    thisPtr[0x15] = 0;                        // +0x54
    thisPtr[0x16] = 0x32;                     // +0x58 (50)
    thisPtr[0x32] = 0;                        // +0xC8

    // Set individual bytes at offsets
    *reinterpret_cast<uint8_t*>(thisPtr + 0x33) = 0;   // byte at +0xCC
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(thisPtr) + 0xCD) = 0;
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(thisPtr) + 0xCE) = 0;
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(thisPtr) + 0xCF) = 0;
    *reinterpret_cast<uint8_t*>(thisPtr + 0x34) = 0;   // byte at +0xD0
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(thisPtr) + 0xD1) = 0;
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(thisPtr) + 0xD2) = 0;
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(thisPtr) + 0xD3) = 0;

    thisPtr[0xB3] = 0;                        // +0x2CC
    thisPtr[0xB4] = 0;                        // +0x2D0
    thisPtr[0xB2] = 0;                        // +0x2C8
    thisPtr[0xB0] = -2;                       // +0x2C0 (0xFFFFFFFE)
    thisPtr[0xB1] = -2;                       // +0x2C4 (0xFFFFFFFE)
    thisPtr[0x17] = 0;                        // +0x5C

    *reinterpret_cast<uint8_t*>(thisPtr + 0x18) = 0;   // byte at +0x60
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(thisPtr) + 0x61) = 0;
    thisPtr[0x2E] = 0;                        // +0xB8
    thisPtr[0x2F] = 0;                        // +0xBC
    thisPtr[0x30] = -1;                       // +0xC0
    thisPtr[0x19] = 1;                        // +0x64
    thisPtr[0x1A] = 0;                        // +0x68
    thisPtr[0x1B] = 0;                        // +0x6C
    *reinterpret_cast<uint8_t*>(thisPtr + 0x1C) = 0;   // byte at +0x70
    thisPtr[0x26] = 0;                        // +0x98
    *reinterpret_cast<uint8_t*>(thisPtr + 0x21) = 0;   // byte at +0x84
    thisPtr[0x22] = uVar2;                    // +0x88
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(thisPtr) + 0x85) = 0;
    thisPtr[0x23] = uVar4;                    // +0x8C
    thisPtr[0x24] = uVar1;                    // +0x90
    thisPtr[0x25] = 0;                        // +0x94
    thisPtr[0x27] = 0;                        // +0x9C
    thisPtr[0x28] = 0;                        // +0xA0
    thisPtr[0x29] = uVar2;                    // +0xA4
    thisPtr[0x2A] = uVar2;                    // +0xA8
    thisPtr[0x2B] = uVar2;                    // +0xAC
    thisPtr[0x2C] = 100;                      // +0xB0
    thisPtr[0x2D] = 0;                        // +0xB4
    thisPtr[0x31] = 0;                        // +0xC4

    // Initialize 4 crew member data blocks, each of size 0x78 bytes (30 dwords)
    uint32_t* slotPtr = reinterpret_cast<uint32_t*>(thisPtr + 0x3D); // +0xF4
    for (int i = 0; i < 4; ++i) {
        slotPtr[-5] = 0;           // offset within each block: 0xEC? relative to start of block? 
        slotPtr[0x17] = 0;
        slotPtr[0x18] = 0;
        slotPtr[-4] = 0;
        *reinterpret_cast<uint8_t*>(slotPtr + (-3)) = 0;
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(slotPtr) - 0xB) = 0;
        slotPtr[0x13] = 0;
        slotPtr[0x14] = 0;
        slotPtr[0x15] = -1;
        slotPtr[-2] = 1;
        slotPtr[-1] = 0;
        slotPtr[0] = 0;
        *reinterpret_cast<uint8_t*>(slotPtr + 1) = 0;
        slotPtr[0xB] = 0;
        *reinterpret_cast<uint8_t*>(slotPtr + 6) = 0;
        slotPtr[7] = uVar2;        // default vecX
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(slotPtr) + 0x19) = 0;
        slotPtr[8] = uVar4;        // default vecY
        slotPtr[9] = uVar1;        // default vecZ
        slotPtr[10] = 0;
        slotPtr[0xC] = 0;
        slotPtr[0xD] = 0;
        slotPtr[0xE] = uVar2;
        slotPtr[0xF] = uVar2;
        slotPtr[0x10] = uVar2;
        slotPtr[0x11] = 100;
        slotPtr[0x12] = 0;
        slotPtr[0x16] = 0;
        // Move to next block (0x1E dwords = 0x78 bytes)
        slotPtr += 0x1E;
    }
}