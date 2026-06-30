// FUNC_NAME: Skeleton::setBoneCount

// This function reallocates the bone matrix array, initializes each matrix to identity,
// and optionally sends an update message to the animation system.
// Parameters:
//   this     - Skeleton instance
//   boneDef  - Bone definition object (may be nullptr for clearing)
// Offsets used:
//   +0x54   - some data (pushed as part of message)
//   +0x15e  - flags (bit 0x4000 = matrix data valid)
//   +0x164  - pointer to parent/system (if non-zero, message is sent)
//   +0x20c  - pointer to definition (used for finalize call)
//   +0x218  - pointer to BoneHierarchy (provides bone count & scale)
//   +0x260  - allocated matrix array (float[16] per bone)
//   +0x264  - number of matrices (bones)

void __thiscall Skeleton::setBoneCount(void* boneDef)
{
    struct Allocator* alloc;
    float* matrixData;
    float identityVal;   // = 1.0f (diagonal value of identity matrix)
    int extraData;       // value from FUN_00570f50 result
    int boneCount;
    short hierarchyBoneCount;
    float hierarchyScale;
    int loopIndex;
    uint loopCount;
    int stackStructBuf[3]; // local buffer used with global stack pointer

    // Free existing matrix array if present
    if (this->matrixArray != 0) {
        alloc = (struct Allocator*)getGlobalAllocator();
        alloc->vtable->deallocate(this->matrixArray, 0); // flag 0 = free
        this->matrixArray = 0;
    }
    this->numMatrices = 0;

    if (boneDef != 0) {
        boneCount = *(int*)((char*)boneDef + 0x38); // boneDef->boneCount

        // Special case: if boneCount==1 and we have a bone hierarchy with >1 bones,
        // override the count with the hierarchy's count
        if (boneCount == 1 && this->hierarchy != 0 && this->someFlag != 0) {
            hierarchyBoneCount = *(short*)(this->hierarchy + 0xb0); // hierarchy->numBones
            if (hierarchyBoneCount > 1) {
                boneCount = hierarchyBoneCount;
            }
        }

        // Re-free (probably redundant, but matches original logic)
        if (this->matrixArray != 0) {
            alloc = (struct Allocator*)getGlobalAllocator();
            alloc->vtable->deallocate(this->matrixArray, 0);
            this->matrixArray = 0;
        }

        this->numMatrices = boneCount;
        if (boneCount != 0) {
            alloc = (struct Allocator*)getGlobalAllocator();
            // Allocate 64 bytes per bone (16 floats = 4x4 matrix)
            stackStructBuf[0] = 2;      // alignment flag? float 8.96831e-44 is denormal zero
            stackStructBuf[1] = 0;      // effectively zero
            stackStructBuf[2] = 0;
            this->matrixArray = (float*)alloc->vtable->allocate(
                boneCount * 64,        // size
                stackStructBuf         // flags struct
            );
        }

        // If pointer at +0x164 is non‑zero, send an update message to the animation system
        if (this->callbackSystem != 0) {
            // Determine values for the message
            if (this->hierarchy != 0) {
                hierarchyScale = *(float*)(this->hierarchy + 0x104); // hierarchy->scale
                extraData = FUN_00570f50(this->hierarchy);
            } else {
                hierarchyScale = 0.0f;
                extraData = 0;
            }
            if (extraData != 0) {
                extraData = *(int*)(extraData + 0x10); // some field
            } else {
                extraData = 0;
            }

            // Build message on global stack (used by animation system)
            // The global pointer at DAT_01206880+0x14 points to the current stack pointer
            // We rewrite the stack as if pushing a struct:
            //   { float scale; int count; int extraData; }
            // Also write a vtable pointer for the message type.
            {
                int** stackPtr = (int**)(*(int*)(DAT_01206880 + 0x14)); // pointer to current stack ptr
                **(int***)(DAT_01206880 + 0x14) = &PTR_LAB_0110b960;   // set message vtable
                (*stackPtr)++;                                          // advance
                *(*stackPtr) = (int)(this + 0x54);                      // store pointer to this->field54
                stackPtr = (int**)(*stackPtr);                          // get new address of stack ptr
                // Align to 8 bytes
                *stackPtr = (int*)(((int)*stackPtr + 7) & 0xFFFFFFFC);
                // Write the data: double (scale, count) + int extraData
                *(double*)*stackPtr = (double)hierarchyScale + (double)this->numMatrices; // CONCAT44
                *(*stackPtr + 2) = extraData; // after double (8 bytes), 3rd int
                *stackPtr += 3;               // advance by 12 bytes (3 ints)
            }

            // Set flag at +0x15e to indicate matrix data is present
            if (hierarchyScale == 0.0f && this->numMatrices == 0) {
                *(unsigned short*)(this + 0x15e) &= 0xBFFF; // clear bit 0x4000
            } else {
                *(unsigned short*)(this + 0x15e) |= 0x4000; // set bit 0x4000
            }
        }

        // Initialize each matrix to identity
        identityVal = 1.0f; // DAT_00e2b1a4 is effectively 1.0
        if (this->numMatrices != 0) {
            loopIndex = 0;
            loopCount = 0;
            do {
                matrixData = this->matrixArray + loopIndex;
                *matrixData = identityVal;
                matrixData[1] = 0.0f;
                matrixData[2] = 0.0f;
                matrixData[3] = 0.0f;
                matrixData[4] = 0.0f;
                matrixData[5] = identityVal;
                matrixData[6] = 0.0f;
                matrixData[7] = 0.0f;
                matrixData[8] = 0.0f;
                matrixData[9] = 0.0f;
                matrixData[10] = identityVal;
                matrixData[11] = 0.0f;
                matrixData[12] = 0.0f;
                matrixData[13] = 0.0f;
                matrixData[14] = 0.0f;
                matrixData[15] = identityVal;
                loopCount++;
                loopIndex += 16; // each matrix: 16 floats = 64 bytes
            } while (loopCount < (uint)this->numMatrices);
        }

        // Finalize with the definition object if a callback is set
        if (this->someDefinitionPtr != 0) {
            FUN_00570430(boneDef);
        }
    }
    return;
}