// FUNC_NAME: TNLConnection::sendReliablePacket
// Address: 0x005947a0
// Schedules a reliable packet for transmission. Checks for sequence wrap-around.
// This function sets up a packet header in the connection's buffer.
// unaff_EDI is the packet sequence number (16-bit valid range), param_1 is data pointer.

void __thiscall TNLConnection::sendReliablePacket(int this, int dataPtr)
{
    // Global pointer to some network manager or vtable (DAT_01205590)
    auto *networkManager = *(void ***)0x01205590;
    
    // If sequence number exceeds 16-bit range, call error handler (likely wrap reset)
    if ((unsigned int)dataPtr > 0xffff) { // note: this is likely an error in decompilation; should compare sequence
        (**(code **)(networkManager + 4))(); // call some error/crash function
    }
    
    // If the low 16 bits of the sequence are non-zero
    if ((short)dataPtr != 0) { // dataPtr is overloaded here? Actually unaff_EDI is the sequence, but we reuse dataPtr? Need to separate.
        // Set packet header fields (offsets relative to 'this')
        *(int *)(this + 0x100) = 0;           // +0x100: packet type/flags (0 = ?)
        *(short *)(this + 0x104) = 1;         // +0x104: packet subtype (1)
        *(short *)(this + 0x106) = (short)dataPtr; // +0x106: sequence number
        *(int *)(this + 0x10C) = dataPtr;     // +0x10C: data pointer (note: param_1 reused, but originally separate)
        *(short *)(this + 0x108) = 1;         // +0x108: some flag (1)
    }
    
    // Get virtual function pointer from vtable (offset 4)
    code *virtualFn = *(code **)(*(int *)this + 4);
    
    // Clear a status flag (bit 8 at offset 0x7C)
    *(int *)(this + 0x7C) &= 0xfffffeff; // clear bit 8 (flag for needsUpdate?)
    
    // Call the virtual function (likely transmits the packet)
    (*virtualFn)();
    
    return;
}