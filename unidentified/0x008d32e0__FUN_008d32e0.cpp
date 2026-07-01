// FUNC_NAME: SomeClass::~SomeClass (destructor)
// Address: 0x008d32e0
// Identified as a destructor for an EARS engine object with two vtable pointers.
// This pattern is common for classes derived from multiple base classes or using virtual inheritance.
// The function sets vtable pointers, releases sub-objects, and updates global state.

void __thiscall SomeClass::~SomeClass(void)
{
    // Set vtable pointers (first base class vtable at +0x00, second at +0x0C)
    this->vtable0 = &PTR_FUN_00d7d4a4;
    this->vtable1 = &PTR_LAB_00d7d4a0;  // +0x0C

    // Call static destructors/release on global objects (likely initializers)
    // FUN_004086d0 might be a destructor for a static object at 0x012069d4
    StaticObjectA::release();  // &DAT_012069d4
    // FUN_00408310 might be a destructor for a static object at 0x0112f9d0
    StaticObjectB::release();  // &DAT_0112f9d0
    // Another release call for static object at 0x0112b36c
    StaticObjectC::release();  // &DAT_0112b36c

    // If a sub-object pointer at +0x18 (offset 6 * 4) is non-null, release it
    if (this->subObject != nullptr) {
        subObject->release();  // FUN_009c8f10 (likely a virtual destructor or release method)
    }

    // Change second vtable pointer to a different destructor vtable
    this->vtable1 = &PTR_LAB_00d7d480;  // +0x0C

    // Clear a global flag (possibly reference count or initialization flag)
    g_someGlobalFlag = 0;  // DAT_011299a4

    // Final cleanup call (possibly global destructor or static deinit)
    GlobalCleanup::perform();  // FUN_004083d0
}