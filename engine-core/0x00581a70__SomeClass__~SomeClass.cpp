// FUNC_NAME: SomeClass::~SomeClass

void __fastcall SomeClass::~SomeClass(SomeClass* this)
{
    // Set vtable to the destructor version (typically points to the correct vtable for this class)
    this->vtable = reinterpret_cast<SomeClassVTable*>(&PTR_FUN_00e3ac24);

    // Retrieve sub-object stored at offset 0x64 (0x19 * 4)
    SomeSubObject* subObj = reinterpret_cast<SomeSubObject*>(this->field_0x64);

    if (subObj != nullptr)
    {
        // Call virtual method at index 1 on the sub-object with argument 0 (likely Release() or similar)
        subObj->vtable->method1(subObj, 0);

        // If there is a second-level sub-object at offset 0x0C from subObj, release it as well
        if (subObj->field_0x0C != nullptr)
        {
            subObj->field_0x0C->vtable->method1(subObj->field_0x0C, 0);
        }

        // Call virtual method at index 3 (destructor or cleanup) on the sub-object
        subObj->vtable->method3();

        // Call a global singleton's release method (vtable index 1) on the sub-object
        // DAT_0120556c points to a singleton object with its own vtable
        SomeSingleton* singleton = reinterpret_cast<SomeSingleton*>(DAT_0120556c);
        singleton->vtable->method1(subObj, 0);
    }
}