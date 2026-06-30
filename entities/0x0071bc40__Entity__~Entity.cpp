// FUNC_NAME: Entity::~Entity

int __thiscall Entity::~Entity(byte deleteFlag)
{
    // If the sub-object pointer at offset +0x1c is non-null, release it
    if (*(int *)(this + 0x1c) != 0) {
        safeDeletePointer((void **)(this + 0x1c)); // FUN_004daf90 – destroys sub-object and nullifies pointer
    }

    // If deleteFlag & 1, free the memory of this object
    if ((deleteFlag & 1) != 0) {
        operatorDelete(this); // FUN_009c8eb0 – operator delete
    }

    return this;
}