// FUNC_NAME: GameObject::getTransformedFlags
// Address: 0x00872d50
// Role: Returns transformed flags from an owner object (this+0x64) at owner+0xD4,
//       or default with low byte zeroed if owner is null or sentinel (0x48).

uint __fastcall GameObject::getTransformedFlags(uint defaultFlags)
{
    // this+0x64: m_pOwner (pointer to parent/owner object)
    int* pOwner = *(int**)((int)this + 100);

    // Check if owner exists and is not the invalid sentinel (0x48)
    if (pOwner != nullptr && pOwner != (int*)0x48)
    {
        // owner+0xD4: m_flags (bitfield)
        uint ownerFlags = *(uint*)((int)pOwner + 0xD4);
        return (ownerFlags >> 2) & 0xFFFFFF01;
    }

    // Default: clear low byte of input parameter
    return defaultFlags & 0xFFFFFF00;
}