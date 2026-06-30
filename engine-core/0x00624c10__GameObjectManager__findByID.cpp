// FUNC_NAME: GameObjectManager::findByID
// Address: 0x00624c10 (thunk for 0x00624bd0)
// Role: Finds an object in a singly linked list by its virtual getId() return value.
// Structure: this+0x20 = head pointer, each node: +0x00 vtable, +0x28 next pointer.

class GameObject; // forward declaration

GameObject* __thiscall GameObjectManager::findByID(int targetID) {
    GameObject* current = *(GameObject**)((char*)this + 0x20); // head of linked list
    if (current == nullptr) {
        return nullptr;
    }
    do {
        GameObject* next = *(GameObject**)((char*)current + 0x28); // +0x28: next node
        int currentID = (*(int(__thiscall**)(GameObject*))(*((int*)current)))(current); // vtable[0] = getId
        if (currentID == targetID) {
            return current;
        }
        current = next;
    } while (current != nullptr);
    return nullptr;
}