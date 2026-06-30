// FUNC_NAME: WriteCountedBuffer
struct CountedBuffer {
    int field_0x00;          // +0x00
    int field_0x04;          // +0x04
    int field_0x08;          // +0x08
    int size;                // +0x0C
    void* data;              // +0x10
};

struct StreamContext {
    void* context;           // +0x00 (first argument to write func)
    void (*write)(void*, const void*, int, void*); // +0x04 function pointer
    void* userData;          // +0x08 (fourth argument to write func)
};

void WriteCountedBuffer(void* thisObj, StreamContext* stream) {
    CountedBuffer* obj = (CountedBuffer*)thisObj;
    int dataSize;

    if (obj != nullptr && obj->data != nullptr) {
        // Size prefix
        dataSize = obj->size + 1; // +1 likely for null terminator or count
        stream->write(stream->context, &dataSize, 4, stream->userData);
        // Actual data
        stream->write(stream->context, obj->data, obj->size, stream->userData);
    } else {
        dataSize = 0;
        stream->write(stream->context, &dataSize, 4, stream->userData);
    }
}