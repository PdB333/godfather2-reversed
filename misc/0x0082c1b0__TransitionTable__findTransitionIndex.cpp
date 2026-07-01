// FUNC_NAME: TransitionTable::findTransitionIndex

// This function finds the index of the transition segment that contains the given value.
// The table stores a circular array of control points, and each edge from index i to i+1 (wrapping)
// defines a range. FUN_00821840 is a comparison function that checks if the value falls within
// the range defined by two consecutive control points.
//
// Structure at 'this':
// +0x4: uint m_currentIndex (preferred starting search index)
// +0x8: int* m_pControlPoints (array of pointers to control point structures)
// +0xc: uint m_count (number of control points)
//
// Each control point structure contains data at +0x4 (e.g., a float or key value).

uint __thiscall TransitionTable::findTransitionIndex(void* this, uint paramValue)
{
    uint count = *(uint*)((int)this + 0xc);
    if (count == 0) {
        return 0xffffffff;
    }
    if (count == 1) {
        return 0;
    }

    uint currentIndex = *(uint*)((int)this + 0x4);
    uint nextIndex;
    if (currentIndex < count - 1) {
        nextIndex = currentIndex + 1;
    } else {
        nextIndex = 0;
    }

    // Try the current edge first
    char result = FUN_00821840(paramValue,
                               *(int*)(*(int*)((int)this + 0x8) + currentIndex * 4) + 4,
                               *(int*)(*(int*)((int)this + 0x8) + nextIndex * 4) + 4);
    if (result != '\0') {
        return currentIndex;
    }

    // Fallback: search all edges
    uint limit = *(uint*)((int)this + 0xc);
    uint i = 0;
    if (limit != 0) {
        do {
            uint j;
            if (i < limit - 1) {
                j = i + 1;
            } else {
                j = 0;
            }
            result = FUN_00821840(paramValue,
                                  *(int*)(*(int*)((int)this + 0x8) + i * 4) + 4,
                                  *(int*)(*(int*)((int)this + 0x8) + j * 4) + 4);
            if (result != '\0') {
                return i;
            }
            limit = *(uint*)((int)this + 0xc);
            i++;
        } while (i < limit);
    }
    return 0xffffffff;
}