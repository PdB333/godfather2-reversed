// FUNC_NAME: RefCountedObject::conditionalRelease
// Address: 0x004f2ce0
// This function is part of EA's EARS engine intrusive reference counting.
// It decrements the reference count of a managed object (with vtable at +0x00 and refcount at +0x04)
// after checking a condition via a virtual function at vtable+0x08.
// Returns a non-null pointer if the condition was true (indicating the release was "successful"),
// or null if false. The returned pointer points to a local dummy variable (treated as a success flag).

typedef bool (__fastcall* ConditionCheckFunc)(int param); // vtable[2]
typedef void (__fastcall* DestructorFunc)();             // vtable[1]

void* __fastcall RefCountedObject::conditionalRelease(int param2, int* pManagedObject)
{
    static int dummyFlag = 0;  // dummy stack-like variable, used for pointer return

    if (pManagedObject == nullptr)
        return nullptr;

    // pManagedObject[0] is vtable pointer
    void** vtable = *(void***)pManagedObject;

    // Call condition check virtual function (vtable offset 0x08)
    ConditionCheckFunc checkCondition = (ConditionCheckFunc)vtable[2];
    bool conditionSatisfied = checkCondition(param2);

    // Decrement reference count at pManagedObject[1] (offset +0x04)
    int* refCount = &pManagedObject[1];
    (*refCount)--;

    // If refcount reached zero, call destructor (vtable offset 0x04)
    if (*refCount == 0)
    {
        DestructorFunc destroy = (DestructorFunc)vtable[1];
        destroy();
    }

    // Return a non-null pointer to indicate "success" when condition satisfied
    // (the actual address is not meaningful; caller only checks for null/non-null)
    if (conditionSatisfied)
        return (void*)&dummyFlag;
    else
        return nullptr;
}