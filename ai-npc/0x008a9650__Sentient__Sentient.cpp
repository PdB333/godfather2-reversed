// FUNC_NAME: Sentient::Sentient
// Address: 0x008a9650
// Constructor for the Sentient base class (likely for NPC/Player).
// Initializes vtable pointers for multiple inheritance, and optionally allocates a sub-object.

Sentient* __thiscall Sentient::Sentient(Sentient* this, int bCreateSubObject)
{
    void* pSubObject = nullptr;
    if (bCreateSubObject != 0)
    {
        pSubObject = (void*)FUN_00481610(); // Allocates sub-object (e.g., AI component)
    }

    FUN_0064d390(0, 1); // Engine-level initialization (e.g., debug flags)

    // Primary vtable (base class)
    this->vtable = (void*)0x00e317dc; // +0x00: First vtable pointer
    this->field_0x18 = 0;             // +0x18: Clear field

    FUN_00454a10(pSubObject); // Attach/integrate sub-object

    this->field_0x24 = 1;             // +0x24: Set flag (e.g., "initialized")
    // Overwrite primary vtable (likely switches to fully constructed vtable)
    this->vtable = (void*)0x00d79d70; // +0x00: Final vtable pointer

    // Secondary interface table (e.g., AI interface)
    this->secondaryTablePtr = (void*)0x00d79bc0; // +0x28: Points to secondary vtable
    this->funcPtr = (void*)0x008a89b0;           // +0x30: Function pointer (e.g., virtual method stub)
    this->field_0x34 = 0;                        // +0x34: Clear field

    // Self-pointer to secondary table (used for adjusting `this` for secondary interface)
    this->selfAdjustPtr = (int*)((char*)this + 0x28); // +0x14: Points to offset 0x28

    return this;
}
```