// FUNC_NAME: EARSObject::EARSObject
// 0x00442a10 - Constructor for an EARS Object, optionally marks heap allocation.
// Called with a byte parameter: bit 0 indicates if the object was heap-allocated.

// Base class constructor (likely default)
void FUN_00442a30(); // 0x00442a30 - presumed base class default constructor

// Helper function to mark heap allocation (or perform post-construction steps)
void setHeapAllocated(EARSObject* obj); // 0x009c8eb0

class EARSObject : public BaseClass // BaseClass unknown, assume some EA engine base
{
public:
    EARSObject(byte flags);
    // ... other members
};

EARSObject::EARSObject(byte flags)
{
    // Call base constructor (via this pointer)
    FUN_00442a30(); // BaseClass::BaseClass()

    // If bit 0 set, mark as heap-allocated (or perform additional init)
    if (flags & 1)
    {
        setHeapAllocated(this); // 0x009c8eb0 - stores allocation info or registers object
    }

    // Return this (implicit)
}