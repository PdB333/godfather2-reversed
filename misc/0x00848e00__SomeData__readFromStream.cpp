// FUNC_NAME: SomeData::readFromStream
void __thiscall SomeData::readFromStream(Stream* stream) {
    // Initialize stream and verify magic number (0x69db6c5e)
    stream->init(stream);
    stream->readMagic(0x69db6c5e);

    // Loop until end of stream (isEnd returns non-zero when done)
    while (!stream->isEnd()) {
        int type = stream->readType(); // FUN_0043ab70

        if (type == 0) {
            // Read a pointer to a structure and copy value at offset +8 into field at +0x50
            void* ptr = stream->readPointer(); // FUN_0043b210
            this->field_0x50 = *(int*)((char*)ptr + 8);
        }
        else if (type == 1) {
            // Skip an integer, then read a float and assign it to field at +0x54
            stream->readPointer(); // discard
            float value = stream->readFloat(); // FUN_0043ab90
            setFloatAtOffset(this + 0x54, value); // FUN_004089b0
        }
        else if (type == 2) {
            // Read a pointer and copy value at offset +8 into field at +0x5c
            void* ptr = stream->readPointer(); // FUN_0043b210
            this->field_0x5c = *(int*)((char*)ptr + 8);
        }

        stream->advanceToNextChunk(); // FUN_0043b1a0
    }
}