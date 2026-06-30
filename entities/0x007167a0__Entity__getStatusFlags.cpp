// FUNC_NAME: Entity::getStatusFlags
uint __thiscall Entity::getStatusFlags(void* thisPtr)
{
    // Reads a packed flags field at offset 0x154, shifts right by 2 bits
    // and masks with 0xFFFFFF01 (keeps bit0 and bits8-31, clears bits1-7).
    // This isolates a specific subset: original bit2 (now bit0) and original bits10-31.
    // Possibly extracts a "type" or "state" field after discarding lower alignment bits.
    return (*(uint*)((int)thisPtr + 0x154) >> 2) & 0xFFFFFF01;
}