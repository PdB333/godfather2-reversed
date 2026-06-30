// FUNC_NAME: EARSContainer::pushBack

// 0x004adae0: Push a new element onto the container, using a virtual factory method to create it.
// Container structure:
//   +0x00: vtable pointer
//   +0x04: data array pointer (int*)
//   +0x08: size (int)
//   +0x0C: capacity (int)

int EARSContainer::pushBack(int *param_1)
{
    int vtableFunc;
    int newValue;
    int local_c[3]; // passed to virtual factory; local_c[2] = result index? actually only local_c[2] used.

    local_c[0] = 0;
    local_c[1] = 0;
    local_c[2] = 0;

    // Virtual call at vtable+0x88: factory method with id 0x88 and output buffer local_c
    vtableFunc = (*(code **)this->vtable)[0x88](0x88, local_c);
    if (vtableFunc == 0) {
        newValue = 0;
    } else {
        newValue = FUN_004ac9c0(local_c[2]); // create/initialize the new element from factory buffer
    }

    // Check if capacity needs to grow
    if (this->size == this->capacity) {
        int newCapacity;
        if (this->capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = this->capacity * 2;
        }
        FUN_004aeab0(newCapacity); // reallocate internal array to new capacity
    }

    // Store new value at end of array
    int *slot = this->data + this->size;
    this->size++;
    if (slot != NULL) {
        *slot = newValue;
    }

    return newValue;
}