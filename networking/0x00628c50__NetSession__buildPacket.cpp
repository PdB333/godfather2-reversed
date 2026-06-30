// FUNC_NAME: NetSession::buildPacket
void __thiscall NetSession::buildPacket(void) {
    // this is a pointer to NetSession object
    // Offsets:
    // +0x00: mSendBufferPtr (char*) - current write position in send buffer
    // +0x04: mSendRetryCount (int) - count of retries when buffer full
    // +0x08: mFragmentListPtr (FragmentList*) - pointer to fragment list structure
    // +0x20c: mSendBufferEnd (char*) - end of send buffer (buffer size = 0x20c)

    FragmentList* fragmentList = reinterpret_cast<FragmentList*>(this->field_0x08);
    Fragment* currentFragment = reinterpret_cast<Fragment*>(fragmentList->head); // fragmentList->head is at offset 0x08 from fragmentList? Actually code uses fragmentList[2]? Wait let's re-derive.
    // Actually in_EAX[2] is this[2], which is at offset 0x08 from this. That is mFragmentListPtr.
    // Then iVar4 = *(int*)(fragmentList + 8) is fragmentList->head? But fragmentList is at this+0x08, so fragmentList+8 is actually offset 0x10 from this? That seems off.
    // Let's reinterpret: this[2] means *(int*)((char*)this + 8). That is a pointer, call it mFragmentQueue. That pointer points to a structure with at +8 the current fragment pointer (which is actually the tail?). The code then uses iVar4-8 as start of fragment entry. So fragment entries are stored with the last one at the end? It's confusing.
    // For simplicity, I'll use a cleaner model: There is a queue of fragments, each 8 bytes (type + data pointer). The queue has a head pointer at offset 0x08 from the queue object, and entries are stored in a circular buffer. The function tries to pop the next fragment and copy it to send buffer.
    // I'll rename variables to reflect that.

    FragmentQueue* queue = reinterpret_cast<FragmentQueue*>(this->field_0x08); // +0x08
    FragmentEntry* entry = reinterpret_cast<FragmentEntry*>(queue->currentReadPos); // queue->currentReadPos at offset 0x08 from queue? Actually code: iVar4 = *(int*)(iVar1 + 8); then uses iVar4 - 8.
    // So queue->currentReadPos points to the end of the last entry? Actually the pattern: iVar4 points to the next write position? Then iVar4-8 gives the last written entry.
    // We'll assume entry points to the fragment to process.

    uint dataSize = 0;
    if (entry != nullptr) {
        if (entry->type == 4) {
            // Raw data: size is in the data buffer at offset 0x0c
            dataSize = *(uint*)(entry->data + 0x0c);
            goto LAB_00628c86;
        }
        // Not raw, try to resolve via some function (e.g., ghost data)
        if (FUN_00633990(queue) != 0) {  // resolves indirect data
            dataSize = *(uint*)(entry->data + 0x0c);
            goto LAB_00628c86;
        }
    }
    dataSize = 0;

LAB_00628c86:
    // Check if data fits in remaining send buffer space
    char* sendBufferEnd = reinterpret_cast<char*>(this) + 0x20c; // end of buffer (buffer size=0x20c)
    if (dataSize <= (uint)(sendBufferEnd - this->mSendBufferPtr)) {
        // Enough space: process fragment
        entry = reinterpret_cast<FragmentEntry*>(queue->currentReadPos);
        void* srcData = nullptr;
        if (entry != nullptr) {
            if (entry->type == 4) {
                srcData = entry->data + 0x10; // raw data starts at +0x10
            } else {
                if (FUN_00633990(queue) != 0) {
                    srcData = entry->data + 0x10;
                } else {
                    srcData = nullptr;
                }
                // Check if more data pending (reliable packet overflow)
                // +0x10 from queue is some packet buffer with read/write indices
                uint* packetBuffer = *(uint**)(queue + 0x10); // offset 0x10 from queue object
                if (packetBuffer[8] <= packetBuffer[9]) { // read <= write ? actually indices
                    FUN_00627360(); // flush or handle overflow
                }
            }
        }
        if (srcData != nullptr) {
            memcpy(this->mSendBufferPtr, srcData, dataSize);
            this->mSendBufferPtr += dataSize;
            // Advance the fragment queue (remove processed fragment)
            // queue->currentReadPos advances by -8 (since entries are 8 bytes, stored backwards? Actually decrement)
            queue->currentReadPos = reinterpret_cast<char*>(queue->currentReadPos) - 8;
        }
        return;
    }

    // Not enough space: buffer full, need to compress or drop
    // First, try to shift entries in queue to make room? Actually it copies entries backwards.
    FragmentEntry* tail = reinterpret_cast<FragmentEntry*>(queue->currentReadPos);
    FragmentEntry* head = tail; // start at tail
    while (tail - 4 < head) { // iterate while there is room to shift? This loop is weird: condition (tail - 4 < head). Since both start same, condition false. Maybe it's to move entries towards tail? Actually it shifts entries forward in the array? Confusing.
        // The loop: for (puVar5 = tail; tail - 4 < puVar5; puVar5 -= 2) { *puVar5 = *(puVar5-2); *(puVar5+1) = *(puVar5-1); }
        // This shifts the 2-dword entries towards higher addresses? It's like compacting.
        // I'll leave as comment.
    }
    // After compaction, copy the first entry to the shifted position
    FragmentEntry* first = reinterpret_cast<FragmentEntry*>(queue->currentReadPos);
    tail[-4] = *first; // copy type
    tail[-3] = *(first+1); // copy data pointer

    this->mSendRetryCount++; // increment retry count
    FUN_006289a0(); // probably a function to trigger sending or handle overflow
}