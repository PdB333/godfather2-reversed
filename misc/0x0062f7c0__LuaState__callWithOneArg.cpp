// FUNC_NAME: LuaState::callWithOneArg
// Address: 0x0062f7c0
// This function pushes a value obtained from getValue() onto the Lua stack,
// then checks if the function at the stack base (param_1+0x0C) is a valid Lua function.
// If valid, it copies the function to the top and calls it with the pushed argument.
// Otherwise, it triggers a Lua error.

#include <cstdint>

// Forward declarations of helper functions (from other translation units)
void checkStack(LuaState* L);           // FUN_00627360 - ensure stack space
int getValue();                         // FUN_00627770 - retrieve a value (e.g., from global)
void callFunction(LuaState* L);         // FUN_00625540 - perform the actual Lua call
void error(LuaState* L, int code, const char* msg); // FUN_00627a20 - raise Lua error

// Lua type constants (custom or standard)
enum LuaType {
    LUA_TNIL = 0,
    LUA_TBOOLEAN = 1,
    LUA_TLIGHTUSERDATA = 2,
    LUA_TNUMBER = 3,
    LUA_TSTRING = 4,
    LUA_TTABLE = 5,
    LUA_TFUNCTION = 6,
    LUA_TUSERDATA = 7,
    LUA_TTHREAD = 8
};

// Structure representing a Lua TValue (type + value)
struct TValue {
    LuaType type;   // +0x00
    int value;      // +0x04 (could be a pointer or number)
};

// Structure representing a Lua function closure
struct Closure {
    // ... other fields
    char flags;     // +0x06 (e.g., isC flag)
};

// Structure representing the Lua state (partial)
struct LuaState {
    // +0x00: unknown
    // +0x04: unknown
    TValue* stackTop;       // +0x08: pointer to next free stack slot
    TValue* stackBase;      // +0x0C: pointer to base of current function call
    void* globalState;      // +0x10: pointer to global state (e.g., lua_State->l_G)
    // +0x14: unknown
    // +0x18: unknown
    // +0x1C: unknown
    // +0x20: stack size limit? (offset from globalState)
    // +0x24: current stack size? (offset from globalState)
};

int LuaState::callWithOneArg() {
    // Check if stack has room (compare sizes at globalState+0x20 and +0x24)
    if (*(uint32_t*)(*(int*)(this + 0x10) + 0x20) <= *(uint32_t*)(*(int*)(this + 0x10) + 0x24)) {
        checkStack(this);
    }

    // Get the value to push (e.g., a number from a global or argument)
    int value = getValue();

    // Push a TValue of type LUA_TTHREAD (8) with the obtained value
    TValue* top = this->stackTop;
    top->type = LUA_TTHREAD;   // 8
    top->value = value;
    this->stackTop = top + 1;  // advance stack pointer

    // Now check if the function at the stack base is a valid Lua function
    TValue* base = this->stackBase;
    TValue* newTop = this->stackTop;

    // Condition: base < newTop (there is something to read), base != NULL,
    // base->type == LUA_TFUNCTION, and the function's closure has a zero flag at offset +6
    if (base < newTop && base != nullptr && base->type == LUA_TFUNCTION) {
        // Check the closure's flag byte (offset +6 of the value part)
        Closure* closure = reinterpret_cast<Closure*>(base->value);
        if (closure->flags == 0) {
            // Copy the function TValue to the top of the stack
            newTop->type = base->type;
            newTop->value = base->value;
            this->stackTop = newTop + 1;

            // Call the function (which will consume the argument below)
            callFunction(this);
            return 1;
        }
    }

    // If not a valid function, raise an error
    error(this, 1, "Lua function expected");
    // Trigger a software interrupt (debug break) and call a function pointer
    // (This is likely a fatal error handler)
    void (*handler)() = reinterpret_cast<void (*)()>(swi(3));
    handler();
    return 0; // unreachable
}