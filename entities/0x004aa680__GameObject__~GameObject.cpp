// FUNC_NAME: GameObject::~GameObject

void __thiscall GameObject::~GameObject(GameObject* this) {
    int iVar1;
    GameObjectChild* pChild;
    GameObjectChild* pNextChild;

    // Set vtable pointer to base class destructor vtable
    this->vtable = &PTR_FUN_00e3566c;  // +0x00: vtable
    this->field_0x08 = &PTR_LAB_00e35670; // +0x08: some data pointer

    // Unlink this node from a doubly linked list (e.g., sibling list)
    if (this->prev != nullptr) {          // +0x0C: prev pointer
        *reinterpret_cast<GameObject**>(this->prev) = this->next; // prev->next = this->next
    }
    if (this->next != nullptr) {          // +0x10: next pointer
        *(reinterpret_cast<GameObject**>(this->next) + 3) = this->prev; // next->prev = this->prev (next + 0x0C)
    }
    this->next = nullptr;
    this->prev = nullptr;

    // Return an ID/handle to a global free pool (e.g., object ID recycling)
    iVar1 = this->objectID;               // +0x18: some ID/handle
    if (iVar1 != 0) {
        // Global pool at DAT_01206880 + 0x14 is a stack/array
        int* poolTop = reinterpret_cast<int*>(DAT_01206880 + 0x14);
        *(void***)*poolTop = &PTR_LAB_01123be8; // push dummy? or pointer to sentinel
        *poolTop = *poolTop + 4;
        *(int*)*poolTop = iVar1;
        *poolTop = *poolTop + 4;
        this->objectID = 0;               // ID recycled
        this->field_0x1C = 0;             // +0x1C: probably another field
    }

    // Reset vtable to final class (maybe base class cleanup)
    this->field_0x08 = &PTR_LAB_00e32854;
    this->vtable = &PTR_FUN_00e32808;

    // Clear children: iterate over singly linked list at this->firstChild (+0x04)
    pChild = reinterpret_cast<GameObjectChild*>(this->firstChild);
    while (pChild != nullptr) {
        pNextChild = reinterpret_cast<GameObjectChild*>(pChild->next); // +0x04: next pointer
        pChild->next = nullptr;
        pChild->data = nullptr;           // +0x00: data pointer
        pChild = pNextChild;
    }
    // Note: Children are not deleted, only cleared. Dtor likely called separately.
}