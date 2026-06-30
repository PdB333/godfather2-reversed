// FUNC_NAME: GameObject::hasFlag
uint __thiscall GameObject::hasFlag(uint flag)
{
    uint unused = 0; // output parameter (ignored)
    // Call virtual function at vtable+0x10 (4th entry, returns char)
    char result = (this->vtable[4])(flag, &unused);
    // Return flag if result is non-zero, else 0
    return (result != 0) ? flag : 0;
}