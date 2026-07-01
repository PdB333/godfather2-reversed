// FUNC_NAME: EventPairBuffer::appendEventPair

void __thiscall EventPairBuffer::appendEventPair(int p1, int p2)
{
    // this: param_1
    uint count = *(uint *)(this + 0x1f50); // count of stored pairs (+0x1f50)
    if (count < 500) { // maximum 500 pairs
        // store pair at index count, starting at +0xfb0, each pair occupies 8 bytes (two ints)
        *(int *)(this + 0xfb0 + count * 8) = p1;   // first element of pair
        *(int *)(this + 0xfb4 + count * 8) = p2;   // second element of pair
        *(int *)(this + 0x1f50) = count + 1;       // increment count
    }
}