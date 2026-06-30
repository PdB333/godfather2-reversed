// FUNC_NAME: CGenericManager::DestroyChildren
void __thiscall CGenericManager::DestroyChildren(CChildContainer* pContainer) {
    // pContainer is param_2, has an array of child objects (array at +4, count at +0x104)
    uint childCount = *(uint*)((int)pContainer + 0x104);
    if (childCount != 0) {
        int* pChildIter = (int*)((int)pContainer + 4); // pointer to start of child array
        uint i = 0;
        do {
            CChildObject* pChild = (CChildObject*)*pChildIter; // current child object

            // Call all registered handlers (in this) on this child, in reverse order
            int handlerCount = *(int*)((int)this + 0x1c); // number of handlers
            if (handlerCount > 0) {
                int** pHandlerSlot = (int**)((int)this + 8 + (handlerCount - 1) * 4);
                for (int j = handlerCount - 1; j >= 0; j--) {
                    int* pHandler = *pHandlerSlot; // handler object
                    // Call vtable+4 (presumably destruction/notification method) with child as argument
                    (*(void (__thiscall*)(CChildObject*))(**(pHandler + 4) /* actually via *(int*)(*pHandler + 4) */))(pHandler, pChild);
                    pHandlerSlot--;
                }
            }

            // Mark child as deleted/inactive
            *(uint8*)((int)pChild + 0x128) = 1;

            // Free any sub-resources attached to this child (array at +0x12c, count at +0x14c)
            uint subCount = *(uint*)((int)pChild + 0x14c);
            if (subCount != 0) {
                void** pSubResource = (void**)((int)pChild + 0x12c); // 300 decimal
                for (uint k = 0; k < subCount; k++) {
                    FUN_009c8eb0(*pSubResource); // deallocate resource
                    pSubResource++;
                }
            }
            *(uint*)((int)pChild + 0x14c) = 0; // clear sub-resource count

            i++;
            pChildIter++;
        } while (i < childCount);
    }

    // Additional cleanup of the container itself
    FUN_00569650((int)pContainer);
    FUN_005696c0();
}