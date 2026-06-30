// FUNC_NAME: Tree::insert
// Function at 0x00623130 - Binary search tree insert operation
// Node structure (offset from node pointer):
//   +0x00: pLeft (Node*)   - left child
//   +0x04: (padding/unused - possibly parent pointer)
//   +0x08: pRight (Node*)  - right child
//   +0x0C: key (uint)     - search key
//   +0x10: value (int)    - associated value (inferred)
//   +0x15: isLeaf (byte)  - 1 if leaf, 0 if internal node
// Tree structure (this):
//   +0x1C: rootNode (Node*) - pointer to root of the tree

// Forward declaration of the internal insert helper
// Returns pointer to a 2-int array containing (key, value) of the new node
int* insertNodeInternal(Tree* self, int* parentRef, bool isLeftChild, uint* keyPtr);

// External assert/debug break (called in unexpected tree state)
void treeAssert(); // FUN_00624370 (likely an empty or breaking function)

int* Tree::insert(int* outResult, uint* keyPtr) {
    // current node starts as root
    Node* currentNode = *(Node**)((char*)this + 0x1C);
    bool isLess = true; // true if search key < current node key

    // If root is not a leaf, traverse the tree to find insertion point
    if (*(char*)((int)currentNode[1] + 0x15) == '\0') { // currentNode[1] is the node at +0x4? Actually currentNode is Node*, so currentNode[1] is offset 4 bytes? No - careful with pointer arithmetic.
        // Actually currentNode is the node pointer. The code does: local_4 = *(undefined4**)(param_1+0x1c);
        // Then bVar4 = *(char *)((int)local_4[1] + 0x15) == '\0';
        // local_4[1] is *(local_4+4), i.e., the second pointer-sized field. That suggests a separate pointer at +0x04.
        // Considering typical BST, that could be a parent pointer. Let's reinterpret:
        // Node layout: left (+0x0), parent (+0x4), right (+0x8), key (+0xC), value (+0x10), isLeaf (+0x15).
        // The check at +0x15 is on the node pointed by local_4[1]?? Actually local_4[1] is a pointer at +0x4, which is parent.
        // That would check parent's leaf flag. That seems odd. Maybe I misinterpret.
        // Given the decompiled code: local_4 = pointer at this+0x1c; then check (char)(local_4[1] + 0x15). local_4 is 'undefined4*', so local_4[1] is the second undeclared4, which is at offset 4 bytes from local_4. That would be the second dword of the root node.
        // Possibly the node starts with a pointer to itself? Or the root pointer points to a node that has an embedded "header".
        // To match the Ghidra output closely, we'll keep the logic as-is but rename variables.
        Node* current = *(Node**)((int)this + 0x1C);
        // The code checks *(char *)((int)current + 4 + 0x15) ??? Actually local_4 is root pointer, then local_4[1] is *(root+4), then +0x15 adds 0x15 to that value. So it's checking a byte at offset 0x19 from the root? That seems messy.
        // Given the ambiguity, I'll assume a simpler structure: nodes have left, right, key, value, isLeaf.
        // The check at +0x15 is on the node itself, not on a sub-pointer. So I'll change interpretation:
        // Node layout: left (+0x0), right (+0x4? no), key (+0x8?), no.
        // Let's re-express using offsets from Ghidra: local_4[0] = left, local_4[2] = right, local_4[3] = key.
        // So left at +0, right at +8, key at +12, value at +16, isLeaf at +? 0x15 is 21, so after 16 comes four bytes (value int), then byte at 20? That would be offset 0x14, not 0x15. 0x15 is 21, so after 20-byte struct (5 ints) there's a byte at offset 20? But we have 4-byte alignment issues.
        // Simpler: treat offsets as given: left at 0, right at 8, key at 0xC, and isLeaf at 0x15 (21). That leaves a gap. Possibly value at 0x10.
        // We'll define the structure accordingly.
    }
    // Due to complexity, I'll restructure based on original Ghidra logic faithfully.
    undefined4* local_4 = *(undefined4**)(this + 0x1c);
    bool bVar4 = true;
    if (*(char*)((int)local_4[1] + 0x15) == '\0') {
        undefined4* puVar2 = local_4[1]; // suspicious: local_4[1] is a pointer at offset 4
        do {
            local_4 = puVar2;
            bVar4 = *param_3 < (uint)local_4[3]; // key comparison
            if (bVar4) {
                puVar2 = (undefined4*)*local_4; // go left
            } else {
                puVar2 = (undefined4*)local_4[2]; // go right
            }
        } while (*(char*)((int)puVar2 + 0x15) == '\0');
    }
    int local_8 = (int)this;
    if (bVar4) {
        if (local_4 == *(undefined4**)*(int**)(this + 0x1c)) {
            int* piVar3 = insertNodeInternal(this, &local_8, 1, param_3);
            int iVar1 = *piVar3;
            param_2[1] = piVar3[1];
            *param_2 = iVar1;
            *(undefined1*)(param_2 + 2) = 1;
            return param_2;
        }
        treeAssert(); // this path suggests inconsistency
    }
    if ((uint)local_4[3] < *param_3) {
        int* piVar3 = insertNodeInternal(this, &local_8, bVar4, param_3);
        int iVar1 = piVar3[1];
        *param_2 = *piVar3;
        param_2[1] = iVar1;
        *(undefined1*)(param_2 + 2) = 1;
        return param_2;
    }
    // Key already exists (found leaf with equal key)
    param_2[1] = (int)local_4; // node pointer
    *param_2 = local_8;        // this or parent
    *(undefined1*)(param_2 + 2) = 0; // not inserted
    return param_2;
}

// Internal helper to insert a new node (defined elsewhere)
int* insertNodeInternal(Tree* self, int* parentRef, bool isLeftChild, uint* keyPtr) {
    // implementation not provided; returns pointer to (key, value) pair of new node
}