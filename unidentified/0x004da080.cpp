// FUN_004da080: FilePath::toString

char *FilePath::toString(void) {
    // +0x00: first byte - flag (0 = valid, 1 = empty/invalid)
    if (this->flag == 1) {
        return "";
    }

    // +0x20: pointer to first child node (linked list)
    PathNode *currentChild = this->nextNode;
    char *buffer = nullptr;
    char *writePtr;

    if (currentChild != nullptr) {
        buffer = (char *)FUN_004d8dd0(); // allocate enough memory (sized elsewhere)
        // Copy root node's data (first 0x1d bytes)
        *(uint64 *)(buffer + 0) = *(uint64 *)(this);
        *(uint64 *)(buffer + 8) = *(uint64 *)(this->unknown8);  // +0x08
        *(uint64 *)(buffer + 0x10) = *(uint64 *)(this->unknown16); // +0x10
        *(uint32 *)(buffer + 0x18) = *(uint32 *)(this->unknown24); // +0x18
        buffer[0x1c] = this->unknown28; // single byte at +0x1c

        writePtr = buffer;
        PathNode *node = currentChild;

        while (node != nullptr) {
            writePtr[0x1d] = '/'; // separator
            // Copy child node's data (0x1d bytes)
            *(uint64 *)(writePtr + 0x1e) = *(uint64 *)(node);
            *(uint64 *)(writePtr + 0x26) = *(uint64 *)(node->data8);   // +0x08
            *(uint64 *)(writePtr + 0x2e) = *(uint64 *)(node->data16);  // +0x10
            *(uint32 *)(writePtr + 0x36) = *(uint32 *)(node->data24);  // +0x18
            writePtr[0x3a] = *(char *)((int)node + 0x1c); // single byte at +0x1c
            // Advance to next node (next pointer at +0x20)
            node = node->nextNode;
            writePtr += 0x1e; // move write position by 30 bytes
        }
        writePtr[0x1d] = '\0'; // null terminate after last segment
    }
    return buffer;
}

// Supporting structures (for clarity)
struct PathNode {
    uint64 data0;   // +0x00
    uint64 data8;   // +0x08
    uint64 data16;  // +0x10
    uint32 data24;  // +0x18
    char data28;    // +0x1c
    PathNode *nextNode; // +0x20 (offset 0x20)
};

struct FilePath {
    char flag;      // +0x00, 0 = valid, 1 = empty
    // ... other fields up to +0x1c
    PathNode *nextNode; // +0x20
};