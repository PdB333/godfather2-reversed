// FUNC_NAME: ActionResponseHandler::processRequestPacket
int __thiscall ActionResponseHandler::processRequestPacket(void) {
    int* readPtr = *(int**)(this + 0xc);  // +0xC: current read position in incoming buffer
    int* writePtr = *(int**)(this + 0x8); // +0x8: current write position in outgoing buffer
    int responseValue = 0;
    const uint entriesBase = DAT_0122346c + 0x14; // Base of action entry table (0x54 bytes per entry)
    float idFloat = 0.0f;
    uint id;

    // Check if there is any data to read
    if ((writePtr <= readPtr) || (readPtr == nullptr)) {
        goto write_response;
    }

    // Read message type from incoming packet
    int msgType = *readPtr;
    if (msgType == 3) {
        // Type 3: straightforward ID
        idFloat = (float)readPtr[1];
    } else if (msgType == 4) {
        // Type 4: requires validation via helper function
        int valid = FUN_00636850(&this);  // Security check
        if (valid != 0) {
            idFloat = (float)readPtr[1];
        } else {
            idFloat = 0.0f;
        }
    } else {
        idFloat = 0.0f;
    }

    // Round float ID to integer
    id = (uint)(longlong)roundf(idFloat);
    if (id < 0x80) {
        int* entry = (int*)(entriesBase + id * 0x54);
        if (*entry == (int)this) {  // Entry's first field matches this object
            responseValue = entry[1]; // Second field is the response data
        }
    }

write_response:
    // Write response message: type 3 with responseValue as float
    uint* out = *(uint**)(this + 0x8);  // Re-read write pointer (may have shifted if we advanced earlier? But no, we haven't changed it yet)
    out[0] = 3;
    out[1] = (float)responseValue;
    *(int*)(this + 0x8) = (int)out + 8; // Advance write pointer by 8 bytes
    return 1;
}