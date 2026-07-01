// FUNC_NAME: SerializableObject::readFromStream
// Address: 0x0077e6a0
// Role: Deserializes object fields from a binary stream using a keyed reader.
// The stream contains tagged data blocks; each block has a type (0-12) and associated value.
// Values are stored at offsets 0x50-0x80 of the object.

void __thiscall SerializableObject::readFromStream(int this, void* stream)
{
    char hasMore;
    int type;
    int elementPtr;
    int stringId;
    int bitfield;

    // Initialize stream reader with key 0xd4e81ecc
    streamReaderInit(stream);
    streamReaderSetKey(stream, 0xd4e81ecc);

    hasMore = streamReaderHasMore(stream);
    while (hasMore == 0) {
        // Read next element header
        streamReaderReadNextElement(stream);
        type = streamReaderGetType(stream);
        switch (type) {
        case 0: // String field -> hash and store at +0x50
            streamReaderReadNextElement(stream);
            stringId = streamReaderReadString(stream);
            *(int*)(this + 0x50) = hashStringOrLookup(stringId);
            break;
        case 1: // Integer field -> store at +0x54
            elementPtr = streamReaderReadNextElement(stream);
            *(int*)(this + 0x54) = *(int*)(elementPtr + 8);
            break;
        case 2: // Integer field -> store at +0x58
            elementPtr = streamReaderReadNextElement(stream);
            *(int*)(this + 0x58) = *(int*)(elementPtr + 8);
            break;
        case 3: // String field -> hash via another function and store at +0x5c
            streamReaderReadNextElement(stream);
            stringId = streamReaderReadString(stream);
            *(int*)(this + 0x5c) = readSomeOtherObject(stringId);
            break;
        case 4: // Integer field -> store at +0x60
            elementPtr = streamReaderReadNextElement(stream);
            *(int*)(this + 0x60) = *(int*)(elementPtr + 8);
            break;
        case 5: // Integer field -> store at +0x64 (100 decimal)
            elementPtr = streamReaderReadNextElement(stream);
            *(int*)(this + 100) = *(int*)(elementPtr + 8);
            break;
        case 6: // Integer field -> store at +0x68
            elementPtr = streamReaderReadNextElement(stream);
            *(int*)(this + 0x68) = *(int*)(elementPtr + 8);
            break;
        case 7: // Integer field -> store at +0x6c
            elementPtr = streamReaderReadNextElement(stream);
            *(int*)(this + 0x6c) = *(int*)(elementPtr + 8);
            break;
        case 8: // Integer field -> store at +0x70
            elementPtr = streamReaderReadNextElement(stream);
            *(int*)(this + 0x70) = *(int*)(elementPtr + 8);
            break;
        case 9: // Integer field -> store at +0x74
            elementPtr = streamReaderReadNextElement(stream);
            *(int*)(this + 0x74) = *(int*)(elementPtr + 8);
            break;
        case 10: // Integer field -> store at +0x78
            elementPtr = streamReaderReadNextElement(stream);
            *(int*)(this + 0x78) = *(int*)(elementPtr + 8);
            break;
        case 11: // Integer field -> store at +0x7c
            elementPtr = streamReaderReadNextElement(stream);
            *(int*)(this + 0x7c) = *(int*)(elementPtr + 8);
            break;
        case 12: // Bitfield field -> OR value into +0x80
            elementPtr = streamReaderReadNextElement(stream);
            bitfield = *(int*)(elementPtr + 8);
            *(int*)(this + 0x80) = *(int*)(this + 0x80) | bitfield;
            break;
        }
        // Advance to next element
        streamReaderAdvance(stream);
        hasMore = streamReaderHasMore(stream);
    }
    return;
}