// FUNC_NAME: EntityDeserializer::deserializeDataFromStream
// Address: 0x008fc310
// Role: Reads entity data fields from a serialization stream. Parses type/value pairs.

void __thiscall EntityDeserializer::deserializeDataFromStream(int thisPtr, undefined4 stream)
{
    char hasMoreData;
    undefined4 readValue;
    int readInt;
    undefined4* readVec4;

    // Initialize stream and set expected class marker
    Stream::beginRead(stream);                                         // +0x0846c710
    Stream::writeUint32(stream, 0xd1460da2);                           // Magic number / class ID? (0xd1460da2 is likely a tag)

    hasMoreData = Stream::hasMoreData(stream);                         // +0x0843b120
    while (hasMoreData == 0) {
        readInt = Stream::readUint32(stream);                          // +0x0843b210 (peek next token? used in switch but also for data)
        switch (Stream::readEnum8(stream)) {                           // +0x0843ab70 - Reads a type discriminator
        case 0:
            // Type 0: read an integer reference and store value at +0x50
            readInt = Stream::readUint32(stream);                      // +0x0843b210
            *(int*)(thisPtr + 0x50) = *(int*)(readInt + 8);           // Likely dereference a handle or pool pointer
            break;

        case 1:
            // Type 1: similar to type 0, stores at +0x54
            readInt = Stream::readUint32(stream);
            *(int*)(thisPtr + 0x54) = *(int*)(readInt + 8);
            break;

        case 2:
            // Type 2: read 4 consecutive floats (quaternion/axis-angle?) into +0x58..+0x64
            Stream::readUint32(stream);                                // read skip or advance
            readVec4 = (undefined4*)Stream::readVec4(stream);         // +0x0843abc0
            *(int*)(thisPtr + 0x58) = *readVec4;                      // x / element0
            *(int*)(thisPtr + 0x5c) = readVec4[1];                    // y / element1
            *(int*)(thisPtr + 0x60) = readVec4[2];                    // z / element2
            *(int*)(thisPtr + 0x64) = readVec4[3];                    // w / element3
            break;

        case 3:
            // Type 3: read a string/resource reference into +0x68
            Stream::readUint32(stream);                                // skip
            readValue = Stream::readResourceId(stream);               // +0x0843ab90
            String::assign(thisPtr + 0x68, readValue);                // +0x084089b0 (copy string or store handle)
            break;
        }
        Stream::advanceStream(stream);                                 // +0x0843b1a0
        hasMoreData = Stream::hasMoreData(stream);
    }

    // Note: no explicit stream close; stream is presumably owned by caller
}