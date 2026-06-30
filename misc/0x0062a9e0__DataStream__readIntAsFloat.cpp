// FUNC_NAME: DataStream::readIntAsFloat
int __thiscall DataStream::readIntAsFloat() {
    int* readPtr = *(int**)(this + 0xC); // +0xC: read pointer
    int* writePtr = *(int**)(this + 0x8); // +0x8: write pointer
    int value = 0;

    if (readPtr < writePtr && readPtr != nullptr) {
        int tokenType = *readPtr;
        if (tokenType == 4) {
            value = readPtr[1] + 0x10; // offset to value for type 4
        } else {
            int result = readNext(); // FUN_00633990
            if (result != 0) {
                value = readPtr[1] + 0x10;
            }
            // Check if buffer needs flushing (+0x10 points to metadata)
            if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24)) {
                flush(); // FUN_00627360
            }
        }
        if (value == 0) {
            reportError("ERROR_READING_FLOAT"); // FUN_00627ac0
        }
    } else {
        reportError("ERROR_READING_FLOAT");
    }

    // Re-read state after potential error handling
    readPtr = *(int**)(this + 0xC);
    if (readPtr < writePtr && readPtr != nullptr) {
        if (*readPtr == 4) {
            value = *(int*)(readPtr[1] + 0xC); // float value at offset 0xC
            goto writeFloat;
        }
        int result = readNext();
        if (result != 0) {
            value = *(int*)(readPtr[1] + 0xC);
            goto writeFloat;
        }
    }
    value = 0;

writeFloat:
    float floatVal = (float)value;
    writePtr[0] = 3; // type tag for float
    reinterpret_cast<float*>(writePtr + 1)[0] = floatVal; // store float bytes
    *(int*)(this + 0x8) += 8; // advance write pointer by 2 ints
    return 1;
}