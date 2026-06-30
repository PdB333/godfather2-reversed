// FUNC_NAME: SimManager::addObject
void __thiscall SimManager::addObject(int *this, undefined4 someParam, undefined4 unusedParam, undefined4 objectType)
{
    int *globalCounterPtr; // DAT_012234ac - global object ID counter manager
    int objectPtr; // newly created object
    int allocationInfo; // from object type
    code *vtable; // object's vtable

    // Get global counter manager (likely a singleton)
    globalCounterPtr = (int *)DAT_012234ac;
    
    // Get allocation info for the given object type
    allocationInfo = getObjectAllocationInfo(objectType); // FUN_00621530
    
    // Retrieve the object's vtable from allocation info
    vtable = (code *)getObjectVTable(*(undefined4 *)(allocationInfo + 8)); // FUN_00621610
    
    // Call the object's constructor (vtable[0]) with objectType and 0
    objectPtr = (*vtable)(objectType, 0);
    
    // Assign a unique ID from the global counter (offset +0x8 in global struct)
    *(undefined4 *)(objectPtr + 0x2c) = *(undefined4 *)(globalCounterPtr + 2); // +0x8 = nextId
    // Increment the global counter
    globalCounterPtr[2] = globalCounterPtr[2] + 1;
    
    // Set object's owner/manager reference (offset +0x4) to this->someField (offset +0x4 in SimManager)
    *(int *)(objectPtr + 4) = this[1]; // this+0x4
    
    // Call virtual function at vtable+0x10 (likely onObjectAdded)
    (**(code **)(*this + 0x10))(objectPtr);
    
    // Call virtual function at vtable+0x18 (likely notifyListeners) with return address and someParam
    (**(code **)(*this + 0x18))(unaff_retaddr, someParam, objectPtr);
    
    return;
}