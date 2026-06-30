// FUNC_NAME: binarySearchLowerBound
int* __fastcall binarySearchLowerBound(int* arrayStart, int* arrayEnd, int* key, int (*comparator)(int, int))
{
    // This function implements a binary search to find the insertion point for a key in a sorted array.
    // It returns a pointer to the first element for which the comparator returns non-zero (i.e., key > element?).
    // Parameters:
    //   arrayStart - pointer to start of array (in ECX or stack? actual param_1)
    //   arrayEnd   - pointer to end of array (passed in EAX in original, here as explicit second param)
    //   key        - pointer to the key value (param_2)
    //   comparator - comparison function: returns non-zero if key > element (param_3)
    // The array elements are 4 bytes each (int or pointer).

    int count = (arrayEnd - arrayStart); // Number of elements (since pointer diff is in int* units)
    int* result = arrayStart;

    while (count > 0)
    {
        int half = count / 2;
        int cmpResult = comparator(result[half], *key);
        if (cmpResult != 0)
        {
            result = &result[half + 1]; // Move past the half-th element
            count = count - half - 1;
        }
        else
        {
            count = half; // Search in lower half
        }
    }
    return result;
}