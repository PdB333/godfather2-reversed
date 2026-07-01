// FUNC_NAME: SomeGameObject::operator=
int __thiscall SomeGameObject::operator=(SomeGameObject *thisObj, SomeGameObject *otherObj)
{
    if (thisObj != otherObj) {
        // These functions are called on the source object, possibly to perform a deep copy
        // or to detach shared resources before assignment. Typically, assignment operators
        // copy data from the source to this, but here the functions modify otherObj.
        assignPart1(otherObj);  // FUN_00820830
        assignPart2(otherObj);  // FUN_00820980
    }
    return (int)thisObj;
}