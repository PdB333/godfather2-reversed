// FUNC_NAME: ParticleSystem::emitNode

void ParticleSystem::emitNode(int *param_1) // param_1 is actually a pointer to a found entity, not this
{
    // Check if any of the four render targets (textures) are set
    if ((m_renderTarget[0] != 0) || (m_renderTarget[1] != 0) || 
        (m_renderTarget[2] != 0) || (m_renderTarget[3] != 0))
    {
        uint flags = m_flags; // +0xE4
        byte shiftBit;
        
        // Determine shift based on global config pointer
        if ((g_renderConfig != 0) && (*(int *)(g_renderConfig + 0xC) != 0))
            shiftBit = (byte)(flags >> 6);
        else
            shiftBit = (byte)(flags >> 7);
        
        // Proceed only if the selected bit is clear
        if ((~shiftBit & 1) != 0)
        {
            int *foundEntity = param_1;
            
            // If bit 1 of flags is clear, search for a source entity
            if ((flags >> 1 & 1) == 0)
            {
                // Check if all four source pointers are null
                if ((m_source[0] == 0) && (m_source[1] == 0) && 
                    (m_source[2] == 0) && (m_source[3] == 0))
                {
                    foundEntity = 0;
                }
                else
                {
                    // Iterate through source list, find entity with hash
                    int iter = iterateList(m_source, 0); // +0xD4 is first element
                    int *entity = 0;
                    if (iter != 0)
                    {
                        findEntityWithHash(iter, 0x38523fc3, &entity);
                        while (entity != 0)
                        {
                            // Check if entity has specific flag at +0x30
                            if ((entity[0x19] == 0) || ((*(uint *)(entity[0x19] + 0x30) >> 1 & 1) == 0))
                                break;
                            iter = iterateList(m_source, iter);
                            findEntityWithHash(iter, 0x38523fc3, &entity);
                        }
                        foundEntity = entity;
                    }
                }
            }
            
            // Optional transform matrix from m_tint (if bit 24 set)
            undefined4 *tintMatrix = 0;
            if ((flags >> 0x18 & 1) != 0)
            {
                local_60 = *(undefined4 *)(this + 0xEC); // +0xEC
                local_5c = *(undefined4 *)(this + 0xF0); // +0xF0
                local_58 = *(undefined4 *)(this + 0xF4); // +0xF4
                local_54 = g_globalAlpha; // DAT_00e2b1a4
                tintMatrix = &local_60;
            }
            
            // Two main branches based on flag bit 2
            if (((flags >> 2 & 1) == 0) || (foundEntity == 0))
            {
                // Branch A: Create new node from matrix and optional tint
                // Copy the 4x4 matrix from +0x80 to local buffer
                undefined4 local_50 = *(undefined4 *)(this + 0x80);
                uStack_4c = *(undefined4 *)(this + 0x84);
                uStack_48 = *(undefined4 *)(this + 0x88);
                uStack_44 = *(undefined4 *)(this + 0x8C);
                local_40 = *(undefined4 *)(this + 0x90);
                uStack_3c = *(undefined4 *)(this + 0x94);
                uStack_38 = *(undefined4 *)(this + 0x98);
                uStack_34 = *(undefined4 *)(this + 0x9C);
                local_30 = *(undefined4 *)(this + 0xA0);
                uStack_2c = *(undefined4 *)(this + 0xA4);
                uStack_28 = *(undefined4 *)(this + 0xA8);
                uStack_24 = *(undefined4 *)(this + 0xAC);
                local_20 = *(undefined4 *)(this + 0xB0);
                uStack_1c = *(undefined4 *)(this + 0xB4);
                uStack_18 = *(undefined4 *)(this + 0xB8);
                uStack_14 = *(undefined4 *)(this + 0xBC);
                
                if (tintMatrix != 0)
                {
                    applyTintToMatrix(this + 0x80, tintMatrix, &local_20); // FUN_0056b420
                    foundEntity = (int *)extraout_EDX; // regression?
                }
                
                undefined4 renderTarget;
                if (foundEntity == 0)
                    renderTarget = *(undefined4 *)(this + 0xF8); // +0xF8: default render target
                else
                    renderTarget = foundEntity->vtable[0x58](); // virtual getRenderTarget
                
                int newListNode = 0;
                allocateListNode(&newListNode, this + 0xC0, &local_50, renderTarget, 0, &newListNode); // FUN_004df270
                
                // Update linked list at +0xD0
                int *listHead = this + 0xD0; // +0xD0
                if (*(int *)(this + 0xD0) != 0)
                {
                    *(undefined4 *)(*(int *)(this + 0xD0) + 8) = 0;
                    *listHead = 0;
                }
                *listHead = newListNode;
                if (newListNode != 0)
                    *(int **)(newListNode + 8) = listHead;
            }
            else
            {
                // Branch B: Use entity and tint to create node
                undefined4 result = createOrUpdateNode(&local_68, this + 0xC0, foundEntity, 
                                                       *(undefined4 *)(this + 0xE8), tintMatrix); // FUN_00475550
                releaseResource(result); // FUN_00414db0
                if (local_68 != 0)
                {
                    *(undefined4 *)(local_68 + 8) = 0;
                    return;
                }
            }
        }
    }
    return;
}