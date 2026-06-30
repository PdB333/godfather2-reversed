// FUNC_NAME: SomeClass::initializeFromData
undefined1 __thiscall SomeClass::initializeFromData(undefined4 *this, undefined4 dataPtr)
{
    undefined1 *pLocalString;
    undefined4 result;
    undefined1 retValue;
    undefined1 *localString;          // pointer to string data (might be allocated)
    int localFlag;                    // flag indicating success/failure of previous steps
    code *localDestructor;            // destructor function pointer for localString

    retValue = 0;                     // default failure
    FUN_004d3bc0(dataPtr);            // parse/validate input data
    FUN_004d54c0();                   // global state initialization (e.g., reset counters)
    FUN_004d5900(1);                  // set some global flag to 1

    if (localFlag != 0)               // if the previous steps succeeded
    {
        pLocalString = localString;
        if (localString == (undefined1 *)0x0)
        {
            pLocalString = &DAT_0120546e;   // default string constant (e.g., "default")
        }
        result = FUN_004dafd0(pLocalString); // lookup or create entity by name
        this[0] = result;                    // copy result into 4 consecutive fields
        this[1] = result;
        this[2] = result;
        this[3] = result;                    // likely an array/struct of 4 identical values (e.g., RGBA, quaternion)
        retValue = 1;                        // success
    }
    if (localString != (undefined1 *)0x0)
    {
        (*localDestructor)(localString);     // free allocated string if needed
    }
    return retValue;
}