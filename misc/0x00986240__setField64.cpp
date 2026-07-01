// FUNC_NAME: setField64
void __thiscall setField64(void* this, int value)
{
    // +0x64 (100) - unknown integer field (e.g., state, ID, or flag)
    *(int*)((char*)this + 100) = value;
}