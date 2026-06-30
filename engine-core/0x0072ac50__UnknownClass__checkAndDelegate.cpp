// FUNC_NAME: UnknownClass::checkAndDelegate
uint __fastcall UnknownClass::checkAndDelegate(int this)
{
    // +0x14: type/state identifier field
    uint type = *(uint *)(this + 0x14);

    // If type is 0 or 0x48, return low byte masked; otherwise delegate to another function
    if (type != 0 && type != 0x48) {
        // +0x04: pointer to a derived object or sub‑component
        return FUN_00782790(this + 4);
    }
    return type & 0xFFFFFF00;
}