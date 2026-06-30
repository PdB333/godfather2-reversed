// FUNC_NAME: setSubObjectFlag
void __thiscall setSubObjectFlag(byte value)
{
    // +0x18: pointer to sub-object
    // +0x10: flag byte within sub-object
    byte* subObject = *(byte**)((byte*)this + 0x18);
    subObject[0x10] = value;
}