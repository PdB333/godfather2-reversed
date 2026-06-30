// FUNC_NAME: SerializableArray::serializeToBuffer

// Reconstructed from 0x004adc20 - Serializes an array of objects into a memory buffer.
// The object's layout (offsets relative to 'this' in EDI):
//   +0x04: Pointer to array of pointers to ISerializable objects
//   +0x08: Count of objects in the array

class ISerializable {
public:
    // vtable+0x04 - Returns the serialized size of the object
    virtual int getSerializedSize() = 0;

    // vtable+0x08 - Writes object data to the buffer.
    //   param1: current write offset (as integer address)
    //   param2: pointer to base buffer pointer (allows function to read base)
    //   returns: value to be stored in the header array (likely ID or size)
    virtual int writeToBuffer(int currentOffset, int* baseBuffer) = 0;
};

class SerializableArray {
public:
    // Returns the original buffer pointer after serialization.
    int serializeToBuffer(int* buffer);

private:
    // Helper called at start (FUN_004adbc0)
    void resetSerialization();

    // Fields (from EDI offsets)
    int field_0;                // +0x00 (unknown)
    ISerializable** items;      // +0x04
    int itemCount;              // +0x08
    // Additional fields might follow
};

void SerializableArray::resetSerialization() {
    // Implementation unknown, likely resets some internal state
}

int SerializableArray::serializeToBuffer(int* buffer) {
    // Layout: buffer[0..itemCount-1] stores return values from writeToBuffer,
    // then actual serialized data begins at buffer + itemCount.
    int* currentWritePos = buffer + itemCount;  // iVar4 = param_1 + count*4

    resetSerialization();

    for (int i = 0; i < itemCount; i++) {
        ISerializable* obj = items[i];

        // Call writeToBuffer at current position, passing base pointer
        int headerValue = obj->writeToBuffer((int)currentWritePos, &buffer);
        buffer[i] = headerValue;

        // Get size of this element's serialized data
        int objSize = obj->getSerializedSize();

        // Advance write position: align size to 4 bytes, then add 4 bytes
        // This likely accounts for a 4-byte header written by writeToBuffer
        int alignedSize = ((int)currentWritePos + objSize) & ~3;  // round down to multiple of 4
        currentWritePos = (int*)(alignedSize + 4);
    }

    return (int)buffer;  // original base pointer
}