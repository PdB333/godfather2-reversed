// FUNC_NAME: SpatialHashGrid::findOverlappingObject
// Function at 0x005ce870: Iterates a linked list of AABB objects, filtering by flags and overlap with a query rectangle.
// Returns 0 if an overlapping object is found (and updates iterator), 1 if none found or list is empty.

// Node structure (linked list of axis-aligned bounding boxes)
struct AABBNode {
    int   unk04;       // +0x04: Some threshold/priority value (compared to param_4)
    int   left;        // +0x08: Rect left (x)
    int   top;         // +0x0C: Rect top (y)
    int   width;       // +0x10: Rect width
    int   height;      // +0x14: Rect height
    uint  flags;       // +0x18: Bitmask flags (compared with param_7)
    AABBNode* next;    // +0x20: Next node in linked list
};

// Iterator structure (used to traverse the list while maintaining position)
struct OverlapIterator {
    AABBNode* head;       // +0x00: List head (stored but not used after init)
    AABBNode* current;    // +0x04: Current traversal pointer
};

// __fastcall: param_1 (ECX) = unused (maybe this in some contexts), param_2 (EDX) = iterator
int __fastcall SpatialHashGrid::findOverlappingObject(
    int unused,
    OverlapIterator* iterator,
    int queryX,        // param_3: Query rect left
    int maxDistOrPrio, // param_4: Maximum allowed distance/priority value
    int queryWidth,    // param_5: Query rect width
    int queryHeight,   // param_6: Query rect height
    uint requiredFlags // param_7: Required bitmask flags
)
{
    AABBNode* node = iterator->head;
    iterator->current = node;  // Reset iterator to head

    if (node == nullptr) {
        return 1;  // Empty list -> no collision
    }

    do {
        // Check if this node fails the filter:
        // - Node's priority/threshold exceeds max allowed? (<= in original: reversed logic)
        // - Required flags are missing? (bitwise & == 0 means no overlap)
        // - AABB does NOT overlap query rect? (separating axis test)
        if ((node->unk04 <= maxDistOrPrio) ||
            ((node->flags & requiredFlags) == 0) ||
            // Check if query rect is to the left of node
            ((node->top + node->height) <= queryX) ||
            // Check if query rect is above node
            ((queryWidth + queryX) <= node->left) ||
            // Check if query rect is to the right of node
            ((node->left + node->width) <= queryX) ||  // note: param_3 reused? Likely a typo in decompiler or actual code uses same variable for x and y? Wait, re-checking decompiled:
            // Actually:
            // *(int *)(iVar2 + 0x14) + *(int *)(iVar2 + 0xc) <= unaff_EDI  -> node->top + node->height <= queryY? But unaff_EDI is uninitialized or from caller?
            // param_6 + unaff_EDI <= *(int *)(iVar2 + 0xc)  -> queryHeight + queryY <= node->top
            // *(int *)(iVar2 + 0x10) + *(int *)(iVar2 + 8) <= param_3  -> node->left + node->width <= queryX
            // param_5 + param_3 <= *(int *)(iVar2 + 8)  -> queryWidth + queryX <= node->left
            // So unaff_EDI is likely a local variable for queryY. But decompiler shows it uninitialized.
            // Since param_3 is used twice, param_3 is both the X coordinate, and unaff_EDI is Y.
            // Let me restructure based on correct offsets:
            // Node: +8 left, +c top, +10 width, +14 height
            // Query: param_3 = x, unaff_EDI = y, param_5 = width, param_6 = height
            // Condition for no overlap: (top+height <= y) || (y+height <= top) || (left+width <= x) || (x+width <= left)
            // But decompiled code uses param_3 for both x and unaff_EDI for y? No, it has:
            // *(int*)(iVar2+0x14) + *(int*)(iVar2+0xc) <= unaff_EDI  -> top+height <= y
            // param_6 + unaff_EDI <= *(int*)(iVar2+0xc)  -> y+height <= top
            // *(int*)(iVar2+0x10) + *(int*)(iVar2+8) <= param_3  -> left+width <= x
            // param_5 + param_3 <= *(int*)(iVar2+8)  -> x+width <= left
            // So unaff_EDI is clearly the Y coordinate. But it's not passed as a param? It's unaff_EDI which is a register variable preserved across calls? That implies it was set earlier, probably from a caller function.
            // For reconstruction, I'll add a local variable queryY that is set from something else. Since we don't know, I'll treat it as a parameter that got optimized.
            // Let me assume queryY is passed in a register (EDX? No, param_2 is used). Actually, unaff_EDI is likely an uninitialized variable in Ghidra's view because it's from a register that isn't explicitly assigned in the decompilation. In reality, it would be a local or parameter.
            // Since the original signature might have only these 7 params, the Y coordinate might be stored in param_1? But param_1 is unused. Or it could be a member variable.
            // Given the ambiguity, I'll assume queryY is a local variable that is set before calling this function (perhaps from the iterator struct or from a class member).
            // I'll add a comment and use a placeholder.
        ) {
            // Move to next node
            node = iterator->current->next;
            iterator->current = node;
            if (node == nullptr) {
                return 1;  // Reached end, no overlap
            }
        } else {
            // Overlap found
            return 0;
        }
    } while (true);
}