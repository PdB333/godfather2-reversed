// FUNC_NAME: writeHierarchicalShortListToBuffer
void writeHierarchicalShortListToBuffer(int this_)
{
    // Offsets in this class:
    // +0x14: pointer to the start of a short output buffer.
    // +0x24: pointer to the head of the outer linked list.
    //
    // Outer list nodes: +0x04 = next pointer, +0x0c = pointer to middle list.
    // Middle list nodes: +0x04 = next pointer, +0x0c = pointer to inner list.
    // Inner list nodes:  +0x04 = next pointer, +0x0c = short value to write.
    //
    // Traverses the three-level hierarchical list and writes the short values
    // sequentially into the output buffer until a value of -1 is encountered.

    short* outputBuffer = *(short**)(this_ + 0x14);
    int* outerNode    = nullptr;   // iVar5
    int* middleNode   = nullptr;   // iVar3
    int* innerNode    = nullptr;   // iVar2
    int  bufferOffset = 0;         // iVar4 in bytes

    do {
        // Advance inner list if current node is exhausted
        if (innerNode == nullptr || (innerNode = *(int**)(innerNode + 4)) == nullptr) {
            // Advance middle list if current node is exhausted
            if (middleNode == nullptr || (middleNode = *(int**)(middleNode + 4)) == nullptr) {
                // Advance outer list
                outerNode = (outerNode == nullptr)
                    ? *(int**)(this_ + 0x24)
                    : *(int**)(outerNode + 4);

                if (outerNode != nullptr) {
                    middleNode = *(int**)(outerNode + 0xc);
                }

                if (middleNode != nullptr) {
                    goto getInner;
                }
            } else {
getInner:
                innerNode = *(int**)(middleNode + 0xc);
            }

            if (innerNode == nullptr) {
                return;
            }
        }

        int value = *(int*)(innerNode + 0xc);
        *(outputBuffer + bufferOffset) = (short)value;
        bufferOffset += 2;

        if (value == -1) {
            return;
        }
    } while (true);
}