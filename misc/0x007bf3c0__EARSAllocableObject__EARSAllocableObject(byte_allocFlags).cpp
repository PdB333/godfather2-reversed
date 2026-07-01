// FUNC_NAME: EARSAllocableObject::EARSAllocableObject(byte allocFlags)

// Address: 0x007bf3c0
// Role: Constructor that chains to base constructor and optionally performs additional
//       resource management based on the allocFlags parameter.
//       This pattern is typical for EA EARS engine objects that support both
//       standard allocation and placement new with a flag (bit 0 = placement flag).

uint32 __thiscall EARSAllocableObject::EARSAllocableObject(EARSAllocableObject* this, byte allocFlags)
{
    EARSObject::EARSObject(this);                       // base class constructor at 0x007BF2F0

    if ((allocFlags & 1) != 0)                          // bit 0 set: placement or cleanup needed
    {
        EARSObject::handlePlacementCleanup(this);       // appropriate function at 0x00624DA0
    }

    return this;                                        // MSVC __thiscall convention: return this
}