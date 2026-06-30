// FUNC_NAME: StreamManager::beginAsyncLoad
// Address: 0x005e1ee0
// Role: Initiates an asynchronous stream load for a resource in EA EARS streaming system.

struct StreamRequest {
    uint32_t field0;  // +0x00
    uint32_t field4;  // +0x04
    uint32_t field8;  // +0x08
    uint8_t  fieldC;  // +0x0C
};

bool StreamManager::beginAsyncLoad() {
    StreamRequest request;
    request.field0 = 1;
    request.field4 = 0;
    request.field8 = 0;
    request.fieldC = 0;

    char result = initStreamRequest(&request); // returns non-zero on success

    for (int i = 0; i < 5; i++) {
        yieldToPendingOps(); // yield a few frames to let streaming progress
    }

    // Clear stream state and free associated buffer
    *(uint32_t*)(this + 0x173C) = 0;                  // +0x173C: stream active flag
    freeStreamBuffer(*(uint32_t*)(this + 0x1738));    // +0x1738: stream buffer pointer
    *(uint32_t*)(this + 0x1738) = 0;                  // clear buffer pointer
    *(uint32_t*)(this + 0x1740) = 0;                  // +0x1740: stream size/handle

    return result != 0;
}