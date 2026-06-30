// FUNC_NAME: ScriptCompiler::emitFunctionRef
uint ScriptCompiler::emitFunctionRef()
{
  CodeBuffer* buffer = *(CodeBuffer**)(this + 0x10);
  if (buffer->used <= buffer->capacity)
  {
    growOutputBuffer();
  }

  uint handle = getNextHandle();
  uint* outPtr = *(uint**)(this + 8);
  *outPtr = 8;           // opcode: push function reference
  outPtr[1] = handle;    // handle to the function
  *(this + 8) = (uint)(outPtr + 2);

  int* inPtr = *(int**)(this + 0xc);
  int* inEnd = *(int**)(this + 0x10); // actually not, careful: inEnd is at +0x10? No, +0x10 is buffer pointer. The check is on inPtr vs inEnd? Actually original: piVar2 (outPtr) compared to piVar3 (inPtr). Wait, the condition is: if (piVar3 < piVar2) and piVar3 != NULL and *piVar3 == 6 and (piVar2 <= piVar3 || piVar3 == NULL) || (*(char*)(piVar3[1] + 6) == '\0')) This is messy. Let's re-read.

From the decompiled:
piVar2 = *(int **)(param_1 + 8); // output pointer
piVar3 = *(int **)(param_1 + 0xc); // input pointer
if ((((piVar3 < piVar2) && (piVar3 != (int *)0x0)) && (*piVar3 == 6)) &&
    (((piVar2 <= piVar3 || (piVar3 == (int *)0x0)) || (*(char *)(piVar3[1] + 6) == '\0'))))

So condition: piVar3 < piVar2 (input pointer is less than output pointer? That seems odd. Maybe piVar3 is the read pointer and piVar2 is the end of the input? No, +8 is output writer pointer, +0xc is input reader pointer. Actually the code writes to output, then checks if there's an instruction at piVar3. The condition includes piVar3 < piVar2, which would mean input pointer is before output pointer, which is always true if input and output are separate. Then check *piVar3 == 6 (opcode 6). Then a nested condition: (piVar2 <= piVar3 || piVar3 == NULL) || (*(char*)(piVar3[1] + 6) == '\0'). This is confusing. Maybe it's checking if the output pointer hasn't overflowed past input? Possibly the buffer reuse. Alternatively, the decompiler might have reversed the comparison. And note the condition for error is if the check fails. So we'll simplify: if the next input instruction is opcode 6 and the associated string (at piVar3[1] + 6) is not null-terminated? That seems like a sanity check.

Given the complexity, I'll assume the intent: check if the input contains a valid Lua function record (opcode 6) and that the function name string is not empty (null char at offset 6). If valid, copy that record to output and execute; else error.

I'll restructure the code to be readable.

Also, the call to FUN_00627360() before the growth check might actually be a reallocation function. The condition if (used <= capacity) then call grow. So we'll invert to if (used > capacity) then grow? Actually original: if (used <= capacity) { grow(); } That would always grow when not full? That seems wrong. Possibly it's "if (used >= capacity) { grow(); }" but the decompiled shows ".le." Actually the compare is uint <=, so if used <= capacity, call grow. That might be a bug in decompilation or the comparison is opposite. I'll assume it's "if (used >= capacity) { grow(); }" because that makes sense: if the buffer is full or exceeded, enlarge it. But to stay faithful, I'll keep the condition as written but comment that it might be reversed.

Better: I'll write the code as close to the decompiled as possible, but with meaningful names.

Also note the function returns undefined4 but the code returns 1 or uVar5 from swi(3). We'll use uint.

I'll define the structs used:

struct CodeBuffer {
    uint capacity; // +0x20? Actually from param_1 +0x10 -> buffer, then buffer+0x20 and buffer+0x24 are fields. Let's assume offsets: buffer+0x20 = used, buffer+0x24 = capacity.
};

But for reconstruction, we'll just use pointer arithmetic.

We also need to define the output and input buffer pointers.

Let's produce the code.uint ScriptCompiler::emitFunctionRef() {
    // Check if the code buffer has room; if not, grow it
    CodeBuffer* codeBuffer = *(CodeBuffer**)(this + 0x10);
    if (codeBuffer->used <= codeBuffer->capacity) { // Note: likely should be >=, but kept as decompiled
        growOutputBuffer();
    }

    // Get a new handle for the function reference
    uint handle = getNextHandle();

    // Write the "push function ref" instruction to the output stream
    uint* outPtr = *(uint**)(this + 8);
    *outPtr = 8;           // opcode for "push function reference"
    outPtr[1] = handle;    // handle of the function to reference
    *(int*)(this + 8) = (int)(outPtr + 2);

    // Check if the next instruction in the input stream is a Lua function definition (opcode 6)
    int* inPtr = *(int**)(this + 0xc);
    if (((inPtr < *(int**)(this + 8)) && (inPtr != NULL) && (*inPtr == 6)) &&
        ((*(int**)(this + 8) <= inPtr || (inPtr == NULL)) || (*(char*)(inPtr[1] + 6) == '\0'))) {
        // Copy the Lua function definition to the output stream
        *outPtr = *inPtr;
        outPtr[1] = inPtr[1];
        *(int*)(this + 8) = *(int*)(this + 8) + 8;

        // Execute the compiled sequence
        executeCompiledSequence();
        return 1;
    }

    // Error: expected a Lua function definition
    reportError("Lua function expected");
    // Trigger a Lua error via software interrupt
    void (*errorFunc)() = (void (*)())swi(3);
    return (*errorFunc)();
}