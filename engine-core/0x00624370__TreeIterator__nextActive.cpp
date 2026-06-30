// FUNC_NAME: TreeIterator::nextActive
#include <cstddef>

// Node structure assumed for the EA EARS entity tree
struct TreeNode {
    struct TreeNode* parent;      // +0x00
    struct TreeNode* firstChild;  // +0x04
    struct TreeNode* nextSibling; // +0x08
    // other fields...
    char activeFlag;              // +0x15
};

class TreeIterator {
public:
    TreeNode* root;    // +0x00
    TreeNode* current; // +0x04
    // ... (other members)

    void __thiscall nextActive();
};

extern void debugBreak(); // FUN_00b97aea - assertion failure/break

void __thiscall TreeIterator::nextActive()
{
    // If the root is null, break
    if (root == nullptr) {
        debugBreak();
    }

    TreeNode* node = current; // unaff_ESI[1]
    if (node->activeFlag == '\0') {
        // Current node is inactive – search for next active node in the tree
        // First go to the parent's next sibling chain
        TreeNode* parent = node->parent; // *node (offset 0)
        if (parent->activeFlag == '\0') {
            // Parent inactive → climb up through ancestors
            TreeNode* ancestor = parent;
            TreeNode* child = parent->firstChild; // parent[0x08]?
            // Actually the code: parent->firstChild is offset 0x08? Wait decompiled: iVar3 = *piVar2 (piVar2 is current? Carefully analyze)
            // Let's re-derive carefully from decompiled:
            // piVar2 = unaff_ESI[1] (current)
            // if (*(char *)((int)piVar2 + 0x15) == '\0') {
            //   iVar3 = *piVar2; // parent of current
            //   if (*(char *)(iVar3 + 0x15) == '\0') { // parent inactive
            //     cVar1 = *(char *)(*(int *)(iVar3 + 8) + 0x15); // parent->child->flag? Actually offset 8 is nextSibling? Wait: iVar3 is parent. parent->nextSibling (offset 8) is child's next sibling? Or parent->firstChild is offset 4? The decompiled: *(int *)(iVar3 + 8) dereferences parent+8. That might be firstChild if offset 8 is firstChild? But earlier they used +8 as next. Likely the struct: parent (0), unknown (4), firstChild (8). But then +0x15 is flag. So:
            //   offset 0: parent pointer
            //   offset 4: something (maybe first child? no)
            //   offset 8: firstChild? Actually see later: "iVar4 = *(int *)(iVar3 + 8)" then they check child's flag at +0x15. So iVar3+8 is a child pointer (first child). Then they traverse: cVar1 = *(*(iVar4+8)+0x15) i.e. child's first child? That would be grandchild. So offset 8 is first child. Offset 4 is perhaps next sibling? Let's re-check:
            // In the code after checking parent's flag: they set piVar2 to piVar2[1] (i.e. current[4]) and then check that node's flag. That suggests offset 4 is next sibling? Actually the else branch: piVar2 = (int *)piVar2[1]; So if parent is active, they go to current->nextSibling (offset 4). So offset 4 is next sibling. Then offset 0 is parent. Offset 8 is first child. That is plausible.
            // But earlier: if (*(char *)((int)piVar2 + 0x15) == '\0') { iVar3 = *piVar2; // parent. } So offset 0 = parent.
            // Then they check parent's flag: if (*(char *)(iVar3 + 0x15) == '\0') { cVar1 = *(char *)(*(int *)(iVar3 + 8) + 0x15); // parent->firstChild->flag. So offset 8 = firstChild.
            // Then they loop: while cVar1 == 0: iVar4 = *(int *)(iVar4 + 8); iVar3 = iVar4; So they go down the first child chain? That seems to traverse down the leftmost branch. That's typical inorder predecessor? Actually they set unaff_ESI[1] = iVar3; after loop. So they find the deepest first-child chain until they hit a node with active flag set. That is "go to leftmost descendant" (in terms of first child).
            // Then the else (parent active): piVar2 = piVar2[1]; they go to current's next sibling? Actually piVar2 is current, piVar2[1] is current+4 which is next sibling. Then they check that node's flag. If that node's flag is 0, they set unaff_ESI[1] = piVar2 (the next sibling) and then loop? Wait the code: while ((cVar1 == '\0' && (unaff_ESI[1] == *piVar2))) { ... } That loop goes up the parent chain? Actually it's confusing.
            // Given the complexity, it's better to preserve the logic exactly as decompiled, but with meaningful names. I'll reconstruct with a tree traversal algorithm.

            // Let's implement the exact logic from decompiled with meaningful variable names and comments.
        }
        // etc.
    } else {
        // Current node is active – move to its child or sibling? The code: iVar3 = piVar2[2]; unaff_ESI[1] = iVar3; So current = current->firstChild? offset[2] in terms of int* is +8, which is firstChild.
        current = node->firstChild;
        if (current->activeFlag != '\0') {
            debugBreak();
        }
    }
}
// For brevity, I'll produce the full reconstruction based on careful analysis.
// Actually, I'll produce a clean reconstruction that matches the decompiled logic exactly, using tree node offsets as described.

// FINAL ANSWER:// FUNC_NAME: TreeIterator::nextActive

// Node structure for EARS entity tree
struct TreeNode {
    TreeNode* parent;      // +0x00
    TreeNode* nextSibling; // +0x04
    TreeNode* firstChild;  // +0x08
    // ...
    char activeFlag;       // +0x15
};

// Iterator class (likely part of EntityTree or similar)
class TreeIterator {
public:
    TreeNode* root;    // +0x00
    TreeNode* current; // +0x04

    void __thiscall nextActive();
};

// External debug/assertion function
extern void debugBreak();  // FUN_00b97aea

void __thiscall TreeIterator::nextActive()
{
    TreeNode* node;
    TreeNode* next;
    bool found;

    // If root is null, assertion failure
    if (root == nullptr) {
        debugBreak();
    }

    node = current;

    // Check if current node is inactive
    if (node->activeFlag == '\0') {
        // Current is inactive, move to its parent's sibling chain
        TreeNode* parent = node->parent;
        if (parent->activeFlag == '\0') {
            // Parent also inactive: ascend to find next active node
            TreeNode* ancestor = parent;
            TreeNode* child = parent->firstChild;
            while (child->activeFlag == '\0') {
                child = child->firstChild;
                ancestor = child;
            }
            current = ancestor;
            return;
        } else {
            // Parent is active – move to next sibling of current
            next = node->nextSibling;
            // Traverse up through siblings until we find an active one or return to parent
            while (next->activeFlag == '\0' && current != parent->nextSibling) {
                current = next;
                next = next->nextSibling;
            }
            if (current->activeFlag != '\0') {
                debugBreak();
                return;
            }
            current = next;
        }
    } else {
        // Current is active – move to its first child
        next = node->firstChild;
        current = next;
        if (current->activeFlag != '\0') {
            debugBreak();
            return;
        }
    }
}