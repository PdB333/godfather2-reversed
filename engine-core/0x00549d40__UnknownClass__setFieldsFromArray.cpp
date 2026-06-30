// FUNC_NAME: UnknownClass::setFieldsFromArray
// Address: 0x00549d40
// Role: Copies three values from input array into offsets 0x40, 0x44, 0x48, and sets offset 0x4c from a global constant.

// Global constant used for the fourth field (unknown source)
extern float DAT_00e2b1a4;

void __thiscall UnknownClass::setFieldsFromArray(void* this, float* pArray) {
    // Copy first three values from the input array
    *(float*)((uint32_t)this + 0x40) = pArray[0]; // +0x40
    *(float*)((uint32_t)this + 0x44) = pArray[1]; // +0x44
    *(float*)((uint32_t)this + 0x48) = pArray[2]; // +0x48
    // Set the fourth field from a global constant
    *(float*)((uint32_t)this + 0x4c) = DAT_00e2b1a4; // +0x4c
}