// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(void)
{
    // unaff_ESI likely points to 'this' object
    int thisPtr = unaff_ESI;
    // Stack variable for a structure or buffer
    undefined1 *stackBufferPtr;
    int stackVar1;
    undefined4 stackVar2;
    undefined1 localBuffer [12];
    undefined4 localVar1;
    undefined4 localVar2;
    undefined4 stackVar3;
    undefined4 stackVar4;
    undefined4 localVar3;
    undefined1 anotherBuffer [8];
    undefined4 localVar4;
    undefined4 stackVar5;
    undefined4 stackVar6;
    undefined4 stackVar7;
    undefined4 stackVar8;
    
    stackVar2 = 1; // Some flag or count set to 1
    stackVar1 = thisPtr + 0x48; // +0x48: offset to some member
    stackBufferPtr = localBuffer; // Initialize pointer to local buffer
    localVar1 = 0; // Clear local variables
    localVar2 = 0;
    localVar3 = 0;
    localVar4 = DAT_00e2b1a4; // Global data reference
    
    // Call a virtual function at offset 0x90 from vtable at this+0x44
    // +0x44: pointer to vtable or another object
    (**(code **)(**(int **)(thisPtr + 0x44) + 0x90))();
    
    // Copy stack variables into another set
    stackVar5 = stackVar3;
    stackVar6 = stackVar4;
    stackVar7 = localVar3;
    stackVar8 = DAT_00e2b1a4;
    
    // Call function with stackBufferPtr and anotherBuffer as parameters
    FUN_004b59d0(&stackBufferPtr, anotherBuffer);
    
    // Call function with this pointer
    FUN_00aa1fc0(thisPtr);
    
    // Check if a member at +0x40 is non-zero and call another function
    if (*(int *)(thisPtr + 0x40) != 0) {
        FUN_009f4cd0(anotherBuffer);
    }
    
    return;
}