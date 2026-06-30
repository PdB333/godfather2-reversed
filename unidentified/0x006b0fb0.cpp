// FUN_006b0fb0: SomeClass::checkAndExecute
void SomeClass::checkAndExecute(undefined4 param_1) {
    int iVar1;
    
    // Check if condition is met (returns non-zero if true)
    iVar1 = FUN_006b0ee0(param_1);  // SomeClass::shouldProcess
    if (iVar1 != 0) {
        FUN_006b5040();              // SomeClass::executeAction
    }
    return;
}