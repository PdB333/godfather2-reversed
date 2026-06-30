// FUNC_NAME: updateAllRegisteredObjects

// Function at 0x00698760: Iterates over a global array of objects and calls their virtual update method (second vtable entry).
// Used to tick a set of registered objects, likely part of a manager or framework update loop.
// Called from multiple locations (0x0068d010, 0x00697680, 0x00988070, 0x009246a0) indicating it's a core update mechanism.

void updateAllRegisteredObjects(void)
{
    // Global pointers to start and end of the registered object array.
    // DAT_01129f8c and DAT_01129f90 are static global variables.
    unsigned int** pCurrent = DAT_01129f8c;  // pointer to start of array of object pointers
    unsigned int** pEnd = DAT_01129f90;      // pointer to end of array

    while (pCurrent != pEnd)
    {
        // Each element is a pointer to an object. The object's first 4 bytes are its vtable pointer.
        // The second virtual function (offset +4 from vtable base) is the update function.
        // Typically this is the 'update' or 'process' method.
        unsigned int* vtable = (unsigned int*)(*pCurrent);  // object's vtable pointer
        void (*updateFunc)(void) = (void (*)(void))vtable[1]; // second virtual function (index 1)
        updateFunc();                                        // call the update

        pCurrent++;
    }
    // No return value.
}