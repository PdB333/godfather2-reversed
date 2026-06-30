// FUNC_NAME: GrowingArray::appendPair
// Address: 0x005efb60
// 
// This function appends an 8-byte pair (two int32) to a dynamic array.
// The array structure (offsets relative to this):
//   +0x00: int* data        – pointer to allocated buffer
//   +0x04: int  count        – number of elements currently stored
//   +0x08: int  capacity     – maximum number of elements before reallocation
//
// The value to append is passed as a pointer to two consecutive int32s
// (in EDI via __thiscall convention, parameter not visible in Ghidra).

class GrowingArray {
public:
    int*  data;        // +0x00
    int   count;       // +0x04
    int   capacity;    // +0x08

    // Note: grow() is an internal method (FUN_005efad0) that reallocates
    // the internal buffer to a new capacity.
    void grow(int newCapacity);
    void appendPair(const int* value);
};

void GrowingArray::appendPair(const int* value) {
    int cap = this->capacity;                     // iVar2 = in_EAX[2]
    
    if (this->count == cap) {                     // if (in_EAX[1] == iVar2)
        if (cap == 0) {
            cap = 1;
        } else {
            cap *= 2;                             // double the capacity
        }
        this->grow(cap);                          // FUN_005efad0(iVar2)
    }
    
    // Compute destination slot: data + count * 2 (each element is 2 ints)
    int* slot = this->data + this->count * 2;     // puVar1 = *in_EAX + in_EAX[1] * 8
    this->count++;                                 // in_EAX[1] = in_EAX[1] + 1
    
    if (slot != nullptr) {                        // if (puVar1 != 0)
        slot[0] = value[0];                       // *puVar1 = *unaff_EDI
        slot[1] = value[1];                       // puVar1[1] = unaff_EDI[1]
    }
}