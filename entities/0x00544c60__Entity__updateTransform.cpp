// FUNC_NAME: Entity::updateTransform
void __thiscall Entity::updateTransform(int* thisPtr, int* transformPtr)
{
    int iVar1;
    char cVar2;
    undefined4 localVec[4]; // Vector4 (x,y,z,w)
    undefined4 localMatrix[15]; // 60 bytes, likely a 4x4 matrix but only 15 floats used? Or 3x4?
    undefined4 localResult[4]; // 16 bytes, Vector4

    // Call base class update or pre-update
    FUN_00470e30(transformPtr);

    // Check virtual function at vtable offset 0x19c (index 103)
    // Likely isActive() or isVisible()
    cVar2 = (**(code (**)(void))(*thisPtr + 0x19c))();
    if (cVar2 == '\0') {
        // If not active/visible
        if (iVar1 != 0) {
            // iVar1 is thisPtr[0xba] (offset 0x2E8) - maybe m_pTransform or m_bHasTransform
            // Extract transform matrix from transformPtr
            FUN_004b59d0(transformPtr, (char*)localMatrix);
            // Convert to local space (inverse or something)
            FUN_00aa3930((char*)localMatrix);
            // Build a vector from transformPtr's position (offset 0x30) and a global constant
            localVec[0] = *(undefined4*)(transformPtr + 0x30); // x
            localVec[1] = *(undefined4*)(transformPtr + 0x34); // y
            localVec[2] = *(undefined4*)(transformPtr + 0x38); // z
            localVec[3] = DAT_00e2b1a4; // w (likely 1.0f)
            // Transform the vector by the matrix
            FUN_009f4ca0(&localVec, (char*)localResult);
        }
    }
    else {
        // If active/visible, call reset or deactivate
        FUN_0055d970();
    }

    // Call post-update virtual at vtable offset 600 (index 150)
    (**(code (**)(void))(*thisPtr + 600))();
    return;
}