// FUNC_NAME: ObjectRegistry_registerObject

int ObjectRegistry_registerObject(void* object)
{
    int* node;
    int current;
    uint key;

    if (object == 0) {
        return 0;
    }

    key = *(uint*)((int)object + 0x30);  // +0x30: object's unique ID/hash
    // Hash table at DAT_012054ac, 0x2000 buckets (mask 0x1fff)
    current = *(int*)(DAT_012054ac + (key & 0x1fff) * 4);
    while (current != 0) {
        if (*(uint*)(current + 0xc) == key) {  // +0x0c: node's stored key
            return 1;  // Already registered
        }
        current = *(int*)(current + 0x10);  // +0x10: next node pointer
    }

    // Not found, allocate a new node
    node = (int*)FUN_004d2050();  // Allocator (likely malloc or pool)
    if (node == 0) {
        return 0;
    }

    node[3] = (int)key;          // +0x0c: store key
    LOCK();
    node[0] = 1;                 // +0x00: flag (in use)
    UNLOCK();
    node[2] = (int)object;       // +0x08: pointer to the object
    LOCK();
    node[1] = 0;                 // +0x04: some other field (unused?)
    int tableBase = DAT_012054ac;
    UNLOCK();
    node[4] = *(int*)(tableBase + (key & 0x1fff) * 4);  // +0x10: link to old head
    *(int**)(tableBase + (key & 0x1fff) * 4) = node;    // Insert at head
    int* countPtr = (int*)(tableBase + 0x8000);          // +0x8000: total count
    *countPtr = *countPtr + 1;
    return 1;
}