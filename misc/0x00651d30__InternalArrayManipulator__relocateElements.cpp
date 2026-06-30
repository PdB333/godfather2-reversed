// FUNC_NAME: InternalArrayManipulator::relocateElements

void* relocateElements(void* dest, void* src, int destCount, int srcCount, void* pool) {
    int capacity = getPoolCapacity(); // FUN_00651610

    if (destCount <= srcCount && destCount <= capacity) {
        // Use temporary buffer to shift elements left (close the gap)
        TempBuffer* buf = *(TempBuffer**)((int)pool + 0x14);
        buf->end = buf->start;                 // reset temporary buffer
        resetTemporaryBufferCallback();        // FUN_00651c20
        if (local_14 != 0) {
            freeMem(local_14);                 // FUN_009c8eb0
        }

        int moveCount = ((int)src - (int)in_EAX) >> 2;       // elements from in_EAX to src
        memmove_s(dest, moveCount * 4, in_EAX, moveCount * 4);

        void* bufStart = buf->start;
        int bufCount = (buf->end - (int)bufStart) >> 2;       // elements in temp buffer (now 0)
        src = (void*)((int)src - bufCount * 4);
        if (bufCount > 0) {
            memmove_s(src, bufCount * 4, bufStart, bufCount * 4);
        }
        return src;
    }
    else if (srcCount <= capacity) {
        // Use temporary buffer to shift elements right (make room)
        TempBuffer* buf = *(TempBuffer**)((int)pool + 0x14);
        buf->end = buf->start;                 // reset temporary buffer
        resetTemporaryBufferCallback();        // FUN_00651c20
        if (local_14 != 0) {
            freeMem(local_14);                 // FUN_009c8eb0
        }

        int moveCount = ((int)in_EAX - (int)dest) >> 2;       // elements from dest to in_EAX
        memmove_s((void*)((int)src + moveCount * -4), moveCount * 4, dest, moveCount * 4);

        void* bufStart = buf->start;
        int bufCount = (buf->end - (int)bufStart) >> 2;       // elements in temp buffer (now 0)
        int bufBytes = bufCount * 4;
        if (bufCount > 0) {
            memmove_s(dest, bufBytes, bufStart, bufBytes);
        }
        return (void*)((int)dest + bufBytes);
    }
    else {
        // Direct shift without temporary buffer (no overlap guard)
        if (dest != in_EAX && in_EAX != src) {
            directElementShift(dest, src);     // FUN_00652420
        }
        return (void*)((int)dest + srcCount * 4);
    }
}