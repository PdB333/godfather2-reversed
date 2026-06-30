// FUNC_NAME: SimManager::destroyAllObjects
void __thiscall SimManager::destroyAllObjects(SimManager* thisPtr)
{
    // thisPtr layout:
    // +0x00: firstObject (pointer to head of singly-linked list)
    // +0x0C: specialObject (pointer to a singular object)
    // +0x10: vtable (pointer to function table for objects in list)
    SimObject* currentObject = thisPtr->firstObject;
    while (currentObject != nullptr)
    {
        SimObject* nextObject = currentObject->next; // next pointer at offset +0x04
        // Call second vtable function (destroy) on each object with flag=0
        thisPtr->vtable->destroy(currentObject, 0);
        currentObject = nextObject;
    }
    if (thisPtr->specialObject != nullptr)
    {
        // Also destroy the special object
        thisPtr->vtable->destroy(thisPtr->specialObject, 0);
    }
    // Call fourth vtable function (finalize) on the manager itself
    thisPtr->vtable->finalize();
}