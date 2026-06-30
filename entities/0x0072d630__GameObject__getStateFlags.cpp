// FUNC_NAME: GameObject::getStateFlags
uint __fastcall GameObject::getStateFlags(GameObject* this)
{
    // Reads a 32-bit field at offset 0x1F5C, shifts right by 5, then masks out bits 1-7.
    // Extracts bit 5 (now bit 0) and bits 13-31 (now bits 8-28) for combined state flags.
    return (*(uint*)((char*)this + 0x1F5C) >> 5) & 0xFFFFFF01;
}