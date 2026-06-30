// FUNC_NAME: Cache::findMatching

struct CacheNode {
    void* object;          // +0x00
    // padding / other fields omitted for clarity
    CacheNode* next;       // +0x20
};

struct Cache {
    CacheNode* head;       // +0x00
    CacheNode* current;    // +0x04 (iterator used during search)
};

// External key comparison helper (provided by callee)
bool __cdecl CacheKeyCompare(const void* a, const void* b); // FUN_005cd3e0

__thiscall CacheNode* Cache::findMatching(void* key) {
    CacheNode* node;

    // Check for cached pointer directly in key object
    node = *(CacheNode**)((char*)key + 0x30);
    if (node != nullptr) {
        return node;
    }

    // Start traversal from head
    node = this->head;
    this->current = node;

    while (node != nullptr) {
        void* obj = node->object;

        // Direct pointer match
        if (obj == key) {
            return node;
        }

        // Compare a set of fields at known offsets
        // Offset 0x04: integer ID
        // Offset 0x08: float value (coordinate, time, etc.)
        // Offsets 0x10–0x28: integers (variety of attributes)
        bool fieldMatch =
            (*(int*)((char*)obj + 4) == *(int*)((char*)key + 4)) ||
            (
                (*(int*)((char*)obj + 4) == *(int*)((char*)key + 4)) &&
                (*(float*)((char*)obj + 8) == *(float*)((char*)key + 8)) &&
                (*(int*)((char*)obj + 0x10) == *(int*)((char*)key + 0x10)) &&
                (*(int*)((char*)obj + 0x14) == *(int*)((char*)key + 0x14)) &&
                (*(int*)((char*)obj + 0x18) == *(int*)((char*)key + 0x18)) &&
                (*(int*)((char*)obj + 0x1c) == *(int*)((char*)key + 0x1c)) &&
                (*(int*)((char*)obj + 0x20) == *(int*)((char*)key + 0x20)) &&
                (*(int*)((char*)obj + 0x24) == *(int*)((char*)key + 0x24)) &&
                (*(int*)((char*)obj + 0x28) == *(int*)((char*)key + 0x28))
            );

        if (fieldMatch && CacheKeyCompare(obj, key)) {
            return node;
        }

        // Advance iterator
        node = this->current->next;
        this->current = node;
    }

    return nullptr;
}