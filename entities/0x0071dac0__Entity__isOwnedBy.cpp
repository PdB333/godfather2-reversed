// FUNC_NAME: Entity::isOwnedBy
// Address: 0x0071dac0
// This function checks if the given entity (pOwner) is the owner/parent of this entity.
// It uses two methods: direct parent pointer comparison (offset -0x48 from child link at this+0x78)
// and a virtual function call on the candidate owner (vtable offset 0x1c).

bool __thiscall Entity::isOwnedBy(Entity *pOwner) {
    // Retrieve the child link stored at this+0x78.
    Entity *pChildLink = *(Entity**)((char*)this + 0x78); // +0x78: pointer to child node
    Entity *pParent = nullptr;
    if (pChildLink != nullptr) {
        // The parent pointer is located 0x48 bytes before the child link.
        pParent = (Entity*)((char*)pChildLink - 0x48);
    }

    // Fast path: direct parent comparison.
    if (pOwner == pParent) {
        return true;
    }

    // Slower path: check if the entity ID/handle at this+0xc is valid
    // and the candidate owner agrees.
    uint handle = *(uint*)((char*)this + 0xc); // +0xc: entity handle/ID
    if (FUN_00727700(handle) != 0) {
        // Call virtual function at vtable offset 0x1c on pOwner.
        // This function likely tests ownership or association.
        bool (__thiscall *canAccept)(void*, uint) = (bool (__thiscall*)(void*, uint))(*(int*)*(int*)pOwner + 0x1c);
        if (canAccept(pOwner, handle)) {
            return true;
        }
    }
    return false;
}