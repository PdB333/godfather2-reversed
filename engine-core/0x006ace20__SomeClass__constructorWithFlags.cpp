// FUNC_NAME: SomeClass::constructorWithFlags
// Address: 0x006ace20
// Role: Constructor that calls a base initializer (FUN_006ac960) and conditionally calls a secondary initializer (FUN_009c8eb0) if flags bit 0 is set.
// Typical pattern: if placement new flag is set, perform additional setup (e.g. allocate internal buffers or set vtable).

// Unknown class – placeholder. Real class likely derived from a common EARS base (e.g., EARSObject).
class SomeClass;

// Base initializer (called unconditionally)
void __thiscall baseConstructor(SomeClass* thisPtr); // FUN_006ac960

// Secondary initializer (called if flags & 1)
void __thiscall extraInit(SomeClass* thisPtr); // FUN_009c8eb0

// Actual constructor
SomeClass* __thiscall SomeClass::constructorWithFlags(SomeClass* thisPtr, uint8_t flags)
{
    // Call base class constructor (vtable setup, zero-init, etc.)
    baseConstructor(thisPtr);

    // If the lowest bit is set, perform additional initialization
    if ((flags & 1) != 0)
    {
        extraInit(thisPtr);
    }

    // Return self (standard C++ constructor return)
    return thisPtr;
}