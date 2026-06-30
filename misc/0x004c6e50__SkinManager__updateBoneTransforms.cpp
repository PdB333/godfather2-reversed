// FUNC_NAME: SkinManager::updateBoneTransforms

void __thiscall SkinManager::updateBoneTransforms(SkinManager* this, Skeleton* skeleton)
{
    int boneCount;
    int currentIndex;
    int boneArrayBase;
    int bufferPtr;
    int bufferEnd;
    int iVar1;
    int iVar2;
    int iVar4;
    int iVar8;
    char cVar3;
    uint uVar6;
    uint uVar7;
    undefined4* puVar5;
    int local_38;
    undefined** local_2c;
    int local_28;
    int local_24;
    undefined4 local_20;
    undefined4 local_1c;
    undefined1 local_18[16];
    uint uStack_8;

    // skeleton +0xa0 points to bone data structure
    BoneData* boneData = *(BoneData**)(skeleton + 0xa0);
    
    // this->+4 is base pointer for output buffer, this->+8 is pointer to current index
    int* indexPtr = *(int**)(this + 8);
    currentIndex = **indexPtr;
    bufferPtr = *(int*)(this + 4) + currentIndex * 0x50; // each output entry is 0x50 bytes

    uVar7 = 0;
    boneCount = *(short*)(boneData + 0x44);
    if (boneCount != 0) {
        local_38 = 0;
        do {
            // boneData+0x80 points to array of BoneNode structures (size 0x28)
            puVar5 = (undefined4*)(*(int*)(boneData + 0x80) + local_38);
            BoneNode* boneNode = (BoneNode*)puVar5;
            
            if (*(char*)(boneNode + 0x1c) == '\0') {
                // Bone has no transform provider, use precomputed index at +0x14
                uVar6 = *(uint*)(boneNode + 0x14);
            }
            else {
                // Bone has a transform provider, call virtual function at vtable+0x34
                // This fills a 16-byte buffer (local_18) and returns a hash/ID in uStack_8
                (*(code**)(*(int*)(*puVar5) + 0x34))((int*)(*puVar5), local_18);
                uVar6 = uStack_8;
            }
            
            // Recompute current buffer position after potential increment
            iVar8 = *(int*)(this + 4) + **indexPtr * 0x50;
            
            // Convert uVar6 (bone ID) to index: uVar6 / 0x14 * 0xc
            iVar2 = (uVar6 / 0x14) * 0xc;
            
            // Copy bone transform data to output slot (two halves: at offset 0 and 0x28, each 0x1a bytes)
            memcpyBytes(iVar2, 0, iVar8, 0x1a);          // Upper 26 bytes
            memcpyBytes(iVar2, 0, iVar8 + 0x28, 0x1a); // Lower 26 bytes
            
            // Increment the output index
            (**indexPtr)++;
            
            local_38 += 0x28;
            uVar7++;
        } while (uVar7 < *(ushort*)(boneData + 0x44));
    }
    
    // Store some additional state for later submission
    local_20 = *(undefined4*)(this + 0xc);
    local_1c = *(undefined4*)(this + 0x10);
    local_2c = &PTR_FUN_00e36554; // Global conditional function pointer
    local_28 = (int)skeleton;
    local_24 = bufferPtr;
    
    // If bit0 of skeleton+0xb2 is set, or global condition returns false, submit batch
    if (((*(byte*)(skeleton + 0xb2) & 1) != 0) ||
        (cVar3 = (*(code*)PTR_FUN_00e36554)(), cVar3 == '\0')) {
        submitSkinBatch((code*)&LAB_0049cd60, &local_2c);
    }
    return;
}