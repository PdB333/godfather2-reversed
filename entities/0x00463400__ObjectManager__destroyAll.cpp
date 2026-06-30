// FUNC_NAME: ObjectManager::destroyAll
// Address: 0x00463400
// This function iterates a linked list of managed objects, releases each one,
// releases a special active object if present, then calls a finalization method.
// Class layout:
//   +0x00: head of linked list (Node*)
//   +0x04: (unused in this function)
//   +0x08: (unused in this function)
//   +0x0C: activeItem (IDestroyable*)
//   +0x10: m_vtablePtr (int*) – pointer to vtable shared among all objects of this container type

class IDestroyable {
public:
    virtual void release(int arg) = 0; // vtable index 1 (offset 4)
};

class ObjectManager {
private:
    struct Node {
        IDestroyable* obj; // actual game object
        Node* next;        // +0x04
    };

    // +0x00
    Node* head;

    // +0x04, +0x08: reserved / other members

    // +0x0C
    IDestroyable* activeItem;

    // +0x10
    int* m_vtablePtr; // points to array of function pointers for contained objects

public:
    void destroyAll() {
        // Get the vtable (shared for all objects of this container type)
        int* vtable = reinterpret_cast<int*>(*m_vtablePtr);
        typedef void (__thiscall *ReleaseFunc)(IDestroyable*, int);
        ReleaseFunc release = reinterpret_cast<ReleaseFunc>(vtable[1]); // index 1 => offset 4

        // Release all nodes in the linked list
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            release(current->obj, 0);
            current = next;
        }

        // Release the active item if it exists
        if (activeItem != nullptr) {
            release(activeItem, 0);
        }

        // Call finalization on this object (vtable index 3 => offset 0xC)
        typedef void (__thiscall *FinalizeFunc)(ObjectManager*);
        FinalizeFunc finalize = reinterpret_cast<FinalizeFunc>(vtable[3]);
        finalize(this);
    }
};