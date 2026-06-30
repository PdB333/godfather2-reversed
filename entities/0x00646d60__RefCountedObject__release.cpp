//FUNC_NAME: RefCountedObject::release
void RefCountedObject::release(int param_1) {
    // Call cleanup routine (likely releases resources or decrements reference)
    cleanup(param_1);
    // Clear lower 3 bits of the reference count/flags field at offset +4
    // The mask 0x7ffffff8 preserves the upper 29 bits and zeros bits 0-2
    *(uint *)(this + 4) &= 0x7ffffff8;
}