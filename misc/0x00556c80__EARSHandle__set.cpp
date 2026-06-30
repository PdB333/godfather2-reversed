// FUNC_NAME: EARSHandle::set
void __thiscall EARSHandle::set(void *resourcePtr, int flags, uint slotIndex) {
    void *oldPtr = *(void **)(this + 0x10); // +0x10: mPtr
    void *newPtr = this; // Actually unaff_EDI which is the new pointer? Unclear; based on asm it's passed in edi.
    // The decompiled shows unaff_EDI is the new value to set at this+0x10.
    // But we don't have it as parameter; likely it's passed in register (EDI) as part of the calling convention.
    // Since Ghidra doesn't capture that, we assume the new pointer is the "this" itself? No, that doesn't make sense.
    // Actually looking at the code: puVar1 = unaff_ESI[0x10]; if (puVar1 != unaff_EDI) { ... } then unaff_ESI[0x10] = unaff_EDI;
    // So unaff_EDI is the new pointer value. It might be the 'this' pointer? Or a hidden parameter?
    // In typical thiscall, ESI holds this. EDI might hold a parameter? Possibly the compiler hoisted the new pointer into EDI.
    // For reconstruction, we add a hidden parameter "void *newPtr". But given the callers, they likely pass it via register.
    // We'll add an extra parameter but note the convention.
    // Actually the function signature is "undefined FUN_00556c80(void)" with no parameters in Ghidra, but the decompiler showed param_1, param_2, param_3. The new pointer might be from unaff_EDI which could be the return of a previous call or a global. We'll ignore that and assume the new pointer is passed as a hidden parameter.
    // For clarity, we'll comment that the new pointer is passed via EDI.
    // This makes the function complex. Better to assume the pointer is the first argument? But there are three int args already.
    // Given the difficulty, I'll reconstruct based on typical resource handle set pattern.
    // We'll treat the new pointer as coming from the "resourcePtr" parameter? No, resourcePtr is param_1.
    // Re-reading: The if (puVar1 != unaff_EDI) suggests that the "new" pointer is actually the address of the source object? Or maybe it's the result of resourcePtr manipulation?
    // Actually, look at the code: After releasing old ref, it sets unaff_ESI[0x10] = unaff_EDI. Then later it uses param_1 to compute things. So unaff_EDI is likely a separate input. In the callers, what is passed? For example, at 0x004b5df0, the instruction might set ESI and EDI before call.
    // To simplify, I'll assume the new pointer is the resourcePtr itself (param_1) because later param_1 is used as a pointer to an object with offset 0xe0. So resourcePtr is the source. Then the new pointer (to set at this+0x10) is the resource object? But then the code compares puVar1 (old) to unaff_EDI (new) which would be the resource object. That makes sense: the handle holds a pointer to the resource object. So the new pointer is resourcePtr.
    // So: if (this->mPtr != resourcePtr) { ... } then set this->mPtr = resourcePtr.
    // That matches typical handle set where you release old and acquire new.
    // So rename: void* newPtr = resourcePtr;
    // But wait, the code does not assign resourcePtr to unaff_EDI; unaff_EDI is separate. However, in many callers, it's likely that EDI holds resourcePtr. So we assume that.
    
    // Given the confusion, I'll produce the code as the decompiler hinted but with meaningful names.
    // The decompiler's param_1 is "int param_1" used as a condition (if param_1 != 0). So param_1 is a boolean or pointer. We'll treat it as "int resourceNonNull" and also use it as a pointer? No, it's used as pointer later: param_1 + 0xe0. So it's definitely a pointer. So param_1 = resourcePtr.
    // param_2 = flags, param_3 = slotIndex.
    // The new pointer for the handle is the resource itself? Or something else? The code at the start uses unaff_EDI (likely the register EDI) as the new pointer. That could be a different object, maybe a wrapper? But looking at the callers: e.g., at 0x00556be0, it's calling this function after setting up some registers. Hard to know.
    // Given the decompiler output, it's best to not overcomplicate; I'll write the function as if the new pointer is passed as a hidden parameter, but since we can't, I'll omit that part and assume the code is for a set method that takes the resource pointer directly (resourcePtr = the object to point to). However, the function also uses resourcePtr for other calculations. So it's plausible that the handle's internal pointer is set to the resource object itself.
    // Actually, the reference counting decrement and increment point to the same object (the resource). So this->mPtr should point to the resource. So the new pointer is the resource object. Then why is there a separate unaff_EDI? In x86, the second argument is often passed in EDI for thiscall? No, thiscall uses ECX for this, but here it uses ESI for this. That's unusual. Maybe it's a different convention (e.g., fastcall with ESI/EDI). Given the game uses EA's compiler, it might use custom conventions.
    // To avoid speculation, I'll write the function with the assumption that the new pointer is actually the first parameter (resourcePtr), and that the register assignments are not visible.
    // However, the decompiled code uses unaff_ESI as this, and unaff_EDI as the new pointer, and param_1 is something else. So I'll keep the three parameters as given.
    
    // Actually, re-read the decompiled: it doesn't show unaff_EDI as a parameter; it shows param_1, param_2, param_3. unaff_EDI is a register that the decompiler didn't map. So the function actually takes 4 arguments? The signature says 0 parameters, but the decompiler guessed 3. So we need to add an extra argument for the new pointer. Since Ghidra didn't catch it, we have to infer.
    // For a clean reconstruction, we'll add a fourth parameter: void *newResourcePtr. But that changes the interface. Better to assume that the new resource pointer is derived from param_1? Possibly param_1 is the new resource and there is no other new pointer. Then the pointer comparison is between this->mPtr and resourcePtr. That makes sense.
    // So I'll set: if (this->mPtr != resourcePtr) { ... } then set this->mPtr = resourcePtr.
    // The cast: *(short *)((int)puVar1 + 6) = *(short *)((int)puVar1 + 6) + -1; This decrements a 16-bit reference count at offset 6 of the resource object. So resource object has a ref count at +6.
    
    // With that, we can reconstruct.
    
    // Let's write the reconstructed code.
    
    // Variables: resourcePtr (param_1), flags (param_2), slotIndex (param_3)
    
    void *oldPtr = *(void **)((char *)this + 0x10); // +0x10: mResource
    if (oldPtr != resourcePtr) {
        if (oldPtr != NULL) {
            if (*(short *)((int)oldPtr + 2) != 0) { // +2: mRefCount? wait, offset 2 from pointer? Actually offset from base: *(short *)(puVar1 + 1) means offset 4? Since puVar1 is undefined4*, so puVar1[1] is offset 4. But the code dereferences as *(short *)(puVar1 + 1) which is likely a 16-bit field at offset 4. Then another at offset 6. Let's use offsets as bytes: *(short *)((int)oldPtr + 4) and *(short *)((int)oldPtr + 6).
            // Actually in decompiled: `if (*(short *)(puVar1 + 1) != 0)` where puVar1 is int*, so puVar1[1] is at offset 4. That's likely a reference count word. Then `*(short *)((int)puVar1 + 6) = ...` So two 16-bit fields: one at +4 (maybe a flag), one at +6 (actual ref count).
            if (*(short *)((int)oldPtr + 4) != 0) { // likely a flag indicating if it's reference counted
                // decrement ref count at offset 6
                *(short *)((int)oldPtr + 6) = *(short *)((int)oldPtr + 6) - 1;
                if (*(short *)((int)oldPtr + 6) == 0) {
                    (*(void (__thiscall *)(int))(*oldPtr))(1); // virtual destructor call? First virtual function with argument 1.
                }
            }
        }
        *(void **)((char *)this + 0x10) = resourcePtr;
        if (resourcePtr != NULL) {
            if (*(short *)((int)resourcePtr + 4) != 0) {
                *(short *)((int)resourcePtr + 6) = *(short *)((int)resourcePtr + 6) + 1;
            }
        }
    }
    // Store flags at +0x44 (0x11 * 4)
    *(int *)((char *)this + 0x44) = flags;
    
    if (resourcePtr == NULL) { // param_1 == 0
        FUN_0045cbe0(); // likely some global time initialization
        // Set several fields to a global value
        int globalVal = DAT_00e2b1a4; // unknown global
        *(int *)this = globalVal;
        *(int *)((char *)this + 0x14) = globalVal; // +0x14
        *(int *)((char *)this + 0x28) = globalVal; // +0x28
        *(int *)((char *)this + 0x3C) = 0;        // +0x3C
        *(int *)((char *)this + 0x38) = 0;        // +0x38
        *(int *)((char *)this + 0x34) = 0;        // +0x34
        *(int *)((char *)this + 0x30) = 0;        // +0x30
    } else {
        FUN_005420c0((int)resourcePtr + 0xe0); // call some method on resource + 0xe0
        if (flags != 0) {
            FUN_00556fd0((int)resourcePtr); // call another function on resource
            int extraVal = 0;
            if (*(int *)((int)resourcePtr + 0xc) != 0) {
                extraVal = *(int *)((int)resourcePtr + 0xc);
            }
            if (*(int *)((char *)this + 0x60) != extraVal) { // +0x60 (0x18*4)
                *(int *)((char *)this + 0x60) = extraVal;
            }
        }
    }
    
    // Compute handle value
    uint handleBase;
    if (flags != 0) {
        handleBase = FUN_0043b490(); // likely a generation or ID function
    } else {
        handleBase = 0;
    }
    // Build 64-bit handle: high word from some global table, low word packed with slot and handleBase
    uint tableVal = *(int *)(*(int *)(DAT_01223480 + 0x54) + 0x34 + slotIndex * 4);
    uint64 handle = ((uint64)tableVal << 32) | ((handleBase & 0xfff) << 16) | (slotIndex & 0x1f);
    handle |= 0x3e0ULL; // set bits 5-9
    *(uint64 *)((char *)this + 0x4C) = handle; // +0x4C (0x13*4)
    *(uint64 *)((char *)this + 0x54) = 0xffffffffffffffffULL; // +0x54 (0x15*4)
    *(int *)((char *)this + 0x5C) = 0; // +0x5C (0x17*4)
}