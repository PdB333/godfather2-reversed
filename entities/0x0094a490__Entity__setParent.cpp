// FUNC_NAME: Entity::setParent
// Address: 0x0094a490
// Manages attachment of this entity to a parent entity (linked list of children).
// The parent pointer is stored as an intrusive linked list node at this+0x15c.
// Only allowed when state (this+0x118) is 4 or 5 (e.g., InWorld, Attached?).
// If setting a new parent, updates the child's local transform from the parent's world transform.

class Entity {
public:
    // offsets: mostly guessed based on typical EARS engine layout
    // +0x118: state enum (4=InWorld, 5=AttachedToParent? Others=Detached)
    int state; 

    // +0x15c: pointer to a ParentListNode (intrusive list node)
    // The node points back to the parent's child list via +0x04 (next pointer)
    ParentListNode* parentNode;

    // +0x130..0x13c: local transform (quaternion+position?) relative to parent
    // Stored as four floats: probably (x,y,z,w) for quaternion + position offset?
    float localTransform[4]; // adjust type as needed

    // ... other members ...

    void setParent(Entity* newParent, int param2); // actually the function signature
};

// Forward declaration of node deletion helper
void FUN_004daf90(ParentListNode* node); // destroys a parent list node

// Forward declaration: returns pointer to global transform (e.g., world origin?)
float* FUN_00790cd0();

void __thiscall Entity::setParent(void* thisPtr, int param_2) {
    Entity* self = (Entity*)thisPtr;
    ParentListNode* node = &self->parentNode; // actually pointer at +0x15c
    int parentOffset = (param_2 == 0) ? 0 : (param_2 + 0x48); // offset by 0x48 if non-null? Secret? 

    // Only allow parent change if state is 4 or 5 (active/attached)
    if (self->state == 4 || self->state == 5) {
        // If we have a previous parent, detach
        if (self->parentNode != (ParentListNode*)parentOffset) {
            if (self->parentNode != nullptr) {
                FUN_004daf90(self->parentNode); // remove old node
            }
            // Set new parent node pointer
            self->parentNode = (ParentListNode*)parentOffset;
            if (parentOffset != 0) {
                // Update linked list: node->next points back to self->parentNode address?
                self->parentNode->next = (ParentListNode*)(self->parentNode + 4); // actually self->parentNode->next = &self->parentNode
                // The original code: *(int **)(param_2 + 4) = piVar1; -> that sets the new node's next ptr to point to self's node pointer location.
                // This is typical intrusive list where the node itself is embedded.
                // We'll reinterpret as: self->parentNode->next = &self->parentNode;
            }
        }
    } else {
        // Not in allowed state – detach any existing parent
        if (self->parentNode != nullptr) {
            FUN_004daf90(self->parentNode);
            self->parentNode = nullptr;
        }
    }

    // Update local transform based on whether we successfully attached to a non-null parent
    if (self->parentNode != nullptr && self->parentNode != (ParentListNode*)0x48) {
        // Get world transform of parent (some global?) and copy to local transform
        float* worldTransform = FUN_00790cd0();
        self->localTransform[0] = worldTransform[0];
        self->localTransform[1] = worldTransform[1];
        self->localTransform[2] = worldTransform[2];
        self->localTransform[3] = worldTransform[3]; // note: original uses _DAT_00d5780c for fourth element
    } else {
        // No parent – zero local transform
        self->localTransform[0] = 0.0f;
        self->localTransform[1] = 0.0f;
        self->localTransform[2] = 0.0f;
        self->localTransform[3] = 0.0f;
    }
}