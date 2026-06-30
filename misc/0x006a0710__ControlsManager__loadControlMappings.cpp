// FUNC_NAME: ControlsManager::loadControlMappings
void __cdecl ControlsManager::loadControlMappings(void)
{
    undefined *pControlsRmp;
    undefined4 uVar2;
    undefined2 **ppuVar3;
    undefined2 *puVar4;
    undefined2 *local_30 [3];
    code *pcStack_24;
    int local_20;
    undefined4 local_1c;
    code *local_14;
    int local_10;
    undefined4 local_c;
    code *pcStack_4;
    
    pControlsRmp = PTR_u_controls_rmp_00e50c74; // Pointer to "controls.rmp" string
    if (*(int *)(DAT_01129828 + 0x2264) == 0) { // Check if controls are disabled (offset +0x2264)
        FUN_006a0480(); // Load default controls
        return;
    }
    uVar2 = FUN_004dbef0(PTR_u_controls_rmp_00e50c74); // Get file size of controls.rmp
    FUN_004dba00(pControlsRmp, uVar2); // Read controls.rmp into memory
    puVar4 = *(undefined2 **)(DAT_01129828 + 0x2260); // Get custom controls file path (offset +0x2260)
    if (puVar4 == (undefined2 *)0x0) {
        puVar4 = &DAT_00e2df14; // Default empty string
    }
    uVar2 = FUN_004dbef0(puVar4); // Get file size of custom controls
    FUN_004dba00(puVar4, uVar2); // Read custom controls into memory
    FUN_004dbf70(&DAT_00e36ef4, 1, local_10, local_c); // Parse XML controls file (1 = parse mode)
    FUN_004dbd90(local_20, 0, local_1c); // Get root XML element
    if (local_20 != 0) {
        (*local_14)(local_20); // Process root element
    }
    puVar4 = local_30[0];
    if (local_30[0] == (undefined2 *)0x0) {
        puVar4 = &DAT_00e2df14; // Default empty string
    }
    ppuVar3 = (undefined2 **)FUN_00699080(&local_20, puVar4, 3); // Find action mappings (type 3)
    if (local_30 != ppuVar3) {
        puVar4 = *ppuVar3;
        if (puVar4 == (undefined2 *)0x0) {
            puVar4 = &DAT_00e2df14; // Default empty string
        }
        FUN_004dbb10(puVar4, 0, ppuVar3[1]); // Apply action mapping
    }
    if (local_20 != 0) {
        (*local_14)(local_20); // Cleanup root element
    }
    puVar4 = local_30[0];
    if (local_30[0] == (undefined2 *)0x0) {
        puVar4 = &DAT_00e2df14; // Default empty string
    }
    FUN_00497470(puVar4); // Finalize control mappings
    if (local_30[0] != (undefined2 *)0x0) {
        (*pcStack_24)(local_30[0]); // Free action mapping
    }
    if (local_10 != 0) {
        (*pcStack_4)(local_10); // Free XML parser
    }
    return;
}