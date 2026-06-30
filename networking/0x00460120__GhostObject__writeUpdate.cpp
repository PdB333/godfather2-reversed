// FUNC_NAME: GhostObject::writeUpdate
// Address: 0x00460120
// This function builds an update packet for a ghost object. It copies the object's
// state from offset +0x34, checks for any active fields, and writes the packet.

struct GhostObjectState
{
    char data[76];
    // Offsets within the state struct (from Ghidra analysis):
    // +0x54: int field_0x54
    // +0x58: uint field_0x58
    // +0x5C: int* field_0x5C
    // +0x60: int field_0x60
};

// Global helper functions (names guessed by behavior)
extern void* GetNetInterface();                  // FUN_004dafd0
extern void memcpy(void* dst, void* src, int size); // FUN_0044b4e0
extern void WriteUpdateFlags(uint32 flags);      // FUN_004eacb0
extern void* AllocatePacket();                    // FUN_004e0f60
extern void WritePacketBody(void* packet, GhostObjectState* state, uint32 dataLen, int unk); // FUN_004df210

// __thiscall
int* __thiscall GhostObject::writeUpdate(int* outResult, int param_3)
{
    int vtable = *(int*)(this);                 // this->vtable
    uint32 updateMask = 0xFFFFFFFF;
    GhostObjectState state;
    int* packet;
    
    // The in_EAX value is treated as a connection handle (passed in EAX via fastcall convention)
    // For cleanliness we keep the original logic with a hidden parameter.
    int connectionHandle = /* value of EAX at entry */ 0; // placeholder, actual code uses EAX

    if (connectionHandle != 0)
    {
        uint32 tmpSeq = 0;
        uint32 netIf = GetNetInterface();          // returns a NetInterface*
        // Call virtual method at vtable+0x98:
        // void GetPacketSequence(uint32* outSeq, NetInterface* net)
        void (*getSeq)(uint32*, uint32) = (void (*)(uint32*, uint32)) (vtable + 0x98);
        getSeq(&tmpSeq, netIf);
        updateMask = tmpSeq >> 2;
    }

    // Copy object's state at offset +0x34 into local buffer
    memcpy(&state, (void*)((int)this + 0x34), sizeof(state));

    // Call virtual method at vtable+0x58 to get data length
    uint32 dataLen = (*(uint32 (*)())(vtable + 0x58))();

    // Write update flags from param_3
    WriteUpdateFlags(param_3);

    // Check if state fields at offsets 0x54,0x5C,0x58,0x60 are non-zero
    int* field60 = (int*)((int)&state + 0x60);
    int* field5C = (int*)((int)&state + 0x5C);
    uint* field58 = (uint*)((int)&state + 0x58);
    int* field54 = (int*)((int)&state + 0x54);

    if (*field60 != 0 || *field5C != 0 || *field58 != 0 || *field54 != 0)
    {
        packet = (int*)AllocatePacket();
        if (packet != 0 && *(int*)packet != 0) // packet->valid
        {
            // Set packet fields
            *(int*)((int)packet + 0x60) = 2;     // packet type = 2
            *(int*)((int)packet + 0x54) = 0;     // some field = 0
            *(int**)((int)packet + 0x5C) = this; // store this pointer
            *(uint*)((int)packet + 0x58) = updateMask; // store update mask

            WritePacketBody(*(int*)packet, &state, dataLen, 0);
            return outResult;
        }
    }

    *outResult = 0;
    return outResult;
}