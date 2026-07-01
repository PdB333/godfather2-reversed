// FUNC_NAME: ChaseCamera::updateInterpolatedTargets
// Function at 0x00860170: Updates two interpolated target positions for a chase camera.
// Uses two transforms (likely from a character bone) to compute positions along the local Z-axis
// and adds translation offsets. The first position uses a delta from +0xFA0, the second uses a
// global value and a delta from +0xFA4. Sets a flag at +0xF28 (bit 0x8000) after update.

void __fastcall ChaseCamera::updateInterpolatedTargets(int thisPtr)
{
    // Get pointer to two matrices (likely character world transforms)
    int* pMatrix1 = (int*)getMatrix();  // FUN_00471610
    int* pMatrix2 = (int*)getMatrix();  // FUN_00471610

    // Compute first target position: interpolate along Z-axis of matrix1, add translation of matrix2
    float delta = *(float*)(thisPtr + 0xFA0) - *(float*)(thisPtr + 0xFC0);  // +0xFA0 = currentOffset, +0xFC0 = baseOffset
    *(float*)(thisPtr + 0xFA8) = *(float*)(pMatrix1 + 0x20) * delta + *(float*)(pMatrix2 + 0x30);  // +0xFA8 = targetPosX
    *(float*)(thisPtr + 0xFAC) = *(float*)(pMatrix1 + 0x24) * delta + *(float*)(pMatrix2 + 0x34);  // +0xFAC = targetPosY
    *(float*)(thisPtr + 0xFB0) = *(float*)(pMatrix1 + 0x28) * delta + *(float*)(pMatrix2 + 0x38);  // +0xFB0 = targetPosZ

    // Get matrices again for second target
    pMatrix1 = (int*)getMatrix();  // FUN_00471610
    pMatrix2 = (int*)getMatrix();  // FUN_00471610

    // Compute second target position (likely worldOffset or lookAt)
    // DAT_00e44564 is a global constant (e.g., camera distance)
    float delta2 = DAT_00e44564 - ( *(float*)(thisPtr + 0xFA4) - *(float*)(thisPtr + 0xFC0) );  // +0xFA4 = anotherOffset
    *(float*)(thisPtr + 0xFB4) = *(float*)(pMatrix1 + 0x20) * delta2 + *(float*)(pMatrix2 + 0x30);  // +0xFB4 = worldPosX
    *(float*)(thisPtr + 0xFB8) = *(float*)(pMatrix1 + 0x24) * delta2 + *(float*)(pMatrix2 + 0x34);  // +0xFB8 = worldPosY
    *(float*)(thisPtr + 0xFBC) = *(float*)(pMatrix1 + 0x28) * delta2 + *(float*)(pMatrix2 + 0x38);  // +0xFBC = worldPosZ

    // Mark positions as updated (bit 0x8000 set at +0xF28)
    *(int*)(thisPtr + 0xF28) |= 0x8000;
}