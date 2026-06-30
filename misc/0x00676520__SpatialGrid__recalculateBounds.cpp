// FUNC_NAME: SpatialGrid::recalculateBounds

#include <cstddef>

// Offset constants for member fields
constexpr size_t OFFSET_MIN_IDX1 = 0xD4;
constexpr size_t OFFSET_MAX_IDX1 = 0xD8;
constexpr size_t OFFSET_CELL_ARRAY1 = 0xCC;
constexpr size_t OFFSET_MIN_IDX2 = 0x164;
constexpr size_t OFFSET_MAX_IDX2 = 0x168;
constexpr size_t OFFSET_CELL_ARRAY2 = 0x15C;
constexpr size_t OFFSET_USE_SECONDARY = 0x2209; // char flag
constexpr size_t OFFSET_BOUNDS1_MIN = 0x28;
constexpr size_t OFFSET_BOUNDS1_MAX = 0x2C;
constexpr size_t OFFSET_BOUNDS2_MIN = 0x30;
constexpr size_t OFFSET_BOUNDS2_MAX = 0x34;
constexpr size_t OFFSET_BOUNDS_DIRTY = 0x24; // set to 1

struct LinkedListNode {
    int value;      // +0x00
    LinkedListNode* next; // +0x04
};

class SpatialGrid {
public:
    void recalculateBounds();

private:
    // Assuming this is the layout starting at this
    // Various data...
    // +0x24: int boundsDirty
    // +0x28: int bounds1_min
    // +0x2C: int bounds1_max
    // +0x30: int bounds2_min
    // +0x34: int bounds2_max
    // +0xCC: int* cellArray1 // array of pointers
    // +0xD4: int cellMinIdx1
    // +0xD8: int cellMaxIdx1
    // +0x15C: int* cellArray2
    // +0x164: int cellMinIdx2
    // +0x168: int cellMaxIdx2
    // +0x2209: char useSecondaryBounds
};

void SpatialGrid::recalculateBounds() {
    int cellMin1 = *(int*)((char*)this + OFFSET_MIN_IDX1);
    int cellMax1 = *(int*)((char*)this + OFFSET_MAX_IDX1);
    int** cellArray1 = *(int***)((char*)this + OFFSET_CELL_ARRAY1);

    // Initialize extremes
    int primaryBoundsMin = 0x7FFFFFFF;
    int primaryBoundsMax = -0x7FFFFFFF;
    int primaryCellMinCandidate = 0x7FFFFFFF;
    int primaryCellMaxCandidate = -0x7FFFFFFF;

    int* currentCell = nullptr; // used for later checks

    if (cellMin1 <= cellMax1) {
        int idx = cellMin1;
        int* cellPtr = *cellArray1 + idx;
        // Scan from left to find first non-null cell
        while (idx <= cellMax1) {
            currentCell = (int*)*cellPtr;
            if (currentCell != nullptr) {
                int candidate = idx * 0x40 + 0x20;
                if (candidate < 0x7FFFFFFF) { // always true
                    primaryCellMinCandidate = candidate;
                }
                // Jump to scan from right
                break;
            }
            idx++;
            cellPtr++;
        }

        // Scan from right
        if (idx <= cellMax1) {
            int idxRight = cellMax1;
            int* cellPtrRight = *cellArray1 + idxRight;
            while (idxRight >= idx) {
                currentCell = (int*)*cellPtrRight;
                if (currentCell != nullptr) {
                    int candidate = idxRight * 0x40 + 0x20;
                    if (candidate > -0x7FFFFFFF) {
                        primaryCellMaxCandidate = candidate;
                    }
                    break;
                }
                idxRight--;
                cellPtrRight--;
            }
            cellMax1 = idxRight;
        }
        cellMin1 = idx;
    }

    // Now process all cells in [cellMin1, cellMax1] to get actual min/max from linked lists
    if (cellMin1 <= cellMax1) {
        int numCells = cellMax1 - cellMin1 + 1;
        int* cellPtr = *cellArray1 + cellMin1;
        for (int i = 0; i < numCells; i++) {
            LinkedListNode* node = (LinkedListNode*)*cellPtr;
            if (node != nullptr) {
                // Traverse linked list to find min and max of (value >> 1)
                int currentValue = node->value >> 1;
                if (currentValue < primaryBoundsMin) {
                    primaryBoundsMin = currentValue;
                }
                // Reach end of list
                LinkedListNode* lastNode = node;
                while (lastNode->next != nullptr) {
                    lastNode = lastNode->next;
                }
                currentValue = lastNode->value >> 1;
                if (currentValue > primaryBoundsMax) {
                    primaryBoundsMax = currentValue;
                }
            }
            cellPtr++;
        }
    }

    // Update indices
    *(int*)((char*)this + OFFSET_MIN_IDX1) = cellMin1;
    *(int*)((char*)this + OFFSET_MAX_IDX1) = cellMax1;

    // Secondary array processing if flag set
    int secondaryBoundsMin = 0x7FFFFFFF;
    int secondaryBoundsMax = -0x7FFFFFFF;
    int secondaryCellMinCandidate = 0x7FFFFFFF;
    int secondaryCellMaxCandidate = -0x7FFFFFFF;

    if (*(char*)((char*)this + OFFSET_USE_SECONDARY) != 0) {
        int cellMin2 = *(int*)((char*)this + OFFSET_MIN_IDX2);
        int cellMax2 = *(int*)((char*)this + OFFSET_MAX_IDX2);
        int** cellArray2 = *(int***)((char*)this + OFFSET_CELL_ARRAY2);

        if (cellMin2 <= cellMax2) {
            int idx = cellMin2;
            int* cellPtr = *cellArray2 + idx;
            // Scan from left
            while (idx <= cellMax2) {
                currentCell = (int*)*cellPtr;
                if (currentCell != nullptr) {
                    int candidate = idx * 0x40 + 0x20;
                    if (candidate < primaryBoundsMin) {
                        primaryBoundsMin = candidate; // merge candidate into primary min
                    }
                    break;
                }
                idx++;
                cellPtr++;
            }

            // Scan from right
            if (idx <= cellMax2) {
                int idxRight = cellMax2;
                int* cellPtrRight = *cellArray2 + idxRight;
                while (idxRight >= idx) {
                    currentCell = (int*)*cellPtrRight;
                    if (currentCell != nullptr) {
                        int candidate = idxRight * 0x40 + 0x20;
                        if (candidate > primaryBoundsMax) {
                            primaryBoundsMax = candidate; // merge candidate into primary max
                        }
                        break;
                    }
                    idxRight--;
                    cellPtrRight--;
                }
                cellMax2 = idxRight;
            }
            cellMin2 = idx;
        }

        // Update secondary indices
        *(int*)((char*)this + OFFSET_MIN_IDX2) = cellMin2;
        *(int*)((char*)this + OFFSET_MAX_IDX2) = cellMax2;

        // Process linked lists for secondary array, storing results in secondaryBoundsMin/Max
        if (cellMin2 <= cellMax2) {
            int numCells = cellMax2 - cellMin2 + 1;
            int* cellPtr = *cellArray2 + cellMin2;
            for (int i = 0; i < numCells; i++) {
                LinkedListNode* node = (LinkedListNode*)*cellPtr;
                if (node != nullptr) {
                    int currentValue = node->value >> 1;
                    if (currentValue < secondaryBoundsMin) {
                        secondaryBoundsMin = currentValue;
                    }
                    LinkedListNode* lastNode = node;
                    while (lastNode->next != nullptr) {
                        lastNode = lastNode->next;
                    }
                    currentValue = lastNode->value >> 1;
                    if (currentValue > secondaryBoundsMax) {
                        secondaryBoundsMax = currentValue;
                    }
                }
                cellPtr++;
            }
        }
    }

    // Clamp bounds: if no valid values, set to 0
    if (primaryBoundsMax < primaryBoundsMin) {
        primaryBoundsMin = 0;
        primaryBoundsMax = 0;
    }
    if (secondaryBoundsMax < secondaryBoundsMin) {
        secondaryBoundsMin = 0;
        secondaryBoundsMax = 0;
    }

    // Store results
    *(int*)((char*)this + OFFSET_BOUNDS1_MIN) = primaryBoundsMin;
    *(int*)((char*)this + OFFSET_BOUNDS1_MAX) = primaryBoundsMax;
    *(int*)((char*)this + OFFSET_BOUNDS2_MIN) = secondaryBoundsMin;
    *(int*)((char*)this + OFFSET_BOUNDS2_MAX) = secondaryBoundsMax;

    // Mark bounds as dirty/updated
    *(int*)((char*)this + OFFSET_BOUNDS_DIRTY) = 1;
}