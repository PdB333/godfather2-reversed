// FUNC_NAME: PropertySet::selectAndApplyValue
void __thiscall PropertySet::selectAndApplyValue()
{
    // Read default value from +0x20 (likely a float or int property)
    int selectedValue = *(int*)(this + 0x20);
    
    // Check type ID at offset 0xc of the object referenced by this+0x50
    // The object at this+0x50 is a polymorphic container; its type ID is at +0x0c
    if (*(int*)(*(int*)(this + 0x50) + 0xc) == 0xb) {
        // If type is 0xb, use override value from +0x24 instead
        selectedValue = *(int*)(this + 0x24);
    }
    
    // Apply the selected value via the container's setter function
    // The container pointer is at this+0x50, and the value is passed as an argument
    FUN_005566a0(*(int**)(this + 0x50), selectedValue);
}