// FUNC_NAME: EARSObject::emptyStub
// Function address: 0x006eb850
// Role: Empty virtual stub in base class. Does nothing. Called from 0x006ef910 and 0x006efa30, likely as a vtable entry for an overridable event or cleanup.
// Assumption: This is a default implementation of a virtual member function of EARSObject (or similar base class) that is meant to be overridden by derived classes when functionality is needed.
// Note: The original Ghidra decompile shows a pure return; no registers or stack are modified.

void __thiscall EARSObject::emptyStub(void)
{
    // No operation performed.
    // This function is a placeholder that may be overridden in subclasses.
    // Example derived classes that could override: SimNpc, Player, Animated, etc.
    return;
}