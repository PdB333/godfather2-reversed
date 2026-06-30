// FUNC_NAME: RedBlackTree::insert
undefined4 * __thiscall RedBlackTree::insert(int this, int *key, int *value, undefined4 *data)
{
    undefined4 uVar1;
    int *piVar2;
    int *piVar3;
    undefined4 *puVar4;
    int iVar5;
    int iVar6;
    undefined4 *unaff_retaddr;
    
    iVar5 = *key;
    if (iVar5 == 0) {
        puVar4 = *(undefined4 **)(this + 8);  // +0x8: allocator pointer
        if (puVar4 == (undefined4 *)0x0) {
            puVar4 = &DAT_01218a14;
        }
        // Allocate new node (size 0x18)
        puVar4 = (undefined4 *)(**(code **)**(undefined4 **)(this + 0xc))(0x18, puVar4);  // +0xC: vtable or alloc function
        if (puVar4 == (undefined4 *)0x0) {
            *key = 0;
            *(int *)(this + 4) = *(int *)(this + 4) + 1;  // +0x4: node count
            return (undefined4 *)0x0;
        }
        iVar5 = *key;
        uVar1 = *unaff_retaddr;  // Return address used as sentinel value
        // Initialize new node
        *puVar4 = 0;        // +0x0: parent
        puVar4[1] = 0;      // +0x4: left child
        puVar4[2] = 0;      // +0x8: right child
        puVar4[3] = 0;      // +0xC: color (0 = red)
        puVar4[4] = uVar1;  // +0x10: key
        puVar4[5] = iVar5;  // +0x14: value
        *key = (int)puVar4;
        *(int *)(this + 4) = *(int *)(this + 4) + 1;  // Increment node count
        return puVar4;
    }
    // Compare keys to traverse tree
    if (*value < *(int *)(iVar5 + 0x10)) {  // +0x10: current node's key
        puVar4 = (undefined4 *)RedBlackTree::insert(iVar5 + 8, value, data);  // Go left child (+0x8)
        if (puVar4[1] == 0) {  // +0x4: left child
            puVar4[1] = *key;  // Set parent
        }
        // Check for rebalancing (red-red violation)
        piVar2 = *(int **)(*key + 8);  // +0x8: right child
        if (piVar2 == (int *)0x0) {
            iVar5 = -1;
        }
        else {
            iVar5 = *piVar2;
        }
        piVar3 = *(int **)(*key + 0xc);  // +0xC: left child
        if (piVar3 == (int *)0x0) {
            iVar6 = -1;
        }
        else {
            iVar6 = *piVar3;
        }
        if (iVar5 - iVar6 == 2) {
            if (piVar2[4] <= *value) {  // +0x10: right child's key
                RedBlackTree::rotateLeft(this);
            }
            RedBlackTree::rotateRight(this);
            return puVar4;
        }
    }
    else {
        if (*value <= *(int *)(iVar5 + 0x10)) {
            *(undefined4 *)(iVar5 + 0x14) = *data;  // Update value at +0x14
            return (undefined4 *)*key;
        }
        puVar4 = (undefined4 *)RedBlackTree::insert(iVar5 + 0xc, value, data);  // Go right child (+0xC)
        if (puVar4[1] == 0) {
            puVar4[1] = *key;
        }
        // Check for rebalancing
        piVar2 = *(int **)(*key + 0xc);
        if (piVar2 == (int *)0x0) {
            iVar5 = -1;
        }
        else {
            iVar5 = *piVar2;
        }
        piVar3 = *(int **)(*key + 8);
        if (piVar3 == (int *)0x0) {
            iVar6 = -1;
        }
        else {
            iVar6 = *piVar3;
        }
        if (iVar5 - iVar6 == 2) {
            if (*value <= piVar2[4]) {
                RedBlackTree::rotateRight();
                return puVar4;
            }
            RedBlackTree::rotateLeft(this);
            return puVar4;
        }
    }
    RedBlackTree::fixUp();
    return puVar4;
}