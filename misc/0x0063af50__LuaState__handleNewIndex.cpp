// FUNC_NAME: LuaState::handleNewIndex
// Address: 0x0063af50
// Role: Implements the __newindex metamethod for custom userdata types (likely game objects).
// Handles assignment of values to table-like structures, with type checking and conversion.

#include <cstdint>

// Forward declarations of Lua helper functions (inferred from callees)
void lua_pushstring(void* L, const char* str); // 0x00625ca0
int* lua_tonumber(void* L); // 0x00637f10
int* lua_tostring(void* L); // 0x00637f90
int* lua_touserdata(void* L); // 0x00637ea0
void lua_call(void* L); // 0x00625e70
void lua_settable(void* L, int offset); // 0x006362d0
void* lua_newuserdata(void* L, int size); // 0x00638020

// Lua type constants (guessed)
const int LUA_TNUMBER = 3;
const int LUA_TSTRING = 4;
const int LUA_TTABLE = 5;
const int LUA_TFUNCTION = 6;
const int LUA_TUSERDATA = 7;

// Lua state structure offsets (relative to param_1)
// +0x08: stackTop (current stack pointer)
// +0x0C: stackBase (bottom of stack)
// +0x10: extraPtr (maybe registry or global table)

int __thiscall handleNewIndex(void* L) {
    int* stackTop;
    int* piVar4;
    int* piVar2;
    int* puVar5;
    int iVar6;
    int type;
    int* typeValue;

    // Push "__newindex" string onto stack
    lua_pushstring(L, "__newindex");

    stackTop = *(int**)((char*)L + 8); // current stack top
    type = *(int*)((char*)stackTop - 8); // type of value at stack[-1] (the key?)

    // Determine the type of the value being assigned and get its internal representation
    if (type == LUA_TNUMBER) {
        // Check if float conversion is needed (NaN check)
        float f = *(float*)((char*)stackTop - 4);
        if ((float)(int)f != f) goto LAB_0063afa6;
        typeValue = (int*)lua_tonumber(L);
    }
    else if (type == LUA_TSTRING) {
        typeValue = (int*)lua_tostring(L);
    }
    else {
LAB_0063afa6:
        typeValue = (int*)lua_touserdata(L);
    }

    // Overwrite the stack top with the resolved type/value
    *(int*)((char*)stackTop - 8) = *typeValue;
    *(int*)((char*)stackTop - 4) = typeValue[1];

    piVar4 = *(int**)((char*)L + 8); // re-read stack top after potential changes

    // Check if the previous stack entry (key) is a table
    if ((piVar4 - 2 != nullptr) && (*(piVar4 - 2) == LUA_TTABLE)) {
        iVar6 = *(int*)((char*)L + 0xC); // stack base
        *piVar4 = *(int*)(iVar6 + 8);    // copy table pointer?
        piVar4[1] = *(int*)(iVar6 + 0xC);
        *(int*)((char*)L + 8) = (int)((char*)piVar4 + 8); // advance stack

        lua_call(L); // call the table's __newindex function?

        piVar4 = *(int**)((char*)L + 8);
        // Check if the result is a function and has a specific flag
        if ((piVar4 - 2 != nullptr) && (*(piVar4 - 2) == LUA_TFUNCTION && *(char*)(*(piVar4 - 1) + 6) != '\0')) {
            piVar2 = *(int**)((char*)L + 0xC);
            *piVar4 = *piVar2;
            piVar4[1] = piVar2[1];
            *(int*)((char*)L + 8) = (int)((char*)piVar4 + 8);

            iVar6 = *(int*)((char*)L + 0xC);
            puVar5 = *(int**)((char*)L + 8);
            *puVar5 = *(int*)(iVar6 + 0x10);
            puVar5[1] = *(int*)(iVar6 + 0x14);
            *(int*)((char*)L + 8) = (int)((char*)puVar5 + 8);

            lua_settable(L, *(int*)((char*)L + 8) - 0x18);
            return 0;
        }
    }

    piVar2 = *(int**)((char*)L + 0xC); // stack base
    if ((piVar2 < piVar4) && (piVar2 != nullptr)) {
        // Check the type at the base
        if (*piVar2 == LUA_TTABLE) {
            iVar6 = *(int*)(piVar2[1] + 8);
        }
        else {
            if (*piVar2 != LUA_TUSERDATA) goto LAB_0063b155;
            iVar6 = *(int*)(piVar2[1] + 8);
        }
        // If the value is non-zero and different from a stored reference
        if ((iVar6 != 0) && (iVar6 != *(int*)(*(int*)((char*)L + 0x10) + 0x38))) {
            piVar4[1] = iVar6;
            *piVar4 = LUA_TTABLE;
            *(int*)((char*)L + 8) = (int)((char*)piVar4 + 8);

            puVar5 = *(int**)((char*)L + 8);
            if (puVar5 - 2 != nullptr) {
                iVar6 = puVar5[-2];
                if (iVar6 == LUA_TTABLE) {
                    iVar6 = *(int*)(puVar5[-1] + 8);
                }
                else {
                    if (iVar6 != LUA_TUSERDATA) goto LAB_0063b155;
                    iVar6 = *(int*)(puVar5[-1] + 8);
                }
                if ((iVar6 != 0) && (iVar6 != *(int*)(*(int*)((char*)L + 0x10) + 0x38))) {
                    *puVar5 = LUA_TTABLE;
                    puVar5[1] = iVar6;
                    *(int*)((char*)L + 8) = (int)((char*)puVar5 + 8);

                    lua_pushstring(L, "__newindex");
                    lua_call(L);

                    puVar5 = *(int**)((char*)L + 8);
                    if ((puVar5 - 2 != nullptr) && (puVar5[-2] == LUA_TFUNCTION)) {
                        int* base = *(int**)((char*)L + 0xC);
                        *puVar5 = *base;
                        puVar5[1] = base[1];
                        *(int*)((char*)L + 8) = (int)((char*)puVar5 + 8);

                        iVar6 = *(int*)((char*)L + 0xC);
                        puVar5 = *(int**)((char*)L + 8);
                        *puVar5 = *(int*)(iVar6 + 8);
                        puVar5[1] = *(int*)(iVar6 + 0xC);
                        *(int*)((char*)L + 8) = (int)((char*)puVar5 + 8);

                        iVar6 = *(int*)((char*)L + 0xC);
                        puVar5 = *(int**)((char*)L + 8);
                        *puVar5 = *(int*)(iVar6 + 0x10);
                        puVar5[1] = *(int*)(iVar6 + 0x14);
                        *(int*)((char*)L + 8) = (int)((char*)puVar5 + 8);

                        lua_settable(L, *(int*)((char*)L + 8) - 0x20);
                    }
                }
            }
        }
    }

LAB_0063b155:
    // Clear remaining stack entries up to base+0x18
    if ((uintptr_t)*(int*)((char*)L + 8) < (uintptr_t)(*(int*)((char*)L + 0xC) + 0x18)) {
        do {
            **(int**)((char*)L + 8) = 0;
            *(int*)((char*)L + 8) = *(int*)((char*)L + 8) + 8;
        } while ((uintptr_t)*(int*)((char*)L + 8) < (uintptr_t)(*(int*)((char*)L + 0xC) + 0x18));
    }

    iVar6 = *(int*)((char*)L + 0xC);
    *(int*)((char*)L + 8) = iVar6 + 0x18; // reset stack top to base+0x18

    // Create a new userdata and store the result
    puVar5 = (int*)lua_newuserdata(L, *(int*)(iVar6 + 4));
    *puVar5 = *(int*)(iVar6 + 0x10);
    puVar5[1] = *(int*)(iVar6 + 0x14);
    *(int*)((char*)L + 8) = *(int*)((char*)L + 8) - 0x10; // adjust stack

    return 0;
}