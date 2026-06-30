// FUNC_NAME: CTransformArray::getTransformAddress
// Address: 0x004baaa0
// Role: Compute pointer to a transform element within an array
// Assumes element size is 0x20 (32 bytes) and array base is stored at offset +0x10 of a descriptor pointed by this+0x08
// Fields: this+0x04 = index, this+0x08 = pointer to descriptor (contains array base at +0x10)
// Returns an integer that is the memory address of the element (can be cast to TransformElement*)

int __fastcall CTransformArray::getTransformAddress(int this) {
    // Read index from this+0x04
    int index = *(int*)(this + 4);
    // Read descriptor pointer from this+0x08
    int descriptorPtr = *(int*)(this + 8);
    // Read array base address from descriptor+0x10
    int baseAddress = *(int*)(descriptorPtr + 0x10);
    // Compute element address: base + index * 32
    return index * 0x20 + baseAddress;
}