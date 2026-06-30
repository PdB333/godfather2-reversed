// FUNC_NAME: Entity::reloadRenderData
void Entity::reloadRenderData(Entity* this)
{
    int* existingRenderData;
    int* ptr;
    void* memoryMgr;
    int newRenderData;
    uint someHandle;
    struct {
        uint field0;  // +0x0: alignment flag? (2)
        uint field4;  // +0x4: size flag? (0x10)
        uint field8;  // +0x8: unknown (0)
    } allocParams;
    
    // Clean up existing render data if present (offset +0x218)
    existingRenderData = (int*)this->renderDataPtr; // this[0x86]
    if (existingRenderData != nullptr) {
        this->renderDataPtr = (int*)existingRenderData; // preserve? no, param_1 reused
        FUN_00463520(&this->renderDataPtr); // likely destroyRenderData
        FUN_00518ff0(this);
        FUN_00570530();
        memoryMgr = (void*)FUN_009c8f80(); // MemoryManager::getInstance()
        // Call a cleanup virtual method on the render data object (vtable+4)
        (**(code**)(*memoryMgr))(this->renderDataPtr, 0); // actually memoryMgr is not renderData, but piVar2 was used differently; recheck.
    }
    
    // Allocate new render data (size 0x3b0)
    memoryMgr = (void*)FUN_009c8f80();
    allocParams.field0 = 2;
    allocParams.field4 = 0x10;
    allocParams.field8 = 0;
    newRenderData = (**(code**)*memoryMgr)(0x3b0, &allocParams); // Alloc(0x3b0, &params)
    this->renderDataPtr = newRenderData; // this[0x86]
    
    // Get some handle from a virtual method (vtable offset 0x17c = 95)
    someHandle = (**(code**)(*this + 0x17c))(); // likely getModelHandle()
    
    // Setup bounding box or similar using this[0x8c] (+0x230) and the handle
    FUN_00570060(this, this->boundingBoxData, someHandle); // this[0x8c]
    
    // Initialize the new render data object
    FUN_00462740(this->renderDataPtr);
    
    // Set a pointer in the render data object to point to this's sub-structure at offset +0x3c
    *(int**)(this->renderDataPtr + 0xbc) = &this->subStruct; // this + 0xf
    
    // If a flag (offset +0x164) is set, register a callback
    if (this->hasCallbackFlag != 0) { // this[0x59]
        uint valueFromRenderData = *(uint*)(this->renderDataPtr + 0x104);
        ptr = (int*)(DAT_01206880 + 0x14); // global callback list pointer
        **(int**)(DAT_01206880 + 0x14) = &PTR_LAB_0110b988; // set type info
        *ptr = *ptr + 4; // increment stored pointer?
        *(int**)*ptr = &this->someOtherSubStruct; // this + 0x15
        int iVar4 = *ptr;
        *(uint*)(iVar4 + 4) = valueFromRenderData;
        *ptr = iVar4 + 8;
    }
}