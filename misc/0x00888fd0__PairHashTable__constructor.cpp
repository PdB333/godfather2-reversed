// FUNC_NAME: PairHashTable::constructor
void __fastcall PairHashTable::constructor(int this)
{
    PairHashTable::resize(*(undefined4 *)(this + 4), *(undefined4 *)(this + 8));
    *(undefined4 *)(this + 0xc) = 0;  // +0x0C: itemCount = 0
    if (1 < *(uint *)(this + 8)) {    // +0x08: capacity check
        PairHashTable::deallocateEntries(*(undefined4 *)(this + 4));  // +0x04: entry array cleanup
    }
}