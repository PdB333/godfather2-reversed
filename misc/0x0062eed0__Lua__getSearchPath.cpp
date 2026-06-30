// FUNC_NAME: Lua::getSearchPath
// Address: 0x0062eed0
// Retrieve a Lua search path string from the top of the stack (if a string), 
// else fallback to the LUA_PATH environment variable, or the default "?;?.lua".
// Stack is managed as a simple array of TValue entries (8 bytes each: type + data pointer).

struct Lua;

// Forward declarations for internal functions
void __cdecl initialize();                          // FUN_00625ca0
void* __cdecl getStackTop();                        // FUN_00633cb0 – returns pointer to current top TValue
int __cdecl checkStackOverflow(void* state, int);   // FUN_00633990 – returns nonzero if overflow allowed
void __cdecl handleStackOverflow();                 // FUN_00627360 – error handling / stack growth

char* __thiscall Lua::getSearchPath(Lua* this) {
    int* stackPtr;          // pointer to current stack position (from this+0x08)
    void* topAddr;          // address of top TValue from external function
    int typeTag;            // type tag of the TValue (0=nil, 4=string)
    char* result;           // returned path string
    int overflowFlag;       // result of overflow check
    int thisAsInt = reinterpret_cast<int>(this); // for offset arithmetic

    initialize();
    topAddr = getStackTop();              // get the current top value from somewhere
    stackPtr = *reinterpret_cast<int**>(thisAsInt + 0x08); // this->stackPtr

    // Copy the TValue data into the stack slot below the current pointer
    *reinterpret_cast<int*>(stackPtr - 2) = *reinterpret_cast<int*>(topAddr);           // copy type
    *reinterpret_cast<int*>(stackPtr - 1) = *reinterpret_cast<int*>(static_cast<char*>(topAddr) + 4); // copy data

    // Read the type tag from the newly written slot
    typeTag = *reinterpret_cast<int*>(stackPtr - 2);

    if (typeTag == 0) {
        // Nil type -> no path on stack
        result = nullptr;
    }
    else if (typeTag == 4) {
        // String type -> the data part is a pointer to a TString struct; string chars at offset +0x10
        result = reinterpret_cast<char*>(*reinterpret_cast<int*>(stackPtr - 1) + 0x10);
    }
    else {
        // Other types: check if we can still convert (or fallback)
        overflowFlag = checkStackOverflow(
            *reinterpret_cast<void**>(thisAsInt + 0x10), // this->stateControl
            0 // assumed base index
        );
        if (overflowFlag == 0) {
            result = nullptr;
        }
        else {
            result = reinterpret_cast<char*>(*reinterpret_cast<int*>(stackPtr - 1) + 0x10);
        }
        // Stack overflow protection check (compare two fields in control structure)
        if (*reinterpret_cast<uint*>(*reinterpret_cast<int*>(thisAsInt + 0x10) + 0x20) <=
            *reinterpret_cast<uint*>(*reinterpret_cast<int*>(thisAsInt + 0x10) + 0x24)) {
            handleStackOverflow();
        }
    }

    // Pop the stack by decrementing the pointer (8 bytes = 2 ints)
    *reinterpret_cast<int*>(thisAsInt + 0x10) = reinterpret_cast<int>(stackPtr - 2);

    // If no string on stack, try environment, then default
    if (result == nullptr) {
        result = _getenv("LUA_PATH");
        if (result == nullptr) {
            result = "?;?.lua";
        }
    }
    return result;
}