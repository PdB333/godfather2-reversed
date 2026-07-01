// FUNC_NAME: ActionData::readFromStream

void __thiscall ActionData::readFromStream(ActionData* this, StreamHandle stream)
{
    float floatVal;
    char isEnd;
    int opcode;
    int stringIndex;
    void* blockData;

    // Initialize stream and expect a specific type identifier (possibly CRC for ActionData)
    StreamOpen(stream);
    StreamSetTypeId(stream, 0x726dbfc6);

    isEnd = StreamIsEnd(stream);
    while (!isEnd) {
        StreamNextBlock(stream);                // Advance to next command block
        opcode = StreamReadOpcode(stream);
        switch (opcode) {
        case 0:                                 // Set first string (e.g., actionName or target)
            StreamNextBlock(stream);
            stringIndex = StreamReadInt32(stream);
            setStringFromTable(&this->field_0x50, stringIndex); // FUN_004089b0 sets string at offset +0x50
            break;
        case 1:                                 // Execute/play action
            if (this->field_0x64 != 0) {        // Check if action is active
                if (this->field_0x60 != 0) {
                    // Call the action callback function stored at +0x6c with the object at +0x60
                    (*(this->field_0x6c))(this->field_0x60);
                }
                this->field_0x60 = 0;           // Clear callback object
                this->field_0x68 = 0;           // Clear additional data
                this->field_0x64 = 0;           // Mark as inactive
            }
            StreamNextBlock(stream);
            stringIndex = StreamReadInt32(stream);
            playSoundOrAnimation(stringIndex);  // FUN_004d3d90 – play audio/animation
            setGlobalFlag(1);                   // FUN_004d5900 – set global state flag
            break;
        case 2:                                 // Set float parameter (e.g., duration/volume)
            blockData = StreamReadBlockData(stream); // Returns pointer to block structure
            floatVal = (float)*(int*)((char*)blockData + 8);
            if (*(int*)((char*)blockData + 8) < 0) {
                floatVal += BIG_FLOAT_CONSTANT; // DAT_00e44578 (likely 0.0f or a magic number)
            }
            this->field_0x70 = floatVal;        // +0x70 float field
            break;
        case 3:                                 // Set second string (e.g., animation name)
            StreamNextBlock(stream);
            stringIndex = StreamReadInt32(stream);
            setStringFromTable(&this->field_0x58, stringIndex); // FUN_00408980 sets string at offset +0x58
            break;
        }
        StreamCloseBlock(stream);               // FUN_0043b1a0 – finalize current block
        isEnd = StreamIsEnd(stream);
    }
}