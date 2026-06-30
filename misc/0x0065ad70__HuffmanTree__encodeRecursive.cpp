// FUNC_NAME: HuffmanTree::encodeRecursive
void __thiscall HuffmanTree::encodeRecursive( int thisPtr, int nodeIndex, int bitDepth )
{
    int iVar1;
    char checkResult;
    int savedBitCount;
    byte *bitBuffer;
    
    if ( nodeIndex < 0 ) {
        // Leaf node case: store the symbol value at this leaf
        // The -4 scaling accounts for the tree structure layout
        // DAT_01223360 points to the leaf table (size: numSymbols * 8? Actually +4 for value, +1 for bit length)
        // Actually leaf table is at DAT_01223360 with each entry: 4 bytes value, 1 byte bit length (total 8 bytes padded?)
        // param_1 + 0xc -> pointer to bit buffer? Likely the output bit stream or symbol table
        int leafTableOffset = DAT_01223360 + (nodeIndex * 3 + 3) * -4;
        *(undefined4 *)(leafTableOffset + 8) = **(undefined4 **)(thisPtr + 0xc);  // Store symbol value
        *(byte *)(leafTableOffset + 4) = (byte)bitDepth;  // Store bit length
        return;
    }
    
    // Internal node: process left and right children
    // DAT_01223354 points to internal node table (each node: short leftChild, short rightChild)
    int internalNodeOffset = DAT_01223354 + nodeIndex * 8;
    
    savedBitCount = *(int *)(thisPtr + 0x18);  // Current bit position in output buffer
    
    // Check if buffer is full before writing left edge bit
    if ( *(uint *)(thisPtr + 0x30) < savedBitCount + 1U ) {
        checkResult = FUN_0064b7c0();  // Check if buffer expansion is possible
        if ( checkResult != 0 ) goto writeBit;
    }
    else {
writeBit:
        // Write a '0' bit at current position for left child
        bitBuffer = (byte *)(*(int *)(thisPtr + 0xc) + (*(uint *)(thisPtr + 0x18) >> 3));
        *bitBuffer = *bitBuffer & ~( 1 << ( (byte)*(uint *)(thisPtr + 0x18) & 7 ) );
        *(int *)(thisPtr + 0x18) = *(int *)(thisPtr + 0x18) + 1;
    }
    
    // Recursively encode left child
    HuffmanTree::encodeRecursive( thisPtr, (int)*(short *)(internalNodeOffset + 4), bitDepth + 1 );
    
    // Restore bit count and write '1' bit for right child
    *(int *)(thisPtr + 0x18) = savedBitCount;
    
    if ( *(uint *)(thisPtr + 0x30) < savedBitCount + 1U ) {
        checkResult = FUN_0064b7c0();
        if ( checkResult == 0 ) goto skipRightBit;
    }
    // Write a '1' bit at current position for right child
    bitBuffer = (byte *)(*(int *)(thisPtr + 0xc) + (*(uint *)(thisPtr + 0x18) >> 3));
    *bitBuffer = *bitBuffer | ( 1 << ( (byte)*(uint *)(thisPtr + 0x18) & 7 ) );
    *(int *)(thisPtr + 0x18) = *(int *)(thisPtr + 0x18) + 1;
    
skipRightBit:
    // Recursively encode right child
    HuffmanTree::encodeRecursive( thisPtr, (int)*(short *)(internalNodeOffset + 6), bitDepth + 1 );
    
    *(int *)(thisPtr + 0x18) = savedBitCount;
    return;
}