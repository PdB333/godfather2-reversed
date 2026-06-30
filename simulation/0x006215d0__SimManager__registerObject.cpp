// FUNC_NAME: SimManager::registerObject
void __thiscall SimManager::registerObject(int thisPtr, int objectKey, int initData)
{
    int managerPtr;
    code *virtualFunc;

    // Resolve the object manager or factory from the key (e.g., object type or template ID)
    managerPtr = FUN_00621530(objectKey);

    // Get the virtual function pointer from the manager's function table at offset +8
    // (likely a virtual function table or dispatch table)
    virtualFunc = (code *)FUN_00621610(*(int *)(managerPtr + 8));

    // Call the virtual function to create or initialize the object, returns the new object pointer
    int newObject = (*virtualFunc)(objectKey, initData);

    // Assign a unique ID from this manager's counter to the object at offset +0x2c
    *(int *)(newObject + 0x2c) = *(int *)(thisPtr + 8);

    // Increment the global ID counter for the next registration
    *(int *)(thisPtr + 8) = *(int *)(thisPtr + 8) + 1;
}