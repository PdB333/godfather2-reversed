// FUNC_NAME: ModelInstance::updateSkinIndices
void __thiscall ModelInstance::updateSkinIndices(void) {
    int* skinDataTable;
    int* skinPartData;
    short currentSkinIndex;
    int i;
    
    if (*(void**)(this + 0xB8) != nullptr) {  // +0xB8: mesh pointer (non-null means loaded)
        skinDataTable = *(int**)(this + 0x70);  // +0x70: pointer to skin data table
        currentSkinIndex = *(short*)(this + 0x76);  // +0x76: current skin part index (short)
        
        // Validate skin data table and current index
        if ((skinDataTable != nullptr) &&
            (*(int*)(skinDataTable + 0x18) > 0) &&      // +0x18: number of skin parts
            (*(int*)(skinDataTable + 0x1C) != nullptr)) // +0x1C: array of skin part data (0x18 bytes each)
        {
            if ((currentSkinIndex >= 0) && (currentSkinIndex < *(int*)(skinDataTable + 0x18))) {
                skinPartData = *(int**)(skinDataTable + 0x1C) + currentSkinIndex * 0x18;
            } else {
                skinPartData = nullptr;
            }
        } else {
            skinPartData = nullptr;
        }
        
        if (skinPartData != nullptr) {
            int influenceCount = *(int*)(skinPartData + 8);  // +0x08: number of influences for this part
            if (influenceCount > 0) {
                char* influenceIndices = *(char**)(this + 0xB4);  // +0xB4: array of influence indices
                for (i = 0; i < influenceCount; i++) {
                    if (influenceIndices[i] != -1) {
                        // Process this influence (e.g., update matrix weights)
                        FUN_00424470();  // Called with no explicit parameters; probably uses global state or "this" via thread-local
                    }
                }
            }
        }
    }
}