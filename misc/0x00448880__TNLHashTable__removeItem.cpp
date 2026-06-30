// FUNC_NAME: TNLHashTable::removeItem
// Address: 0x00448880
// Role: Removes an item from a hash table bucket linked list. Returns 0 if removed, 1 if not found.
// Hash table structure (this):
//   +0x00: bucketArray (int**) - array of pointers to head of each bucket list
//   +0x04: bucketCount (int) - number of buckets
//   +0x08: itemCount (int) - total number of items in hash table
// Item node structure (item):
//   +0x20: hashedKey (some data used for computing hash)
//   +0x30: next (int*) - pointer to next item in the same bucket list

int __thiscall TNLHashTable::removeItem(int* this, int* item)
{
    int bucketIndex;
    int prevItem;
    int currentItem;

    bucketIndex = FUN_004209c0(item + 8) % this[1]; // hash from item+0x20, bucketCount at this+0x04
    currentItem = *(int*)(this[0] + bucketIndex * 4); // head of bucket list
    prevItem = 0;

    while (true)
    {
        if (currentItem == 0)
        {
            return 1; // item not found
        }
        if (currentItem == (int)item)
        {
            break; // found the item to remove
        }
        prevItem = currentItem;
        currentItem = *(int*)(currentItem + 0x30); // follow next pointer
    }

    // Remove item from the singly linked list
    if (prevItem == 0)
    {
        // Removing head of the bucket
        *(int*)(this[0] + bucketIndex * 4) = *(int*)(item + 0x30);
    }
    else
    {
        *(int*)(prevItem + 0x30) = *(int*)(item + 0x30);
    }
    this[2] = this[2] - 1; // decrement item count
    return 0;
}