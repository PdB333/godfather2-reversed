// FUNC_NAME: FlagManager::setFlagForEntity

void __thiscall FlagManager::setFlagForEntity(int entityId, char setFlag)
{
    ushort *bitmaskArray; // pointer to array of ushort bitmasks (+0x0c)
    ushort flagBit = DAT_012053d8; // global bit flag constant
    int count = *(int *)(this + 0x38); // number of entries
    int i;

    if (setFlag == '\0') {
        // Set the flag (OR)
        if (count > 0) {
            for (i = 0; i < count; i++) {
                // Compare entity ID at offset +0x1c in each 0x20-byte struct
                if (*(int *)(*(int *)(this + 0x10) + 0x1c + i * 0x20) == entityId) {
                    bitmaskArray = (ushort *)(*(int *)(this + 0x0c) + i * 2);
                    *bitmaskArray = *bitmaskArray | flagBit;
                }
            }
        }
    } else {
        // Clear the flag (AND with complement)
        if (count > 0) {
            for (i = 0; i < count; i++) {
                if (*(int *)(*(int *)(this + 0x10) + 0x1c + i * 0x20) == entityId) {
                    bitmaskArray = (ushort *)(*(int *)(this + 0x0c) + i * 2);
                    *bitmaskArray = *bitmaskArray & ~flagBit;
                }
            }
        }
    }
}