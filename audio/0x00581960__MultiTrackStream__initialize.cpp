// FUNC_NAME: MultiTrackStream::initialize
// Address: 0x00581960
// Role: Initialize a MultiTrackStream object, allocate and set sub-track data (20 bytes)

#include <cstdint>

// External globals (from .data section)
extern uint32_t DAT_00e2b1a4;          // default stream value
extern void* PTR_FUN_00e3ac24;         // vtable for MultiTrackStream
extern int* DAT_0120556c;              // global allocator instance (vtable pointer)

uint32_t FUN_004265d0(void* param, int* allocator); // creates stream buffer/reader

void __thiscall MultiTrackStream::initialize(void)
{
    uint32_t* thisStream = (uint32_t*)this;
    int* allocator = DAT_0120556c;
    uint32_t defaultVal = DAT_00e2b1a4;
    uint32_t stackParam[4] = {0}; // parameters for allocator
    uint32_t* subTrack; // allocated 20-byte block

    // Set vtable at offset 0x00
    thisStream[0] = (uint32_t)&PTR_FUN_00e3ac24;

    // ---- initialise stream properties ----
    thisStream[4]  = 8;                    // +0x10: maxTrackCount = 8
    thisStream[7]  = 0;                    // +0x1C: someFlag = false
    thisStream[8]  = 0;                    // +0x20: someIndex = 0
    thisStream[9]  = defaultVal;           // +0x24: maybe startOffset
    thisStream[10] = defaultVal;           // +0x28: maybe endOffset
    thisStream[0xb] = 1;                   // +0x2C: loopEnabled = true
    *(uint8_t*)&thisStream[0xc] = 0;       // +0x30: a byte flag = 0
    thisStream[5]  = 0xffffffff;           // +0x14: activeTrack = -1 (none)
    thisStream[6]  = 0xffffffff;           // +0x18: pendingTrack = -1 (none)

    // additional zero fields
    thisStream[0x12] = 0;                  // +0x48
    thisStream[0x11] = 0;                  // +0x44
    thisStream[0x10] = 0;                  // +0x40

    thisStream[0x13] = defaultVal;         // +0x4C: probably another offset
    thisStream[0x16] = 0;                  // +0x58
    thisStream[0x15] = 0;                  // +0x54
    thisStream[0x14] = 0;                  // +0x50

    thisStream[0x17] = defaultVal;         // +0x5C
    thisStream[0x18] = 0;                  // +0x60: trackChangeCount
    thisStream[0x19] = 0;                  // +0x64: subTrack pointer (null)
    thisStream[0x1a] = 0;                  // +0x68

    // ----- allocate sub-track structure (20 bytes) -----
    stackParam[0] = 0;
    stackParam[1] = 0;
    stackParam[2] = 0;
    stackParam[3] = 0;

    // allocator is a class with a virtual function at vtable+0 that takes size and a struct
    subTrack = (uint32_t*)((**(code**)*allocator)(0x14, &stackParam));
    if (subTrack != nullptr)
    {
        // Reuse stackParam for sub-init
        stackParam[1] = 0;
        stackParam[2] = 0;
        stackParam[3] = 0;
        uint32_t result = FUN_004265d0(&stackParam[1], allocator);
        subTrack[3] = result;        // subTrack+0x0C: some handle
        subTrack[4] = (uint32_t)allocator; // subTrack+0x10: store allocator pointer
        // Call method at allocator vtable+8 (e.g., allocate buffer or finalize)
        ((void(*)(void))(**(code**)(*allocator + 8)))();

        // Clear first three dwords of subTrack
        subTrack[0] = 0;             // +0x00
        subTrack[2] = 0;             // +0x08
        subTrack[1] = 0;             // +0x04

        thisStream[0x19] = (uint32_t)subTrack; // store at +0x64
        return;
    }

    thisStream[0x19] = 0; // failed, keep null
}