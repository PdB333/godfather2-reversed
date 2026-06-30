// FUNC_NAME: DelegateInvoker::callWithThisCopy
void __fastcall DelegateInvoker::callWithThisCopy(void* thisPointer) {
    void* thisCopy = thisPointer;  // store a copy of this pointer for later use
    void* functionPointer = FUN_004dafd0(thisPointer, &thisCopy);  // resolve function pointer or delegate
    FUN_005e9d90(functionPointer, &thisCopy);  // invoke the resolved delegate with the this copy
    return;
}