// FUNC_NAME: GameplayDebugger::fillDebugInfo
void __thiscall GameplayDebugger::fillDebugInfo(int thisPtr, DebugOutput* outInfo)
{
    int iVar1;
    int* piVar2;
    char cVar3;
    int localArray[3];

    // Clear the output structure (16 bytes)
    outInfo->field0 = 0;
    outInfo->field8 = 0;

    // Unknown helper, maybe prepares a stack or timing
    FUN_006b2910();

    // Access m_pDebugTarget (offset 0x194 from this)
    iVar1 = *(int*)(thisPtr + 0x194);
    if (iVar1 != 0 && iVar1 != 0x48) {
        // Get pointer to debug component (offset 0xe8 from target)
        piVar2 = *(int**)(iVar1 + 0xe8);
        if (piVar2 != (int*)0x0) {
            // Call virtual function at vtable+0x10 (probably isActive or something)
            cVar3 = (**(code**)(*piVar2 + 0x10))();
            if (cVar3 != '\0') {
                // Gather debug data from component
                localArray[0] = piVar2[8]; // e.g., position x
                localArray[1] = 0;         // possibly padding
                localArray[2] = piVar2[10];// e.g., position z

                // Call helper to fill output with debug info and a hash constant
                FUN_0097c010(outInfo, localArray, piVar2[0xb], 0x17f92c3a);
            }
        }
        // Store this object ID in output
        *(int*)((int)outInfo + 0xc) = thisPtr;
        return;
    }
    // No valid target, just store thisPtr
    *(int*)((int)outInfo + 0xc) = thisPtr;
    return;
}