// FUNC_NAME: Component::setOwner

// Function at 0x75a260: Attaches this component to a new owner entity.
// The owner entity has a component list head at offset 0x50.
// The component stores a pointer to that list head in its first field (+0x00)
// and a next pointer in its second field (+0x04).
// If the component is already attached to a different owner, it is removed first.

class Component {
public:
    // Set the owner entity for this component.
    // newOwner: pointer to the entity, or null to detach.
    void setOwner(Entity* newOwner) {
        // Compute pointer to the component list head inside the owner.
        // The list head is at offset 0x50 in the entity.
        ComponentListNode* newHead = nullptr;
        if (newOwner != nullptr) {
            newHead = reinterpret_cast<ComponentListNode*>(
                reinterpret_cast<uint8_t*>(newOwner) + 0x50);
        }

        // Only change if the owner is different from the current one.
        if (this->ownerListHead == newHead) {
            return; // Already attached to this owner.
        }

        // Remove from current owner's list if currently attached.
        if (this->ownerListHead != nullptr) {
            this->removeFromCurrentList(); // Calls FUN_004daf90
        }

        // Update the stored list head pointer.
        this->ownerListHead = newHead;

        // Insert this component at the head of the new owner's component list.
        if (newHead != nullptr) {
            // The list head has a "next" pointer at offset +0x04.
            this->nextComponent = newHead->firstComponent;
            newHead->firstComponent = this;
        }
    }

private:
    // +0x00: pointer to the component list head inside the owner entity
    ComponentListNode* ownerListHead;

    // +0x04: pointer to the next component in the owner's list
    Component* nextComponent;

    // Helper: remove this component from the current owner's list.
    // Called via FUN_004daf90 (unimplemented here).
    void removeFromCurrentList();
};

// Internal structure representing the list head embedded in an Entity at +0x50.
struct ComponentListNode {
    // +0x00: (unused, but part of Entity's layout)
    // +0x04: pointer to the first component in the list
    Component* firstComponent;
};