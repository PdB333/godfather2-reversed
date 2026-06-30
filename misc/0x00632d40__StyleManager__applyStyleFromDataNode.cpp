// FUNC_NAME: StyleManager::applyStyleFromDataNode
void __thiscall StyleManager::applyStyleFromDataNode(Style* pStyle) {
    // this: pointer to StyleManager instance (in_EAX)
    // pStyle: output style structure to fill (param_1)
    
    // Access internal data node pointer at offset +0x04 from this
    DataNode* pDataNode = *(DataNode**)((int)this + 4);
    
    // Check flag at offset +0x06 of data node
    if (pDataNode->flag == 0) {  // flag = 0: use standard style
        // Read pointer from data node's linked structure at offset +0x0c
        Something* pSomething = *(Something**)((int)pDataNode + 0xc);
        
        // Set pStyle->colorInfo (offset +0x10) = pSomething->baseColor + 0x10
        pStyle->colorInfo = (ColorInfo*)(pSomething->baseColor + 0x10);  // +0x20 field
        // Set pStyle->textureIndex (offset +0x1c) from pSomething->textureId (offset +0x3c)
        pStyle->textureIndex = pSomething->textureId;
        
        // Choose between two global color material sets based on textureIndex
        if (pStyle->textureIndex != 0) {
            pStyle->materialSet = &globalMaterialSet1;      // DAT_00e37bec
        } else {
            pStyle->materialSet = &globalMaterialSet0;      // DAT_00e41eb8
        }
    } else {
        // flag != 0: use fallback style
        pStyle->colorInfo = &fallbackColorInfo;             // DAT_00e41eac
        pStyle->textureIndex = -1;
        pStyle->materialSet = &fallbackMaterialSet;         // DAT_00e41eb4
    }
    
    // Initialize a sub-structure at offset +0x20 using colorInfo
    initializeStyleSubStruct(&pStyle->subStyle, pStyle->colorInfo);  // FUN_00636c20
}