// FUNC_NAME: Queue::popAndProcess
void __thiscall Queue::popAndProcess(void* this) {
    // Offset +0x48: m_ppEntries (pointer to array of pointers to entries)
    // Offset +0x50: m_headIndex (int)
    // Offset +0x4c: m_capacity (int)
    // Offset +0x54: m_count (int)

    int* ppEntries = *(int**)((int)this + 0x48);
    int headIndex = *(int*)((int)this + 0x50);
    int capacity = *(int*)((int)this + 0x4c);
    int count = *(int*)((int)this + 0x54);

    // Retrieve the entry at the head of the queue
    void* entry = (void*)ppEntries[headIndex];

    // Advance the head index, wrapping if necessary
    headIndex++;
    if (headIndex >= capacity) {
        headIndex = 0;
    }
    *(int*)((int)this + 0x50) = headIndex;

    // Decrement the count of queued entries
    count--;
    *(int*)((int)this + 0x54) = count;

    // Process the popped entry (likely release or execute)
    FUN_00603210(entry);
    FUN_005e3c00(entry);
}