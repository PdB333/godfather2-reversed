// FUNC_NAME: StackEvaluator::findMinValue (address 0x006322f0)
// This function appears to evaluate the minimum value from a stack of values (with type constraints).
// It is likely part of the EARS expression/stack evaluator used for AI or script logic.
// Stack entries are 8 bytes: int type (0=?, 3=number constant, 4=variable/expression) and float value.
// Structure offsets:
//   +0x08: current stack pointer (next free slot)
//   +0x0c: base pointer of allocated stack memory
//   +0x10: pointer to an outer context? Used for negative index -10000
//   +0x40: pointer to a special register? Used for negative index -0x2711

int __thiscall StackEvaluator::findMinValue(int this) {
    float minVal;
    float curVal;
    int type;
    int i;
    int elemCount;
    int *entryPtr;
    int *stackBase;
    int baseOffset;
    int result;

    // Get base and number of entries on stack
    entryPtr = *(int **)(this + 0x0c);               // base of stack
    elemCount = (int)(*(int **)(this + 8) - entryPtr) >> 3;  // each entry is 8 bytes
    if (*(int **)(this + 8) <= entryPtr) goto error; // if stack empty
    if (entryPtr == (int *)0x0) goto error;           // safety

    // Check type of the first entry: must be 3 (number) or 4 (variable)
    if (*entryPtr != 3) {
        if (*entryPtr != 4) goto error;               // unsupported type
        // For type 4, attempt to resolve the variable to a number
        result = FUN_00636850(&minVal);               // likely resolves variable to float
        if (result == 0) goto error;                 // resolution failed
        // Override entry pointer to a temporary local with type 3
        type = 3;
        curVal = minVal;
        entryPtr = &type;  // point to local stack (dangerous, but for reassignment)
    }

    // Read the value from the first (or resolved) entry
    minVal = (float)entryPtr[1];                     // the float value

    // If minVal equals a global sentinel (likely uninitialized/empty), find first valid entry
    if (minVal == DAT_00e2b05c) {                    // sentinel constant
        // Loop to find first entry that is type 3 or type 4 (resolvable)
        while ((entryPtr = *(int **)(this + 0x0c),   // reset to base
                *(int **)(this + 8) <= entryPtr) ||  // stack empty
               (entryPtr == (int *)0x0) ||
               ((*entryPtr != 3 && ((*entryPtr != 4 || (result = FUN_00636850(&curVal), result == 0)))))) {
            FUN_00627ac0(PTR_s_number_00e2a8a8);    // error: "number" expected
error:
            minVal = 0.0f;
        }
    }

    // If there are more than 1 element, iterate to find the minimum
    if (1 < elemCount) {
        i = 2;  // start at index 2 (0-based? Actually indices: first is 0, then 1? but code uses 2 as first loop)
        do {
            curVal = (float)FUN_006259b0(this, i);  // retrieve value at index i
            // If the retrieved value is 0, may indicate a special sentinel; handle by finding alternative
            if (curVal == 0.0f) {
                if (i < 1) goto skipCheck;           // fallback to error
                entryPtr = (int *)(*(int *)(this + 0x0c) + -8 + i * 8);  // compute address
                if (entryPtr < *(int **)(this + 8)) goto checkValid;  // if within valid range, skip error
                // Otherwise, enter error loop and handle negative indices
                do {
                    FUN_00627ac0(PTR_s_number_00e2a8a8);  // error
skipCheck:
                    // Handle special negative indices
                    if (i < -9999) {
                        if (i == -0x2711) {                 // -10001 -> special register
                            entryPtr = (int *)(this + 0x40);
                        }
                        else if (i == -10000) {              // -10000 -> context base +0x2c
                            entryPtr = (int *)(*(int *)(this + 0x10) + 0x2c);
                        }
                        else {
                            // Other negative indices: offset from a base at (current entry?)-4
                            baseOffset = *(int *)(*(int *)(this + 0x0c) + -4);
                            // Check if index is within valid range
                            if ((int)(uint)*(byte *)(baseOffset + 7) < -0x2711 - i) {
                                entryPtr = (int *)0x0;
                            }
                            else {
                                entryPtr = (int *)(baseOffset + 8 + (-0x2711 - i) * 8);
                            }
                        }
                    }
                    else {
                        // Positive or small negative: treat as relative offset from current stack end
                        entryPtr = (int *)(*(int *)(this + 8) + i * 8);
                    }
checkValid:
                } while ((entryPtr == (int *)0x0) ||
                         ((*entryPtr != 3 && ((*entryPtr != 4 || (result = FUN_00636850(&type), result == 0))))));
            }

            // Update minimum if current value is smaller
            if (curVal < minVal) {
                minVal = curVal;
            }
            i = i + 1;
        } while (i <= elemCount);
    }

    // Push the result onto the stack: type 3 (number constant) with the found minimum
    *(int *)(this + 8) = *(int *)(this + 8) + 8;     // advance stack pointer
    *(int *)(*(int *)(this + 8) - 8) = 3;            // store type
    *(float *)(*(int *)(this + 8) - 4) = minVal;     // store value
    return 1;                                          // success
}