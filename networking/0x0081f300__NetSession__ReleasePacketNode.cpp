// FUNC_NAME: NetSession::ReleasePacketNode
void __thiscall NetSession::ReleasePacketNode(void) {
    // this+0x114 is a pointer to a packet node (size 0x48)
    int* packetPtr = (int*)((int)this + 0x114);
    if (*packetPtr != 0 && *packetPtr != (int)0x48) {
        // Compute base pointer of the packet node (subtract size 0x48)
        int basePtr = *packetPtr - 0x48;
        // Remove the node from the free list (FUN_004daf90)
        RemoveFromFreeList(packetPtr);
        *packetPtr = 0;
        // Deallocate the node (FUN_0081efa0)
        DeallocatePacketNode(basePtr);
    }
}