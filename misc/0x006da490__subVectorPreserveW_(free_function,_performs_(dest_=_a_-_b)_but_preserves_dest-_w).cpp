// FUNC_NAME: subVectorPreserveW (free function, performs (dest = a - b) but preserves dest->w)

// Function address: 0x006da490
// Role: Subtracts two 4D vectors (a - b) component-wise, but leaves the w component of the destination unchanged.
// Uses __fastcall: param_1 (unused) in ECX, param_2 (a) in EDX, param_3 (b) on stack.
// The destination pointer is passed via EAX (non-standard).

void __fastcall subVectorPreserveW(void* unused, float* a, float* b)
{
    float* dest; // EAX - destination vector pointer
    asm("mov %0, eax" : "=r"(dest)); // Retrieve EAX as dest pointer (compiler-specific, but reflects decompiled code)

    float origW = dest[3]; // +0x0C: save original w component

    dest[0] = a[0] - b[0]; // x component
    dest[1] = a[1] - b[1]; // y component
    dest[2] = a[2] - b[2]; // z component
    dest[3] = a[3] - b[3]; // w component (temporary)

    dest[3] = origW; // restore original w
}