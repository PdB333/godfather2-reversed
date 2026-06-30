// FUNC_NAME: NavMesh::subdivideTriangle
void __fastcall NavMesh::subdivideTriangle(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10)
{
    int *piVar1;
    int *piVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    int *piVar8;
    int iVar9;
    int local_24c;
    int local_240 [144];
    
    // Calculate subdivision level based on edge lengths
    // param_1 = maxSubdivisions, param_2-param_10 = triangle vertex coordinates
    iVar3 = (((param_6 - param_4) - param_9) + param_2) * 3 + 4 >> 3;
    piVar8 = local_240;
    if (iVar3 < 0) {
        iVar3 = -iVar3;
    }
    if (param_1 < iVar3) {
        param_1 = iVar3;
    }
    iVar3 = (((param_7 - param_5) - param_10) + param_8) * 3 + 4 >> 3;
    if (iVar3 < 0) {
        iVar3 = -iVar3;
    }
    if (param_1 < iVar3) {
        param_1 = iVar3;
    }
    
    // Determine number of subdivision levels based on max allowed
    local_24c = 0;
    for (; *(int *)(param_3 + 0x2200) < param_1; param_1 = param_1 >> 2) {
        local_24c = local_24c + 1;
    }
    
    // Subdivide triangle recursively using stack-based approach
    while( true ) {
        while (0 < local_24c) {
            // Calculate midpoints of edges
            iVar6 = param_6 + param_2 + 1 >> 1;
            iVar5 = param_2 + 1 + param_9 >> 1;
            iVar3 = param_4 + (param_6 + param_2) * 3 + 4 + param_9 >> 3;
            *piVar8 = iVar3;
            local_24c = local_24c + -1;
            iVar4 = param_5 + (param_7 + param_8) * 3 + 4 + param_10 >> 3;
            piVar8[1] = iVar4;
            piVar8[2] = iVar5 + 1 + iVar6 >> 1;
            iVar9 = param_8 + 1 + param_10 >> 1;
            iVar7 = param_7 + param_8 + 1 >> 1;
            piVar8[3] = iVar9 + 1 + iVar7 >> 1;
            piVar8[4] = iVar5;
            piVar8[5] = iVar9;
            piVar8[6] = param_9;
            piVar8[7] = param_10;
            piVar8[8] = local_24c;
            param_6 = param_4 + 1 + param_6 >> 1;
            param_7 = param_5 + 1 + param_7 >> 1;
            param_2 = iVar6 + 1 + param_6 >> 1;
            piVar8 = piVar8 + 9;
            param_8 = param_7 + 1 + iVar7 >> 1;
            param_9 = iVar3;
            param_10 = iVar4;
        }
        // Process leaf triangle
        FUN_006767c0(param_4,param_5,param_9,param_10);
        if (piVar8 <= local_240) break;
        // Pop from stack
        local_24c = piVar8[-1];
        piVar1 = piVar8 + -2;
        piVar2 = piVar8 + -3;
        param_8 = piVar8[-4];
        param_7 = piVar8[-6];
        param_6 = piVar8[-7];
        param_2 = piVar8[-5];
        param_5 = piVar8[-8];
        piVar8 = piVar8 + -9;
        param_4 = *piVar8;
        param_9 = *piVar2;
        param_10 = *piVar1;
    }
    return;
}