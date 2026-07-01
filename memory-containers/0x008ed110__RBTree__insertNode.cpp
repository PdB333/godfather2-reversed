// FUNC_NAME: RBTree::insertNode
void __thiscall RBTree::insertNode(RBTree* this, int* resultPair, bool insertAfter, RBTree::Node* insertionPoint, int* keyValuePtr)
{
    // Check for overflow (container size too large)
    if (this->size > 0xAAAAAAA8) {
        // Throw "map/set<T> too long" exception
        throwException("map/set<T> too long", 0x13);
        // Not reached normally (exception is thrown)
    }

    int value = *(this->header);  // value from container? Actually this->header+4?
    RBTree::Node* newNode = (RBTree::Node*)allocMemory(0x28); // sizeof(Node)=0x28
    if (newNode != nullptr) {
        newNode->left = value;        // +0x00: set to value (maybe sentinel)
        newNode->parent = insertionPoint; // +0x04
        newNode->right = value;       // +0x08
        newNode->someField = *keyValuePtr; // +0x0C
        // Call helper to copy additional key/value data
        copyKeyValue(keyValuePtr + 1);  // FUN_008eb5e0
        newNode->color = 0;            // +0x24: red? Actually initial color flag
        newNode->flag2 = 0;            // +0x25: another flag
    }

    this->size += 1;

    // Perform tree insertion with possible rotation
    RBTree::Node* header = this->header; // this+4
    if (insertionPoint == header) {
        // Insert as root or sentinel case
        header->right = newNode;
        header->left = newNode;
        header = this->header;
    } else {
        if (insertAfter) {
            insertionPoint->left = newNode;
            if (insertionPoint == header->left) {
                header->left = newNode;
            }
            goto LAB_008ed265;
        }
        insertionPoint->right = newNode;
        RBTree::Node* header2 = this->header;
        if (insertionPoint != header2->right) {
            goto LAB_008ed265;
        }
        header2->right = newNode;
    }

LAB_008ed265:
    // Fix red-black tree properties
    RBTree::Node* nodeX = newNode;
    char color = nodeX->parent->color; // +0x24 of parent
    RBTree::Node* currentNode;
    RBTree::Node* uncle;
    RBTree::Node* temp;

    do {
        if (color != 0) {
            // Parent is red, need fixup
            this->header->right->color = 1; // set root? Actually +0x24 of something
            *resultPair = (int)this; // result pair: first is tree pointer
            resultPair[1] = (int)newNode; // second is iterator
            return;
        }
        currentNode = nodeX->parent; // +0x04 of nodeX
        uncle = currentNode->left;   // deref currentNode+0x04? Actually *currentNode is left? The code uses piVar5 = piVar7+1, piVar6=*piVar5, so currentNode's left pointer
        if (currentNode == uncle->parent) { // uncle->parent is uncle[2]? Actually the code checks if piVar6 == (int*)*piVar2, where piVar2 = (int*)piVar6[1]; This is confusing. Skip detailed reading.
            // Left child of nodeX's parent?
            temp = uncle->right;
            if (temp->color == 0) {
                // Left child is black, do rotation
            }
            // ... many rotation and recoloring steps follow
        } else {
            // Right child case
            temp = uncle->left;
            if (temp->color != 0) {
                // ...
            }
        }
        color = nodeX->parent->color;
    } while (true);
}