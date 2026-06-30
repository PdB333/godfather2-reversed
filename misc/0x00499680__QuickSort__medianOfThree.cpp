// FUNC_NAME: QuickSort::medianOfThree
// Address: 0x00499680
// Role: Selects a pivot element using median-of-three (or median-of-five/nine for larger arrays)
//        and orders the chosen elements so that *left <= *pivot <= *right (or similar).
//        For small partitions (size < 41), it only sorts the three selected positions.

void __thiscall QuickSort::medianOfThree(uint* left, uint* right)
{
    // Number of uint elements in the range [left, right] inclusive?
    // difference >> 2 gives count-1? Actually (right-left) byte diff /4 = number of elements between them.
    int32_t count = (right - left) >> 2;   // +0x04 offset if derived from iterators

    if (count < 0x29)  // 41 elements or fewer -> just sort the three endpoints
    {
        uint pivotVal = *this;  // this is the pivot pointer (passed in ECX)
        if (pivotVal < *left)
        {
            *this = *left;
            *left = pivotVal;
        }
        pivotVal = *right;
        if (pivotVal < *this)
        {
            *right = *this;
            *this = pivotVal;
        }
        pivotVal = *this;
        if (pivotVal < *left)
        {
            *this = *left;
            *left = pivotVal;
        }
    }
    else
    {
        // Compute step = (count+1)/8  (approx 1/8 of the range)
        int32_t step = (count + 1) >> 3;   // +0x00
        uint temp;

        // Sort three elements at left: left[0], left[step], left[step*2]
        // so that left[step] becomes the median
        temp = left[step];
        if (temp < *left)
        {
            left[step] = *left;
            *left = temp;
        }
        temp = left[step * 2];
        if (temp < left[step])
        {
            left[step * 2] = left[step];
            left[step] = temp;
        }
        temp = left[step];
        if (temp < *left)
        {
            left[step] = *left;
            *left = temp;
        }

        // Sort three elements around the pivot: *pivot, *(pivot - step), *(pivot + step)
        // so that *pivot becomes the median of the three
        temp = *this;
        uint* prev = this - step;
        if (temp < *prev)
        {
            *this = *prev;
            *prev = temp;
        }
        temp = this[step];
        if (temp < *this)
        {
            this[step] = *this;
            *this = temp;
        }
        temp = *this;
        if (temp < *prev)
        {
            *this = *prev;
            *prev = temp;
        }

        // Sort three elements at the right: *(right - 2*step), *(right - step), *right
        // so that *(right - step) becomes the median
        uint* endPrev = right - step;
        temp = *endPrev;
        uint* endPrev2 = right - step * 2;
        if (temp < *endPrev2)
        {
            *endPrev = *endPrev2;
            *endPrev2 = temp;
        }
        temp = *right;
        if (temp < *endPrev)
        {
            *right = *endPrev;
            *endPrev = temp;
        }
        temp = *endPrev;
        if (temp < *endPrev2)
        {
            *endPrev = *endPrev2;
            *endPrev2 = temp;
        }

        // Final adjustment: Ensure *pivot is median of left[step], *pivot, *endPrev
        temp = *this;
        if (temp < left[step])
        {
            *this = left[step];
            left[step] = temp;
        }
        temp = *endPrev;
        if (temp < *this)
        {
            *endPrev = *this;
            *this = temp;
        }
        temp = *this;
        if (temp < left[step])
        {
            *this = left[step];
            left[step] = temp;
        }
    }
}