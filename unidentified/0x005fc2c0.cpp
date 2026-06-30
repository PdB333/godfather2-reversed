// FUN_NAME: SomeClass::copyFrom
void __thiscall SomeClass::copyFrom(int *thisPtr, int sourcePtr)
{
    // Call base class constructor (vtable[2]) on this
    (**(code (__thiscall **)(int *))(*thisPtr + 8))(thisPtr);

    int refValue;
    if (sourcePtr == 0) {
        refValue = 0;
    } else {
        refValue = FUN_004265d0(sourcePtr, thisPtr); // AddRef on source
    }

    FUN_005fc510(thisPtr, refValue); // assign internal data

    // Store this pointer at offset 8 of the object returned by base constructor
    *(int **)(in_EAX + 8) = thisPtr;

    // Call base class virtual function again (likely another init or release)
    (**(code (__thiscall **)(int *))(*thisPtr + 8))();

    if (sourcePtr != 0) {
        refValue = FUN_004265d0(sourcePtr, *(int *)(in_EAX + 8));
        *(int *)(in_EAX + 0xc) = refValue;
        (**(code (__thiscall **)(int *, int))(*(int *)thisPtr + 4))(sourcePtr, 0);
        (**(code (__thiscall **)(int *))(*(int *)thisPtr + 0xc))();
        return;
    }
    *(int *)(in_EAX + 0xc) = 0;
    (**(code (__thiscall **)(int *))(*(int *)thisPtr + 0xc))();
}