// FUNC_NAME: ScriptVM::opPushInt32
int __thiscall ScriptVM::opPushInt32(int this, int value) {
    // Access code block structure at offset 0x10
    CodeBlock* codeBlock = *(CodeBlock**)(this + 0x10);
    // Check instruction pointer bounds
    if (codeBlock->currentInstruction >= codeBlock->instructionLimit) {
        assertionFailed(); // FUN_00627360
    }

    // Allocate a new Int32Object (class ID 4)
    Int32Object* obj = (Int32Object*)allocateObject(4); // FUN_00638a40
    if (obj == nullptr) {
        logError("Failed to create %s object.\n","Int32"); // FUN_00627bd0
        debugBreak(); // swi(3)
        return 0;
    }

    // Get current stack pointer (points to next free slot)
    StackEntry** stackPtr = (StackEntry**)(this + 8);
    StackEntry* entry = *stackPtr;
    // Push type tag 7 (Int32) and object pointer onto the stack
    entry->type = 7; // StackType::Int32
    entry->data = (void*)obj;
    *stackPtr = entry + 1; // advance stack pointer

    // Store the integer value at offset 0x10 in the object
    *(int*)((char*)obj + 0x10) = value;

    // Check if the object needs to be converted to string (debug feature)
    if (checkObjectNeedsToString(this)) { // FUN_00627c90
        printToStringWarning(&PTR_s___tostring_00e325f8); // FUN_004aeb70
    }

    // Post‑stack processing: examine previous two stack entries for an assignment pattern
    StackEntry* topEntry = *stackPtr - 1; // the just‑pushed entry (type 7, data = obj)
    StackEntry* prevEntry = topEntry - 1; // entry below top
    StackEntry* twoBelow = topEntry - 2; // entry two below top

    // If the entry just pushed has a null type (type 0), use a different source for the value
    // (This path handles a separate case, e.g., a compound assignment)
    if (prevEntry->type == 0) {
        // Use the code block's internal data at offset 0x34
        twoBelow = (StackEntry*)(*(int*)(this + 0x10) + 0x34);
    }

    // Check the type of the entry two below the top
    if (twoBelow->type == 5) {
        // Type 5 indicates a variable reference; store the new Int32 object's pointer
        // into the variable object's field at offset 8
        void* varObject = prevEntry->data;
        *(void**)((char*)varObject + 8) = (void*)obj;
    }
    else if (twoBelow->type == 7) {
        // Type 7 indicates another Int32; same store operation but then pop the top
        void* varObject = prevEntry->data;
        *(void**)((char*)varObject + 8) = (void*)obj;
        // Pop the pushed Int32 entry (remove it from stack)
        *stackPtr = *stackPtr - 1;
        return 1;
    }

    // For non‑7 types, just pop the top and return
    *stackPtr = *stackPtr - 1;
    return 1;
}