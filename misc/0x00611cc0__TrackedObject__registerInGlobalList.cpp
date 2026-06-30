// FUNC_NAME: TrackedObject::registerInGlobalList
// Address: 0x00611cc0
// Role: Registers the object into a global linked list, assigns a unique ID, and calls virtual hooks.
// Object layout (offsets from this):
//   +0x00: vtable pointer
//   +0x04: m_pNext (next in global list)
//   +0x08: m_hash (computed from virtual method result)
//   +0x0C: m_id (sequential unique identifier)
extern TrackedObject* g_pGlobalListHead; // 0x012058ec
extern int g_nextId;                      // 0x012058f8

int computeHashFromKey(unsigned int key); // FUN_0060d740

void TrackedObject::registerInGlobalList()
{
    // Virtual call to get a key used for hashing (vtable offset +4, index 1)
    unsigned int key = this->getKey();

    // Compute hash from the key and store in object
    this->m_hash = computeHashFromKey(key);

    // Virtual call for additional setup (vtable offset +0x10, index 4)
    this->onBeforeRegister();

    // Insert this object at head of global linked list
    this->m_pNext = g_pGlobalListHead;
    g_pGlobalListHead = this;

    // Assign a unique sequential ID (increment global counter)
    this->m_id = g_nextId + 1;
    g_nextId++;
}