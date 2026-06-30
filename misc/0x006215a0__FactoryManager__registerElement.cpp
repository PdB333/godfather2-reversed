// FUNC_NAME: FactoryManager::registerElement
void __thiscall FactoryManager::registerElement(int thisPtr, int functorId, int arg1, int arg2) {
    // Get a function pointer (creator/functor) for the given ID
    code* creatorFunc = (code*)FUN_00621610(functorId);
    
    // Call the functor to create a new element
    int newElement = creatorFunc(arg1, arg2);
    
    // Store the current counter (next ID) into the new element at offset +0x2C
    *(int*)(newElement + 0x2C) = *(int*)(thisPtr + 8);
    
    // Increment the counter at thisPtr+0x08
    *(int*)(thisPtr + 8) = *(int*)(thisPtr + 8) + 1;
}