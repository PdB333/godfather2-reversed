// FUNC_NAME: rotateElements (array rotation by offset, similar to std::rotate)
// Address: 0x00588e00
// Rotates an array of 32-bit elements in-place so that the element at 'offset' becomes the first.
// Parameters:
//   begin - start of array
//   end - end of array (exclusive)
//   offset - pointer to the element that will become the new first element (must be within [begin, end))
void rotateElements(uint32_t* begin, uint32_t* end, uint32_t* offset) {
    int32_t totalLength = (end - begin);  // number of uint32 elements
    int32_t offsetIndex = (offset - begin);

    // Compute GCD of totalLength and offsetIndex (Euclidean algorithm)
    int32_t a = offsetIndex;
    int32_t b = totalLength;
    int32_t gcd = a;
    while (gcd != 0) {
        int32_t temp = b % gcd;
        b = gcd;
        gcd = temp;
    }
    gcd = b;

    // If GCD is valid and less than total length, perform cycle rotation
    if ((gcd < totalLength) && (0 < gcd)) {
        uint32_t* currentCycleStart = begin + gcd;  // start from the last cycle group
        do {
            currentCycleStart--;
            uint32_t savedValue = *currentCycleStart;
            uint32_t* src = currentCycleStart + offsetIndex;
            uint32_t* dst = currentCycleStart;

            // Wrap around if src goes beyond end
            if (src >= end) {
                src = begin + (offsetIndex - (end - src));
            }

            // Walk the cycle
            while (src != currentCycleStart) {
                *dst = *src;
                int32_t stepsToEnd = (end - src);
                dst = src;
                if (offsetIndex < stepsToEnd) {
                    src = src + offsetIndex;
                } else {
                    src = begin + (offsetIndex - stepsToEnd);
                }
            }

            *dst = savedValue;
            gcd--;
        } while (0 < gcd);
    }
}