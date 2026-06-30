// FUNC_NAME: getFieldAt0x104
int __fastcall getFieldAt0x104(void* this) {
    // Returns the 4-byte value at offset 0x104 within the object.
    return *(int*)((char*)this + 0x104);
}