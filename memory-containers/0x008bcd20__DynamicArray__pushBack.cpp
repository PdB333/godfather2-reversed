// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int* this, Element* newElement)
{
    int capacity = this[2]; // +0x08: capacity
    int size = this[1];     // +0x04: current size

    if (size == capacity)
    {
        // Grow the array if full
        if (capacity == 0)
        {
            capacity = 1;
        }
        else
        {
            capacity *= 2;
        }
        grow(capacity); // FUN_008bc950
    }

    // Calculate insertion point
    Element* dest = (Element*)(this[0] + size * 0x2c); // +0x00: base pointer, element size 0x2c
    this[1] = size + 1; // Increment size

    if (dest != nullptr)
    {
        // Copy element data (44 bytes = 0x2c)
        dest->field0 = newElement->field0;          // offset 0x00
        dest->field8 = newElement->field8;          // offset 0x08
        dest->field10 = newElement->field10;        // offset 0x10
        dest->field18 = newElement->field18;        // offset 0x18
        dest->field1C = newElement->field1C;        // offset 0x1C
        dest->field20 = newElement->field20;        // offset 0x20
        dest->field24 = newElement->field24;        // offset 0x24
        dest->field28 = newElement->field28;        // offset 0x28
        dest->field29 = newElement->field29;        // offset 0x29
    }
}