// FUNC_NAME: KeyValueNode::KeyValueNode(int*, int)
// Address: 0x0081cac0
// Role: Constructor for a node that associates an IObject pointer with an integer key.
//        Uses a reference-counting/duplication mechanism via duplicateHandle (0x004265d0)
//        and setHandle (0x0081c510). The IObject vtable has virtual functions at offsets 4, 8, 12.

struct IObjectVTable {
    void (*func0)(void*);          // offset 0 (unknown, not used here)
    void (*func1)(void*, int, int); // offset 4
    void (*func2)(void*);          // offset 8
    void (*func3)(void*);          // offset 12
};

struct IObject {
    IObjectVTable* vtable;
};

// External functions (from 0x004265d0 and 0x0081c510)
extern int __stdcall duplicateHandle(int key, IObject* obj);
extern void __thiscall setHandle(IObject* obj, int handle);

int __thiscall KeyValueNode::KeyValueNode(int this, int* pObject, int key)
{
    int handle;
    IObject* obj = (IObject*)pObject;
    int* pObj = pObject;

    // Call virtual function at vtable+8 (func2) on the object (likely AddRef or init)
    obj->vtable->func2(obj);

    if (key == 0) {
        handle = 0;
    } else {
        handle = duplicateHandle(key, obj);
    }

    setHandle(obj, handle);

    *(IObject**)(this + 8) = obj;          // Store object pointer at offset 0x8
    obj->vtable->func2(obj);               // Second call to same virtual (probably finalize)

    if (key != 0) {
        handle = duplicateHandle(key, *(IObject**)(this + 8));
        *(int*)(this + 0xc) = handle;      // Store handle at offset 0xc
        obj->vtable->func1(obj, key, 0);   // Call vtable+4 with two args
        obj->vtable->func3(obj);           // Call vtable+12 (release/cleanup)
        return this;
    }

    *(int*)(this + 0xc) = 0;               // No handle stored
    obj->vtable->func3(obj);               // Call vtable+12
    return this;
}