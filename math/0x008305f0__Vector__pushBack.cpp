// FUNC_NAME: Vector::pushBack
void __thiscall Vector::pushBack(int *this, undefined4 *value)
{
    int capacity = this[2]; // +0x08: capacity
    int size = this[1];     // +0x04: current size

    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2;
        }
        Vector::reallocate(capacity); // FUN_0082a5b0
    }

    int *data = (int *)this[0]; // +0x00: data pointer
    data[size] = *value;        // store the value
    this[1] = size + 1;         // increment size
}