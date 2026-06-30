//FUNC_NAME: TNLConnection::allocateReliablePacket
void __thiscall TNLConnection::allocateReliablePacket(void* this, int param2)
{
    // this+8: pointer to a pre-allocated buffer hint (or null)
    void* bufferHint = *(void**)((char*)this + 8);
    if (bufferHint == nullptr) {
        // Use local stack buffer as fallback (all zeros)
        int localBuffer[3] = {0, 0, 0};
        bufferHint = localBuffer;
    }

    // Call virtual allocator at vtable offset 0 (size 0x18, hint)
    // The allocator is a member function pointer stored at this+4
    void* newPacket = (*(void* (__thiscall**)(void*, int, void*))(*((void**)this + 1)))(this, 0x18, bufferHint);
    if (newPacket != nullptr) {
        // Copy data from source (ESI register) and param2
        // ESI points to a source packet structure (two ints)
        // unaff_retaddr is the return address (used as a callback ID)
        *(int*)newPacket = localBuffer[0];               // +0x00: local_4 (zero)
        *(int*)((char*)newPacket + 4) = unaff_retaddr;   // +0x04: return address
        *(int*)((char*)newPacket + 8) = param2;          // +0x08: parameter
        *(int*)((char*)newPacket + 12) = *unaff_ESI;     // +0x0C: source data word 0
        *(int*)((char*)newPacket + 16) = unaff_ESI[1];   // +0x10: source data word 1
        *(char*)((char*)newPacket + 20) = 0;             // +0x14: zero byte
        *(char*)((char*)newPacket + 21) = 0;             // +0x15: zero byte
    }
}