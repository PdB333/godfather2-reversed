// FUNC_NAME: CoverHintNode::CoverHintNode
// Function address: 0x00596170
// Role: Constructor for CoverHintNode – initializes occupied flag and position vector to zero.
// Presumed base class constructor is at 0x0059b5e0 (unresolved, likely a simple entity or node constructor).

void __thiscall CoverHintNode::CoverHintNode(CoverHintNode* this)
{
    // Call base class constructor (e.g., Entity::Entity or Node::Node)
    // Actual address: 0x0059b5e0
    Entity::Entity(reinterpret_cast<Entity*>(this));

    // Initialize own members
    this->occupiedFlag = false;                                    // +0x70
    this->position.x    = 0.0f;                                   // +0x74
    this->position.y    = 0.0f;                                   // +0x78
    this->position.z    = 0.0f;                                   // +0x7c
}