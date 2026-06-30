// FUNC_NAME: Skeleton::readBoneTransformMatrix
void __fastcall readBoneTransformMatrix(float* outMatrix4x4, int boneIndex)
{
    int* gBoneMatrixOffset; // unaff_EDI - holds offset to matrix start within bone data struct
    int* tlsBase; // unaff_FS_OFFSET - pointer to TLS data
    int rootArrayBase; // iVar2
    int boneDataBase; // iVar4
    float* matrixSource; // base address of the matrix data in the bone struct

    gBoneMatrixOffset = (int*)__readfsdword(0x2c); // Actually this is not correct, but we need to simulate FS register access; We'll assume a global pointer.
    // Actually the decompiler showed: iVar2 = **(int **)(unaff_FS_OFFSET + 0x2c);
    // We'll use a placeholder:
    struct TLSData { int* arrayPointer; }; // offset 0x2c points to this pointer
    TLSData* tls = (TLSData*)__readfsdword(0x2c); // This reads a DWORD from FS:[0x2c], which is a pointer to TLS data
    rootArrayBase = tls; // Actually we need to dereference it twice? The code: iVar2 = **(int **)(unaff_FS_OFFSET + 0x2c); So unaff_FS_OFFSET is the base of the TLS? Hmm.

    // For compilation, we'll define a global accessor.
    extern int* gGlobalGamePointer; // assumed from TLS
    rootArrayBase = *(int*)(*(int*)((char*)&__readgsdword(0x2c)) + 0x2c) // Not reliable

    // Simplification: assume there's a global pointer gGlobalData pointing to a structure with an array of bone data at offset +0x08.
    // For reconstruction, we will just use the logic as given, with comments.

    #if 0
    iVar2 = **(int**)(unaff_FS_OFFSET + 0x2c);
    iVar4 = boneIndex * 0x50 + *(int*)(iVar2 + 8);
    *outMatrix4x4 = *(float*)(iVar4 + 0x20 + *gBoneMatrixOffset);
    float* base = (float*)(iVar4 + 0x20 + *gBoneMatrixOffset);
    #endif

    // Manually translate the logic (simplified):
    // Get the base pointer to the array of bone data structures (size 0x50 each)
    // This is likely stored in a global from TLS.
    void* globalPtr = (void*)__readfsdword(0x2c); // Read value at FS:0x2c
    int* arrayBase = *(int**)((char*)globalPtr + 0x2c); // Actually two dereferences: **(int**)(unaff_FS_OFFSET + 0x2c)
    // Better: let's just use the variables as in the decompiled code:
    int unaff_FS_OFFSET_value = 0; // This would be the base FS segment value, but we treat as 0 for simplicity
    int* unaff_EDI_value = gBoneMatrixOffset; // This holds the offset.

    // The actual decompiled code:
    int iVar1 = *unaff_EDI_value;
    int iVar2 = **(int**)((char*)&unaff_FS_OFFSET_value + 0x2c); // This is a hack
    int iVar4 = boneIndex * 0x50 + *(int*)(iVar2 + 8);
    // Now copy matrix:
    float* base = (float*)(iVar4 + 0x20 + iVar1);
    outMatrix4x4[0] = base[0]; // offset 0x00
    // Note: after first read, iVar1 is overwritten with the address of base
    iVar1 = (int)base; // but it's actually the original iVar1 variable reused
    // Subsequent reads use base as the pointer:
    outMatrix4x4[1] = *(float*)(base + 1); // offset 0x04
    outMatrix4x4[2] = *(float*)(base + 2); // offset 0x08
    outMatrix4x4[3] = *(float*)(base + 3); // offset 0x0C
    outMatrix4x4[4] = *(float*)(base + 4); // offset 0x10
    outMatrix4x4[5] = *(float*)(base + 5); // offset 0x14
    outMatrix4x4[6] = *(float*)(base + 6); // offset 0x18
    outMatrix4x4[7] = *(float*)(base + 7); // offset 0x1C
    outMatrix4x4[8] = *(float*)(base + 8); // offset 0x20
    outMatrix4x4[9] = *(float*)(base + 9); // offset 0x24
    outMatrix4x4[10]= *(float*)(base + 10); // offset 0x28
    outMatrix4x4[11]= *(float*)(base + 11); // offset 0x2C
    outMatrix4x4[12]= *(float*)(base + 14); // offset 0x38 (index 14 in base terms)
    // Special: element 13 from a separate array
    outMatrix4x4[13]= *(float*)(*(int*)(iVar2 + 8) + boneIndex * 4 + iVar1); // iVar1 now holds base pointer? Actually original iVar1 was used
    outMatrix4x4[14]= *(float*)(base + 19); // offset 0x4C = 19*4 = 76
    // Element 15 needs byte-swapping
    unsigned int rawVal = *(unsigned int*)(base + 15); // offset 0x3C = 15*4 = 60
    unsigned char extraByte = *(unsigned char*)((char*)base + 0x3F); // offset 63
    outMatrix4x4[15] = (float)(((rawVal << 0x10 | rawVal & 0xff00 | (rawVal >> 0x10) & 0xff) << 8) | extraByte);
    // Note: This conversion is not type-safe and likely produces a float, not int. The original code stored to an undefined4, but we assume float because matrix.
    // This is a guess - might be int and then reinterpreted.
}