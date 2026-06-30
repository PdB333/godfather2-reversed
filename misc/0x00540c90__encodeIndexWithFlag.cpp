// FUNC_NAME: encodeIndexWithFlag
// Function at 0x00540c90: Takes an index and returns a handle with a high bit (0x40000000) set.
// The shift right by 2 likely removes alignment padding or converts from a byte offset to an index.
// OR-ing with 0x40000000 sets a type or valid flag commonly used in EARS handle schemes.
uint encodeIndexWithFlag(uint aIndex)
{
    return (aIndex >> 2) | 0x40000000;
}