// FUNC_NAME: NetString::writeToStream
struct StreamContext {
    void* stream;      // +0x00
    void (*write)(void*, void*, int, void*); // +0x04
    void* userData;    // +0x08
};

struct NetString {
    int unknown[3];    // +0x00 – +0x08
    int size;          // +0x0c
    char* data;        // +0x10
};

void __thiscall NetString::writeToStream(StreamContext* ctx)
{
    // ctx is passed in ESI; this (NetString*) is in EAX
    if (this != 0 && this->data != 0) {
        int writeLen = this->size + 1; // include null terminator
        // Write length (4 bytes)
        ctx->write(ctx->stream, &writeLen, 4, ctx->userData);
        // Write data (writeLen bytes)
        ctx->write(ctx->stream, this->data, writeLen, ctx->userData);
    } else {
        int writeLen = 0;
        ctx->write(ctx->stream, &writeLen, 4, ctx->userData);
    }
}