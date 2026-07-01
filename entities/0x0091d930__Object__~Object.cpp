// FUNC_NAME: Object::~Object
int __thiscall Object::~Object(void* this, byte destroyFlag)
{
    // +0x4c: pointer to dynamically allocated resource (e.g., string buffer, child object)
    if (*(int*)((char*)this + 0x4c) != 0) {
        freeResource(*(int*)((char*)this + 0x4c)); // FUN_009c8f10 - releases the resource
    }
    engineCleanup(); // FUN_005c16e0 - engine-level cleanup (e.g., memory manager, thread local)
    if ((destroyFlag & 1) != 0) {
        deallocateMemory(this); // FUN_005c4480 - operator delete wrapper
    }
    return (int)this;
}