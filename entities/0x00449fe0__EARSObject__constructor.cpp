// FUNC_NAME: EARSObject::constructor
// Address: 0x00449fe0
// Role: Constructor that calls the base class initializer and optionally performs finalization (e.g., destructor or cleanup) based on a flag.

EARSObject * __thiscall EARSObject::constructor(EARSObject *this, byte flags)
{
    EARSObject::baseConstructor(this);          // Calls base class constructor at 0x0044a030
    if (flags & 1) {                            // If low bit set, run finalization
        EARSObject::finalizeObject(this);       // Possibly call destructor/cleanup at 0x009c8eb0
    }
    return this;                                // Return constructed object
}