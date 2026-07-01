// FUNC_NAME: CharacterRender::renderBoneMesh
// Address: 0x007cd190
// Role: Sets up rendering state for a character bone/mesh based on a render context.
// Uses this->field_1b4 as a pointer to owner data, this->field_1bc as a mesh table,
// and this->field_1d6 as a bone index selector.

void CharacterRender::renderBoneMesh(RenderContext* ctx)
{
    int* ownerBase;
    int index;
    int meshHandle;
    int secondMeshHandle;
    int ctxBoneIndex;

    // Resolve owner object (subtract 0x48 from the pointer at field_1b4)
    if (this->field_1b4 != 0) {
        ownerBase = (int*)((char*)this->field_1b4 - 0x48);
    } else {
        ownerBase = 0;
    }
    // Fetch some data table from owner at offset 0x1f3c and store locally
    this->field_1bc = (int)(ownerBase ? *(int*)((char*)ownerBase + 0x1f3c) : 0);
    if (this->field_1bc == 0) {
        return;
    }

    // Context provides a skeleton/mesh block at offset 0x10
    int* ctxSkeleton = *(int**)((char*)ctx + 0x10);
    int hasMeshList = *(int*)(this->field_1bc + 0x30);
    ctxBoneIndex = *(int*)((char*)ctxSkeleton + 8); // bone index from context

    meshHandle = 0;
    if (hasMeshList != 0 && ctxBoneIndex >= 0) {
        // Determine index into the mesh table
        if (*(int*)(this->field_1bc + 0x18) == 0 || *(int*)(this->field_1bc + 0x14) <= ctxBoneIndex) {
            index = 0;
        } else {
            index = Func_006eca80(this + 0x1d6); // e.g., getBoneIndex(this->field_1d6)
        }
        // Access 12‑byte entry in the mesh slot table at offset 0x1c
        int* meshSlotTable = *(int**)(this->field_1bc + 0x1c);
        if (meshSlotTable != 0) {
            int* entry = meshSlotTable + index * 3; // each entry is 12 bytes
            if (entry != 0) {
                int meshIdx = entry[0];
                if (meshIdx == -1) {
                    // Default mesh from the head of the mesh list
                    meshHandle = **(int**)(*(int*)(this->field_1bc + 0x30)) + 0x10;
                } else {
                    meshHandle = *(int*)(*(int*)(*(int*)(this->field_1bc + 0x30) + meshIdx * 4) + 0x10);
                }
            }
        }
    } else {
        // Fallback: use context's bone transform directly
        Func_007cae10(*(int*)((char*)ctxSkeleton + 0x10), this + 0x1d6);
    }

    // Apply materials/shader from context
    int materialA = *(int*)((char*)ctxSkeleton + 0x18);
    int materialB = *(int*)((char*)ctxSkeleton + 0x14);
    Func_007cbf50(meshHandle);              // set mesh
    Func_007cbfa0(materialB, materialA);   // set material pair
    Func_007cb110((*(uint*)((char*)ctxSkeleton + 0x20) >> 7) & 0xffffff01); // set render flags

    // Second pass for a different LOD or bone variant
    int secondBoneIndex = *(int*)((char*)ctxSkeleton + 0x10);
    secondMeshHandle = 0;
    if (hasMeshList != 0 && secondBoneIndex >= 0) {
        if (*(int*)(this->field_1bc + 0x18) == 0 || *(int*)(this->field_1bc + 0x14) <= secondBoneIndex) {
            secondBoneIndex = 0;
        } else {
            int* table = *(int**)(this->field_1bc + 0x18);
            // Complex lookup using table and this->field_1d6 as a ushort index
            secondBoneIndex = *(int*)((char*)table + secondBoneIndex * 8 + (uint)*(ushort*)(this + 0x1d6) * 4);
        }
        int* meshSlotTable2 = *(int**)(this->field_1bc + 0x1c);
        if (meshSlotTable2 != 0) {
            int* entry2 = meshSlotTable2 + secondBoneIndex * 3;
            if (entry2 != 0) {
                int meshIdx2 = entry2[0];
                if (meshIdx2 == -1) {
                    secondMeshHandle = **(int**)(this->field_1bc + 0x30);
                } else {
                    secondMeshHandle = *(int*)(*(int*)(this->field_1bc + 0x30) + meshIdx2 * 4);
                }
                secondMeshHandle += 0x10;
            }
        }
    }

    // Additional global rendering adjustment
    if (this->field_1b4 != 0 && this->field_1b4 != (void*)0x48) {
        int* globalObj = Func_00625050(0x187b7e2b, 0); // hash lookup for global renderer
        if (globalObj != 0) {
            Func_007cb610(); // set global render state
            Func_00772a60(secondMeshHandle, (*(uint*)(this + 0x1d0) >> 6) & 0xffffff01);
        }
    }

    // Final render state for this object
    Func_007cc030(*(int*)(this + 0x58), *(uint*)((char*)ctxSkeleton + 0x24) & 7,
                  *(uint*)((char*)ctxSkeleton + 0x24) & 0x78, 0);
    // Render state for the owner object
    if (this->field_1b4 == 0) {
        ownerBase = 0;
    } else {
        ownerBase = (int*)((char*)this->field_1b4 - 0x48);
    }
    Func_007cc030(ownerBase, *(uint*)((char*)ctxSkeleton + 0x28) & 7,
                  *(uint*)((char*)ctxSkeleton + 0x28) & 0x78, 0);
}