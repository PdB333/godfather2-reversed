// FUNC_NAME: UnknownManager::applyGlobalConfigField
void __thiscall UnknownManager::applyGlobalConfigField(UnknownManager *this)
{
    // Store global value DAT_01205228 into field at offset 0x388 (likely a configuration pointer or flag)
    *(int *)((int)this + 0x388) = DAT_01205228;
    return;
}