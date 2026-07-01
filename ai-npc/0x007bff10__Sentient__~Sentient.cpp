// FUNC_NAME: Sentient::~Sentient

void __fastcall Sentient::~Sentient(Sentient* thisObj)
{
    bool bVar1;
    int* ownerPtr;
    int* tempPtr;

    // Save pointer to owner/manager at +0x58
    ownerPtr = (int*)thisObj->field_0x58;
    
    // Set vtable for this class (derived destructor start)
    thisObj->vtable = (void*)&PTR_LAB_00d6e2b0;
    
    if (ownerPtr != nullptr) {
        // If component type is valid (not 0 or 0x48), destroy it
        if ((thisObj->componentType != 0) && (thisObj->componentType != 0x48)) {
            destroyComponent();
        }
        
        // Release allocated memory (e.g., component list)
        releaseMemory(0);
        
        // Check if owner has a specific flag (bit 1 at +0x74)
        if ((thisObj->flags >> 1 & 1) != 0) {
            // Call virtual function at vtable offset 0x25c on owner (likely unregister)
            (*(code**)(*ownerPtr + 0x25c))();
        }
        
        // Check if the object is still alive (first call)
        bVar1 = isObjectAlive();
        if (((bVar1) && (thisObj->childPtr != 0)) && (thisObj->childPtr != 0x48)) {
            // Second alive check
            bVar1 = isObjectAlive();
            if (bVar1) {
                // Get parent object by subtracting offset 0x48 from child pointer
                if (thisObj->childPtr == 0) {
                    tempPtr = nullptr;
                } else {
                    tempPtr = (int*)(thisObj->childPtr - 0x48);
                }
                // Call virtual to get a reference/pointer from parent
                tempPtr = (int*)(*(code**)(*tempPtr + 0x180))();
                if (ownerPtr == tempPtr) {
                    // Get parent again
                    if (thisObj->childPtr == 0) {
                        tempPtr = nullptr;
                    } else {
                        tempPtr = (int*)(thisObj->childPtr - 0x48);
                    }
                    // Call parent virtual to detach/remove component
                    (*(code**)(*tempPtr + 0x188))(ownerPtr);
                    // Get parent again
                    if (thisObj->childPtr == 0) {
                        tempPtr = nullptr;
                    } else {
                        tempPtr = (int*)(thisObj->childPtr - 0x48);
                    }
                    // Call parent virtual for final notification
                    (*(code**)(*tempPtr + 0x194))();
                }
            }
        }
        
        // Check if still initialized (e.g., not destroyed)
        bVar1 = isInitialized();
        if (bVar1) {
            // Mark as inactive (e.g., remove from active list)
            setActive(false);
        }
    }
    
    // Release handle at offset +0x80 if valid and global is set
    if ((thisObj->handle != -1) && (g_globalHandleManager != 0)) {
        closeHandle(&thisObj->handle);
    }
    
    // If flag bit 2 is clear and object is still initialized, call shutdown
    if (((thisObj->flags >> 2 & 1) == 0) && (bVar1 = isInitialized(), bVar1)) {
        shutdown();
    }
    
    // Release child pointer reference (smart pointer?)
    if (thisObj->childPtr != 0) {
        releaseReference(&thisObj->childPtr);
    }
    
    // Switch vtable to base class and call base destructor
    thisObj->vtable = (void*)&PTR_LAB_00d6b95c;
    BaseClass::~BaseClass();
    return;
}