// FUNC_NAME: NetSession::CopyPacketWindow
bool __thiscall NetSession::CopyPacketWindow(uint capacity, void* buffer) // buffer pointer passed in EAX (hidden parameter)
{
    // +0x0A: ushort elementCount (number of valid entries)
    // +0x0C: int elementCount (duplicate count? used for memcpy size)
    // +0x10: array of 32-byte packet window entries

    if (*(unsigned short*)(this + 0x0A) <= capacity) {
        // Initialize header portion of output buffer
        *(uint32_t*)((int)buffer + 0x00) = 0;  // header dword 1
        *(uint32_t*)((int)buffer + 0x04) = 0;  // header dword 2
        *(unsigned char*)((int)buffer + 0x09) = 0; // byte field
        *(unsigned char*)((int)buffer + 0x08) = 1; // byte field set to 1
        *(unsigned short*)((int)buffer + 0x0A) = *(unsigned short*)(this + 0x0A); // copy element count
        *(int*)((int)buffer + 0x0C) = *(int*)(this + 0x0C); // copy second count
        // Copy the array of 32-byte entries
        memcpy((void*)((int)buffer + 0x10), (void*)(this + 0x10), *(int*)(this + 0x0C) << 5);
        return 1;
    }
    return 0;
}