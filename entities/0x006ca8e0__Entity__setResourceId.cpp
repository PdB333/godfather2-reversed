// FUNC_NAME: Entity::setResourceId
// Function address: 0x006ca8e0
// Role: Sets a resource ID after lookup and validation. Stores at this+0x6c.
void __thiscall Entity::setResourceId(int this, undefined4 resourceId)
{
    uint lookedUpId;
    char isValid;

    lookedUpId = lookupId(resourceId); // +0x6c field
    *(uint *)(this + 0x6c) = lookedUpId;
    if (lookedUpId != 0xffffffff) {
        isValid = validateId(lookedUpId & 0xff);
        if (isValid == '\0') {
            *(undefined4 *)(this + 0x6c) = 0xffffffff;
        }
    }
    return;
}