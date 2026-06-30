// FUNC_NAME: NetConnection::processIncomingPacket

// Address: 0x00656070
// This function processes an incoming packet on a NetConnection object.
// Checks if the connection is active (offset 0x7c), then validates and handles the packet.

void __thiscall NetConnection::processIncomingPacket(void *this, uint32 param2, uint32 param3)
{
    int *packetObj; // Pointer to a Packet object (vtable-based)
    code *vtableEntry;
    char isValid;
    int currentTick;
    // Local buffers for hash and key material
    uint8 hashBuffer[32];      // Actually 0x20 bytes, at local_174
    uint8 keyBuffer[256];      // at local_100
    // Other locals zeroed
    uint32 dummy1 = 0;
    uint32 dummy2 = 0;
    uint32 dummy3 = 0;
    uint32 dummy4 = 0;
    uint32 dummy5 = 0;
    uint32 dummy6 = 0;
    uint32 dummy7 = 0;
    uint32 dummy8 = 0;
    uint8 dummy9 = 0;
    uint8 dummy10 = 0;
    uint8 dummy11 = 0;
    uint8 dummy12 = 0;
    uint8 dummy13 = 0;
    uint8 dummy14 = 0;

    // Check if connection is active (offset 0x7c)
    if (*(uint8 *)((int)this + 0x7c) == 0) {
        return;
    }

    // Clear local buffers (these are actually not used, but decompiler shows them)
    // In practice they are stack space for later use.

    // Check if network is ready
    if (FUN_00655250() != 0) {
        // Not ready, skip
        goto cleanup;
    }

    // Generate some session-related data
    dummy12 = FUN_0046d790(); // probably random or timestamp
    FUN_0064b9e0(0x20, hashBuffer); // compute hash from ???
    FUN_0064c6b0(keyBuffer); // fill key buffer

    // Allocate a packet object from pool
    packetObj = (int *)FUN_00652a50();
    if (packetObj == nullptr) {
        goto cleanup;
    }

    // Set timestamp on packet via vtable+0x48
    (**(code **)(*packetObj + 0x48))(param3);
    // Increment reference count (offset +8)
    packetObj[2]++;

    // Call some initialization (probably sequence-related)
    FUN_00656210();

    // Copy incoming data from this (the packet payload) into packet object
    // Copy two 64-bit values (16 bytes) at offset 0x100 of packetObj
    *(uint64 *)(packetObj + 0x40) = *(uint64 *)this;          // +0x100
    *(uint64 *)(packetObj + 0x42) = *(uint64 *)((int)this + 8); // +0x108
    // Copy an int at offset 0x10 of this to packetObj+0x44 (offset 0x110)
    packetObj[0x44] = *(int *)((int)this + 0x10);

    // Store current tick/time in multiple fields (offsets 0xA0, 0x90, 0xA8)
    currentTick = iStack_178; // This is a local variable from the stack (provided by caller)
    packetObj[0x28] = currentTick;
    packetObj[0x24] = currentTick;
    packetObj[0x2a] = currentTick;

    // Call some function with unaff_retaddr (maybe return address manipulation)
    FUN_00452df0(unaff_retaddr);

    // Validate the packet using vtable+0x24
    // param2 is passed, hashBuffer is the expected hash
    isValid = (**(code **)(*packetObj + 0x24))(param2, &hashBuffer);

    if (isValid == 0) {
        // Validation failed, drop packet
        FUN_00656600(unaff_retaddr, this);
    } else {
        // Packet valid, prepare for processing
        FUN_00655420(packetObj);
        vtableEntry = *(code **)(*packetObj + 0x14);
        // Set state to 7 (offset 0x1B4)
        packetObj[0x6d] = 7;
        (*vtableEntry)(); // Process the packet
        FUN_00656440(unaff_retaddr);
    }

    // Decrement reference count at offset +8
    int *refCountPtr = packetObj + 2;
    (*refCountPtr)--;
    if (*refCountPtr == 0) {
        // No references, destroy packet via vtable+0x8
        (**(code **)(*packetObj + 8))();
    }

cleanup:
    FUN_00652d00(); // Release some global lock/resource
    return;
}

// Note: iStack_178 and unaff_retaddr are compiler-generated local variables representing a tick value and the return address, respectively.
// The packet object layout (assuming int* base):
// +0x00 : vtable pointer
// +0x08 : reference count (int)
// +0x90 : tick1 (int)
// +0xA0 : tick2 (int)  
// +0xA8 : tick3 (int)
// +0x100: 16 bytes of packet data (two uint64)
// +0x110: additional int data
// +0x1B4: state (int, set to 7 when processing)
// Vtable offsets:
// +0x08: destructor
// +0x14: process
// +0x24: validate (takes param2, hash buffer)
// +0x48: setTimestamp (takes param3)