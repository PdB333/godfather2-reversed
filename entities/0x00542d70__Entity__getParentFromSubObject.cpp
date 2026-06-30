//FUNC_NAME: Entity::getParentFromSubObject
// Function address: 0x00542d70
// Returns a pointer to the parent object if the sub-object pointer at +0x2d0 is non-null.
// The sub-object pointer points into the parent at offset 0x48, so we subtract 0x48 to get the parent base.
int __fastcall Entity::getParentFromSubObject(Entity* this) {
    // +0x2d0: pointer to a sub-object (e.g., a component or child) that is embedded at offset 0x48 within the parent
    if (this->field_0x2d0 != 0) {
        // Subtract 0x48 to get the base address of the owning parent object
        return this->field_0x2d0 - 0x48;
    }
    return 0;
}