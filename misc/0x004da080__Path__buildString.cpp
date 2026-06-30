// FUNC_NAME: Path::buildString
// Function at 0x004da080: Constructs a path string from a linked list of path components.
// Returns an allocated string, or empty string if the path is marked as empty (first byte == 1).
// The path object (this) contains a header (0x1d bytes) and a pointer to a linked list of nodes.
// Each node contributes 0x1d bytes of data, preceded by a '/' separator.
// The output is: header (29 bytes) + for each node: '/' + node data (29 bytes) + null terminator.

#include <cstddef>

// Forward declaration of allocation function (likely from memory manager)
extern char* allocatePathBuffer(); // FUN_004d8dd0

// Node in the path component linked list
struct PathNode {
    char data[0x1d];          // +0x00: 29 bytes of path component data
    PathNode* next;           // +0x20: pointer to next node
};

// Path object (this pointer)
struct Path {
    char flag;                // +0x00: if 1, path is empty
    char header[0x1c];        // +0x01: remaining header data (total 0x1d bytes)
    // padding to align next pointer? Actually header ends at 0x1c, next at 0x20
    PathNode* firstNode;      // +0x20: pointer to first node in linked list
};

char* Path::buildString() {
    // If the path is marked as empty (flag == 1), return empty string
    if (this->flag == 1) {
        return "";
    }

    PathNode* currentNode = this->firstNode;
    char* output = this->header; // start with header pointer (will be replaced if nodes exist)

    if (currentNode != nullptr) {
        // Allocate a buffer for the output string
        output = allocatePathBuffer();

        // Copy the header (0x1d bytes) from this to output
        *reinterpret_cast<unsigned long long*>(output) = *reinterpret_cast<unsigned long long*>(this);
        *reinterpret_cast<unsigned long long*>(output + 8) = *reinterpret_cast<unsigned long long*>(reinterpret_cast<char*>(this) + 8);
        *reinterpret_cast<unsigned long long*>(output + 0x10) = *reinterpret_cast<unsigned long long*>(reinterpret_cast<char*>(this) + 0x10);
        *reinterpret_cast<unsigned int*>(output + 0x18) = *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 0x18);
        output[0x1c] = reinterpret_cast<char*>(this)[0x1c];

        char* writePos = output;

        // Iterate through the linked list of nodes
        while (currentNode != nullptr) {
            // Write '/' separator at offset 0x1d from current write position
            writePos[0x1d] = '/';

            // Copy node data (0x1d bytes) starting at offset 0x1e
            *reinterpret_cast<unsigned long long*>(writePos + 0x1e) = *reinterpret_cast<unsigned long long*>(currentNode->data);
            *reinterpret_cast<unsigned long long*>(writePos + 0x26) = *reinterpret_cast<unsigned long long*>(currentNode->data + 8);
            *reinterpret_cast<unsigned long long*>(writePos + 0x2e) = *reinterpret_cast<unsigned long long*>(currentNode->data + 0x10);
            *reinterpret_cast<unsigned int*>(writePos + 0x36) = *reinterpret_cast<unsigned int*>(currentNode->data + 0x18);
            writePos[0x3a] = currentNode->data[0x1c];

            // Advance to next node
            currentNode = currentNode->next;
            writePos += 0x1e; // Advance write position by 30 bytes (1 separator + 29 data)
        }

        // Null-terminate the string at offset 0x1d from the last write position
        writePos[0x1d] = '\0';
    }

    return output;
}