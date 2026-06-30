// FUNC_NAME: AnimationManager::updateAnimations
void AnimationManager::updateAnimations()
{
    // Determine delta time for this frame.
    float deltaTime;
    if (gGlobalTime <= gMaxTimeThreshold) {
        deltaTime = gDefaultDelta;
    } else {
        deltaTime = gTimeScaleFactor / gGlobalTime;
    }

    // Store current frame time from time manager.
    uint32_t frameTime = *(uint32_t*)(gTimeManager + 0x24);

    // Handle pending attach/detach operation.
    int* pendingSource = *(int**)(this + 0x1c);
    if (pendingSource != nullptr &&
        *(int*)(pendingSource + 8) == 0 &&
        *(int**)(this + 0x20) != nullptr) 
    {
        int* child = *(int**)(pendingSource + 0x10);
        *(int**)(child + 0x18) = *(int**)(this + 0x20); // Attach child to target
        *(uint8_t*)(child + 0x48) = 1;                   // Mark as updated
        FUN_00558b70();                                  // Trigger update event
        FUN_009e7450(pendingSource);                     // Release source object
    }

    // Iterate over the array of 0x70-byte entities.
    int** arrayHeader = *(int***)(this + 4);
    int* basePtr = *arrayHeader;
    int count = arrayHeader[1];
    int* endPtr = basePtr + count * 0x70;

    for (int* entity = basePtr; entity != endPtr; entity += 0x70) 
    {
        // Check if the entity's internal object is still active (indicated by field +8 == 0)
        int* obj = *(int**)(entity + 0x40);
        if (obj != nullptr && *(int*)(obj + 8) == 0) 
        {
            // Advance animation by delta time
            FUN_005570a0(deltaTime);

            // Get the entity's object pointer again (may have changed after update)
            obj = *(int**)(entity + 0x40);
            if (obj != nullptr) 
            {
                // Check the object's 'name string' via a global string manager
                void* stringMgr = (*(code**(*)(void))(**gStringTableVtable + 0x14))();
                uint32_t nameId = (*(code**(*)(void*, int))(*((int*)stringMgr) + 0x10))(obj);
                char* nameStr = (char*)FUN_00ab06f0(&uStack_12, nameId);
                if (*nameStr != '\0') 
                {
                    // Non-empty name: release the object and continue to next entity
                    if (obj != nullptr) {
                        FUN_009e7450(obj);
                    }
                    continue;
                }

                // Check again (redundant, but matches original logic)
                obj = *(int**)(entity + 0x40);
                if (obj != nullptr) 
                {
                    void* stringMgr2 = (*(code**(*)(void))(**gStringTableVtable + 0x14))();
                    uint32_t nameId2 = (*(code**(*)(void*, int))(*((int*)stringMgr2) + 0x10))(obj);
                    char* nameStr2 = (char*)FUN_00ab06f0(&uStack_11, nameId2);
                    if (*nameStr2 == '\0') 
                    {
                        // Empty name: skip setActive call
                        continue;
                    }
                }

                // If name is non-empty and we reached here, set the object active?
                if (obj != nullptr) {
                    FUN_009e6ff0(obj, 1);
                }
            }
        }
    }
}