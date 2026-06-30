// FUNC_NAME: ObjectBase::testAndClearFlags
bool __thiscall ObjectBase::testAndClearFlags(uint flagsToClear)
{
    uint oldFlags = *(uint *)(this + 0x38);
    *(uint *)(this + 0x38) = ~flagsToClear & oldFlags;
    return (flagsToClear & oldFlags) != 0;
}