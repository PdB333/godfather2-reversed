// FUNC_NAME: EARSMemory::CleanupTwoLists
void __thiscall CleanupTwoLists(void* this, void* param_1, void* param_2)
{
    // Stack layout:
    // Block from param_2: 16 bytes (int + undefined4 + undefined4 + code*)
    int node2;
    undefined4 data2_1;
    undefined4 data2_2;
    code* destructor2;

    // Block from param_1: 16 bytes
    int node1;
    undefined4 data1_1;
    undefined4 data1_2;
    code* destructor1;

    // Additional local variables
    int extraNode;
    undefined4 extraData;
    code* extraDestructor;
    int local_10[3];  // Probably a small array or struct with vtable
    code* finalDestructor;  // Actually not used? Decompiler mis-assigned

    // Initialize both blocks using the parameters (likely extracts internal pointers)
    // FUN_0071e8a0 probably sets up linked lists or smart pointer structures
    FUN_0071e8a0(param_1, param_2, &param_2, &param_1);

    // Initialize first block from param_2
    node2 = 0;
    data2_1 = 0;
    data2_2 = 0;
    destructor2 = nullptr;
    FUN_0071ea20(param_2, &node2);  // Extracts object reference from first parameter

    // Initialize second block from param_1
    node1 = 0;
    data1_1 = 0;
    data1_2 = 0;
    destructor1 = nullptr;
    FUN_0071ea20(param_1, &node1);  // Extracts object reference from second parameter

    // Prepare extra destructor pointer
    extraDestructor = nullptr;

    // Compare first block with a global sentinel; if matching, possibly release or mark
    // &DAT_00e337ec is likely a static sentinel object
    FUN_004d3ca0(node2, data2_1, &DAT_00e337ec, 1);

    // Set final destructor to null (decompiler artifact, likely originally stored from compare)
    finalDestructor = nullptr;

    // Compare extra block values with second block
    // extraNode and extraData might have been set by the previous call? Uninitialized in decompiled code.
    FUN_004d3ca0(extraNode, extraData, node1, data1_1);

    // Final cleanup on the temporary structure local_10
    // FUN_004d3e20 might be a cleanup loop or list deletion
    FUN_004d3e20(local_10);

    // If something remains, call the final destructor (in original code likely different pointers)
    if (local_10[0] != 0) {
        (*finalDestructor)(local_10[0]);  // This would crash if null; likely finalDestructor is set elsewhere
    }

    // Call destructor functions for each block if they were set by the extraction functions
    // (Actually these are likely inside the blocks, not separate locals, but decompiler spilled them)
    if (extraNode != 0) {
        (*extraDestructor)(extraNode);
    }
    if (node1 != 0) {
        (*destructor1)(node1);
    }
    if (node2 != 0) {
        (*destructor2)(node2);
    }

    return;
}