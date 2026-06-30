// FUNC_NAME: NetConnection::NetConnection
// 0x007268d0 - Constructor for a network connection object (TNL-based), initializes vtable pointers, magic sentinels, and a large packet buffer from a global template.

// Note: Base constructor at 0x46c590 is NetObject::NetObject or similar.
// Global DAT_0120e93c is a 0x8000-byte template for a reliable packet buffer.
// Magic constants are likely sentinels for debugging (0xFE16702F = "FESP"?).

undefined4* __thiscall NetConnection::NetConnection(NetConnection* this, void* parentObject)
{
    // Call base class constructor (NetObject or similar)
    NetObject::NetObject(parentObject);

    // Set vtable pointers (multiple inheritance / subobjects)
    this->vtable_purecall = &PTR___purecall_00d623c8;   // +0x50 (offset 0x14*4)
    this->primaryVtable = &PTR_FUN_00d623f4;            // +0x00
    this->subVtable1 = &PTR_LAB_00d623e4;               // +0x3C (offset 0x0F*4)
    this->subVtable2 = &PTR_LAB_00d623e0;               // +0x48 (offset 0x12*4)
    this->subVtable3 = &PTR_LAB_00d623d4;               // +0x50 (offset 0x14*4) - overwritten by previous line? Actually two at same offset: last one stays. That might be intentional.

    // Initialize connection state fields
    this->reliableQueue = 0;                             // +0x54 (0x15*4)
    *(short*)&this->reliableQueueFlags = 0;              // +0x58 (0x16*4) partial write
    *(short*)((int)this + 0x5A) = 0;                    // +0x5A
    this->pendingAck = 0;                                // +0x5C (0x17*4)
    *(short*)&this->pendingAckFlags = 0;                 // +0x60 (0x18*4)
    *(short*)((int)this + 0x62) = 0;                    // +0x62
    this->sequenceLocal = 0;                             // +0x64 (0x19*4)
    *(short*)&this->sequenceLocalFlags = 0;              // +0x68 (0x1A*4)
    *(short*)((int)this + 0x6A) = 0;                    // +0x6A
    this->sequenceRemote = 0;                            // +0x6C (0x1B*4)
    *(short*)&this->sequenceRemoteFlags = 0;             // +0x70 (0x1C*4)
    *(short*)((int)this + 0x72) = 0;                    // +0x72

    // Set magic sentinel values (used for buffer overflow detection or state markers)
    this->magic1 = DAT_00e448f0;                        // +0x74 (0x1D*4) - likely from data section
    int uVar1 = DAT_00d5ccf8;                           // some constant
    this->magic2 = DAT_00d5c454;                        // +0x7C (0x1F*4)
    this->magic3 = uVar1;                               // +0x78 (0x1E*4)
    this->magic4 = uVar1;                               // +0x84 (0x21*4)
    this->magic5 = uVar1;                               // +0x88 (0x22*4)
    this->magic6 = DAT_00e445ac;                        // +0x80 (0x20*4)
    *(short*)&this->magicFlags = 1;                     // +0x8C (0x23*4) partial write

    // Initialize packet window tracking (32-slot window)
    this->windowSize = 0;                               // +0x94 (0x25*4)
    this->windowStart = 0;                              // +0x98 (0x26*4)
    this->windowNext = 0;                               // +0x9C (0x27*4)

    // Historical sentinel pattern (seems to be dummy data or debug markers)
    this->sentinelPattern[0] = 0xfe16702f;              // +0xA0 (0x28*4)
    this->sentinelPattern[1] = 0xbadbadba;              // +0xA4 (0x29*4)
    this->sentinelPattern[2] = 0xbeefbeef;              // +0xA8 (0x2A*4)
    this->sentinelPattern[3] = 0xeac15a55;              // +0xAC (0x2B*4)
    this->sentinelPattern[4] = 0x91100911;              // +0xB0 (0x2C*4)

    *(short*)&this->state = 0;                          // +0xB4 (0x2D*4) partial write
    this->connectionFlags = 0;                          // +0xB8 (0x2E*4)

    // More state fields zeroed (likely counters, pointers, timers)
    this->field0xE4 = 0;                                // +0xE4 (0x39*4)
    this->field0xE8 = 0;                                // +0xE8 (0x3A*4)
    this->field0xEC = 0;                                // +0xEC (0x3B*4)
    this->field0xF0 = 0;                                // +0xF0 (0x3C*4)
    this->field0xBC = 0;                                // +0xBC (0x2F*4)
    this->field0xC0 = 0;                                // +0xC0 (0x30*4)
    this->field0xF4 = 0;                                // +0xF4 (0x3D*4)
    this->field0xF8 = 0;                                // +0xF8 (0x3E*4)
    this->field0xFC = 0;                                // +0xFC (0x3F*4)
    this->field0x100 = 0;                               // +0x100 (0x40*4)
    this->field0xC4 = 0;                                // +0xC4 (0x31*4)
    this->field0xC8 = 0;                                // +0xC8 (0x32*4)
    this->field0xCC = 0;                                // +0xCC (0x33*4)
    this->field0xD0 = 0;                                // +0xD0 (0x34*4)
    this->field0xD4 = 0;                                // +0xD4 (0x35*4)
    this->field0xD8 = 0;                                // +0xD8 (0x36*4)
    this->field0xDC = 0;                                // +0xDC (0x37*4)
    this->field0xE0 = 0;                                // +0xE0 (0x38*4)
    this->field0x104 = uVar1;                           // +0x104 (0x41*4) - default value from before

    // Packet buffer initialization
    this->packetBufferWritePos = 0;                     // +0x108 (0x42*4)
    this->packetBufferReadPos = 0;                      // +0x10C (0x43*4)
    this->packetBufferSize = 0;                         // +0x110 (0x44*4)
    *(uint8_t*)&this->packetBufferFlags = 0;            // +0x114 (0x45*4) partial write (byte)
    *(uint8_t*)((int)this + 0x115) = 0;                // +0x115
    *(uint8_t*)((int)this + 0x116) = 0;                // +0x116

    // More pointers/timers
    this->field0x118 = 0;                               // +0x118 (0x46*4)
    this->field0x11C = 0;                               // +0x11C (0x47*4)
    this->field0x128 = 0;                               // +0x128 (0x4A*4)
    this->field0x124 = 0;                               // +0x124 (0x49*4)
    this->field0x120 = 0;                               // +0x120 (0x48*4)
    this->field0x12C = uVar1;                           // +0x12C (0x4B*4) - default value from DAT_00d5780c
    this->field0x138 = 0;                               // +0x138 (0x4E*4)
    this->field0x134 = 0;                               // +0x134 (0x4D*4)
    this->field0x130 = 0;                               // +0x130 (0x4C*4)

    // Copy a 0x8000-byte template from global into the packet history buffer (offset +0x3C)
    if (DAT_0120e93c != 0) {
        memcpy((void*)(this + 0x0F), (void*)DAT_0120e93c, 0x8000); // +0x3C, size 0x8000
    }

    return this;
}