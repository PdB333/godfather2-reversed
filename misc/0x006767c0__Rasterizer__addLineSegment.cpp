// FUNC_NAME: Rasterizer::addLineSegment
// Function address: 0x006767c0
// Role: Inserts a line segment into a bucket-based edge buffer using a DDA algorithm.
// The line is defined by integer coordinates (x1,y1) to (x2,y2). The function handles
// both horizontal and vertical dominant directions, inserting nodes into sorted linked lists
// per bucket (64-unit steps). Supports both small and large delta paths.

void Rasterizer::addLineSegment(int x1, int y1, int x2, int y2)
{
    int *listHead;
    int *currentNode;
    int deltaX, deltaY;
    int stepX, stepY;
    int bucketIndex;
    int interpolatedValue;
    uint *newNode;
    uint *allocPtr;
    uint key;
    bool increasing;
    int baseCoord;
    int startCoord;
    int endCoord;
    int *bucketArray;
    int bucketOffset;

    // Adjust coordinates if they have sub-pixel alignment (low 6 bits == 0x20)
    if (((byte)x1 & 0x3f) == 0x20) {
        x1 = x1 - 1;
    }
    if (((byte)y1 & 0x3f) == 0x20) {
        y1 = y1 - 1;
    }
    if (((byte)x2 & 0x3f) == 0x20) {
        x2 = x2 - 1;
    }
    if (((byte)y2 & 0x3f) == 0x20) {
        y2 = y2 - 1;
    }

    // Only process if the enable flag is set (offset +0x2209)
    if (*(char *)(this + 0x2209) != '\0') {
        // Horizontal-dominant case (x direction)
        if (x1 < x2) {
            deltaX = x2 - x1;
            increasing = true;
            stepY = y2;
            startCoord = x1;
            baseCoord = y1;
            endCoord = x2;
        } else if (x1 > x2) {
            deltaX = x1 - x2;
            increasing = false;
            stepY = y1;
            startCoord = x2;
            baseCoord = y2;
            endCoord = x1;
        } else {
            goto verticalCase;
        }

        // Align start to next bucket boundary (64-unit aligned)
        bucketIndex = (startCoord + 0x1fU & 0xffffffc0) + 0x20;
        if (bucketIndex <= endCoord) {
            int deltaY = stepY - baseCoord;
            bucketArray = (int *)(*(int *)(this + 0x15c) + (bucketIndex >> 6) * 4); // +0x15c: horizontal bucket array

            if ((*(int *)(this + 0x48) == 0) || // +0x48: useSimplePath flag
                ((deltaX < 0xb504 && (deltaY < 0xb504) && (-0xb504 < deltaY)))) {
                // Small delta path: direct integer arithmetic
                int step = (bucketIndex - startCoord) * deltaY;
                do {
                    listHead = (int *)*bucketArray;
                    allocPtr = *(uint **)(this + 0x16c); // +0x16c: allocation pointer
                    key = (step / deltaX + baseCoord) * 2 | (uint)increasing;
                    if (*(uint **)(this + 0x170) <= allocPtr) { // +0x170: allocation limit
                        allocPtr = (uint *)allocateNode(); // FUN_00676300
                    }
                    *(int *)(this + 0x16c) = *(int *)(this + 0x16c) + 8;
                    *allocPtr = key;
                    if ((listHead == (int *)0x0) || ((int)key < *listHead)) {
                        allocPtr[1] = (uint)listHead;
                        *bucketArray = (uint)allocPtr;
                    } else {
                        for (currentNode = (int *)listHead[1]; 
                             (currentNode != (int *)0x0 && (*currentNode <= (int)key));
                             currentNode = (int *)currentNode[1]) {
                            listHead = currentNode;
                        }
                        allocPtr[1] = (uint)currentNode;
                        listHead[1] = (int)allocPtr;
                    }
                    step = step + deltaY * 0x40;
                    bucketIndex = bucketIndex + 0x40;
                    bucketArray = bucketArray + 1;
                } while (bucketIndex <= endCoord);
            } else {
                // Large delta path: use fixed-point helpers
                do {
                    listHead = (int *)*bucketArray;
                    fixedPointMultiply(); // FUN_00676090
                    int temp = fixedPointDivide(); // FUN_00676010
                    allocPtr = *(uint **)(this + 0x16c);
                    key = (temp + baseCoord) * 2 | (uint)increasing;
                    if (*(uint **)(this + 0x170) <= allocPtr) {
                        allocPtr = (uint *)allocateNode();
                    }
                    *(int *)(this + 0x16c) = *(int *)(this + 0x16c) + 8;
                    *allocPtr = key;
                    if ((listHead == (int *)0x0) || ((int)key < *listHead)) {
                        allocPtr[1] = (uint)listHead;
                        *bucketArray = (uint)allocPtr;
                    } else {
                        for (currentNode = (int *)listHead[1]; 
                             (currentNode != (int *)0x0 && (*currentNode <= (int)key));
                             currentNode = (int *)currentNode[1]) {
                            listHead = currentNode;
                        }
                        allocPtr[1] = (uint)currentNode;
                        listHead[1] = (int)allocPtr;
                    }
                    bucketIndex = bucketIndex + 0x40;
                    bucketArray = bucketArray + 1;
                } while (bucketIndex <= endCoord);
            }
        }
    }

verticalCase:
    // Vertical-dominant case (y direction)
    if (y1 < y2) {
        deltaY = y2 - y1;
        increasing = true;
        stepX = x2;
        startCoord = y1;
        baseCoord = x1;
        endCoord = y2;
    } else if (y1 > y2) {
        deltaY = y1 - y2;
        increasing = false;
        stepX = x1;
        startCoord = y2;
        baseCoord = x3;
        endCoord = y1;
    } else {
        return;
    }

    bucketIndex = (startCoord + 0x1fU & 0xffffffc0) + 0x20;
    if (bucketIndex <= endCoord) {
        int deltaX = stepX - baseCoord;
        bucketArray = (int *)(*(int *)(this + 0xcc) + (bucketIndex >> 6) * 4); // +0xcc: vertical bucket array

        if ((*(int *)(this + 0x48) != 0) &&
            ((0xb503 < deltaY || (0xb503 < deltaX) || (deltaX < -0xb503)))) {
            // Large delta path for vertical
            do {
                listHead = (int *)*bucketArray;
                fixedPointMultiply();
                int temp = fixedPointDivide();
                allocPtr = *(uint **)(this + 0x16c);
                key = (temp + baseCoord) * 2 | (uint)increasing;
                if (*(uint **)(this + 0x170) <= allocPtr) {
                    allocPtr = (uint *)allocateNode();
                }
                *(int *)(this + 0x16c) = *(int *)(this + 0x16c) + 8;
                *allocPtr = key;
                if ((listHead == (int *)0x0) || ((int)key < *listHead)) {
                    allocPtr[1] = (uint)listHead;
                    *bucketArray = (uint)allocPtr;
                } else {
                    for (currentNode = (int *)listHead[1]; 
                         (currentNode != (int *)0x0 && (*currentNode <= (int)key));
                         currentNode = (int *)currentNode[1]) {
                        listHead = currentNode;
                    }
                    allocPtr[1] = (uint)currentNode;
                    listHead[1] = (int)allocPtr;
                }
                bucketIndex = bucketIndex + 0x40;
                bucketArray = bucketArray + 1;
            } while (bucketIndex <= endCoord);
            return;
        }

        // Small delta path for vertical
        int step = (bucketIndex - startCoord) * deltaX;
        do {
            listHead = (int *)*bucketArray;
            allocPtr = *(uint **)(this + 0x16c);
            key = (step / deltaY + baseCoord) * 2 | (uint)increasing;
            if (*(uint **)(this + 0x170) <= allocPtr) {
                allocPtr = (uint *)allocateNode();
            }
            *(int *)(this + 0x16c) = *(int *)(this + 0x16c) + 8;
            *allocPtr = key;
            if ((listHead == (int *)0x0) || ((int)key < *listHead)) {
                allocPtr[1] = (uint)listHead;
                *bucketArray = (uint)allocPtr;
            } else {
                for (currentNode = (int *)listHead[1]; 
                     (currentNode != (int *)0x0 && (*currentNode <= (int)key));
                     currentNode = (int *)currentNode[1]) {
                    listHead = currentNode;
                }
                allocPtr[1] = (uint)currentNode;
                listHead[1] = (int)allocPtr;
            }
            step = step + deltaX * 0x40;
            bucketIndex = bucketIndex + 0x40;
            bucketArray = bucketArray + 1;
        } while (bucketIndex <= endCoord);
    }
    return;
}