// FUNC_NAME: HandleManager::lookup
// 0x004d23b0: Look up an object by handle in a fixed-size hash table (8192 buckets).
// Returns pointer to object data, or null if handle is invalid or not found.
// __fastcall: param_1 in ECX (handle)
static class HandleManager {
public:
    struct HashNode {
        int*    data;       // +0x08 : pointer to object data
        uint32  key;        // +0x0c : handle / key
        HashNode* next;     // +0x10 : next node in chain
    };

    static HashNode** s_hashTable; // DAT_012054ac : array of bucket heads
    static const uint32 TABLE_MASK = 0x1fff; // 8192 entries

    static int* lookup(uint32 handle) {
        if (handle == 0)
            return 0;

        HashNode** table = s_hashTable;
        if (table == 0)
            return 0;

        uint32 bucket = handle & TABLE_MASK;
        HashNode* node = table[bucket];
        while (node != 0) {
            if (node->key == handle) {
                return node->data;
            }
            node = node->next;
        }
        return 0;
    }
};