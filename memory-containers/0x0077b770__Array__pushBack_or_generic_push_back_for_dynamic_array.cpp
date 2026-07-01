// FUNC_NAME: Array::pushBack or generic push_back for dynamic array
// Address: 0x0077b770
// Role: Push an element onto a dynamic array (like std::vector::push_back). 
// Structure: [0x00] buffer pointer, [0x04] size, [0x08] capacity.

void __thiscall Array::pushBack(int *this, undefined4 *element)
{
    undefined4 *dest;
    int newCapacity;

    // Check if we need to grow the array
    if (this[1] == this[2])
    {
        // Calculate new capacity: if current is 0, set to 1; otherwise double
        newCapacity = this[2];
        if (newCapacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = newCapacity * 2;
        }
        // Reallocate the internal buffer (FUN_0077b420)
        reallocate(newCapacity);
    }

    // Compute destination address: base + size * 4
    dest = (undefined4 *)(*this + this[1] * 4);
    // Increment size before write (but after compute? Actually original increments after compute)
    this[1] = this[1] + 1;
    // Write the element (skip if null)
    if (dest != (undefined4 *)0x0)
    {
        *dest = *element;
    }
    return;
}