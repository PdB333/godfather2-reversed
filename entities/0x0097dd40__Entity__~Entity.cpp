// FUNC_NAME: Entity::~Entity
// Address: 0x0097dd40
// Role: Destructor for Entity class (EA EARS engine). Releases sub-objects and calls base destructor.
void __fastcall Entity::~Entity(Entity* this)
{
    // Set vtable to derived class vtable (destructor phase 1)
    this->vfTable = &g_EntityVTable;  // +0x00
    this->someField = &g_EntityField2; // +0x04 (maybe derived class data)

    // Initialize sub-objects (constructor-like calls from destructor? Actually this pattern is typical of destructor resetting vtable)
    Entity::initAIComponent(this);   // FUN_0097cd60
    Entity::initPhysicsComponent(this); // FUN_0097ce70
    Entity::initRenderComponent(this);  // FUN_0097cf90
    Entity::initGameplayComponent(this); // FUN_0097d100

    // Set flags bit at offset 0x102 (likely "deleting" flag)
    *(uint16*)((uint8*)this + 0x102) |= 2;

    // Additional initialization in destructor order
    Entity::deinitSoundComponent(this); // FUN_0097d750
    Entity::deinitInputComponent(this); // FUN_0097d9d0
    Entity::deinitAnimationComponent(this); // FUN_0097db10
    Entity::deinitScriptComponent(this); // FUN_0097d890

    // Release global event manager reference
    Entity::releaseGlobalManager(&g_EventManager); // FUN_004086d0 (static address 0x0112a638)

    // Release owned sub-object pointers (offsets 0xD8, 0xCC, 0xC0, 0xB4, 0xA8)
    if (this->ownedObject1 != nullptr) {
        Entity::releaseSubObject(this->ownedObject1); // FUN_009c8f10
    }
    if (this->ownedObject2 != nullptr) {
        Entity::releaseSubObject(this->ownedObject2);
    }
    if (this->ownedObject3 != nullptr) {
        Entity::releaseSubObject(this->ownedObject3);
    }
    if (this->ownedObject4 != nullptr) {
        Entity::releaseSubObject(this->ownedObject4);
    }
    if (this->ownedObject5 != nullptr) {
        Entity::releaseSubObject(this->ownedObject5);
    }

    // Call base class destructor (vtable switch to base)
    Entity::Base::~Base(this); // FUN_004083d0 (base destructor)

    // After base destructor, set vtable to base class vtable (common pattern)
    this->vfTable = &g_BaseVTable; // +0x00 (PTR_LAB_00d8fd5c)

    // Decrement global instance count
    g_GlobalInstanceCounter = 0; // DAT_01130030
}