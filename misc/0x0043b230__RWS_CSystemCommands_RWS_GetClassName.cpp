// Xbox PDB: RWS::CSystemCommands::RWS_GetClassName
// FUNC_NAME: ScriptIterator::init
// Address: 0x0043b230
// Initializes the iterator from a source structure representing a script command list or hierarchy.
// The iterator can be in two modes determined by a flag at source+0x1c:
//   - If flag bit 0 is clear: iterates through a linked chain of nodes, looking for "CSystemCommands" section.
//   - If flag bit 0 is set: uses a flat array of pointers at source+0x2c (count at source+0x1e).
// Returns this pointer.

byte * __thiscall ScriptIterator::init(byte *this, int source)
{
    uint nodeType;
    int comparisonResult;
    int *currentNode;
    byte flagValue;
    bool foundSystemCommands;

    // Read the low bit of the flag at source offset 0x1c
    flagValue = *(byte *)(source + 0x1c) & 1;
    *this = flagValue;  // Store mode flag

    if (flagValue == 0) {
        // Mode 0: Traverse linked nodes starting from source+0x20
        *(int **)(this + 0xc) = (int *)(source + 0x20);
        foundSystemCommands = false;
        if (*(int *)(source + 0x20) != 0) {
            do {
                currentNode = *(int **)(this + 0xc);
                nodeType = currentNode[1];  // Node tag at offset +4
                if ((nodeType != 0x20000000) && (nodeType != 0x40000000)) {
                    if (nodeType == 0x80000000) {  // -0x80000000 as unsigned
                        // Check if the node has a string at +8 and compare with "CSystemCommands"
                        if (currentNode + 2 == (int *)0x0) {
                            currentNode = *(int **)(this + 0xc);
                            foundSystemCommands = false;
                        } else {
                            comparisonResult = __stricmp((char *)(currentNode + 2), "CSystemCommands");
                            foundSystemCommands = (comparisonResult == 0);
                            currentNode = *(int **)(this + 0xc);
                        }
                    } else if (foundSystemCommands) {
                        // If we found the system commands section, check the node's subtype
                        if (*(short *)((int)currentNode + 6) == 0x25e3) {
                            nodeType = (uint)*(ushort *)(currentNode + 1); // +4 as ushort
                        } else {
                            nodeType = currentNode[1];
                        }
                        if (nodeType == 0) {
                            return this;
                        }
                        // Zero out four bytes at this+0xc..0xf
                        this[0xc] = 0;
                        this[0xd] = 0;
                        this[0xe] = 0;
                        this[0xf] = 0;
                        return this;
                    }
                }
                // Move to next node: link offset is stored in first int of current node
                comparisonResult = *currentNode;
                *(int **)(this + 0xc) = (int *)(comparisonResult + (int)currentNode);
                if (*(int *)(comparisonResult + (int)currentNode) == 0) {
                    return this;
                }
            } while( true );
        }
    } else {
        // Mode 1: Flat array at source+0x2c of count source+0x1e
        if (*(char *)(source + 0x1e) == '\0') {
            // Empty array: zero out two fields (this+4..7 and this+8..b)
            this[8] = 0;
            this[9] = 0;
            this[10] = 0;
            this[0xb] = 0;
            this[4] = 0;
            this[5] = 0;
            this[6] = 0;
            this[7] = 0;
            return this;
        }
        // Set this+4 to start of array, this+8 to end (start + count*4)
        *(int *)(this + 4) = source + 0x2c;
        *(uint *)(this + 8) = source + 0x2c + (uint)*(byte *)(source + 0x1e) * 4;
    }
    return this;
}