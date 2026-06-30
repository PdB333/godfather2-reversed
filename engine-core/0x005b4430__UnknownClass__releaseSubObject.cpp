// FUNC_NAME: UnknownClass::releaseSubObject
// Function address: 0x005b4430
// Role: Releases a sub-object at offset 0x220 from this pointer.
// Calls a helper function (FUN_005b4540) and then a function pointer (likely operator delete or virtual destructor).

void __thiscall UnknownClass::releaseSubObject(void) {
    // Assuming this is a member function (in_EAX is this)
    // Offset 0x220 likely points to a dynamically allocated sub-object
    int* subObject = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x220); // +0x220: sub-object pointer or base

    // Call cleanup/destructor on the sub-object
    FUN_005b4540(subObject);

    // Call a function pointer on the same sub-object (likely operator delete or virtual destructor)
    // DAT_0119cb68 is a global function pointer (probably for memory deallocation or finalize)
    ((void (*)(int*))DAT_0119cb68)(subObject);
}