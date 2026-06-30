// FUNC_NAME: insertSortedDescending
// Address: 0x007168b0
// Purpose: Inserts a 3D point (x, y, z) into an array of points sorted in descending order by (y, x).
// The array is sorted lexicographically: first by y descending, then by x descending.
// Returns the new count after insertion. If count is 0, insertion always succeeds.
// Parameters: array (in EDI), count (in EDX), x (in XMM1), y (in XMM0), z (on stack as param_3)
// Note: The original __fastcall signature is adapted to C++ for clarity.

struct Vector3 {
    float x; // offset +0x00
    float y; // offset +0x04
    float z; // offset +0x08
};

int __fastcall insertSortedDescending(Vector3* array, unsigned int count, float x, float y, float z)
{
    unsigned int insertIndex = 0;
    Vector3* current = array;

    if (count != 0) {
        do {
            // Check if current element is smaller than new element (descending order)
            // Condition: (current.y < new.y) OR (current.y == new.y AND current.x < new.x)
            if ((current->y <= y && y != current->y) ||
                (current->x <= x && x != current->x))
            {
                // Found insertion point: shift all elements from insertIndex onward right by 1
                if (insertIndex < count) {
                    Vector3* dest = array + count * 3; // one past end after shift? careful: array + count*3 is beyond valid elements? Actually array+count is the past-the-end. But we shift elements starting from current? The code sets pfVar1 = unaff_EDI + param_2 * 3; which is array + count (in float units). That is one slot past the last element. Then it copies from that position -3 to that position, moving elements right by one slot. So count-insertIndex elements are shifted.
                    int numToShift = count - insertIndex;
                    Vector3* src = current + (numToShift - 1); // Actually the loop copies from pfVar1 - 3 to pfVar1, decrementing. So we implement a memmove-like loop.
                    do {
                        *dest = *src;
                        dest--;
                        src--;
                        numToShift--;
                    } while (numToShift != 0);
                }
                break;
            }
            insertIndex++;
            current++;
        } while (insertIndex < count);
    }

    // Write the new element at the insertion index
    Vector3* insertionPoint = array + insertIndex;
    insertionPoint->y = y;   // Note: order is swapped? The original sets pfVar1[1] = in_XMM0_Da (y) and *pfVar1 = in_XMM1_Da (x). So y is stored at offset +0x04, x at +0x00. That's consistent with our Vector3 struct if we consider y as the sort key first.
    insertionPoint->x = x;
    insertionPoint->z = z;

    return count + 1;
}