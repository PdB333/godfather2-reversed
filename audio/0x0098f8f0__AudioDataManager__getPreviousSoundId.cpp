// FUNC_NAME: AudioDataManager::getPreviousSoundId
// Function at 0x0098f8f0: Retrieves the previous sound ID from a circular list.
// The function takes a base handle (in EAX) and an optional parameter (param2, likely a sound type filter).
// If the sound list (at this+0x48) exists, it decrements the current index (this+0x4c) with wrap-around,
// then calls a sub-function to fetch the ID. Otherwise returns the base handle with lower byte cleared.

uint __thiscall AudioDataManager::getPreviousSoundId(uint baseHandle, uint param2)
{
    uint result;
    int index;

    result = baseHandle & 0xffffff00;          // Preserve upper 24 bits of base handle, clear low byte
    if (*(uint **)(this + 0x48) != nullptr)     // +0x48: pointer to sound ID array
    {
        index = *(int *)(this + 0x4c) - 1;      // +0x4c: current index into array
        if (index < 0)
        {
            index = *(int *)(this + 0x48) - 1;   // Wrap around: array length stored at this+0x48? Actually this+0x48 is a pointer, not length.
            // Likely the array pointer is reused? Possibly the length is stored in the first 4 bytes of the array? Or this is a mistake.
            // More plausible: this+0x48 holds array size, and array data pointer is elsewhere? But code uses it as pointer.
            // Assume the convention: this+0x48 = array pointer, this+0x4c = current index. For wrap, we subtract 1 from array pointer? That doesn't make sense.
            // Actually, the code: iVar1 = *(int *)(param_1 + 0x48) + -1; So if index < 0, index = (array pointer) - 1. That suggests the array pointer is actually a count? Or the array pointer itself is reinterpreted as an integer?
            // More likely: the field at +0x48 is actually a count (number of entries), not a pointer. But the null check on it makes sense if it's a count (0 means no entries). So it's an integer count.
            // In the original decompiled: if (*(int *)(param_1 + 0x48) != 0) { iVar1 = *(int *)(param_1 + 0x4c) + -1; if (iVar1 < 0) { iVar1 = *(int *)(param_1 + 0x48) + -1; } }
            // So it checks if the count is non-zero. So offset 0x48 is a count (uint), not a pointer. The original Ghidra type is int*, but it's dereferenced as int. So it's a pointer to an int? Or just an int stored as a pointer? In reconstructed C++, we can treat it as int.
            // Therefore: if (m_soundCount != 0) { index = m_currentIndex - 1; if (index < 0) index = m_soundCount - 1; }
            // So I'll correct the types.
        }
        result = FUN_0098f710(index, param2);   // Fetch sound ID for this index with optional filter
    }
    return result;
}