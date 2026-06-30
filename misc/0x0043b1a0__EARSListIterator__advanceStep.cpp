// FUNC_NAME: EARSListIterator::advanceStep
// Function at 0x0043b1a0: Advances an internal list/array iterator.
// Expects a structure with fields (offsets from this pointer):
//   +0x00: unsigned char isDone;       // flag: 0 = forward, non-zero = backward? 
//   +0x0C: int currentIndex;           // current position
//   +0x10: int elementCount;           // total number of elements
//   +0x5C: void** pDataOrNode;         // pointer to current node or data pointer
//
// If !isDone (forward iteration):
//   If currentIndex >= 0:
//     If currentIndex < elementCount - 1:
//       pDataOrNode = *pDataOrNode + (int)*pDataOrNode; // double dereference? Likely next node
//       currentIndex++;
//     else:
//       pDataOrNode = &DAT_01163cf8; // static sentinel, end of list
//   else: (negative index): pDataOrNode = *pDataOrNode + (int)*pDataOrNode; call FUN_0043b140 (reset?)
// Else (isDone != 0, backward?):
//   currentIndex++;
//   if currentIndex != elementCount:
//     return FUN_0043b0e0(); // returns pointer to previous element?
//   else:
//     (end reached, returns this pointer)

char* __fastcall EARSListIterator::advanceStep(char* thisPtr)
{
    char* result;

    if (thisPtr[0] == '\0') { // forward iteration
        if (*(int*)(thisPtr + 0x0C) >= 0) {
            if (*(int*)(thisPtr + 0x0C) < *(int*)(thisPtr + 0x10) - 1) {
                // Advance to next node: move to the pointer stored in the current node
                *(int**)(thisPtr + 0x5C) = (int**)(
                    **(int**)(thisPtr + 0x5C) + (int)*(int**)(thisPtr + 0x5C)
                );
                (*(int*)(thisPtr + 0x0C))++;
                return thisPtr;
            }
            // Reached end of list, set to static sentinel
            *(int**)(thisPtr + 0x5C) = &DAT_01163cf8;
            return thisPtr;
        }
        // Negative index case: maybe was reset? Advance node anyway.
        *(int**)(thisPtr + 0x5C) = (int**)(
            **(int**)(thisPtr + 0x5C) + (int)*(int**)(thisPtr + 0x5C)
        );
        FUN_0043b140(); // related to reset or backward orientation
    }
    else {
        // Backward iteration (isDone != 0)
        (*(int*)(thisPtr + 0x0C))++;
        if (*(int*)(thisPtr + 0x0C) != *(int*)(thisPtr + 0x10)) {
            result = (char*)FUN_0043b0e0(); // get previous element pointer?
            return result;
        }
    }
    return thisPtr;
}