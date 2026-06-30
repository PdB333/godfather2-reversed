// FUNC_NAME: Entity::readPropertiesFromStream
// Address: 0x006b83a0
// This function reads a binary data stream to initialize the entity's properties.
// It uses an internal streaming/parsing system (likely part of EARS engine serialization).
// Fields at offsets 0x50, 0x58, 0x5c, 0x60, 0x64 are populated from the stream.

void __thiscall Entity::readPropertiesFromStream(int this, void* stream)
{
    char isEnd;
    int value;
    int typeId;

    bindToStream(stream);                     // FUN_0046c710 - initialize stream binding
    setStreamKey(stream, 0x6c8152cb);        // FUN_0043aff0 - maybe a CRC/hash for verification
    isEnd = isStreamEnd();                   // FUN_0043b120 - check for end-of-data flag
    while (isEnd == '\0') {
        readNextElement();                   // FUN_0043b210 - advance to next element
        typeId = getElementType();           // FUN_0043ab70 - obtain element type ID (0-4)
        switch (typeId) {
        case 0:
            readNextElement();               // FUN_0043b210 - read additional data
            value = readElementValue();      // FUN_0043ab90 - read a value (int/float)
            setFloatField(this + 0x50, value); // FUN_004089b0 - store at offset 0x50 (e.g. a float property)
            break;
        case 1:
            value = readNextElement();       // FUN_0043b210 returns pointer to some data
            *(int*)(this + 0x58) = *(int*)(value + 8); // offset 0x58 set from data[8]
            break;
        case 2:
            value = readNextElement();
            *(int*)(this + 0x5c) = *(int*)(value + 8); // offset 0x5c
            break;
        case 3:
            value = readNextElement();
            *(uint*)(this + 0x60) |= *(uint*)(value + 8); // offset 0x60 is a bitmask (OR)
            break;
        case 4:
            value = readNextElement();
            *(int*)(this + 100) = *(int*)(value + 8); // offset 0x64 (decimal 100)
            break;
        }
        finalizeElement();                   // FUN_0043b1a0 - end current element processing
        isEnd = isStreamEnd();               // check again for next iteration
    }
}