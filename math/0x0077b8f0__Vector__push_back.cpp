// FUNC_NAME: Vector::push_back
void __thiscall Vector::push_back(int *this, undefined4 *element)
{
    int capacity = this[2]; // +8: capacity
    int size = this[1];     // +4: current size

    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2;
        }
        // Grow the array to new capacity
        FUN_0077b550(capacity); // likely reallocate
    }

    // Calculate address of next slot: base + size * elementSize (8)
    undefined4 *slot = (undefined4 *)(*this + size * 8);
    this[1] = size + 1; // increment size

    if (slot != (undefined4 *)0x0) {
        slot[0] = element[0];
        slot[1] = element[1];
    }
    return;
}