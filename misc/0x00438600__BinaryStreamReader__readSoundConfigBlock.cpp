// FUNC_NAME: BinaryStreamReader::readSoundConfigBlock
int BinaryStreamReader::readSoundConfigBlock() {
    // this points to reader object with fields:
    // +0x8: m_End (pointer to end of buffer)
    // +0xc: m_Current (current read position)
    int* current = *(int**)(this + 0xc); // current position pointer
    int* end = *(int**)(this + 0x8);     // end boundary pointer

    // Each entry is 8 bytes: 4 bytes type + 4 bytes data? 
    // We check 5 consecutive entries starting at current.
    int offset = 0;
    while (offset <= 0x20) { // offsets 0, 8, 16, 24, 32 (0x20)
        int* entry = (int*)(*(int*)(this + 0xc) + offset);
        if (end <= entry || entry == (int*)0) {
            return 0;
        }
        int type = *entry;
        if (type != 3) {
            if (type != 4) {
                return 0;
            }
            // Type 4 requires validation (perhaps a sub-block marker)
            char buffer[4];
            int result = readToken(buffer); // FUN_00636850
            if (result == 0) {
                return 0;
            }
        }
        offset += 8;
    }

    // After the header, there is a data block (offset 0x20 is the 5th entry)
    // If the 5th entry exists (already passed check), handle data.
    // Additional entry at offset 0x28 (6th entry)
    int* dataEntry = (int*)(*(int*)(this + 0xc) + 0x28);
    if (end > dataEntry && dataEntry != (int*)0) {
        int dataType = *dataEntry;
        if (dataType != 3) {
            if (dataType != 4) {
                return 0;
            }
            char buffer[4];
            int result = readToken(buffer);
            if (result == 0) return 0;
        }

        // Set default values from global configuration
        float param1 = (float)g_soundDefaultVolume; // DAT_00e44620 -> maybe volume
        int channel = 0x9c;                        // constant channel ID
        float param2 = 0.0f;                       // default pan
        float param3 = (float)g_soundDefaultPitch; // DAT_00e2b1a4 -> pitch
        float param4 = 0.0f;                       // default unknown1
        float param5 = 0.0f;                       // default unknown2

        // Read 6 float parameters (indices 1-6)
        param4 = readFloat(this, 1); // FUN_006259b0(this,1)
        param5 = readFloat(this, 2); // FUN_006259b0(this,2)
        param1 = readFloat(this, 3); // FUN_006259b0(this,3) overrides volume
        param2 = readFloat(this, 4); // FUN_006259b0(this,4) overrides pan
        param3 = readFloat(this, 5); // FUN_006259b0(this,5) overrides pitch
        // Last float (index 6) is passed to another function
        float lastFloat = readFloat(this, 6); // FUN_006259b0(this,6)
        applySoundSetting(lastFloat); // FUN_005e3d90
    }

    return 0;
}