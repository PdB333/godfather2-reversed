// FUNC_NAME: setFlag
void __thiscall setFlag(void* this, char value)
{
    // Dereference pointer at this+0x168 to get subobject, then write byte at offset 100 (0x64)
    *(char*)(*(int*)((char*)this + 0x168) + 100) = value;
    return;
}