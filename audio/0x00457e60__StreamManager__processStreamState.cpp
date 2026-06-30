// FUNC_NAME: StreamManager::processStreamState
void StreamManager::processStreamState(int* thisPtr)
{
    int* streamState = *(int**)(thisPtr + 0x14);  // +0x14: pointer to stream state object
    if ((streamState != 0) && (FUN_00ab4db0(&DAT_00e2e4c8) != 0)) { // global pending operation?
        if ((*(int*)(streamState + 0x170) != 2) && (getAvailableBytes() == 0x20)) {
            if ((*(char*)(streamState + 0x1e0) == 0x03) && // stream type = 3?
                (int* dataStart = *(int**)(streamState + 0x1ec), dataStart != 0)) {
                uint dataSize = *(int*)(streamState + 0x1e8) - (int)dataStart; // computed data size
                if (dataSize != 0) {
                    if ((*(int*)(streamState + 0x1d4) != 0) || (dataSize <= *(uint*)(streamState + 0x1d0))) {
                        goto LAB_00457f95; // buffer already allocated or sufficient
                    }
                    if (*(int*)(streamState + 0x1cc) != 0) {
                        freeBuffer(*(int*)(streamState + 0x1cc)); // free old buffer
                    }
                    int* newBuffer = allocateBuffer(dataSize, 0x10, 0);
                    *(int**)(streamState + 0x1cc) = newBuffer;
                    *(uint*)(streamState + 0x1d0) = dataSize;
                    *(int*)(streamState + 0x1d4) = 0;
                    if (newBuffer != 0) {
LAB_00457f95:
                        *(uint*)(streamState + 0x1d8) = dataSize;
                        *(int*)(streamState + 0x1dc) = 0;
                        *(int*)(streamState + 0x170) = 3; // state = reading
                        asyncRead(*(int*)(streamState + 0x1c8),   // source handle
                                  *(int*)(streamState + 0x1cc),  // buffer
                                  (int)dataStart, var4_00,        // offset? Possibly parameter order differs
                                  dataSize,
                                  0,
                                  onReadComplete,                 // callback
                                  (int)streamState,
                                  0);
                        processAsyncIO();
                        return;
                    }
                    // allocation failed
                    *(uint*)(streamState + 0x1d0) = 0;
                    *(int*)(streamState + 0x1d4) = 0;
                }
                // no data or allocation failure -> set error state
                *(uint*)(streamState + 0x1d8) = 0;
                *(int*)(streamState + 0x1dc) = 0;
                *(int*)(streamState + 0x170) = 4; // error state
                handleStreamError();
            }
        }
        // always cancel/wait for pending async operation
        asyncCancel(*(int*)(streamState + 0x1c8), onError, (int)streamState, 0);
        processAsyncIO();
    }
    return;
}