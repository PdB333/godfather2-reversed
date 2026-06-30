// FUNC_NAME: ResourceLink::attachReferencedObject

void ResourceLink::attachReferencedObject(void* baseObject, int resourceId)
{
    // baseObject is a pointer to an object with a vtable; vtable[2] returns a container pointer
    void* containerPtr = (*(void* (**)(void*))(*(int*)baseObject + 8))(baseObject); // vtable[2]()
    int refCount;
    if (resourceId != 0) {
        refCount = FUN_004265d0(resourceId, baseObject); // likely ResourceManager::acquireRef(resourceId, baseObject)
    } else {
        refCount = 0;
    }
    FUN_005e1390(baseObject, refCount); // e.g., ResourceManager::linkRef(baseObject, refCount)
    *(void**)((int)containerPtr + 0xc) = baseObject; // store baseObject into container's field at +0xc
    (*(void (**)(void*))(*(int*)baseObject + 8))(baseObject); // second call to vtable[2] (possibly to cleanup or sync)
    if (resourceId != 0) {
        int newRef = FUN_004265d0(resourceId, *(void**)((int)containerPtr + 0xc)); // re‑acquire for container
        *(int*)((int)containerPtr + 0x10) = newRef; // store into container's +0x10
        (*(void (**)(void*, int))(*(int*)baseObject + 4))(baseObject, 0); // vtable[1] – likely attach method
        (*(void (**)(void*))(*(int*)baseObject + 0xc))(baseObject); // vtable[3] – finalize
    } else {
        *(int*)((int)containerPtr + 0x10) = 0;
        (*(void (**)(void*))(*(int*)baseObject + 0xc))(baseObject); // vtable[3] – finalize
    }
}