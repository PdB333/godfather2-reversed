// FUNC_NAME: rotateInt32Array
// Function address: 0x0068e770
// Rotates a range of 32-bit integers [first, last) such that middle becomes the new first element.
// This is the classic "juggling" rotation algorithm, also known as the "reverse array" approach for cyclic rotations.
// Parameters:
//   first  - pointer to the start of the array (lowest address)
//   middle - pointer to the element that should become the new first element after rotation
//   last   - pointer to one past the last element of the array
// Precondition: first <= middle <= last, and the array is contiguous in memory.
// Postcondition: The elements are rotated left by (middle - first) positions.
void rotateInt32Array(int32_t* first, int32_t* middle, int32_t* last)
{
    int32_t n = last - first;          // Total number of elements in the range
    int32_t k = middle - first;        // Number of positions to rotate left (distance from first to middle)

    // Compute gcd(n, k) using Euclidean algorithm
    int32_t a = k;
    int32_t b = n;
    while (b != 0)
    {
        int32_t r = a % b;
        a = b;
        b = r;
    }
    int32_t gcd = a;

    // No rotation needed if gcd is zero or >= n (which would imply rotation by full length)
    if (gcd >= n || gcd <= 0)
        return;

    // Process each cycle of the permutation
    // The algorithm visits each cycle in descending order of starting index (gcd..1)
    for (int32_t i = gcd; i > 0; --i)
    {
        int32_t* current = first + i;      // Starting element of this cycle (1-based index)
        int32_t saved = *current;          // Save the value at the cycle start

        // Move elements along the cycle until we return to the starting position
        do
        {
            // Determine the next element in the cycle: move forward by k positions,
            // wrapping around if we go past the end
            int32_t dist_to_end = last - current;  // Number of elements from current to last
            int32_t* next;
            if (k < dist_to_end)
                next = current + k;
            else
                next = first + (k - dist_to_end);  // Wrap around

            *current = *next;   // Shift the element left by k positions
            current = next;
        } while (current != first + i);  // Continue until we come back to the cycle start

        *current = saved;  // Place the saved value at the cycle start
    }
}