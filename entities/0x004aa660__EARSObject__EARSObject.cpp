// FUNC_NAME: EARSObject::EARSObject
// Address: 0x004aa660
// Constructor for EARSObject. Calls base initialization and optionally deallocates object if flag bit0 is set.
// Likely used for custom memory management (e.g., placement new with deallocation control).

EARSObject* EARSObject::EARSObject(byte bShouldDeallocate)
{
    // Call base class initializer (sets vtable and default fields)
    initBase();  // FUN_004aa680
    
    // If the low bit of the flag is set, perform deallocation (e.g., return to pool)
    if (bShouldDeallocate & 1)
    {
        deallocateObject(this);  // FUN_009c8eb0: custom deallocation routine
    }
    
    return this;
}