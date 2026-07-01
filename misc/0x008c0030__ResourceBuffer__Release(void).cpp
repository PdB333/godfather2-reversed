// FUNC_NAME: ResourceBuffer::Release(void)
void __thiscall ResourceBuffer::Release(ResourceBuffer* this) {
    // Free pointer at offset +0xC (field_0xC)
    if (this->field_0xC != nullptr) {
        FUN_009c8f10(this->field_0xC);
    }
    // Free pointer at offset +0x0 (field_0x0)
    if (this->field_0x0 != nullptr) {
        FUN_009c8f10(this->field_0x0);
    }
}