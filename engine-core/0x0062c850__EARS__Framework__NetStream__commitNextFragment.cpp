// FUNC_NAME: EARS::Framework::NetStream::commitNextFragment
class NetStream {
    // +0x00: vtable
    // +0x04: unknown
    // +0x08: mWritePtr (int*)
    // +0x0C: mCurrentElement (int*)
    // +0x10: mBufferContext (pointer to internal buffer descriptor)
};

int __thiscall NetStream::commitNextFragment(int this)
{
    int* currentElement = *(int**)(this + 0xC);
    int* endPtr = *(int**)(this + 0x8);
    int size = 0;
    int stepSize = 8;

    // First: try to determine size from current element
    if ((currentElement < endPtr) && (currentElement != nullptr)) {
        if (*currentElement == 4) {
            // Element type 4: inline data, size is stored in offset +4
            size = *(currentElement + 1) + 0x10;   // +0x10 for metadata
        } else {
            // Other types: use virtual function to get data size
            int ret = advanceElement(this); // FUN_00633990
            if (ret != 0) {
                size = *(currentElement + 1) + 0x10;
            } else {
                size = 0;
            }
            // Check if buffer is full; if so, flush
            int* bufCtx = *(int**)(this + 0x10);
            if (*(unsigned int*)(bufCtx + 0x20) <= *(unsigned int*)(bufCtx + 0x24)) {
                flushBuffer(); // FUN_00627360
            }
        }
        if (size == 0) goto logError;
    } else {
        logError:
        logString(PTR_s_string_00e2a8ac); // FUN_00627ac0
    }

    // Second: try to advance by 8 bytes to next potential element
    int* nextElement = currentElement + 2; // 8 bytes forward
    if ((nextElement < endPtr) && (nextElement != nullptr)) {
        if (*nextElement == 4) {
            size = *(currentElement + 3) + 0x10; // offset 12 from currentElement
        } else {
            int ret2 = advanceElement(this);
            if (ret2 != 0) {
                size = *(currentElement + 3) + 0x10;
            } else {
                size = 0;
            }
            int* bufCtx = *(int**)(this + 0x10);
            if (*(unsigned int*)(bufCtx + 0x20) <= *(unsigned int*)(bufCtx + 0x24)) {
                flushBuffer();
            }
        }
        if (size != 0) goto afterLog;
    }
    stepSize = 2; // fallback: smaller step for different element size
    logString(PTR_s_string_00e2a8ac);

afterLog:
    // Zero memory between write pointer and target position
    int* writePtr = *(int**)(this + 0x8);
    int* target = currentElement + 4; // +0x10 from currentElement
    while ((unsigned int)writePtr < (unsigned int)target) {
        *(int*)writePtr = 0;
        writePtr = (int*)((char*)writePtr + stepSize);
    }

    // Write fragment marker (3) and set next word to 0
    writePtr = target;
    *(int**)(this + 0x8) = writePtr;
    *writePtr = 3;
    *(writePtr + 1) = 0;
    *(int*)(this + 0x8) = (int)writePtr + stepSize;

    // Schedule completion callback (function at 0x0062c610)
    scheduleCompletion(this, (void*)0x0062c610, 3); // FUN_00625d70
    return 1;
}