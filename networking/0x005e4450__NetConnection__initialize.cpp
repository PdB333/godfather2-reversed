// FUNC_NAME: NetConnection::initialize
// Function address: 0x005e4450
// Role: Initializes a NetConnection object, setting up packet window buffers and event history.
// This is a member function called during connection setup.
// Size: 0x6000 for per-slot data (32 slots * 0x300),
// 0x200 entries of 12 bytes for sequence-to-slot map,
// 64 entries of 0x3a0 bytes for packet event log.

#define INVALID_SEQUENCE 0xFFFFFFFF  // placeholder for DAT_00e2b1a4

int __fastcall NetConnection::initialize(void* allocator)
{
    if (allocator == 0) {
        return 0;
    }

    // Store allocator object at offset +0x6010
    this->allocator = allocator;

    // Call the third virtual function in allocator to allocate memory
    // This vtable function returns a pointer to a large buffer of size 0xe800
    this->eventLog = (EventLogEntry*)(*(int (__thiscall**)(void*, int, void*))(*((int*)allocator) + 8))(allocator, 0xe800, &returnAddress);

    // Clear the packet window data (32 slots * 0x300 = 0x6000 bytes)
    memset((void*)(this + 0x10), 0, 0x6000);

    // Initialize sequence-to-slot mapping array (0x200 entries of 12 bytes each)
    // Each entry starts with a uint32 containing its own index
    // Actual structure size is 12 bytes, but only first field is set here
    uint* slotMapEntry = (uint*)(this + 0x24);
    for (uint i = 0; i < 0x200; i++) {
        *slotMapEntry = i;
        slotMapEntry += 3; // skip 12 bytes (3 * 4)
    }

    if (this->eventLog == 0) {
        return 0;
    }

    // Zero out the event log buffer
    memset(this->eventLog, 0, 0xe800);

    // Initialize 64 event log entries of size 0x3a0, each containing 8 uint32 fields
    // Fields are at offsets 0x54, 0xC8 (200), 0x13C, 0x1B0, 0x224, 0x298, 0x30C, 0x380 (relative to entry start)
    for (uint entryIdx = 0; entryIdx < 64; entryIdx++) {
        uint entryBase = entryIdx * 0x3a0;
        *(uint*)(this->eventLog + entryBase + 0x54) = INVALID_SEQUENCE;
        *(uint*)(this->eventLog + entryBase + 0xC8) = INVALID_SEQUENCE;
        *(uint*)(this->eventLog + entryBase + 0x13C) = INVALID_SEQUENCE;
        *(uint*)(this->eventLog + entryBase + 0x1B0) = INVALID_SEQUENCE;
        *(uint*)(this->eventLog + entryBase + 0x224) = INVALID_SEQUENCE;
        *(uint*)(this->eventLog + entryBase + 0x298) = INVALID_SEQUENCE;
        *(uint*)(this->eventLog + entryBase + 0x30C) = INVALID_SEQUENCE;
        *(uint*)(this->eventLog + entryBase + 0x380) = INVALID_SEQUENCE;
    }

    return 1;
}