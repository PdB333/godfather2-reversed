// FUNC_NAME: Object::releaseContained
void __thiscall Object::releaseContained(void* this)
{
    // Offset +0x00: pointer to contained object/resource
    // Offset +0x04: some state or reference count
    // Offset +0x08: another field (maybe flags or handle)

    *(undefined4*)((int)this + 4) = 0;          // +0x04 = 0
    FUN_009c8f10(*(undefined4*)this);           // release the contained object
    *(undefined4*)this = 0;                     // +0x00 = 0
    *(undefined4*)((int)this + 8) = 0;          // +0x08 = 0
}