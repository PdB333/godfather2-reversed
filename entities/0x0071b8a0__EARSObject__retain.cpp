// FUNC_NAME: EARSObject::retain
// Function at 0x0071b8a0 increments reference count at offset +0x18
void EARSObject::retain() {
    // Increment reference count (at offset 0x18)
    *(int*)((char*)this + 0x18) += 1;
}