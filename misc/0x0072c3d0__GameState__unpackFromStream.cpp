// FUNC_NAME: GameState::unpackFromStream
// Function at 0x0072c3d0 – Deserializes game state from a binary stream.
// Reads a series of type-value pairs and writes them into the object at this.
// When skipReading is true, only advances the stream without writing anything.

void __thiscall GameState::unpackFromStream(GameState *this, void *stream, bool skipReading)
{
    bool moreData;
    int typeId;
    int value;
    int dataPtr;
    int stringId;

    // Initialize stream with magic
    StreamBegin(stream, 0x369ac561);

    moreData = StreamAtEnd(stream);
    while (!moreData) {
        StreamNextItem(stream);                 // advance to next item
        typeId = StreamReadType(stream);

        if (!skipReading) {
            switch (typeId) {
                case 1:
                    dataPtr = StreamReadValue(stream);
                    this->field_0x216c = *(int *)(dataPtr + 8);
                    break;
                case 6:
                    dataPtr = StreamReadValue(stream);
                    this->field_8000 = *(int *)(dataPtr + 8);  // offset 0x1F40
                    break;
                case 7:
                    dataPtr = (int)(this + 0x202c);
                    StreamReadValue((void *)dataPtr);  // consumes a value but passes pointer?
                    StreamCopyTo((void *)dataPtr, ???); // FUN_0043ad10 – likely copies data from stream
                    // Note: actual semantics unclear, but this reads a block
                    break;
                case 9:
                    dataPtr = StreamReadValue(stream);
                    this->field_0x1f54 = *(int *)(dataPtr + 8);
                    break;
                case 0xf:
                    dataPtr = (int)(this + 0x2074);
                    StreamReadValue((void *)dataPtr);
                    StreamCopyTo((void *)dataPtr);
                    break;
                case 0x1b:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x1fe8, stringId);
                    break;
                case 0x1c:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x1ff0, stringId);
                    break;
                case 0x1d:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x1fc0, stringId);
                    break;
                case 0x1e:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x1fc8, stringId);
                    break;
                case 0x1f:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x1fd0, stringId);
                    break;
                case 0x21:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x1fe0, stringId);
                    break;
                case 0x22:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x1fd8, stringId);
                    break;
                case 0x2c:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x20d0, stringId);
                    break;
                case 0x2d:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x20d8, stringId);
                    break;
                case 0x2e:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x20e0, stringId);
                    break;
                case 0x2f:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x20e8, stringId);
                    break;
                case 0x30:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x1ff8, stringId);
                    break;
                case 0x31:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x20f0, stringId);
                    break;
                case 0x32:
                    StreamReadValue(stream);
                    stringId = StreamReadString(stream);
                    StreamSetString(this + 0x20f8, stringId);
                    break;
                case 0x33:
                    dataPtr = StreamReadValue(stream);
                    this->field_0x2100 = *(int *)(dataPtr + 8);
                    break;
                case 0x36:
                    dataPtr = StreamReadValue(stream);
                    value = *(int *)(dataPtr + 8);
                    if (value == 1) {
                        this->flags_0x1f5c |= 0x200;
                    } else if (value == 2) {
                        this->flags_0x1f5c |= 0x400;
                    }
                    break;
                case 0x38:
                    dataPtr = StreamReadValue(stream);
                    this->field_0x2670 = *(int *)(dataPtr + 8);
                    break;
                case 0x39:
                    dataPtr = StreamReadValue(stream);
                    this->field_0x266c = *(int *)(dataPtr + 8);
                    break;
                case 0x3a:
                    dataPtr = StreamReadValue(stream);
                    this->field_0x2674 = *(int *)(dataPtr + 8);
                    break;
                default:
                    break;
            }
        }
        StreamEndItem(stream);
        moreData = StreamAtEnd(stream);
    }
}