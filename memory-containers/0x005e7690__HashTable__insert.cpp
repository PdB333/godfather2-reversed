// FUNC_NAME: HashTable::insert
uint __thiscall HashTable::insert(uint hashKey, KeyData* keyData, ValueData* value1, ValueData* value2)
{
    byte maxHash = *(byte*)(this + 0x1c); // +0x1c: maximum allowed hash value (low byte)
    uint hash = hashKey ^ 0xad103100; // xor with constant to produce index
    if (maxHash <= hash) {
        // hash too large; fail
        return hash & 0xffffff00;
    }

    // Compute derived data from key structure (likely used for initialising entry fields)
    uint computed[10]; // local_50, local_4c, local_48, local_40, local_3c, local_38, local_30, local_2c, local_28
    undefined* temp = FUN_0056b8a0(keyData->field1, keyData->field0, keyData->field2, &computed);
    // temp is ignored in success path; used as dummy for failure return.

    if (maxHash != 0) {
        byte keyLow = (byte)hashKey; // low byte of original key
        if (keyLow < maxHash) {
            Entry* slot = *(Entry**)((byte*)this + 4 + (hash & 0xff) * 4); // +0x04..0x04+0x3FC: array of 256 slot pointers
            if (slot != nullptr) {
                // Fill entry with computed and provided data
                slot->field0  = computed[0];  // local_50
                slot->field1  = computed[4];  // local_40 (offset 4 in computed)
                slot->field2  = computed[6];  // local_30
                slot->field3  = 0;
                slot->field4  = computed[1];  // local_4c
                slot->field5  = computed[5];  // local_3c
                slot->field6  = computed[7];  // local_2c
                slot->field7  = 0;
                slot->field8  = computed[2];  // local_48
                slot->field9  = computed[6];  // local_38 (note: seems reused, maybe a bug)
                slot->field10 = computed[8];  // local_28
                slot->field11 = 0;
                slot->field12 = 0;
                slot->field13 = 0;
                slot->field14 = 0;
                slot->field15 = DAT_00e2b1a4; // global sentinel
                slot->field16 = value1[0];
                slot->field17 = DAT_00e2b1a4;
                slot->field18 = value1[1];
                slot->field19 = value1[2];
                slot->field20 = DAT_00e2b1a4;
                slot->field21 = value2[0];
                slot->field22 = value2[1];
                slot->field23 = value2[2];

                // success indicator: slot pointer shifted right 8, low byte set to 1
                return ((uint)slot >> 8) & 0xffffff00 | 1;
            }
        }
    }
    // failure: return temp (modified) with low byte cleared
    return (uint)temp & 0xffffff00;
}