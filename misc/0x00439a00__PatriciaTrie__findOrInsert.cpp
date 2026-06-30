// FUNC_NAME: PatriciaTrie::findOrInsert
class PatriciaTrie {
public:
    // Offsets relative to this:
    // +0x00: rootNode (unsigned int*)
    // +0x04: bitDepth (int)  // current number of bits considered
    // +0x10: nodeCount (int)
    // +0x14: pathArray (unsigned int**)  // array of node pointers, size bitDepth+1
    unsigned int* rootNode;      // 0x00
    int bitDepth;                // 0x04
    int pad_0x08[3];             // 0x08-0x0F padding? (nodeCount at +0x10)
    int nodeCount;               // 0x10
    unsigned int** pathArray;    // 0x14

    // Node structure (24 bytes):
    // +0x00: key (unsigned int)
    // +0x04: data1 (int, unused)
    // +0x08: data2 (int, unused)
    // +0x0C: data3 (int, unused)
    // +0x10: data4 (int, unused)
    // +0x14: childPointers (unsigned int**)  // array of pointers, indexed by bit position

    // Private helper functions (declared elsewhere in the binary)
    static int getKeyBitCount();                     // FUN_00439c10
    static void* allocateNode();                     // FUN_009c8e50 (size 0x18)
    static unsigned int* allocateChildArray(int size); // FUN_009c8e80 (aligned allocation)

    void findOrInsert(unsigned int key, unsigned int** outNode) {
        unsigned int* currentNode = this->rootNode;
        int currentBit = this->bitDepth;

        do {
            if (currentBit < 0) {
                // Base case: reached below the last bit.
                // If found a node with matching key, return it.
                if (currentNode != nullptr && currentNode[0] == key) {
                    *outNode = currentNode;
                    return;
                }

                // Need to insert a new node.
                int requiredDepth = getKeyBitCount();  // e.g., 32 bits
                // Extend path array if necessary
                if (this->bitDepth < requiredDepth) {
                    for (int b = this->bitDepth + 1; b <= requiredDepth; b++) {
                        this->pathArray[b] = this->rootNode;
                    }
                    this->bitDepth = requiredDepth;
                }

                // Allocate new node
                unsigned int* newNode = (unsigned int*)allocateNode();
                if (newNode == nullptr) {
                    *outNode = nullptr;
                    return;
                }
                newNode[0] = 0;  // key
                newNode[1] = 0;  // unused
                newNode[2] = 0;
                newNode[3] = 0;
                newNode[4] = 0;

                // Allocate child pointer array for the new node
                int childArraySize = requiredDepth + 1;
                newNode[5] = allocateChildArray(childArraySize);

                newNode[0] = key;

                // Copy child pointers from the path nodes at each bit level,
                // then link the new node into those slots.
                for (int b = 0; b <= requiredDepth; b++) {
                    unsigned int* pathNode = this->pathArray[b];
                    unsigned int* childSlot = (unsigned int*)(pathNode[5] + b * 4);
                    newNode[b*4 + 5] = *childSlot;  // copy old child pointer
                    *childSlot = newNode;            // replace with new node
                }

                this->nodeCount++;
                *outNode = newNode;
                return;
            }

            // Walk the linked list at this bit level.
            unsigned int** childSlotAddr = (unsigned int**)(currentNode[5] + currentBit * 4);
            unsigned int* nextNode = *childSlotAddr;
            if (nextNode != nullptr) {
                do {
                    if (key <= nextNode[0]) break;
                    childSlotAddr = (unsigned int**)(nextNode[5] + currentBit * 4);
                    currentNode = nextNode;
                    nextNode = *childSlotAddr;
                } while (nextNode != nullptr);
            }

            // Store the current node in the path array at this bit level - 1
            this->pathArray[currentBit] = currentNode;
            currentBit--;
        } while (true);
    }
};