// FUNC_NAME: NetReflectable::unpack
void __thiscall NetReflectable::unpack(int thisPtr, void* stream)
{
    char hasMore;
    int tag;
    unsigned int* vecPtr;

    // Initialize stream and set type hash
    Stream::beginRead(stream);
    Stream::readTypeHash(stream, 0xd31f07cd);  // Hash for this reflectable type

    hasMore = Stream::hasMoreData(stream);
    while (hasMore == '\0') {
        Stream::readNextField(stream);  // advance to next field? (FUN_0043b210)
        tag = Stream::readTag(stream);  // 0 or 1
        if (tag == 0) {
            Stream::readNextField(stream);
            // Read a string (probably name or ID) at +0x80
            *(uint*)Stream::readString(stream) = *(uint*)(thisPtr + 0x80);
        }
        else if (tag == 1) {
            Stream::readNextField(stream);
            vecPtr = (unsigned int*)Stream::readVector4(stream);  // returns pointer to 4 uint components
            // Store 4-component vector at offset 0x88 (probably quaternion or position)
            *(unsigned int*)(thisPtr + 0x88) = vecPtr[0];
            *(unsigned int*)(thisPtr + 0x8c) = vecPtr[1];
            *(unsigned int*)(thisPtr + 0x90) = vecPtr[2];
            *(unsigned int*)(thisPtr + 0x94) = vecPtr[3];
        }
        Stream::endField(stream);  // (FUN_0043b1a0)
        hasMore = Stream::hasMoreData(stream);
    }
    return;
}