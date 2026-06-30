// FUNC_NAME: ObjectTable::storeEntry
uint32 __thiscall ObjectTable::storeEntry(uint32 hash, Key* pKey, DataBlock* pDataA, DataBlock* pDataB) {
    uint8 threshold = *(uint8*)(this + 0x1c);            // max number of entries (must be <= 256)
    uint32 hashed = hash ^ 0xad103100;                   // simple hash
    uint32 index = hashed & 0xff;                        // low byte as bucket index

    if (threshold <= index) {
        return hashed & 0xffffff00;                      // failure – index out of range
    }

    // Temporary storage for processed key data (9 DWORDs)
    uint32 keyData[9];                                   // local_50..local_28 on stack

    void* entryRaw = sub_56B8A0(pKey->field4, pKey->field0, pKey->field8, &keyData);
    if (threshold != 0) {
        uint8 lowHash = (uint8)hash;
        entryRaw = (void*)((uint32)entryRaw & 0xffffff00) | lowHash;  // store low hash byte in lower bits?

        if (lowHash < threshold) {
            uint32** entryPtr = (uint32**)(this + 4 + index * 4);   // array of pointers at +0x04
            uint32* entry = *entryPtr;
            if (entry != nullptr) {
                // Fill the entry structure with the processed key data and the two data blocks
                entry[0x00] = keyData[0];   // local_50
                entry[0x04] = keyData[1];   // local_4c
                entry[0x08] = keyData[2];   // local_48
                entry[0x01] = keyData[3];   // local_40
                entry[0x05] = keyData[4];   // local_3c
                entry[0x02] = keyData[5];   // local_30
                entry[0x06] = keyData[6];   // local_2c
                entry[0x09] = keyData[7];   // local_38
                entry[0x0a] = keyData[8];   // local_28
                entry[0x03] = 0;
                entry[0x07] = 0;
                entry[0x0b] = 0;
                entry[0x0c] = 0;
                entry[0x0d] = 0;
                entry[0x0e] = 0;
                entry[0x0f] = DAT_00e2b1a4;                 // some global constant (maybe sentinel)
                entry[0x10] = pDataA->field0;
                entry[0x13] = DAT_00e2b1a4;
                entry[0x11] = pDataA->field1;
                entry[0x12] = pDataA->field2;
                entry[0x17] = DAT_00e2b1a4;
                entry[0x14] = pDataB->field0;
                entry[0x15] = pDataB->field1;
                entry[0x16] = pDataB->field2;

                return ((uint32)entry & 0xffffff00) | 1;    // return success (low bit set)
            }
        }
    }

    return (uint32)entryRaw & 0xffffff00;                  // failure – entry not written
}