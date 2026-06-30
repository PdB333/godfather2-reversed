// FUNC_NAME: BaseObject::constructor
undefined4 __thiscall BaseObject::constructor(byte flag)
{
    baseInitialize();
    if (flag & 1) {
        postInitialize(this);
    }
    return this;
}