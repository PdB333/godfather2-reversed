// FUNC_NAME: TransformCalculator::applyInputDisplacement
void __thiscall TransformCalculator::applyInputDisplacement(int this, InputTransform* inputTransform)
// this in EAX, inputTransform in EDX (custom __thiscall)
{
    float* pfVar2;
    int iVar3;
    int iVar4;
    uint identityConstant;

    identityConstant = DAT_00e2b1a4; // likely 1.0f for matrix identity
    // Get thread-local storage offset for scratch buffer
    iVar3 = **(int**)(unaff_FS_OFFSET + 0x2c); // TLS structure pointer
    // Point to scratch matrix slot (48 bytes = 12 floats, maybe 3x4 matrix)
    undefined4* tempMatrix = (undefined4*)(*(int*)(this + 0x10) + 0x10 + *(int*)(iVar3 + 8));
    
    // Initialize scratch matrix as identity (only diagonal entries set to identityConstant)
    *tempMatrix = identityConstant;              // +0x00: m00
    tempMatrix[1] = 0;                          // +0x04: m01
    tempMatrix[2] = 0;                          // +0x08: m02
    tempMatrix[3] = 0;                          // +0x0C: m03 (translation x placeholder?)
    tempMatrix[4] = 0;                          // +0x10: m10
    tempMatrix[5] = identityConstant;           // +0x14: m11
    tempMatrix[6] = 0;                          // +0x18: m12
    tempMatrix[7] = 0;                          // +0x1C: m13
    tempMatrix[8] = 0;                          // +0x20: m20
    tempMatrix[9] = 0;                          // +0x24: m21
    tempMatrix[10] = identityConstant;          // +0x28: m22
    tempMatrix[0xb] = 0;                        // +0x2C: m23
    
    // Process displacement vector (inputTransform + 0x14: Vector3 translation)
    if ((*(uint*)(inputTransform + 4) & 1) == 0) // Bit 0: relative mode?
    {
        if ((*(uint*)(inputTransform + 4) & 2) != 0) // Bit 1: absolute set?
        {
            iVar4 = *(int*)(this + 0x10);
            iVar3 = *(int*)(iVar3 + 8);
            // Write absolute translation into buffer at offset 0x40 from base
            *(undefined4*)(iVar4 + 0x40 + iVar3) = *(undefined4*)(inputTransform + 0x14);
            *(undefined4*)(iVar4 + 0x40 + iVar3 + 4) = *(undefined4*)(inputTransform + 0x18);
            *(undefined4*)(iVar4 + 0x40 + iVar3 + 8) = *(undefined4*)(inputTransform + 0x1c);
        }
    }
    else
    {
        // Add translation to existing value (relative displacement)
        pfVar2 = (float*)(*(int*)(this + 0x10) + 0x40 + *(int*)(iVar3 + 8));
        *pfVar2 = *(float*)(inputTransform + 0x14) + *pfVar2;
        pfVar2[1] = *(float*)(inputTransform + 0x18) + pfVar2[1];
        pfVar2[2] = *(float*)(inputTransform + 0x1c) + pfVar2[2];
    }
    
    // Store input transform pointer and other context for later combination
    *(int*)(this + 0x24) = (int)inputTransform;
    *(undefined4*)(this + 0x28) = 0;
    *(undefined4*)(this + 0x2c) = 0;
    *(undefined4*)(this + 0x30) = identityConstant;
    *(undefined4*)(this + 0x34) = *(undefined4*)(inputTransform + 0x20); // e.g., scale or time
    
    // Call the actual transform application (multiply/combine matrices)
    FUN_004f3f70(this, inputTransform, 
                 *(undefined4*)(*(int*)(this + 4) + 0x10),
                 *(undefined4*)(this + 0x10),
                 *(undefined4*)(this + 0x14));
}