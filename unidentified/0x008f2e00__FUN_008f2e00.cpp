// FUNC_NAME: SomeManager::resetState
void __thiscall SomeManager::resetState(int this[/*?*/])
{
    int state; // param_1[3] at offset +0x0C
    void** vtable;
    int result;
    void* childObject;

    this[7] = 0; // +0x1C: reset some field to zero

    state = this[3]; // +0x0C: current state/value

    if (state == 7) {
        FUN_009ca8f0(); // state 7: call some global reset function
    }
    else if (state == 8) {
        // Cleanup for state 8
        childObject = (void*)this[0xB]; // +0x2C: pointer to a sub-object
        // Call a virtual function at vtable index 0 on the sub-object with argument 0
        (*(void (**)(void*, int)) * (void**)childObject)(childObject, 0);

        // Get class descriptor from this[0xA] (+0x28), then call a deallocation function (offset +4)
        // with the sub-object pointer and size 0x3C
        (*(void (**)(void*, int)) ( *(int*)this[0xA] + 4 ))(childObject, 0x3C);

        this[0xB] = 0; // Clear the pointer
    }

    // Call a virtual function from this object's vtable at offset 0x2C (index 11)
    vtable = *(void***)this;
    result = (*(int (**)(void)) (vtable[0x2C / 4]))(); // returns an integer

    // Process result
    FUN_008f2cf0(result);
}