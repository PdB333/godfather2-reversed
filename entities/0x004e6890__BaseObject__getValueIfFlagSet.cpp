// FUNC_NAME: BaseObject::getValueIfFlagSet
int __thiscall BaseObject::getValueIfFlagSet(int param_2)
{
    if (param_2 != 0) {
        // this+0x4 -> pointer to internal data block
        // that block offset +0xC -> some integer field
        return internalGetValue(*(int*)(*(int*)((char*)this + 4) + 0xC));
    }
    return 0;
}