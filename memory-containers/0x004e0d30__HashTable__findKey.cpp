// FUNC_NAME: HashTable::findKey
// Address: 0x004e0d30
// Role: Looks up a 16‑byte key (4 ints) in a custom hash table.
//       The hash table structure (this):
//         +0x00: pointer to array of bucket heads (HashNode**)
//         +0x04: number of buckets (int)
//       HashNode:
//         +0x00: void* data  — pointer to a structure containing a key pointer at +0x10
//         +0x04: HashNode* next
//       Data structure (pointed by HashNode::data):
//         +0x10: int* key  — pointer to the 4‑int key stored in the table
//       The function does not return a result; it simply returns when found.

void __thiscall HashTable::findKey(int* key) // key passed in ESI, this in EAX
{
    if (key == (int*)0x0) {
        return;
    }

    uint hash = 0;
    byte* keyBytes = (byte*)key;
    for (int i = 0; i < 16; i++) {
        hash = hash * 0x1003f + (uint)keyBytes[i];
    }

    int bucketIndex = hash % this->numBuckets; // this+0x04
    HashNode* node = this->buckets[bucketIndex]; // this->buckets = *this

    while (node != (HashNode*)0x0) {
        // node->data at +0x00, then +0x10 to get pointer to key
        int** keyPtrPtr = (int**)((byte*)node->data + 0x10);
        int* storedKey = *keyPtrPtr;
        if (storedKey[0] == key[0] &&
            storedKey[1] == key[1] &&
            storedKey[2] == key[2] &&
            storedKey[3] == key[3]) {
            return;
        }
        node = node->next; // node+0x04
    }
    return;
}