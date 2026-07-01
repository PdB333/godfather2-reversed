// FUNC_NAME: UnknownClass::CleanupResource
// Address: 0x00946b30 - Likely a member function of some EARS class that releases a resource pointed to by offset 0x00
// Offsets: +0x00: pointer to resource, +0x04: unknown, +0x08: unknown
void __fastcall UnknownClass::CleanupResource(void* this) {
    // Assuming param_1 is 'this' pointer in __fastcall (ecx)
    this->field_0x04 = 0;      // +0x04: zero out unknown field
    FUN_009c8f10(this->ptr);   // Release resource pointed to by first field (+0x00)
    this->ptr = 0;             // +0x00: null the pointer
    this->field_0x08 = 0;      // +0x08: zero out another field
}