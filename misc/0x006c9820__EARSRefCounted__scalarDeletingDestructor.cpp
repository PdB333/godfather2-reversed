// FUNC_NAME: EARSRefCounted::scalarDeletingDestructor
void __fastcall EARSRefCounted::scalarDeletingDestructor(int* this)
{
    int* refCountPtr = (int*)(this[0x21]); // offset +0x84: pointer to ref count manager
    *this = (int)&PTR_FUN_00d5f060;       // set vtable for base class destructor
    this[2] = (int)&PTR_LAB_00d5f058;     // set secondary vtable pointer

    if (refCountPtr != nullptr) {
        FUN_009e7530(refCountPtr); // release reference on manager

        // Access the ref count data structure at offset +0x10 within the manager
        int* refCountData = *(int**)(refCountPtr + 0x10);
        if (*(short*)(refCountData + 1) != 0) { // check if weak/strong ref exists
            // decrement a counter at offset +6 (bytes) from the data
            *(short*)((int)refCountData + 6) -= 1;
            if (*(short*)((int)refCountData + 6) == 0) {
                // call a virtual deallocation function (operator delete variant)
                (**(code**)*refCountData)(1);
            }
        }
        FUN_009f01a0(); // free the manager memory
    }
    FUN_00473a60(); // base class cleanup (e.g., ~EARSObject)
}