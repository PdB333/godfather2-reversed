// FUNC_NAME: Entity::Entity
void __thiscall Entity::Entity(int this_)
{
    int subObject;
    int *smallVtable;
    int count;
    int *arrayEntry;

    subObject = allocMemory(0x348);
    if (subObject != 0) {
        subObject = SubObjectConstructor();
    }
    *(int *)(this_ + 0x20) = subObject;

    if (subObject != 0) {
        count = *(int *)(subObject + 0x1c);
        if (count < 5) {
            arrayEntry = (int *)(subObject + 8 + count * 4);
            *arrayEntry = this_ + 4;
            *(int *)(subObject + 0x1c) = count + 1;
        }
    }

    smallVtable = (int *)allocMemory(4);
    if (smallVtable != 0) {
        *smallVtable = (int)&PTR_LAB_00e44554; // vtable for small interface
        *(int *)(this_ + 0x128) = (int)smallVtable;
    }
    else {
        *(int *)(this_ + 0x128) = 0;
    }
}