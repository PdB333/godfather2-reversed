// FUNC_NAME: SomeClass::initializeOrSomething
void __fastcall SomeClass::initializeOrSomething(int thisPtr)
{
    byte local_24[16];
    byte local_14;
    undefined *local_c;

    // Check if bit 1 (0x2) of the flags at offset +0x1a4 is not set
    if ((*(byte *)(thisPtr + 0x1a4) & 2) == 0) {
        // Call a function with thisPtr as argument
        FUN_0072de20(thisPtr);
        
        // Set local_14 to 1 (likely a boolean)
        local_14 = 1;
        
        // Set local_c to point to some global data at 0x00e545b8
        local_c = &DAT_00e545b8;
        
        // Call a function that takes local_24 as a parameter (likely a struct initialization)
        FUN_0081dab0(local_24);
        
        // Set bit 1 (0x2) in the flags at offset +0x1a4
        *(uint *)(thisPtr + 0x1a4) = *(uint *)(thisPtr + 0x1a4) | 2;
        
        // Call another function (no arguments)
        FUN_0072c130();
    }
    return;
}