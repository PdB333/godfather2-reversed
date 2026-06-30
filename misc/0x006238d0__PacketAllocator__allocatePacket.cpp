// FUNC_NAME: PacketAllocator::allocatePacket
void __thiscall PacketAllocator::allocatePacket(int thisPtr, uint param_2)
{
    // Source pointer from member at +0x08 (possibly a free-list or template buffer)
    uint *srcPtr = *(uint **)(thisPtr + 8);
    uint local_4[3] = {0}; // dummy buffer if srcPtr is null

    if (srcPtr == 0) {
        srcPtr = local_4; // use local zeros as source
    }

    // Call allocator function pointer at +0x04 (e.g., from vtable)
    uint *newPacket = (uint *)((**(code **)(**(int **)(thisPtr + 4)))(0x28, srcPtr));
    // If allocation succeeded, populate the packet structure (size 0x28 = 40 bytes)
    if (newPacket != 0) {
        newPacket[0] = local_4[0];          // +0x00: sequence or length field
        newPacket[1] = (uint)__builtin_return_address(0); // +0x04: return address (continuation?)
        newPacket[2] = param_2;             // +0x08: parameter (destination flag?)
        *(uint64 *)(newPacket + 3) = *(uint64 *)esi;            // +0x0C: copy 8 bytes from ESI
        *(uint64 *)(newPacket + 5) = *(uint64 *)(esi + 8);      // +0x14: copy next 8 bytes
        *(uint64 *)(newPacket + 7) = *(uint64 *)(esi + 16);     // +0x1C: copy third 8 bytes
        *(byte *)(newPacket + 9) = 0;       // +0x24: byte flag (clear)
        *(byte *)((int)newPacket + 0x25) = 0; // +0x25: another byte flag
    }
    // Note: ESI is assumed to hold a pointer to the outgoing packet data.
}