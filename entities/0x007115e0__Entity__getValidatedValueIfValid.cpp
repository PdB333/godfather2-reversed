// FUNC_NAME: Entity::getValidatedValueIfValid
// Function address: 0x007115e0
// Role: Checks if a given value (typically a bitmask or ID) passes a virtual validation test.
// Returns the value if validated, otherwise returns 0.

uint __thiscall Entity::getValidatedValueIfValid(void* this, uint value)
{
    uint ignoredOutput; // unused, but passed to virtual function
    char isValid;
    
    ignoredOutput = 0;
    
    // vtable offset 0x10 (5th virtual function) is a validation function
    // It takes the value and an output pointer, returns non-zero if valid
    typedef char (__thiscall *ValidateFunc)(void* this, uint, uint*);
    ValidateFunc validate = *(ValidateFunc*)(*(uint*)this + 0x10);
    
    isValid = validate(this, value, &ignoredOutput);
    
    // If validation succeeds, return the original value; otherwise 0
    return (isValid != 0) ? value : 0;
}