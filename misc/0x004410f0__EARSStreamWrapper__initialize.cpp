// FUNC_NAME: EARSStreamWrapper::initialize
int EARSStreamWrapper::initialize(SomeStream *stream, int flags) {
    // Call vtable function at offset 8 (likely addRef or some init)
    stream->vtable->someFunction(stream);

    int handle;
    if (flags == 0) {
        handle = 0;
    } else {
        handle = duplicateStreamHandle(flags, stream); // FUN_004265d0
    }

    setStreamHandle(stream, handle); // FUN_00441630
    this->streamPtr = stream; // +0x10

    // Second call to vtable offset 8 (perhaps release or get?)
    stream->vtable->someFunction();

    if (flags != 0) {
        handle = duplicateStreamHandle(flags, this->streamPtr); // +0x10
        this->streamHandle = handle; // +0x14
        stream->vtable->addRef(flags, 0); // offset 4
        stream->vtable->someOtherFunc(); // offset 0xc
        return (int)this;
    }

    this->streamHandle = 0; // +0x14
    stream->vtable->someOtherFunc(); // offset 0xc
    return (int)this;
}