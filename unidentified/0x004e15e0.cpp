// FUNC_004e15e0: RectManager::insertRect
// Role: Insert a rectangle into a global sorted list (by top-left corner) after checking for duplicates.
// Uses a static dynamic array with 24-byte elements (4 uint rect + 2 uint padding/next).
// Returns pointer to the inserted rectangle data (first 4 uints) or null if duplicate.

class RectManager {
public:
    // Global data: DAT_012054c0[0] = array base, DAT_012054c0[1] = count
    static RectNode* s_rectArray;       // +0x00: pointer to first element
    static int s_rectCount;             // +0x04: number of elements

    // Assumed node structure (24 bytes)
    struct RectNode {
        uint x1;        // +0x00
        uint y1;        // +0x04
        uint x2;        // +0x08
        uint y2;        // +0x0C
        uint pad[2];    // +0x10, +0x14 (unused or linked list next/prev)
    };

    // __thiscall: 'this' in ESI points to a 4-uint rectangle (x1,y1,x2,y2)
    // Returns pointer to the inserted rectangle data (first 4 uints) or null if duplicate.
    uint* __thiscall insertRect(uint* rectData);
};

// Decompiled reconstruction with meaningful names
uint* __thiscall RectManager::insertRect(uint* rectData) {
    uint newX1 = rectData[0];
    uint newY1 = rectData[1];
    uint newX2 = rectData[2];
    uint newY2 = rectData[3];
    int idx = 0;

    if (s_rectCount > 0) {
        RectNode* current = s_rectArray;
        do {
            uint curX1 = current->x1;
            uint curX2 = current->x2;
            uint curY1 = current->y1;
            uint curY2 = current->y2;

            // Check exact duplicate (all four coordinates equal)
            if (newX1 == curX1 && newX2 == curX2 && newY1 == curY1 && newY2 == curY2) {
                return nullptr; // duplicate found
            }

            // Determine if we should break to insert before this element
            // Primary sort by Y (top), secondary by X (left)
            if (newY2 < curY2 || (newY2 <= curY2 && newX2 < curX2)) {
                break; // new rectangle is entirely above/left of current -> insert here
            }

            if (newX2 == curX2 && newY2 == curY2) {
                // Same bottom-right corner: further sort by top-left
                if (newY1 < curY1 || (newY1 <= curY1 && newX1 < curX1)) {
                    break;
                }
            }

            idx++;
            current++; // advance to next node (24 bytes = 6 uints)
        } while (idx < s_rectCount);
    }

    // Allocate a new node (likely via realloc or custom allocator)
    RectNode* newNode = static_cast<RectNode*>(FUN_004e17b0());
    if (!newNode) return nullptr;

    // Copy rectangle data into the first 16 bytes of the node
    newNode->x1 = newX1;
    newNode->y1 = newY1;
    newNode->x2 = newX2;
    newNode->y2 = newY2;

    // Return pointer to the rectangle data (first 4 uints) inside the node
    return &newNode->x1;
}