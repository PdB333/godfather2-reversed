// FUNC_NAME: ScriptVM::executeFunction
// Function at 0x0058ff90: Script VM main execution loop. Given a bytecode function reference (hash) and arguments, 
// it sets up a local stack frame, looks up the bytecode in a hash table, and runs the opcodes.
// Supports 35 opcodes (0x23) via two dispatch tables: opcodeExecute handles the operation, opcodePost handles side effects.
// The bytecode structure has: +1: argument count, +4: hash, +0xc: argument values (4 bytes each).
// Stack frame is allocated on a custom allocator and stores local variables at indices 0..stackSize-1.
// Special slot at +0x3fc (stack[255]) holds a pointer (param_3) perhaps for the return value target.

#include <cstdint>

// Forward declarations for data tables (defined elsewhere)
extern const void* opcodeExecuteTable[0x23]; // DAT_0103b050
extern const void* opcodePostTable[0x23];    // DAT_0103afc0
extern float globalSomeFloat;                // DAT_00e2b1a4

// Structures
struct ScriptBytecode {
    uint8_t argCount;       // +0: actually used as char at +1? Let's assume offset 0 is something else
    uint32_t hash;          // +4
    // +8 maybe padding? Then +0xc: args array
    uint32_t args[1];       // variable length
};

struct ScriptFunctionEntry {
    uint32_t hash;
    uint8_t* bytecode;      // pointer to opcode bytes
    // followed by next pointer etc.
};

struct HashTable {
    uint32_t size;
    uint32_t numSlots;
    // bucket array
};

struct ScriptVM {
    // +0x70: pointer to something that contains a hash table pointer at +0x30
    uint32_t* hashTablePtr; // relative offset? Actually at +0x70 there is a pointer, then +0x30 inside that points to hash table
    // ... other members
};

// Internal functions (declared elsewhere)
extern void scriptStackInit();                 // FUN_0058ab50
extern int  scriptStackAllocate(int size);     // FUN_005822d0
extern void scriptStackDeallocate(void* ptr);  // FUN_00591c00
extern void scriptStackDestructor(int* stack); // (**(code **)(*local_4 + 4))(stack,0)
extern void scriptStackSizeDestructor(int* size); // (**(code **)(*piStack_c + 4))(size,0)
extern void scriptStackCleanup();              // (**(code **)(*piStack_c + 0xc))()

int __thiscall ScriptVM::executeFunction(void* thisPtr, ScriptBytecode* bytecode, uint32_t* argStack, uint32_t arg4, uint32_t arg5, uint32_t arg6, uint32_t arg7) {
    uint32_t* stack;          // local_14
    uint32_t stackSize;       // local_10 (word at stack[-something]? Actually it's a variable)
    uint32_t localStack;      // local_18 used for initialization
    uint32_t* stackPtr;       // local_4
    uint32_t* stackSizePtr;   // piStack_c

    // Initialization
    scriptStackInit();

    // Ensure stack can hold at least 256 entries (0x100)
    if (stackSize < 0x100) {
        localStack = 0;
        scriptStackAllocate(&localStack); // allocate initial stack?
    }

    // Store the argument stack pointer at slot 0x3fc (special slot)
    *(uint32_t**)((uint8_t*)stack + 0x3fc) = argStack;

    int argIndex = 0;
    // Copy arguments from bytecode into the stack (reverse order? indices 0xfe - argIndex)
    if (bytecode->argCount > 0) {
        uint32_t* srcArgs = &bytecode->args[0]; // assuming args start at +0xc
        do {
            uint32_t stackSlot = 0xfe - argIndex; // 254,253,... (room for 255 args max)
            if (stackSlot >= stackSize) {
                // Expand stack if needed
                int newSize = stackSlot + 1;
                scriptStackAllocate(newSize);
                // Zero out new slots (stack[stackSize] to stack[newSize-1])
                uint32_t* ptr = (uint32_t*)((uint8_t*)stack + stackSize * 4);
                for (uint32_t i = stackSize; i < newSize; i++) {
                    *ptr = 0;
                    ptr++;
                }
                stackSize = newSize;
            }
            // Copy argument value to stack[stackSlot]
            *(uint32_t*)((uint8_t*)stack + stackSlot * 4) = *srcArgs;
            srcArgs++;
            argIndex++;
        } while (argIndex < bytecode->argCount);
    }

    // Lookup function bytecode in hash table
    HashTable* ht = *(HashTable**)(*(uint32_t*)((uint8_t*)thisPtr + 0x70) + 0x30); // this->somePtr->hashTable
    uint32_t hash = bytecode->hash;
    uint32_t bucketIdx = hash % ht->numSlots;
    ScriptFunctionEntry* entry = *(ScriptFunctionEntry**)((uint8_t*)ht + 0x8 + bucketIdx * 4); // bucket array

    while (entry != nullptr) {
        if (entry->hash == hash) {
            uint8_t* pbVar7 = entry->bytecode;
            goto found;
        }
        entry = (ScriptFunctionEntry*)((uint8_t*)entry + 12); // next pointer at +12? Actually hash table entry: hash (4), bytecode (4), next (4)
    }

    // Not found: pbVar7 = null
    pbVar7 = nullptr;

found:
    uint32_t result = 0;
    if (pbVar7 != nullptr) {
        float opResult = globalSomeFloat; // default result?
        uint8_t opcode = (*pbVar7) & 0x3f; // lower 6 bits

        if (opcode < 0x23) {
            // Call the execute handler: it returns a float (maybe the computed value)
            typedef float (*OpcodeExec)(ScriptVM*, uint8_t* bytecode, uint32_t** stack);
            OpcodeExec execFunc = (OpcodeExec)opcodeExecuteTable[opcode];
            opResult = execFunc(thisPtr, pbVar7, &stack);
        }

        int16_t slot = *(int16_t*)(pbVar7 + 2); // slot index where to store result
        if ((uint32_t)slot >= stackSize) {
            // Need to expand stack (or allocate)
            uint32_t* newStack = nullptr;
            scriptStackAllocate(&newStack);
            // copy? Actually the code just calls scriptStackAllocate and ignores result? 
        }
        // Store result in stack[slot]
        *(float*)((uint8_t*)stack + slot * 4) = opResult;

        if (opcode < 0x23) {
            // Call the post-exec handler (returns result to propagate)
            typedef uint32_t (*OpcodePost)(ScriptVM*, uint8_t* bytecode, uint32_t** stack, uint32_t, uint32_t, uint32_t, uint32_t);
            OpcodePost postFunc = (OpcodePost)opcodePostTable[opcode];
            result = postFunc(thisPtr, pbVar7, &stack, arg4, arg5, arg6, arg7);
        } else {
            result = 0;
        }
    }

    // Cleanup
    // Call destructor for stack (via vtable)
    (*(void (*)(uint32_t*, int))(*stackPtr + 4))(stack, 0);   // local_4 destructor
    if (stackSize != 0) {
        (*(void (*)(uint32_t*, int))(*stackSizePtr + 4))(&stackSize, 0); // piStack_c destructor
    }
    (*(void (*)())(*stackSizePtr + 0xc))(); // piStack_c cleanup method

    return result;
}