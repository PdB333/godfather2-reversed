// FUNC_NAME: Entity::setNestedField

void __thiscall Entity::setNestedField(Entity* this, int value) {
    // Dereference pointer at +0x58 to get internal structure, then set field at +0x1eb8
    int* internalStruct = *(int**)((unsigned char*)this + 0x58);
    *(int*)((unsigned char*)internalStruct + 0x1eb8) = value;
}