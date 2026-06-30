// FUNC_NAME: SomeClass::initializeOrResizeArray
int FUN_00547530(undefined4 param_1, int *param_2)
{
    int *piVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    uint uVar5;
    int iVar6;
    uint uVar7;
    int iVar8;
    int iVar9;
    uint uVar10;
    
    uVar5 = (**(code **)(*param_2 + 0x220))(); // Get count/size from some method (+0x220)
    iVar6 = (**(code **)(*param_2 + 0x228))(0); // Get existing count/size (+0x228)
    uVar10 = uVar5 - iVar6; // Difference between new and old size
    TlsGetValue(DAT_01139810); // Get thread-local storage
    iVar6 = FUN_00aa2680(0x1a0, 0xb); // Allocate memory for object (416 bytes, type 0xb)
    *(undefined2 *)(iVar6 + 4) = 0x1a0; // Store size at offset +4
    iVar6 = FUN_00bee720(); // Get some base object pointer
    piVar1 = (int *)(iVar6 + 0x8c); // Pointer to array data at +0x8c
    *(char *)(iVar6 + 0x20) = (char)uVar5; // Set count at +0x20
    
    uVar7 = *(uint *)(iVar6 + 0x94) & 0x3fffffff; // Get capacity at +0x94
    if ((int)uVar7 < (int)uVar5) {
        uVar7 = uVar7 * 2;
        if ((int)uVar7 <= (int)uVar5) {
            uVar7 = uVar5;
        }
        FUN_00aa4110(piVar1, uVar7, 0x28); // Reallocate array with new capacity, element size 0x28
    }
    *(uint *)(iVar6 + 0x90) = uVar5; // Update count at +0x90
    
    if (uVar10 != 0) {
        iVar8 = 0;
        uVar7 = uVar10;
        do {
            *(undefined1 *)(iVar8 + 0x24 + *piVar1) = 0; // Clear some flag at offset 0x24
            iVar8 = iVar8 + 0x28;
            uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
    }
    
    if (uVar10 < uVar5) {
        iVar8 = uVar10 * 0x28;
        iVar9 = uVar5 - uVar10;
        do {
            *(undefined1 *)(iVar8 + 0x24 + *piVar1) = 1; // Set flag to 1 for new elements
            iVar8 = iVar8 + 0x28;
            iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
    }
    
    // Initialize constant values from global data
    uVar4 = DAT_00e445dc;
    uVar3 = DAT_00e2b1a4;
    uVar2 = DAT_00e2b04c;
    
    // Unrolled loop initialization of element fields at offsets 0xc, 0x10, 0x14, 0x1c, 0x18, 0x20
    // Then 0x34, 0x38, 0x3c, 0x44, 0x40, 0x48
    // Then 0x5c, 0x60, 0x64, 0x6c, 0x68, 0x70
    // Then 0x84, 0x88, 0x8c, 0x94, 0x90, 0x98
    uVar7 = 0;
    if (3 < (int)uVar5) {
        iVar8 = 0;
        iVar9 = (uVar5 - 4 >> 2) + 1;
        uVar7 = iVar9 * 4;
        do {
            // Initialize 4 elements at a time (unrolled by 4, each element size 0x28 = 40 bytes)
            // Each element has 6 fields: [0xc]=uVar3, [0x10]=0, [0x14]=uVar2, [0x1c]=uVar3, [0x18]=0, [0x20]=uVar4
            // Then next group: [0x34]=uVar3, [0x38]=0, [0x3c]=uVar2, [0x44]=uVar3, [0x40]=0, [0x48]=uVar4
            // etc. These appear to be vertex data or transform data for 4 sub-elements per element
            *(undefined4 *)(iVar8 + 0xc + *piVar1) = uVar3;
            *(undefined4 *)(iVar8 + 0x10 + *piVar1) = 0;
            *(undefined4 *)(iVar8 + 0x14 + *piVar1) = uVar2;
            *(undefined4 *)(iVar8 + 0x1c + *piVar1) = uVar3;
            *(undefined4 *)(iVar8 + 0x18 + *piVar1) = 0;
            *(undefined4 *)(iVar8 + 0x20 + *piVar1) = uVar4;
            
            *(undefined4 *)(iVar8 + 0x34 + *piVar1) = uVar3;
            *(undefined4 *)(iVar8 + 0x38 + *piVar1) = 0;
            *(undefined4 *)(iVar8 + 0x3c + *piVar1) = uVar2;
            *(undefined4 *)(iVar8 + 0x44 + *piVar1) = uVar3;
            *(undefined4 *)(iVar8 + 0x40 + *piVar1) = 0;
            *(undefined4 *)(iVar8 + 0x48 + *piVar1) = uVar4;
            
            *(undefined4 *)(iVar8 + 0x5c + *piVar1) = uVar3;
            *(undefined4 *)(iVar8 + 0x60 + *piVar1) = 0;
            *(undefined4 *)(iVar8 + 100 + *piVar1) = uVar2;
            *(undefined4 *)(iVar8 + 0x6c + *piVar1) = uVar3;
            *(undefined4 *)(iVar8 + 0x68 + *piVar1) = 0;
            *(undefined4 *)(iVar8 + 0x70 + *piVar1) = uVar4;
            
            *(undefined4 *)(iVar8 + 0x84 + *piVar1) = uVar3;
            *(undefined4 *)(iVar8 + 0x88 + *piVar1) = 0;
            *(undefined4 *)(iVar8 + 0x8c + *piVar1) = uVar2;
            *(undefined4 *)(iVar8 + 0x94 + *piVar1) = uVar3;
            *(undefined4 *)(iVar8 + 0x90 + *piVar1) = 0;
            *(undefined4 *)(iVar8 + 0x98 + *piVar1) = uVar4;
            
            iVar8 = iVar8 + 0xa0; // Advance by 4 elements (4 * 0x28 = 0xa0)
            iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
    }
    
    // Handle remaining elements (less than 4)
    if (uVar7 < uVar5) {
        iVar8 = uVar7 * 0x28;
        iVar9 = uVar5 - uVar7;
        do {
            *(undefined4 *)(iVar8 + 0xc + *piVar1) = uVar3;
            *(undefined4 *)(iVar8 + 0x10 + *piVar1) = 0;
            *(undefined4 *)(iVar8 + 0x14 + *piVar1) = uVar2;
            *(undefined4 *)(iVar8 + 0x1c + *piVar1) = uVar3;
            *(undefined4 *)(iVar8 + 0x18 + *piVar1) = 0;
            *(undefined4 *)(iVar8 + 0x20 + *piVar1) = uVar4;
            iVar8 = iVar8 + 0x28;
            iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
    }
    
    // Initialize object-level fields
    *(undefined4 *)(iVar6 + 0x34) = uVar3;
    *(undefined4 *)(iVar6 + 0x30) = 0;
    *(undefined4 *)(iVar6 + 0x38) = 0;
    *(undefined4 *)(iVar6 + 0x3c) = 0;
    *(undefined4 *)(iVar6 + 0x48) = uVar3;
    uVar2 = DAT_00e2eff4;
    *(undefined4 *)(iVar6 + 0x40) = 0;
    *(undefined4 *)(iVar6 + 0x44) = 0;
    *(undefined4 *)(iVar6 + 0x4c) = 0;
    *(undefined4 *)(iVar6 + 0x50) = uVar2;
    *(undefined4 *)(iVar6 + 0x54) = 0;
    *(undefined4 *)(iVar6 + 0x58) = 0;
    *(undefined4 *)(iVar6 + 0x5c) = 0;
    
    FUN_005477e0(param_1, param_2); // Call some other initialization function
    return iVar6;
}