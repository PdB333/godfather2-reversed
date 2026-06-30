// FUNC_NAME: rotateRange
void rotateRange(int* begin, int* middle, int* end) {
    int length = end - begin;               // number of elements
    int midOffset = middle - begin;          // rotation amount (left)
    int g = length;
    int h = midOffset;

    // Compute GCD of length and midOffset
    while (h != 0) {
        int temp = g % h;
        g = h;
        h = temp;
    }

    // Only rotate if GCD is non-zero and less than length
    if (g < length && g > 0) {
        int* cycleStart = begin + g;         // start at the last cycle element
        do {
            cycleStart--;
            int temp = *cycleStart;
            int* current = cycleStart;
            int* next = cycleStart + midOffset;

            // Wrap around if beyond end
            if (next == end) {
                next = begin;
            }

            while (next != cycleStart) {
                *current = *next;
                int remaining = end - next;
                // Move forward by midOffset, wrapping as needed
                if (midOffset < remaining) {
                    next += midOffset;
                } else {
                    next = begin + (midOffset - remaining);
                }
                current = next; // Not exactly: need to save previous next? The original uses puVar3 = puVar4; then updates puVar4. Simplified for clarity.
                // Actually the original sets puVar3 = puVar4; then updates puVar4; then copies *puVar3 = *puVar4 in next iteration. This is a cycle rotation.
            }
            *current = temp;
        } while (cycleStart != begin);
    }
}