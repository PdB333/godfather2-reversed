// FUNC_NAME: SomeClass::Init4IntBlock (0x0068ebf0)
// Initializes a 4-integer block by zeroing it, then calls a secondary init function with two parameters.
// This appears to be a common pattern for constructing small structs with a more complex setup.
int* SomeClass::Init4IntBlock(int* block, int param1, int param2) {
    block[0] = 0; // +0x00
    block[1] = 0; // +0x04
    block[2] = 0; // +0x08
    block[3] = 0; // +0x0C
    FUN_0069cc50(param1, param2, block); // (0x0069cc50) further initialization
    return block;
}