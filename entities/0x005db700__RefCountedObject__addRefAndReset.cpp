// FUNC_NAME: RefCountedObject::addRefAndReset
void __thiscall RefCountedObject::addRefAndReset(void)
{
    // +0x24: reference counter (incremented)
    *(int *)(this + 0x24) = *(int *)(this + 0x24) + 1;
    // +0x0C: initialization state flag (reset to 0)
    *(undefined4 *)(this + 0x0C) = 0;
    // Call base class initialization (0x005db0a0)
    FUN_005db0a0(this);
    return;
}