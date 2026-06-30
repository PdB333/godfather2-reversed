// FUNC_NAME: HashTable::findEntry
// 0x004461c0 - Look up a 4-int key in a hash table, returns node pointer or 0.
// Uses a separate hash function (0x004209c0) and a node key extractor (0x0043ab10).
// HashTable layout:
//   +0x70: int* buckets        -> array of HashNode* pointers
//   +0x74: int numBuckets      (modulus)
// HashNode layout:
//   +0x00: int key[4]
//   +0x18: HashNode* next

struct HashNode {
    int key[4];          // +0x00
    // ... other data ...
    HashNode* next;      // +0x18
};

uint __fastcall hashFunction(int* key);          // 0x004209c0
int* __fastcall getNodeKey(HashNode* node);      // 0x0043ab10

int __thiscall HashTable::findEntry(int* key)
{
    uint hash = hashFunction(key);
    uint index = hash % *(uint*)(this + 0x74);                // modulus
    HashNode* node = *(HashNode**)(*(int*)(this + 0x70) + index * 4); // bucket → head
    
    while (node != 0) {
        int* nodeKey = (int*)getNodeKey(node);                // get pointer to node's key
        if (nodeKey[0] == key[0] && nodeKey[1] == key[1] &&
            nodeKey[2] == key[2] && nodeKey[3] == key[3]) {
            return (int)node;
        }
        node = node->next;                                    // +0x18
    }
    return 0;
}