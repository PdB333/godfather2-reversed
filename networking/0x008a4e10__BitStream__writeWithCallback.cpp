// FUNC_NAME: BitStream::writeWithCallback
void __thiscall BitStream::writeWithCallback(void* this, void* stream, uint32_t value1, uint32_t value2, uint32_t value3, uint32_t param6, uint32_t param7)
{
    // Build a callback context on the stack
    struct CallbackContext {
        void (*callback)();   // +0x00: function pointer to type-specific writer
        uint32_t data1;       // +0x04: first data value (value1)
        uint64_t data2;       // +0x08: zero padding or additional data
        uint64_t data3;       // +0x10: packed 64-bit value from value2 (low) and value3 (high)
    };

    CallbackContext ctx;
    ctx.callback = (void (*)())0x008a3ab0; // static writer function for this type
    ctx.data1 = value1;
    ctx.data2 = 0;
    ctx.data3 = ((uint64_t)value3 << 32) | value2;

    // Call virtual function at vtable offset 8 (third virtual method)
    // This likely writes the callback context to the stream
    void (*writeFunc)(void*, void*, uint32_t, uint32_t) = (void (*)(void*, void*, uint32_t, uint32_t))(*((void***)this)[2]);
    writeFunc(stream, &ctx, param6, param7);
}