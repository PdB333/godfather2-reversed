// FUNC_NAME: Entity::destroyMemberObjects
void Entity::destroyMemberObjects()
{
    *(char *)(this + 0x68) = 0; // Clear some flag

    // Release and free the first embedded sub-object at +0x44
    releaseSubObject(this + 0x44);
    freeSubObject(this + 0x44);

    // Release and free the second embedded sub-object at +0x4c
    releaseSubObject(this + 0x4c);
    freeSubObject(this + 0x4c);

    // If the pointer at +0x28 is non-null, there is a dynamically allocated sub-object at +0x54
    if (*(int *)(this + 0x28) != 0) {
        releaseSubObject(this + 0x54);
        freeSubObject(this + 0x54);
    }

    // If the pointer at +0x38 is non-null, there is another dynamically allocated sub-object at +0x5c
    if (*(int *)(this + 0x38) != 0) {
        releaseSubObject(this + 0x5c);
        freeSubObject(this + 0x5c);
    }
}