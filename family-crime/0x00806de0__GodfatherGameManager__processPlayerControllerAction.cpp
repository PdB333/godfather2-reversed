// FUNC_NAME: GodfatherGameManager::processPlayerControllerAction
void __fastcall GodfatherGameManager::processPlayerControllerAction(GodfatherGameManager* this)
{
    char cVar1;
    int iVar2;
    int uVar3;
    void* componentPtr;
    void* baseObj;
    void* innerBaseObj;
    void* innerPtr;
    
    // Check if a specific component pointer exists and is valid (not 0x48 sentinel)
    componentPtr = *(void**)((char*)this + 0x74c);
    if ((componentPtr != NULL) && (componentPtr != (void*)0x48)) {
        // Adjust pointer to get the base of the component object (offset -0x48)
        baseObj = (void*)((char*)componentPtr - 0x48);
        
        // Check if component has an active flag (byte at +0x1a8)
        if (*(char*)((char*)baseObj + 0x1a8) == '\x01') {
            // Get inner component pointer at +0x68
            innerPtr = *(void**)((char*)baseObj + 0x68);
            if ((innerPtr != NULL) && (innerPtr != (void*)0x48)) {
                innerBaseObj = (void*)((char*)innerPtr - 0x48);
                // Call virtual function at vtable+0x88 (likely "update" or "process")
                (*(void (__thiscall**)(void*))(*(int*)innerBaseObj + 0x88))(innerBaseObj);
            }
        }
        
        // Call an intermediate helper function (likely debug/log)
        FUN_00707a40();
        
        // Call virtual function at vtable+0x17c on the base component with argument 0
        (*(void (__thiscall**)(void*, int))(*(int*)baseObj + 0x17c))(baseObj, 0);
    }
    
    // Set a global state value at huge offset (0x1eb8)
    *(int*)((char*)this + 0x1eb8) = DAT_01205224;
    
    // Check input condition (e.g., controller button pressed)
    cVar1 = FUN_00481660();
    if (cVar1 != '\0') {
        // Allocate a small structure (0x38 bytes, possibly input event data)
        iVar2 = FUN_009c8e50(0x38);
        if (iVar2 != 0) {
            // Create/initialize the structure using this object
            uVar3 = FUN_008018b0(this);
            // Submit the allocated structure to some queue/handler
            FUN_00481690(uVar3);
            return;
        }
        // Allocation failed, submit NULL
        FUN_00481690(0);
    }
    return;
}