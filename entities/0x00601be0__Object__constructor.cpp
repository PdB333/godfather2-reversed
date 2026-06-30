// FUNC_NAME: Object::constructor
undefined4 __thiscall Object::constructor(Object* this, byte flag) {
    Object::init(this);
    if ((flag & 1) != 0) {
        Object::destroy(this);
    }
    return (undefined4)this;
}