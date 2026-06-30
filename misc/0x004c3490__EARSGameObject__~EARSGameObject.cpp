// FUNC_NAME: EARSGameObject::~EARSGameObject
// Address: 0x004c3490
// Destructor for EARSGameObject. Sets vtable to base class, calls base destructor, frees resource at +0x208, then performs additional cleanup. If param_2 bit 0 set, calls operator delete.

__thiscall unsigned int* EARSGameObject__dtor(unsigned int* this, byte param_2)
{
    // Set vtable pointer to base class (expected vtable at 0x00e36290)
    *this = (unsigned int)&PTR_FUN_00e36290;

    // Call base class destructor (likely EARSBaseObject::~EARSBaseObject)
    FUN_004c33a0();

    // Free allocated resource at offset 0x208 (0x82 * 4)
    if (this[0x82] != 0) {
        FUN_009c8f10(this[0x82]);   // operator delete for resource
    }

    // Perform additional cleanup (e.g., release other members)
    FUN_004c27f0();

    // If deletion flag is set, free this object's memory
    if ((param_2 & 1) != 0) {
        FUN_009c8eb0(this);         // global operator delete
    }

    return this;
}