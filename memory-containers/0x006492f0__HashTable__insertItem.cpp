// FUNC_NAME: HashTable::insertItem
void __thiscall HashTable::insertItem(void* item) {
    // this points to a struct with fields:
    // +0x00: int* table (array of pointers to head nodes)
    // +0x04: int capacity (size of table array)
    // +0x08: int minCapacity (maybe threshold for resize)
    // +0x0C: int count (number of items inserted)
    // item points to a struct with:
    // +0x08: uint key (some hashable value)
    // +0x18: int* next (pointer to next item in chain)

    uint uVar1;
    if ((uint)(this->capacity * 2) <= this->count * 4 + 4U) {
        uVar1 = this->capacity * 2 + 1;
        if (uVar1 < (uint)this->minCapacity) {
            uVar1 = this->minCapacity;
        }
        resize(uVar1); // FUN_0064a7c0 likely resizes the table
    }
    // Hash the item's key (shifted right 4 bits to spread? Or maybe key is a pointer/ID)
    uVar1 = (*(uint *)((int)item + 8) >> 4) % (uint)this->capacity;
    // Classic separate chaining insertion: item->next = table[index]; table[index] = item
    *(uint *)((int)item + 0x18) = *(uint *)(this->table + uVar1 * 4);
    *(int *)(this->table + uVar1 * 4) = (int)item;
    this->count++;
}