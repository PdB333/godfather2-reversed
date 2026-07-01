// FUNC_NAME: RenderObject::isCulled
// Function address: 0x00903e60
// This function checks if a render object (this) should be considered visible/active based on flags, bounding box, and culling system.
// param_1 (this): pointer to render object data (CullData)
// param_2: pointer to a RenderProxy (with vtable)
// Returns 1 if visible, 0 if culled.

undefined4 __thiscall RenderObject::isCulled(byte *this, int *pRenderProxy) {
    byte *pbVar1;
    char cVar2;
    int *piVar3;
    undefined4 uVar4;
    float10 fVar5;
    int *local_8; // used with hash lookup
    int iStack_4; // result from hash get

    uVar4 = 0;
    piVar3 = (int *)0x0;
    
    // Check flags at this+0x14 (bit0 -> skip, bits 2,3,5 -> perform hash lookup)
    if ((this[0x14] & 1) == 0) {
        if ((this[0x14] & 0x34) != 0) {
            local_8 = (int *)0x0;
            // Virtual function at +0x10 on pRenderProxy: query by hash (e.g., "culling")
            cVar2 = (**(code **)(*pRenderProxy + 0x10))(0xf8b45dfb, &local_8);
            piVar3 = local_8;
            if (cVar2 == '\0') {
                piVar3 = (int *)0x0;
            } else if (local_8 != (int *)0x0) {
                // If found, call virtual at +0x1e4 (maybe get cull state)
                uVar4 = (**(code **)(*local_8 + 0x1e4))();
            }
        }
        // Update the render proxy based on the found object and state
        pRenderProxy = (int *)FUN_00903af0(pRenderProxy, piVar3, uVar4);
    }
    
    if (pRenderProxy != (int *)0x0) {
        pbVar1 = this + 4; // pointer to bounding box start (4 ints)
        // Check if any of the four ints (bounding box) are non-zero
        if ((((((*(int *)(this + 4) != 0) || (*(int *)(this + 8) != 0)) ||
               (*(int *)(this + 0xc) != 0)) || (*(int *)(this + 0x10) != 0)) &&
            // Check if the bounding box differs from the proxy's stored box (offset 8-11)
            (((pRenderProxy[8] != *(int *)pbVar1 || (pRenderProxy[9] != *(int *)(this + 8))) ||
             ((pRenderProxy[10] != *(int *)(this + 0xc) || (pRenderProxy[0xb] != *(int *)(this + 0x10))))))
           && // And either no hash object or the bounding box is valid (non-zero)
           ((piVar3 == (int *)0x0 || (cVar2 = FUN_00461f90(pbVar1), cVar2 != '\0')))) {
            iStack_4 = 0;
            uVar4 = FUN_00445ff0(pbVar1, 0);  // Hash lookup based on bounding box
            FUN_0083b910(uVar4, 0x63c72601, &iStack_4); // Get value by hash (e.g., "visible")
            if (iStack_4 == 0) {
                return 0;
            }
            // Check if proxy's cull distance is valid (function at +0x8 on proxy)
            cVar2 = FUN_0083faa0(pRenderProxy + 8);
            if (cVar2 == '\0') {
                if (piVar3 == (int *)0x0) {
                    return 0;
                }
                // Fallback check on the hash object's cull distance
                cVar2 = FUN_0083faa0(piVar3 + 8);
                if (cVar2 == '\0') {
                    return 0;
                }
            }
        }
        // Finally, check if the object is always visible (flag bit0 at this+0) or if it's within cull distance
        if (((*this & 1) != 0) ||
           (fVar5 = (float10)(**(code **)(*pRenderProxy + 0xc0))(), (float10)0 < fVar5)) {
            return 1;
        }
    }
    return 0;
}