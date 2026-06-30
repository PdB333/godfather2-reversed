// FUNC_NAME: initKernelPoints
// Address: 0x006e5df0
// Role: Initializes a global sorted list of (x,y) points from -5 to 5 by increasing squared distance from origin, keeping only the 29 closest points. Used for a blur kernel or similar.

#include <cstring>

// Global buffer for 29 pairs of (x,y) signed chars, 58 bytes total
static char kernelBuffer[58]; // corresponds to DAT_0112a960

void initKernelPoints(void)
{
    // Pointer to the start of the buffer for iteration
    char *pPair = kernelBuffer + 1; // starts at second byte, careful with offset

    // Initialize all pairs to (99,99) (large distance marker)
    do {
        pPair[-1] = 99;  // previous byte
        *pPair = 99;     // current byte
        pPair += 2;
    } while (pPair < kernelBuffer + 59); // 0x112a99b relative: kernelBuffer + 59

    int x = -5;
    int y = -5;
    int squaredX = 25; // x*x for x=-5

    do {
        // y loops from -5 to 5
        do {
            int squaredDist = y * y + squaredX; // x^2 + y^2

            // Scan through existing sorted kernel points
            char *scan = kernelBuffer; // address of first byte of first pair
            int index = 0;
            do {
                // Compute squared distance of stored point
                int storedDist = (int)*scan * (int)*scan + (int)scan[1] * (int)scan[1];

                if (squaredDist < storedDist) {
                    // Insert new point at this index, shift rest right
                    if (index != 28) { // 0x1c = 28 (0-indexed, move elements from index to end)
                        memmove(&kernelBuffer[2 + index * 2], // +0x112a962 offset? Actually kernelBuffer+2+index*2
                               &kernelBuffer[index * 2], // +0x112a960+index*2
                               (28 - index) * 2); // 0x1c-index is number of pairs to shift
                    }
                    // Write the new point (x,y) as signed chars
                    *scan = (char)x;
                    scan[1] = (char)y;
                    break;
                }
                scan += 2;
                index++;
            } while (scan < kernelBuffer + 58); // 0x112a99a

            y++;
            if (y > 5) {
                break;
            }
        } while (true);

        x++;
        if (x > 5) {
            return;
        }
        squaredX = x * x;
        y = -5;
    } while (true);
}