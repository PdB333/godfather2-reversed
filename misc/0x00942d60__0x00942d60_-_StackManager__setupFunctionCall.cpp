// FUNC_NAME: 0x00942d60 - StackManager::setupFunctionCall

// Reconstructed C++ for EA EARS engine - sets up arguments for a function call via stack manipulation
// param_1: Pointer to a context structure (contains a stack pointer at offset +0x18)
// param_2: Pointer to a function to call with prepared arguments

void StackManager::setupFunctionCall(int context, undefined4 *funcPtr)
{
    undefined4 uVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    int iVar4;
    uint uVar5;
    undefined4 *puVar6;
    undefined4 *puVar7;
    undefined4 localArgs[13]; // sized based on loop count (0xD)
    undefined4 alignedStack[9]; // +0x60 offset area
    // note: actual locals may overlap, but we simplify

    // Initialize localArgs from global constants (likely type descriptors or constants)
    localArgs[0] = DAT_00d8b2ac;
    localArgs[1] = DAT_00d8b2ac;
    localArgs[2] = DAT_00d8b2a4;
    localArgs[3] = DAT_00d5f378;
    localArgs[4] = DAT_00e446f4;
    localArgs[5] = 0;
    localArgs[6] = DAT_00d8b2a0;
    localArgs[7] = DAT_00d8b29c;
    localArgs[8] = DAT_00d8b298;
    localArgs[9] = DAT_00d8b2a8;
    localArgs[10] = _DAT_00d5780c; // overlap with smaller symbol
    localArgs[11] = DAT_00d75ca0;
    localArgs[12] = _DAT_00d5780c;

    // Retrieve current stack pointer from context
    uVar2 = **(undefined4 **)(context + 0x18); // first word at stack pointer
    uVar5 = (int)*(undefined4 **)(context + 0x18) + 0x13U & 0xfffffff0; // align to 16

    // Read specific values from aligned stack area
    uVar1 = *(undefined4 *)(uVar5 + 0x60);
    *(uint *)(context + 0x18) = uVar5 + 0x60; // update stack pointer

    // Store pointer to aligned stack into context at +0x18?
    *(undefined4 **)(context + 0x18) = (undefined4 *)(uVar5 + 100); // +0x64
    uVar3 = *(undefined4 *)(uVar5 + 100);
    // Set additional stack push parameters (likely metadata)
    uStack_54 = 4;  // count?
    *(uint *)(context + 0x18) = uVar5 + 0x68;
    uStack_58 = 0x34; // size?
    puStack_5c = localArgs; // pointer to args buffer
    uStack_60 = 0x942e68; // some code address? Might be a resolver stub

    // Call internal helper (perhaps finalizes stack frame or validates)
    FUN_0049c470(); // may be StackBase::prepareCall or similar

    // Copy constant arguments to aligned stack area (13 dwords = 52 bytes)
    puVar6 = localArgs;
    puVar7 = alignedStack;
    for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
    }

    // Call the target function with the prepared stack values
    // arguments: original stack pointer high word, aligned stack base,
    //            base+0x10, base+0x20, plus two values from stack
    (*(code *)*funcPtr)(uVar2, uVar5, uVar5 + 0x10, uVar5 + 0x20, uVar1, uVar3);
}