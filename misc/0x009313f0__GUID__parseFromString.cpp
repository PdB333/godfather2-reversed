// FUNC_NAME: GUID::parseFromString
void __thiscall GUID::parseFromString(uint initialHash, GUIDString* stringDesc, GUIDOutput* output) {
    bool isValidFormat = true;
    uint currentHash = initialHash;
    uint byteCount = 0;

    // If output already has content, call its cleanup function (offset +0x0C)
    if (*output != 0) {
        (*(void(__thiscall*)(GUIDOutput*))output->cleanupFunction)(output);
    }

    // Reset output structure
    *output = 0;                          // +0x00: pointer or handle
    output->field_4 = 0;                  // +0x04
    output->field_8 = 0;                  // +0x08

    currentHash = currentHash & 0xFFFFFF; // Use lower 24 bits as initial seed

    const char* data = stringDesc->data;     // +0x00: string pointer
    int length = stringDesc->length;         // +0x04: string length

    for (uint i = 0; i < (uint)length; i++) {
        // Shift in next character from the string (big‑endian accumulation)
        currentHash = ((uint)(unsigned char)data[i] << 24) | (currentHash & 0xFFFFFF);

        // Every 4 characters, expect a hyphen; if not, report an error
        if (i != 0 && (i & 3) == 0) {
            if (data[i] == '-') {
                isValidFormat = false;
            } else {
                FUN_004d4300(&DAT_00d68478); // Debug assertion or error logging
            }
        }

        // Accumulate the current high byte into the output
        FUN_004d43f0((int)&currentHash + 3, 0, 1); // Store the most recent character byte
    }

    // Finalize parsing
    FUN_004d55a0();
}