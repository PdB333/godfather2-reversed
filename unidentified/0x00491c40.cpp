// FUN_NAME: EARS::Object::constructor

void __thiscall EARS_Object_constructor(void *this)
{
    // Call base class constructor (likely EARS::BaseObject or similar)
    EARS_BaseObject_constructor();
    
    // Set vtable pointer from global
    *(void**)this = &PTR_LAB_00e346d0;   // +0x00: vtable
    
    // Zero out a series of fields (offsets from this)
    *(int*)((char*)this + 0x1C0) = 0;    // +0x1C0: field0
    *(int*)((char*)this + 0x1E0) = 0;    // +0x1E0: field1
    *(int*)((char*)this + 0x1E4) = 0;    // +0x1E4: field2
    *(int*)((char*)this + 0x1E8) = 0;    // +0x1E8: field3
    *(int*)((char*)this + 0x200) = 0;    // +0x200: field4
    *(int*)((char*)this + 0x1FC) = 0;    // +0x1FC: field5
    *(int*)((char*)this + 0x1F8) = 0;    // +0x1F8: field6
    *(int*)((char*)this + 0x1F4) = 0;    // +0x1F4: field7
    *(int*)((char*)this + 0x1F0) = 0;    // +0x1F0: field8
    *(int*)((char*)this + 0x21C) = 0;    // +0x21C: field9
    *(int*)((char*)this + 0x218) = 0;    // +0x218: field10
    *(int*)((char*)this + 0x214) = 0;    // +0x214: field11
    *(int*)((char*)this + 0x210) = 0;    // +0x210: field12
}