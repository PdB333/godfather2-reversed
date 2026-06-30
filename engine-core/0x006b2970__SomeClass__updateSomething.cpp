// FUNC_NAME: SomeClass::updateSomething
void __fastcall SomeClass::updateSomething(int thisPtr)
{
    undefined1 local_8;
    undefined1 uStack_7;
    undefined2 uStack_6;
    undefined1 uStack_4;
    undefined1 uStack_3;
    
    // Check if pointer at +0x19c is non-null
    if (*(int *)(thisPtr + 0x19c) != 0) {
        // Call function to get some data from +0x40
        FUN_008c76a0(&local_8, *(undefined4 *)(thisPtr + 0x40));
        
        // Call function with constructed parameters from local data
        FUN_0094ac00(
            *(undefined4 *)(thisPtr + 0x19c),
            CONCAT22(uStack_6, CONCAT11(uStack_7, local_8)),
            CONCAT13(uStack_4, CONCAT21(uStack_6, uStack_7)),
            CONCAT13(uStack_3, CONCAT12(uStack_4, uStack_6))
        );
    }
    return;
}