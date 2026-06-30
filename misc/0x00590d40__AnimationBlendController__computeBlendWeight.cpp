// FUNC_NAME: AnimationBlendController::computeBlendWeight
// Note: The decompilation is ambiguous due to float/int casting. This reconstruction assumes param_2 is actually a pointer (void*) passed as float, param_3 is 'this', and param_1 is unused or a resource identifier.

float computeBlendWeight(void* param_1, void* param_2, class SomeManager* param_3)
{
    int iVar1 = (int)param_2; // Treat param_2 as pointer (cast from float)
    float in_XMM0_Da; // Register variable

    // Check if the manager's count (at +0x04) is <= the object's list length (at offset +0x0C from a pointer at param_2+0x04)
    if (*(unsigned int*)((char*)param_3 + 4) <= *(unsigned int*)(*(int*)((char*)param_2 + 4) + 0x0C)) {
        in_XMM0_Da = 0.0f;
        param_2 = 0; // Reset pointer (null)
        resetBlendState(&param_2); // Calls FUN_00591c00 with address of param_2
    }

    // Check if the object's state byte at offset +0x01 is less than 2 (e.g., idle/not active)
    if (*(char*)(iVar1 + 1) < 2) {
        return g_someGlobalFloat; // DAT_00e2b1a4 (constant)
    }

    // Perform two blend operations (FUN_00591160)
    doBlendOperation(); // FUN_00591160
    param_2 = (void*)(int)in_XMM0_Da; // Convert float back to pointer? Unusual
    doBlendOperation(); // FUN_00591160

    // Return the maximum of the two values (in_XMM0_Da and param_2 as a float)
    if (in_XMM0_Da < *(float*)¶m_2) { // Compare as floats (casting dereference)
        in_XMM0_Da = *(float*)¶m_2;
    }
    return in_XMM0_Da;
}