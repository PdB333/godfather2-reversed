// FUNC_NAME: FixedSizeBuffer::copyToTarget
// This function copies the contents of a FixedSizeBuffer (this) into a pre-allocated target buffer (passed in EAX).
// It returns 1 on success, 0 if the required size (param_2) exceeds the capacity.
// The target buffer structure is initialized with default values and then populated from the source.
// Class layout (offsets from this):
// +0x0: (unknown)
// +0x4: (unknown)  
// +0x8: (unknown)
// +0xA: ushort capacity
// +0xC: uint dataSize (bytes)
// +0x10: byte nullTerminatedFlag
// +0x14: byte data[] (dataSize bytes)
// Target buffer layout (offsets from target pointer in EAX):
// +0x0: uint (set to 0)
// +0x4: uint (set to 0)
// +0x8: byte (set to 1)
// +0x9: byte (set to 0)
// +0xA: ushort capacity (copied from source)
// +0xC: uint dataSize (copied from source)
// +0x10: byte nullTerminatedFlag (copied from source)
// +0x11: byte data[] (copied from source)

int __thiscall FixedSizeBuffer::copyToTarget(int this, uint neededSize) {
    // in_EAX: pointer to target buffer, passed by caller in EAX (non‑standard calling convention)
    // Ghidra's in_EAX is reinterpreted as a local pointer to the destination.
    char* target = (char*)in_EAX;
    
    // Check if source has enough capacity for the requested size
    if (*(unsigned short*)(this + 0xA) <= neededSize) {
        // Initialize target buffer fields
        *(uint*)(target) = 0;                  // +0x0
        *(uint*)(target + 4) = 0;              // +0x4
        *(target + 8) = 1;                     // +0x8
        *(target + 9) = 0;                     // +0x9
        *(unsigned short*)(target + 0xA) = *(unsigned short*)(this + 0xA); // capacity
        *(uint*)(target + 0xC) = *(uint*)(this + 0xC);                     // dataSize
        *(target + 0x10) = *(char*)(this + 0x10);                         // nullTerminatedFlag
        // Copy the actual data
        _memcpy(target + 0x11, (void*)(this + 0x14), *(size_t*)(this + 0xC));
        return 1; // success
    }
    return 0; // failure – neededSize exceeds capacity
}