// FUNC_NAME: GameObject::removeFromList
// Address: 0x004503d0
// Removes 'this' node from a doubly linked list whose head is stored in 'list'.
// If 'this' is the head (prev == nullptr), updates the list head pointer.
class GameObject {
public:
    GameObject* prev; // +0x9C
    GameObject* next; // +0xA0
};

class GameObjectList {
public:
    GameObject* head; // +0x10
};

void GameObject::removeFromList(GameObjectList* list)
{
    // Relink the successor's previous pointer
    if (next != nullptr) {
        next->prev = prev;
    }

    // If this node has a predecessor, relink and detach the node
    if (prev != nullptr) {
        prev->next = next;
        prev = nullptr;
        next = nullptr;
        return;
    }

    // This node was the head of the list; update the list's head pointer
    list->head = next;
    prev = nullptr;
    next = nullptr;
}