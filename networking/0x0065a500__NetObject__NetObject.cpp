// FUNC_NAME: NetObject::NetObject
#include <cstdint>

// External functions
extern void FUN_00660a10(uint32_t, int, int, uint32_t*);
extern void FUN_00661210(uint32_t*, uint32_t*, uint32_t*);

// External vtable pointer
extern uint32_t PTR_LAB_00e433dc;

uint32_t* __fastcall NetObject(uint32_t unused_ecx, uint32_t sourceHandle, uint32_t* obj, uint64_t* sequenceData) {
    uint32_t tempBuffer[1064]; // temporary buffer for data read
    uint32_t* src;
    uint32_t* dst;
    int i;

    // Initialize object header: vtable pointer, then two zero fields
    obj[0] = (uint32_t)&PTR_LAB_00e433dc; // vtable
    obj[1] = 0;
    obj[2] = 0;

    // Read 0x10 units? from sourceHandle into tempBuffer
    FUN_00660a10(sourceHandle, 0x10, 0, tempBuffer);

    // Copy 0x81 (129) dwords from tempBuffer to obj+0x6C (offset of 0x1b * 4)
    src = tempBuffer;
    dst = obj + 0x1b; // +0x6C
    for (i = 0x81; i != 0; i--) {
        *dst = *src;
        src++;
        dst++;
    }

    // Replicate the 64-bit sequence data into four positions in the object
    *reinterpret_cast<uint64_t*>(obj + 3)  = *sequenceData;        // offset +0x0C
    *reinterpret_cast<uint64_t*>(obj + 5)  = sequenceData[1];     // offset +0x14
    *reinterpret_cast<uint64_t*>(obj + 7)  = *sequenceData;        // offset +0x1C
    *reinterpret_cast<uint64_t*>(obj + 9)  = sequenceData[1];     // offset +0x24

    // Additional initialization call
    FUN_00661210(obj + 3, obj + 0x17, tempBuffer); // offsets +0x0C and +0x5C

    // Zero out a field at offset 0x270 (uint32)
    obj[0x9c] = 0;

    return obj;
}