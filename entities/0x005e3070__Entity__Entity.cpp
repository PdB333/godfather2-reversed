// FUNC_NAME: Entity::Entity
void __fastcall Entity::Entity(int* thisPtr)
{
    // Zero-initialize all 8 dword fields (32 bytes total)
    // Note: fields are zeroed in a specific order (index 7 before 6)
    thisPtr[0] = 0;  // +0x00
    thisPtr[1] = 0;  // +0x04
    thisPtr[2] = 0;  // +0x08
    thisPtr[3] = 0;  // +0x0C
    thisPtr[4] = 0;  // +0x10
    thisPtr[5] = 0;  // +0x14
    thisPtr[7] = 0;  // +0x1C
    thisPtr[6] = 0;  // +0x18
}