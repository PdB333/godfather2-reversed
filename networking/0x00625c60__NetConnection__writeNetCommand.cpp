// FUNC_NAME: NetConnection::writeNetCommand
void __thiscall NetConnection::writeNetCommand(void) {
    // Check if command buffer is full (count >= max)
    // +0x10 points to a command buffer header structure
    // +0x20: current count; +0x24: max count
    int *header = *(int **)(this + 0x10);
    if (*(unsigned int *)(header + 0x20) <= *(unsigned int *)(header + 0x24)) {
        // Buffer is full, need to flush or allocate more space
        FUN_00627360(); // likely ensureCommandBufferSpace
    }

    // Get current command write pointer from +0x8
    unsigned int *cmdPtr = *(unsigned int **)(this + 8);
    *cmdPtr = 4; // Command type (e.g., NETCOMMAND_GAMESTATE_UPDATE?)

    // Get a sequence ID or handle from another function
    unsigned int seqId = FUN_00638920(); // e.g., generateSequenceID
    cmdPtr[1] = seqId;

    // Advance the write pointer by 2 unsigned ints (8 bytes)
    *(int *)(this + 8) = (int)(cmdPtr + 2);
}