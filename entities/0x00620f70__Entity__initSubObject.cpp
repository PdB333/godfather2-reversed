// FUNC_NAME: Entity::initSubObject
void __fastcall Entity::initSubObject(Entity* this) {
    // Initialize the subobject at offset +0x4 (likely a member or base class)
    // Calls FUN_0066f3f0 which is believed to be SubObject::init or constructor
    SubObject::init(reinterpret_cast<SubObject*>(reinterpret_cast<uint8_t*>(this) + 4));
}