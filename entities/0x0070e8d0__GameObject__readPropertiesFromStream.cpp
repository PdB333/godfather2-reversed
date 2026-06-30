// FUNC_NAME: GameObject::readPropertiesFromStream
void __thiscall GameObject::readPropertiesFromStream(int this, void* stream)
{
    char isStreamEnd;
    int commandType;
    int readValue;
    char buffer[100];

    readStreamBegin(stream);
    readStreamTag(stream, 0x30754d75); // Magic tag for property stream

    isStreamEnd = isReadStreamEnd(stream);
    do {
        if (isStreamEnd != '\0') {
            return;
        }
        advanceStream(stream);
        commandType = readStreamCommandType(stream);
        switch(commandType) {
            case 0: // Property ID 0: read string into buffer
                readStringProperty(0, buffer); // likely stores at a field related to index 0
                break;
            case 1:
                readStringProperty(1, buffer);
                break;
            case 2:
                readStringProperty(2, buffer);
                break;
            case 3:
                readStringProperty(3, buffer);
                break;
            case 4:
                readStringProperty(4, buffer);
                break;
            case 5:
                readStringProperty(5, buffer);
                break;
            case 6:
                readStringProperty(6, buffer);
                break;
            case 7:
                readStringProperty(7, buffer);
                break;
            case 8:
                readStringProperty(8, buffer);
                break;
            case 9:
                readStringProperty(9, buffer);
                break;
            case 10:
                readStringProperty(10, buffer);
                break;
            case 0xb:
                readStringProperty(11, buffer);
                break;
            case 0xc:
                readStringProperty(12, buffer);
                break;
            case 0xd:
                readStringProperty(13, buffer);
                break;
            case 0xe:
                readStringProperty(14, buffer);
                break;
            case 0xf:
                readStringProperty(15, buffer);
                break;
            case 0x10: // String field at offset 0x3c0
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x3c0, readValue);
                break;
            case 0x11: // Offset 0x3c8
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x3c8, readValue);
                break;
            case 0x12: // Offset 0x3b0
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x3b0, readValue);
                break;
            case 0x13: // Offset 0x3b8
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x3b8, readValue);
                break;
            case 0x14: // Bool at offset 0x242
                readValue = readStreamInt32(stream);
                *(bool*)(this + 0x242) = (*(int*)(readValue + 8) != 0);
                break;
            case 0x15: // Int at offset 0x210
                readValue = readStreamInt32(stream);
                *(int*)(this + 0x210) = *(int*)(readValue + 8);
                break;
            case 0x16: // Offset 0x214
                readValue = readStreamInt32(stream);
                *(int*)(this + 0x214) = *(int*)(readValue + 8);
                break;
            case 0x17: // Offset 0x218
                readValue = readStreamInt32(stream);
                *(int*)(this + 0x218) = *(int*)(readValue + 8);
                break;
            case 0x18: // Offset 0x21c
                readValue = readStreamInt32(stream);
                *(int*)(this + 0x21c) = *(int*)(readValue + 8);
                break;
            case 0x19: // Offset 0x31c
                readValue = readStreamInt32(stream);
                *(int*)(this + 0x31c) = *(int*)(readValue + 8);
                break;
            case 0x1a: // Object field at offset 0x3d0
                advanceStream(stream);
                readValue = readStreamObjectHandle(stream);
                setObjectField(this + 0x3d0, readValue);
                break;
            case 0x1b: // Object field at offset 0x3d8
                advanceStream(stream);
                readValue = readStreamObjectHandle(stream);
                setObjectField(this + 0x3d8, readValue);
                break;
            case 0x1c: // Bool at offset 0x241
                readValue = readStreamInt32(stream);
                *(bool*)(this + 0x241) = (*(int*)(readValue + 8) != 0);
                break;
            case 0x1d: // String at offset 0x380
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x380, readValue);
                break;
            case 0x1e: // Offset 0x388
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x388, readValue);
                break;
            case 0x1f: // Offset 0x390
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x390, readValue);
                break;
            case 0x20: // Offset 0x398
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x398, readValue);
                break;
            case 0x21: // Offset 0x360
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x360, readValue);
                break;
            case 0x22: // Offset 0x368
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x368, readValue);
                break;
            case 0x23: // Offset 0x370
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x370, readValue);
                break;
            case 0x24: // Offset 0x378
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x378, readValue);
                break;
            case 0x25: // Offset 0x340
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x340, readValue);
                break;
            case 0x26: // Offset 0x348
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x348, readValue);
                break;
            case 0x27: // Offset 0x350
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x350, readValue);
                break;
            case 0x28: // Offset 0x358
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x358, readValue);
                break;
            case 0x29: // Offset 0x320 (800 decimal)
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x320, readValue);
                break;
            case 0x2a: // Offset 0x328
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x328, readValue);
                break;
            case 0x2b: // Offset 0x330
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x330, readValue);
                break;
            case 0x2c: // Offset 0x338
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x338, readValue);
                break;
            case 0x2d: // Offset 0x3a8
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x3a8, readValue);
                break;
            case 0x2e: // Offset 0x3a0
                advanceStream(stream);
                readValue = readStreamStringHandle(stream);
                setStringField(this + 0x3a0, readValue);
                break;
            case 0x2f: // Int at offset 0x244
                readValue = readStreamInt32(stream);
                *(int*)(this + 0x244) = *(int*)(readValue + 8);
                break;
            case 0x30: // Offset 0x248
                readValue = readStreamInt32(stream);
                *(int*)(this + 0x248) = *(int*)(readValue + 8);
                break;
            case 0x31: // Offset 0x24c
                readValue = readStreamInt32(stream);
                *(int*)(this + 0x24c) = *(int*)(readValue + 8);
                break;
            case 0x32: // Offset 0x250
                readValue = readStreamInt32(stream);
                *(int*)(this + 0x250) = *(int*)(readValue + 8);
                break;
        }
        advanceStream(stream);
        isStreamEnd = isReadStreamEnd(stream);
    } while( true );
}