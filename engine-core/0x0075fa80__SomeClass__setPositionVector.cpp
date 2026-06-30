// FUNC_NAME: SomeClass::setPositionVector
void __thiscall SomeClass::setPositionVector(int this, const void* src)
{
    // Copy 8 bytes (likely two floats) to offset +0x50 (e.g., x and y)
    *(undefined8*)(this + 0x50) = *(const undefined8*)src;
    // Copy 4 bytes (likely one float) to offset +0x58 (e.g., z)
    *(undefined4*)(this + 0x58) = *(const undefined4*)((const char*)src + 8);
}