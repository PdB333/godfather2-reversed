// FUNC_NAME: EARSObject::setPosition
void __thiscall EARSObject::setPosition(int this, int x, int y)
{
    // +0x10: x coordinate
    *(int *)(this + 0x10) = x;
    // +0x14: y coordinate
    *(int *)(this + 0x14) = y;
    return;
}