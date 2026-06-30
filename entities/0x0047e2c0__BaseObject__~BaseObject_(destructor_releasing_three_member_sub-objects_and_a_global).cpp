// FUNC_NAME: BaseObject::~BaseObject (destructor releasing three member sub-objects and a global)
void __thiscall BaseObject::~BaseObject()
{
    // +0x5c: first sub-object (likely a container or resource handle)
    destroySubobject(reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0x5c));
    zeroSubobject(reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0x5c));

    // +0x54: second sub-object
    destroySubobject(reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0x54));
    zeroSubobject(reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0x54));

    // +0x64 (100 decimal): third sub-object
    destroySubobject(reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0x64));
    zeroSubobject(reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0x64));

    // Global singleton destruction (address 0x012069f4)
    destroySubobject(&g_globalSingleton);
    // Note: no corresponding zeroSubobject call for the global – probably handled elsewhere
}