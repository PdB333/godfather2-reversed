// FUNC_NAME: ExpressionCompiler::remapReferences
// Address: 0x0063fcb0
// Role: Iterates a linked list of variable references and remaps any with matching IDs to the current temp variable index. If any remapping occurred, emits a new temp variable and increments the complexity counter. If complexity exceeds max, reports error "function or expression too complex".

void __fastcall ExpressionCompiler::remapReferences(int this, int* listHead) // listHead passed in EAX
{
    int* state = *(int**)(this + 0x1c);      // +0x1c: pointer to compiler state
    int newTempIndex = state[9];              // current temp variable counter (starts at some base)
    bool bRemapped = false;

    if (listHead == nullptr)
        return;

    int* current = listHead;
    int baseId = *(int*)(unaff_EDI + 4);     // ID of the current function/locals block (EDI assumed to hold a struct pointer, +4 = ID)

    do {
        if (current[1] == 8) {               // +4: type field, 8 = variable reference
            if (current[2] == baseId) {      // +8: source variable ID
                bRemapped = true;
                current[2] = newTempIndex;    // reassign to current temp index
            }
            if (current[3] == baseId) {      // +12: destination variable ID
                bRemapped = true;
                current[3] = newTempIndex;
            }
        }
        current = (int*)*current;             // linked list next pointer
    } while (current != nullptr);

    if (bRemapped) {
        // Emit a new temp variable entry: combine baseId and newTempIndex into a handle, then call emission function
        int handle = (newTempIndex << 9 | baseId) << 0xf;  // packed handle?
        emitTempVariable(handle, *(int*)(state[3] + 8));   // state[3] some buffer, +8 = extra data

        // Increment temp counter
        int newCount = newTempIndex + 1;
        int* header = (int*)*state;          // first word of state points to some header
        if ((int)(uint)*(byte*)(header + 0x47) < newCount) { // +0x47: max temp count (byte)
            if (newCount > 0xf9) {
                // Error: too complex
                int* errorBuf = (int*)state[3];
                reportError("function or expression too complex");
                // note: error reporting may change extraout_ECX, but we ignore
            }
            *(char*)(header + 0x47) = (char)newCount; // update max
        }
        state[9] = newCount;                 // store new counter
    }
}