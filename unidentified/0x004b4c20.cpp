// FUN_004b4c20: GameObject::createSubObject
void GameObject::createSubObject(uint param_1)
{
    int pNewObj = allocateMemory(0x520);
    if (pNewObj != 0) {
        // Initialize the new object with parent's ID (at this+0x0C) and the given parameter
        pNewObj = initializeObject(*(int*)(this + 0x0C), param_1, 0, 0, 0, 0);
    }
    // Store pointer to the created sub-object at this+0x40
    *(int*)(this + 0x40) = pNewObj;
    // Initialize fields in the sub-object
    *(byte*)(pNewObj + 0x46D) = 0;            // +0x46D: byte flag (0 = inactive?)
    *(int*)(pNewObj + 0x494) = 0x7FFFFFFF;    // +0x494: large value (e.g., infinite time, max priority)
    *(int*)(pNewObj + 0x490) = 0;             // +0x490: counter or state
    // Set vtable and back-pointer to parent
    *(void**)(pNewObj + 0x4AC) = (void*)&vtable_004b4bf0;  // +0x4AC: vtable pointer
    *(int*)(pNewObj + 0x4B0) = (int)this;                  // +0x4B0: parent pointer
}