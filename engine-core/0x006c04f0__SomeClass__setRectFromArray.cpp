// FUNC_NAME: SomeClass::setRectFromArray
void __thiscall SomeClass::setRectFromArray(uint32_t *src)
{
    // Copy 4 consecutive uint32 values from src into object at offsets +0x10 to +0x1C
    // Typically used to set a rectangle or vector4 (x, y, z, w) or (left, top, right, bottom)
    *(uint32_t *)((int)this + 0x10) = src[0]; // +0x10
    *(uint32_t *)((int)this + 0x14) = src[1]; // +0x14
    *(uint32_t *)((int)this + 0x18) = src[2]; // +0x18
    *(uint32_t *)((int)this + 0x1c) = src[3]; // +0x1c
}