// FUNC_NAME: AnimationNode::evaluateBlend (likely part of EARS animation system)
// Address: 0x005dc6e0
// Purpose: Takes a float array of blend parameters and applies them to a node, using either COMBINE or REPLACE mode.
//          Mode is determined by param[7] (non-zero => REPLACE). Calls into lower-level blend function.

undefined4 __thiscall AnimationNode::evaluateBlend(float *params)
{
    int iVar1;
    undefined1 *puVar2;
    undefined4 uVar3;
    char *modeStr;
    char buffer[39]; // Local buffer for blend output? (size 39 likely 39 bytes)
    
    // Get the node object from some manager (likely ID stored in this? but in_EAX is used as this)
    // For now, assume this function is a member, and the first thing is to get the node from a pool.
    // In Ghidra, in_EAX would be the implicit 'this' pointer.
    // But the actual call to FUN_005dc670 uses in_EAX as argument.
    // That suggests FUN_005dc670 might be a method of another class? Or it's a global function taking this pointer.
    // Let's interpret as: node = getNode(this) where this is some handle/ID.
    iVar1 = AnimationNodeManager::getNode(this); // FUN_005dc670 likely returns node pointer or 0
    if (iVar1 != 0) {
        // Choose blend mode based on params[7] (index 7 -> the 8th float, often used as mode flag)
        if (params[7] != 0.0f) {
            modeStr = "REPLACE";
        } else {
            modeStr = "COMBINE";
        }
        
        // Push some global state? Possibly for logging or debug.
        FUN_004d9080(); // Unclear function, maybe debug push or stack marker
        
        // Get blend source data from node; offset 0x2A0 is likely a pointer to a source animation or bone data.
        puVar2 = *(undefined1 **)(iVar1 + 0x2A0);
        if (puVar2 == (undefined1 *)0x0) {
            // Use default string/pointer if null (DAT_0120546e is a placeholder string, maybe "NONE" or empty)
            puVar2 = &DAT_0120546e;
        }
        
        // Call the actual blend function with parameters:
        // - source data pointer
        // - params[0..6] as doubles (likely blending factors or weights)
        // - mode string ("COMBINE" or "REPLACE")
        // - buffer for result (size 39 bytes)
        // The function uses doubles, so the original params are floats but converted to double.
        FUN_005dbc10(puVar2, 
                     (double)params[0], (double)params[1], 
                     (double)params[3], (double)params[4], 
                     (double)params[5], (double)params[6], 
                     modeStr, buffer);
        
        // Perform final processing and return result (likely an error code or handle)
        uVar3 = FUN_005dd3f0(); // Might be finalize or get result ID
        return uVar3;
    }
    return 0;
}