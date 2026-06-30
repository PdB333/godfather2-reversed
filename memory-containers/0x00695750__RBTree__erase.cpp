// FUNC_NAME: RBTree::erase

/**
 * Red-black tree erase implementation (internal).
 * Removes a node from the tree and rebalances.
 * 
 * Node layout (offsets from node pointer):
 * +0x00: left child pointer
 * +0x04: right child pointer  
 * +0x08: parent pointer
 * +0x09: color (0=black, 1=red) (stored as byte)
 * +0x0C: data payload start (unused here)
 * +0x24: ? possibly another color byte (maybe for sentinel?)
 * +0x25: ? (checked for null/zero)
 *
 * Tree container layout (this):
 * +0x00: this pointer (some vtable?)
 * +0x04: pointer to head node (dummy sentinel)
 * +0x08: reference count or size
 */

#include <exception>

// Forward declarations for helper functions
int* __thiscall RBTree::treeMin(int* node);
int* __thiscall RBTree::treeMax(int* node);
void __thiscall RBTree::rotateLeft(int* node);
void __thiscall RBTree::rotateRight(int* node);
void __cdecl RBTree::debugAssert(const char* msg, int line);
void __cdecl RBTree::deallocate(void* ptr);
void __thiscall RBTree::fixupAfterInsert(int* node); // probably FUN_006940f0

void __thiscall RBTree::erase(int thisPtr, undefined4* outIterator, undefined4 outValue, int* nodeToRemove)
{
    int *leftChild, *rightChild, *parent;
    int *x, *y;
    int *iterNext;
    undefined4 uVar4;
    int *tempNode;
    char color;
    
    // Debug check for invalid iterator (nodeToRemove must be valid)
    if (*(char*)((int)nodeToRemove + 0x25) != '\0') {
        // This branch calls an error handler for invalid map/set iterator
        // It will throw an exception (unreachable in release)
        // (omitted the detailed exception throwing for clarity)
        RBTree::debugAssert("invalid map/set<T> iterator", 0x1b);
        // ... (throw)
    }
    
    // Possibly prefix operation (adjust tree state before removal)
    RBTree::fixupAfterInsert(); // FUN_006940f0
    
    // Determine the node y that will actually be removed (standard RB tree splice)
    leftChild = (int*)*nodeToRemove;   // +0x00
    rightChild = (int*)nodeToRemove[1]; // +0x04
    
    // Check if left child is a leaf (sentinel?) using +0x25 byte
    if (*(char*)((int)leftChild + 0x25) == '\0') {
        // left child is valid, check right child
        if (*(char*)((int)rightChild + 0x25) == '\0') {
            // Both children are non-null -> pick y as the node to splice
            y = (int*)nodeToRemove[2]; // parent
        } else {
            y = (int*)nodeToRemove[2]; // parent
        }
    } else {
        y = (int*)nodeToRemove[2]; // parent
    }
    
    parent = (int*)nodeToRemove[1]; // same as rightChild?
    if (*(char*)((int)y + 0x25) == '\0') {
        y[1] = (int)parent; // set parent's child -> y
    }
    
    // Update parent pointers using the head sentinel stored at this+0x04
    if (*(int**)(*(int*)(thisPtr + 4) + 4) == nodeToRemove) {
        // root child of head sentinel
        *(int**)(*(int*)(thisPtr + 4) + 4) = y;
    } else if ((int*)*parent == nodeToRemove) {
        // left child of parent
        *parent = (int)y;
    } else {
        // right child of parent
        parent[2] = (int)y;
    }
    
    // Update head sentinel's first child (minimum) if needed
    int* head = *(int**)(thisPtr + 4);
    if ((int*)*head == nodeToRemove) {
        tempNode = parent;
        if (*(char*)((int)y + 0x25) == '\0') {
            tempNode = (int*)RBTree::treeMin(y); // FUN_00693fe0
        }
        *head = tempNode;
    }
    
    // Update head sentinel's last child (maximum) if needed
    int headPtr = *(int*)(thisPtr + 4);
    if (*(int**)(headPtr + 8) == nodeToRemove) {
        if (*(char*)((int)y + 0x25) == '\0') {
            uVar4 = (undefined4)RBTree::treeMax(y); // FUN_00693fc0
            *(undefined4*)(headPtr + 8) = uVar4;
        } else {
            *(int**)(headPtr + 8) = parent;
        }
    }
    
    // If the removed node was black, we need to fix the tree
    if ((char)nodeToRemove[9] == '\x01') {
        // Rebalancing loop
        while (y != *(int**)(*(int*)(thisPtr + 4) + 4)) {
            // Determine sibling of y
            tempNode = parent;
            if ((char)y[9] != '\x01') break;
            parent = (int*)*tempNode;
            if (y == parent) {
                // y is left child
                parent = (int*)tempNode[2];
                if ((char)parent[9] == '\0') {
                    // case 1: sibling black
                    parent[9] = 1;            // color sibling red
                    tempNode[9] = 0;          // color parent black
                    RBTree::rotateLeft(tempNode); // FUN_006949d0
                    parent = (int*)tempNode[2];
                }
                if (*(char*)((int)parent + 0x25) == '\0') {
                    // Check children colors
                    if ((*(char*)(*parent + 0x24) != '\x01') || (*(char*)(parent[2] + 0x24) != '\x01')) {
                        if (*(char*)(parent[2] + 0x24) == '\x01') {
                            // case 2: right child red
                            *parent[(int)*parent + 0x24] = 1;
                            parent[9] = 0;
                            RBTree::rotateRight(parent); // FUN_00693e70
                            parent = (int*)tempNode[2];
                        }
                        // case 3
                        parent[9] = (char)tempNode[9];
                        tempNode[9] = 1;
                        parent[2] + 0x24 = 1;
                        RBTree::rotateLeft(tempNode);
                        break;
                    }
                }
                // else goto label
LAB_006959f4:
                parent[9] = 0;
            } else {
                // y is right child (mirror)
                if ((char)parent[9] == '\0') {
                    parent[9] = 1;
                    tempNode[9] = 0;
                    RBTree::rotateRight(tempNode);
                    parent = (int*)*tempNode;
                }
                if (*(char*)((int)parent + 0x25) == '\0') {
                    if ((*(char*)(parent[2] + 0x24) == '\x01') && (*(char*)(*parent + 0x24) == '\x01'))
                        goto LAB_006959f4;
                    if (*(char*)(*parent + 0x24) == '\x01') {
                        parent[2] + 0x24 = 1;
                        parent[9] = 0;
                        RBTree::rotateLeft(parent);
                        parent = (int*)*tempNode;
                    }
                    parent[9] = (char)tempNode[9];
                    tempNode[9] = 1;
                    *parent + 0x24 = 1;
                    RBTree::rotateRight(tempNode);
                    break;
                }
            }
            // Move up
            parent = (int*)tempNode[1];
            y = tempNode;
        }
        // Ensure y is black
        y[9] = 1;
    }
    
    // If node has a destructor, call it
    if (nodeToRemove[3] != 0) {
        (*(code*)nodeToRemove[6])(nodeToRemove[3]); // destructor at +0x18? +0x0c? Actually offset 24 (6*4) is function pointer
    }
    
    // Deallocate memory for the node
    RBTree::deallocate(nodeToRemove); // FUN_009c8eb0
    
    // Decrease reference count if applicable
    if (*(int*)(thisPtr + 8) != 0) {
        *(int*)(thisPtr + 8) -= 1;
    }
    
    // Set output iterator (next node and maybe value?)
    *outIterator = outValue;
    outIterator[1] = (undefined4)nodeToRemove; // not sure why nodeToRemove is stored again
    return;
}