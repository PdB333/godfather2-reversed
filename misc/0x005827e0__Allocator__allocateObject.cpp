// FUNC_NAME: Allocator::allocateObject
int __thiscall Allocator::allocateObject(int sizeIndex) {
    int firstBlock;
    int secondBlock;
    // Structure used for allocation info (likely internal metadata)
    struct {} allocInfo;  // placeholder for 16 bytes at local_18,14,10,c
    int dummy;

    firstBlock = (**(code **)this)(sizeIndex * 4, &allocInfo); // Allocate first block with size = sizeIndex*4
    // Zero-initialize the second allocation info
    dummy = 0;
    secondBlock = (**(code **)this)(0x10, &dummy); // Allocate second block of fixed size 0x10
    if (secondBlock != 0) {
        firstBlock = FUN_00582620(firstBlock, this); // Initialize/attach first block to allocator
        return firstBlock;
    }
    return 0;
}