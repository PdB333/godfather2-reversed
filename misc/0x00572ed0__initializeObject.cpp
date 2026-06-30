// FUNC_NAME: initializeObject
void initializeObject(void) {
    // Stack-based temporary structure, likely used for some identifier or initialization data
    int local_c[3] = {0, 0, 0}; // Equivalent to local_c, local_8, local_4

    // Clear first two fields of the object pointed by ESI (assumed to be 'this')
    int *self = someGlobalOrRegister; // unaff_ESI points to the object being initialized
    self[0] = 0;                      // +0x00
    self[1] = 0;                      // +0x04

    // Call helper function (could be creating a unique ID or allocating a resource)
    int result = FUN_004265d0(&local_c);
    self[2] = result;                 // +0x08 - store result (e.g., resource handle)

    // Set the vtable pointer or base object reference
    void *baseObj = someOtherRegister; // unaff_EDI points to a base object (or vtable)
    self[3] = (int)baseObj;           // +0x0C - store base object pointer

    // Call a virtual function on the base object (offset 8 in vtable, i.e., third virtual function)
    (*(void (__thiscall**)(void*))(*(int*)baseObj + 8))(baseObj);
}