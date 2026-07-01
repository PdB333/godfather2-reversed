// FUNC_NAME: Entity::handleEventDispatch
// Address: 0x008b86c0
// This function checks a flag (bit 12) on the entity, and if set, calls a virtual pre-event handler,
// then dispatches two messages via a component (likely a message/network handler), sets additional flags,
// and finally constructs a data structure from the input event data and passes it to the component's process method.

#include <cstdint>

// Assuming these globals exist in the game's data section
extern const uint32_t GLOBAL_EVENT_TIME;    // _DAT_00d5780c (0 constant?)
extern const uint32_t GLOBAL_EVENT_UNKNOWN; // DAT_00d5ccf8 (another constant?)

// Structure used to package event data for the component
struct EventPacket {
    uint32_t field_0x00;
    uint32_t field_0x04;
    uint32_t field_0x08;
    uint32_t field_0x0c; // from global
    uint32_t field_0x10; // from global
    uint32_t field_0x14; // from global
    uint32_t field_0x18; // from global, or zero
    uint32_t field_0x1c; // zero
    uint32_t field_0x20; // zero
    uint32_t field_0x24; // zero
    uint32_t field_0x28; // zero
    uint32_t field_0x2c; // zero
    uint32_t field_0x30; // zero
    uint32_t field_0x34; // zero
    uint32_t field_0x38; // zero
    uint32_t field_0x3c; // zero
    uint32_t field_0x40; // zero
    uint32_t field_0x44; // input[0]
    uint32_t field_0x48; // input[1]
    uint32_t field_0x4c; // input[2]
    uint32_t field_0x50; // global (time?)
    uint32_t field_0x54; // global (unknown)
};

void __thiscall Entity::handleEventDispatch(uint32_t* thisPtr, const uint32_t* eventData) {
    // Check if bit 12 of flags (+0x18c) is set
    if (((thisPtr[99] >> 12) & 1) == 0) { // param_1[99] at offset 0x18c (99 * 4)
        return; // Do nothing if flag not set
    }

    // Call virtual function at vtable offset 0x7c (likely a pre-event callback)
    (**(void(__thiscall**)(uint32_t*))(thisPtr[0] + 0x7c))(thisPtr);

    // Retrieve component pointer at offset 0x130 (thisPtr[0x4c])
    uint32_t* component = (uint32_t*)thisPtr[0x4c];
    if (component == nullptr) {
        return;
    }

    // First message send: using component's vtbl[0x40] (offset 0x40)
    // Message ID: 0x2ff1b913, parameter: thisPtr[0x6c] (offset 0x1b0)
    typedef void(__thiscall* SendMsgFunc)(uint32_t*, uint32_t, uint32_t);
    ((SendMsgFunc)(component[0] + 0x40))(component, 0x2ff1b913, thisPtr[0x6c]);

    // Compute a hash or ID via utility functions
    uint32_t hashVal = FUN_0043b490(); // likely returns current time or frame count
    hashVal = FUN_00540c60(8, 0x15, hashVal); // bit manipulation or encoding

    // Second message send: with different ID
    ((SendMsgFunc)(component[0] + 0x44))(component, 0xb49c1276, hashVal);

    // Set additional flags: bits 0x20000 and 0x800 (0x20800)
    thisPtr[99] |= 0x20800;

    // If component still valid (redundant check)
    if (component == nullptr) {
        return;
    }

    // Build EventPacket structure on stack using eventData input and globals
    EventPacket packet;
    packet.field_0x00 = eventData[0];
    packet.field_0x04 = eventData[1];
    packet.field_0x08 = eventData[2];
    packet.field_0x0c = GLOBAL_EVENT_TIME;
    packet.field_0x10 = GLOBAL_EVENT_TIME;
    packet.field_0x14 = GLOBAL_EVENT_TIME;
    packet.field_0x18 = GLOBAL_EVENT_UNKNOWN;
    packet.field_0x1c = 0;
    packet.field_0x20 = 0;
    packet.field_0x24 = 0;
    packet.field_0x28 = 0;
    packet.field_0x2c = 0;
    packet.field_0x30 = 0;
    packet.field_0x34 = 0;
    packet.field_0x38 = 0;
    packet.field_0x3c = 0;
    packet.field_0x40 = 0;
    packet.field_0x44 = eventData[0];
    packet.field_0x48 = eventData[1];
    packet.field_0x4c = eventData[2];
    packet.field_0x50 = GLOBAL_EVENT_TIME;
    packet.field_0x54 = GLOBAL_EVENT_UNKNOWN;

    // Call component's vtbl[0x58] to process the packet
    typedef void(__thiscall* ProcessPacketFunc)(uint32_t*, EventPacket*, EventPacket*, EventPacket*);
    // The decompiled shows three stack addresses: &uStack_60, &uStack_6c, &stack0xffffff88.
    // This corresponds to &packet.field_0x18 (?), &packet, and &packet.field_0x00?
    // However, for simplicity we pass the packet as the second argument, and dummy for third? 
    // More accurate: The third argument is actually a pointer to a struct starting at uStack_6c (which is the packet itself)
    // The first argument to the call is &uStack_60 (which is packet.field_0x18), second is &uStack_6c (packet), third is stack0xffffff88 (offset something)
    // But based on the stack layout, it seems the call expects three pointers to sub-parts of the packet.
    // We'll model it as a call to ProcessPacket with appropriately defined arguments.
    // For reconstruction, we can treat the packet struct as contiguous and pass three pointers.
    uint32_t* packetStart = (uint32_t*)&packet;
    ((ProcessPacketFunc)(component[0] + 0x58))(component, packetStart + 0x18, packetStart, packetStart + 0x1C); // approximate offsets
}