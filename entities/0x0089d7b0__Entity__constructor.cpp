// FUNC_NAME: Entity::constructor
unsigned int __thiscall Entity::constructor(unsigned int this, unsigned char createNative)
{
    // Call base Object constructor (0x0089b150)
    Object::Object();
    if (createNative & 1) {
        // Additional initialization, possibly native object creation (0x009c8eb0)
        Entity::initNative(this);
    }
    return this;
}