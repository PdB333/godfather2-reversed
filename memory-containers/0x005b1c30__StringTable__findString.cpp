// FUNC_NAME: StringTable::findString
uint StringTable::findString(const char* str) {
    uint count = *unaff_EDI;          // +0x00: number of strings in table
    uint index = 0;
    
    if ((int)count > 0) {
        do {
            if (*str == '\0') break;  // empty string check
            if (*(char*)(index + unaff_EDI[2]) != *str) goto LAB_005b1c66;
            index++;
            str++;
        } while ((int)index < (int)count);
    }
    
    if ((index == count) && (*str == '\0')) {
        // Found exact match - return success with index
        return CONCAT31((int3)(index >> 8), 1);
    }
    
LAB_005b1c66:
    // Not found - return failure with partial match index
    return index & 0xffffff00;
}