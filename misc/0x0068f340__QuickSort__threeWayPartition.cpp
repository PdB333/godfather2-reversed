// FUNC_NAME: QuickSort::threeWayPartition
// Function at 0x0068f340 - Internal three-way partition for quicksort.
// Partitions integer array [first, last) and returns boundaries of equal range.
void threeWayPartition(int** outBounds, int* first, int* last, int (*compare)(int,int))
{
    int *mid, *leftEq, *rightEq, *i, *j;
    int temp;

    // Compute midpoint index (element count / 2)
    mid = first + ((( (int)last - (int)first >> 2) - ((int)last - (int)first >> 0x1f)) >> 1);

    // Place pivot at end using median-of-three (calls FUN_0068f140)
    medianOfThree(first, mid, last - 1, compare);

    leftEq = mid; // start from midpoint
    // Move leftEq leftwards while elements are equal
    while (first < leftEq &&
           (*compare)(leftEq[-1], *leftEq) == 0 &&
           (*compare)(*leftEq, leftEq[-1]) == 0)
        leftEq--;

    do {
        rightEq = rightEq + 1;
        i = rightEq;
        j = leftEq;
        if (last <= rightEq || (*compare)(*rightEq, *leftEq) != 0)
            break;
        if ((*compare)(*leftEq, *rightEq) != 0)
            goto label1;
        // Elements equal, no swap needed? (Original code only has assignment before label)
        // Actually original does not swap here; it continues after check.
    } while (true);

label1:
    do {
        if (last <= i)
            goto label2;
        // Compare *leftEq with *i
        if ((*compare)(*leftEq, *i) == 0) {
            if ((*compare)(*i, *leftEq) != 0)
                goto label2;
            // Swap rightEq and i, then advance rightEq
            temp = *rightEq;
            *rightEq = *i;
            rightEq = rightEq + 1;
            *i = temp;
        }
        i = i + 1;
    } while (true);

label2:
    for (; first < j; j = j - 1) {
        if ((*compare)(j[-1], *leftEq) == 0) {
            if ((*compare)(*leftEq, j[-1]) != 0)
                break;
            // Swap leftEq-1 with j-1
            temp = leftEq[-1];
            leftEq = leftEq - 1;
            *leftEq = j[-1];
            j[-1] = temp;
        }
    }

    if (j == first) {
        if (i == last) {
            // Both sides fully processed – store boundaries
            outBounds[0] = leftEq;
            outBounds[1] = rightEq;
            return;
        }
        if (rightEq != i) {
            // Swap pivot with rightEq
            temp = *leftEq;
            *leftEq = *rightEq;
            *rightEq = temp;
        }
        // Move pivot into place
        temp = *leftEq;
        *leftEq = *i;
        rightEq = rightEq + 1;
        leftEq = leftEq + 1;
        *i = temp;
        i = i + 1;
    } else {
        j = j - 1;
        if (i == last) {
            leftEq = leftEq - 1;
            if (j != leftEq) {
                temp = *j;
                *j = *leftEq;
                *leftEq = temp;
            }
            // Swap leftEq with rightEq-1
            temp = *leftEq;
            leftEq = leftEq - 1;
            *leftEq = temp;
            rightEq = rightEq - 1;
        } else {
            // Swap i and j
            temp = *i;
            *i = *j;
            *j = temp;
            i = i + 1;
        }
    }
    goto label1;
}