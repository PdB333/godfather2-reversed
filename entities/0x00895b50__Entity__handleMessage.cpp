// FUNC_NAME: Entity::handleMessage
// Function at 0x00895b50: Event/message handler for entity class
// Uses a vtable at this-0x3c, slot 0x1c (presumably a virtual method)
// Event data structure: [int typeID, int* targetObject, ...]
void __thiscall Entity::handleMessage(void* this, int* eventData)
{
    unknownInit(eventData); // FUN_0046c6a0 - initialization of event data?
    // Check event type and global flag
    if (*eventData == kExpectedEventType && gSomeGlobalManager->someFlag != 0) 
    {
        int* targetObject = eventData[1];
        bool isActive = checkGameActiveFlag(); // FUN_00481620
        // Verify target object ID matches this's ID (offset +0x28)
        if (isActive && targetObject[2] == *(int*)((char*)this + 0x28)) 
        {
            // Call virtual function: vtable at this-0x3c, method index 0x1c (28)
            // Arguments: targetObject[4] and targetObject[5] (offset +0x10, +0x14)
            ((void (*)(int, int))(*(int*)(*(int*)((char*)this - 0x3c) + 0x1c)))
                (targetObject[4], targetObject[5]);
        }
    }
}