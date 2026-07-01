// FUNC_NAME: AptFunctionContext::callFunction
// Address: 0x005a04a0
// Role: Calls an ActionScript function by name with typed parameters. Handles parameter allocation, conversion, and cleanup.

#include <cstdint>
#include <cstring>
#include <cassert>

// Forward declarations for called functions
void* AptContextCreate(int flags, int size, int unk1, int unk2);
void AptContextPushValue(void* context, void* value, int paramIndex, int unk1, int unk2);
void AptContextExecute(void* context, int paramIndex);
void AptContextPop(void* context, int numParams);
void* AptValueAlloc(int size, int zeroFlag); // size=0x24
void AptValueInit(void* value); // sets up type/refcount
void AptValueSetString(void* value, const char* str, int maxLen);
void AptValueFree(void* value); // decref/destroy
char* ToLowerStringBuffer(const char* src, int maxLen); // returns new buffer or src if unchanged

extern int gAptDebugEnabled; // DAT_012055b0
extern void* gAptAllocator; // DAT_0119caf0 (function pointer)
extern void (*gAptFree)(void* ptr); // DAT_0119caf4

void aptCallFunction(void* contextHandle, char* functionName, int paramSize, int numParams)
{
    int i;
    void* execContext = nullptr;
    void* valueArray[32]; // stack-allocated for up to 32 params

    if (!gAptDebugEnabled)
        return;

    // Validate parameter count
    if (numParams < 0 || numParams >= 32) {
        // EA assert: nNumParams >= 0 && nNumParams < 32
        // In debug build, trigger breakpoint
        assert(!"nNumParams out of range");
        return;
    }

    // Create execution context: if paramSize==0, empty; else create with given size
    if (paramSize == 0) {
        execContext = AptContextCreate();
    } else {
        uint32_t flags = 1; // or something
        execContext = AptContextCreate(0, paramSize, 1, 1);
    }

    // Allocate and initialize value objects for each parameter
    for (i = 0; i < numParams; i++) {
        void* value = AptValueAlloc(0x24, 0); // size 0x24, zero-initialized
        if (value) {
            // Set initial type/flags: bit0=1 (object?), bit15=1 (string?), flags = 0x8001
            *(uint32_t*)value = (*(uint32_t*)value & 0xFFFF8001) | 1;
            *(uint16_t*)((uintptr_t)value + 2) = 0; // clear high bits
            *(uint32_t*)value = *(uint32_t*)value | 0x8000; // set type flag
            AptValueInit(value); // additional init
            valueArray[i] = value;
        }
        // Push value onto context (using param index? Actually the loop after collecting all values calls a push)
        // But note: The decompiled code calls push after each allocation? No, it does a separate loop at the end.
        // Actually the original code:
        //   puStack_84 = &param_4;
        //   do { ... puVar11 = puVar8; ... puStack_84++; auStack_80[iVar10] = puVar11; ... } while ...
        // Then later: while (iVar4-- > -1) { FUN_005a0b60(auStack_80[iVar4]); }
        // So it stores values, then after all allocations, it iterates back and destroys them.
        // But then after that, it calls FUN_005aea60 and FUN_005aec20. So the values are not pushed individually here.
        // The actual push likely happens inside FUN_005aea60 when given the array? Or maybe the array is passed as a list.
        // To match the original, we'll keep the allocation loop, then after that, push all values, then execute.
    }

    // Push all values onto the context (probably via a batch push function)
    // In the original, after the loop it calls FUN_005aea60 (push) and FUN_005aec20 (execute)
    // But the order is: after the loop, if pContext==0 assert, then FUN_005aea60, then FUN_005aec20.
    // So we need to push the values first.
    // For simplicity, we'll call a batch push: pushValues(context, valueArray, numParams)
    // But the original code calls FUN_005a0b60 on each value (which is deallocation) before the push? No, the second loop is for deallocation.
    // Wait, let's re-express the decompiled logic:
    // line: iVar10=0; iVar4=iVar12; if (0 < iVar12) { do { allocate...; puStack_84++; auStack_80[iVar10]=puVar11; ... iVar10++; } while (iVar10 < param_4); }
    // That allocates all values and stores them in auStack_80[0..param_4-1].
    // Then next: while (iVar4-- > -1) { FUN_005a0b60(auStack_80[iVar4]); iVar12=param_4; }
    // This second loop *frees* the values (decref). But it frees them all immediately after allocation, before calling the context functions.
    // That seems wrong: why allocate then free? Possibly the allocate function also registers the value in the context? Or the free function is actually a "publish" that adds them to context? No.
    // More likely, the second loop is actually pushing values to context, and the decompiler mis-identified the function.
    // Or maybe the free function is misnamed: it could be "AptValuePush" that adds to context and decrements ref? Unclear.
    // Given the pattern: allocate, store, then loop backward calling FUN_005a0b60, then call context functions, then cleanup string.
    // I think FUN_005a0b60 is "push value to context" (or "add to argument list") and also possibly increases refcount in context.
    // Then after the push loop, the context functions execute and pop.
    // So we'll treat FUN_005a0b60 as "pushValueToContext".

    // Let's implement as:
    // for (i=0; i<numParams; i++) { value = allocate...; valueArray[i]=value; pushValueToContext(execContext, value, i); }
    // Then execute.
    for (i = 0; i < numParams; i++) {
        void* value = AptValueAlloc(0x24, 0);
        if (value) {
            // init
            *(uint32_t*)value = (*(uint32_t*)value & 0xFFFF8001) | 1;
            *(uint16_t*)((uintptr_t)value + 2) = 0;
            *(uint32_t*)value = *(uint32_t*)value | 0x8000;
            AptValueInit(value);
            // Push to context (the original uses FUN_005a0b60)
            AptValuePushToContext(execContext, value);
            valueArray[i] = value; // Not used further
        }
    }

    // Now assert context is valid
    assert(execContext != nullptr); // "pContext" assertion at line 0x393

    // Execute the function call (the "push" and "execute" in original: FUN_005aea60 and FUN_005aec20)
    // The original: FUN_005aea60(iVar7,0,param_1,1,1); then FUN_005aec20(iVar7,iVar12);
    // But note: param_1 is the first argument to this function (contextHandle? Actually in callers, param_1 is often a pointer to something? We'll treat it as the "this" context or target object).
    // Since we don't have exact semantics, we'll map to:
    AptContextPushAndExecute(execContext, 0, contextHandle, 1, 1); // push and call
    AptContextPop(execContext, numParams);

    // String conversion for function name (lowercase in-place)
    if (functionName != nullptr) {
        char* buffer = ToLowerStringBuffer(functionName, 256); // 0x100 bytes
        if (buffer != functionName) {
            // Copy from buffer back to original (memmove)
            int diff = (intptr_t)functionName - (intptr_t)buffer;
            char* p = buffer;
            do {
                *p = *(p + diff); // Actually the code does: pcVar9[iVar12] = *pcVar9; pcVar9++; while *pcVar9 != '\0'
                // This is a weird copy but essentially it copies the string from buffer to functionName
                // We'll use memmove
                memmove(functionName, buffer, strlen(buffer) + 1);
                break;
            } while (false);
        }
    }

    // Cleanup (maybe pop or finalize)
    AptContextCleanup(execContext);
}