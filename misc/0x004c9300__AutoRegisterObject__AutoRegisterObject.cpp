// FUNC_NAME: AutoRegisterObject::AutoRegisterObject

void __thiscall AutoRegisterObject::AutoRegisterObject(AutoRegisterObject *this) {
    AutoRegisterObject *original;
    int size;
    int capacity;
    int *pArrayBase;
    AutoRegPair *pairArray;
    AutoRegPair *newPair;

    // Call base class constructor
    BaseClass::BaseClass(this);

    // Global object list manager
    ObjectListManager *manager = s_objectListManager; // 0x0122350c

    // Get current size and capacity from manager struct at offsets
    capacity = *(int *)(manager + 0x1740);   // m_capacity
    pArrayBase = (int *)(manager + 0x1738);  // pointer to array base (m_pArray)
    size = *(int *)(manager + 0x173c);       // m_size

    // Resize array if full
    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        FUN_005e3000(capacity);  // reallocateArray(capacity)
    }

    // Add new pair (destructor stub, this) to the array
    size = *(int *)(manager + 0x173c);                             // m_size
    pairArray = (AutoRegPair *)(*pArrayBase + size * sizeof(AutoRegPair));
    *(int *)(manager + 0x173c) = size + 1;                         // m_size++

    if (pairArray != nullptr) {
        pairArray->destructor = &AutoRegisterObject::destructorStub; // 0x004c97f0
        pairArray->object = this;
    }

    // If a global event list exists, attach this object's event callback at +0x4
    if (s_globalEventList != nullptr) { // 0x012069d4
        FUN_00407e60(this + 4, &s_globalEventList);  // attachToEventList
    }
}