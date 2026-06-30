// FUNC_NAME: Object::Object
Object* __thiscall Object::Object(Object* this, byte allocFlag)
{
    // Call base constructor (0x0065ea30)
    FUN_0065ea30(this); // Assume base class initialization
    if ((allocFlag & 1) != 0) {
        // If heap-allocated, free memory (0x009c8eb0 - likely operator delete)
        FUN_009c8eb0(this);
    }
    return this;
}