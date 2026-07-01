// FUNC_NAME: NetSerializable::retrieveData
size_t __thiscall NetSerializable::retrieveData(void* destBuffer, int unusedParam, bool* outChangedFlag) {
    size_t dataSize;
    void* dataBuffer;

    // Check if data has been initialized (offset +0x2c stores initialization flag)
    if (*(int*)(this + 0x2c) == 0) {
        // Perform initialization
        FUN_008f1ef0(); // initData() – likely creates or prepares the serialized buffer
        // Log some event (offset +0x28 is some identifier, 0xb is a message type)
        FUN_004c03c0(*(int*)(this + 0x28), 0xb); // logMessage(id, 11)
        *outChangedFlag = true;
    } else {
        *outChangedFlag = false;
    }

    // Obtain the serialized buffer and its size (likely from an internal cache)
    FUN_004c0350(&dataBuffer, &dataSize); // getSerializedBuffer(&buffer, &size)
    // Copy the serialized data to the caller's destination
    _memcpy(destBuffer, dataBuffer, dataSize);
    return dataSize;
}