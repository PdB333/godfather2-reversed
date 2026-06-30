// FUNC_NAME: Entity::ReadFromStream
void __thiscall Entity::ReadFromStream(uint streamHandle)
{
    // Initialize stream with class identifier hash (likely for serialization versioning)
    beginReadStream(streamHandle, 0x83c382cf);

    // Loop while more fields remain in the stream
    while (!isStreamEnd()) {
        // Each field begins with a type identifier (0=float, 1=int, 2=substructure)
        int fieldType = readFieldType();

        if (fieldType == 0) {
            // Read a float from the next field (offset +0x8 is the value after header)
            void* fieldBuffer = readNextField(); // returns pointer to field data
            float value = *(float*)((int)fieldBuffer + 8);

            // Store at +0x10, clamp to >=0
            this->field_0x10 = value;
            if (value < 0.0f) {
                this->field_0x10 = 0.0f;
            }
        }
        else if (fieldType == 1) {
            // Read an int (or possibly another float) at +0x8 into +0x69c
            void* fieldBuffer = readNextField();
            this->field_0x69c = *(int*)((int)fieldBuffer + 8);
        }
        else if (fieldType == 2) {
            // Read a substructure directly into +0x67c, then process it
            void* dest = (void*)((int)this + 0x67c);
            readNextFieldInto(dest);
            processSubStructure(dest); // e.g., unpack or transform
        }

        // Advance to next field marker in the stream
        advanceStream();
    }
}