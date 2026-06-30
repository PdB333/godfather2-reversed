// FUNC_NAME: ToluaBinding::gcCallback
// Handles garbage collection and value pushing for bound objects (lightuserdata/userdata)
// Based on EA Godfather 2 tolua binding runtime

typedef unsigned int uint32;

struct tolua_State {
    // +0x00: unknown
    // +0x04: unknown
    void* stackTop;      // +0x08: current top of stack (pointer to array of TValue)
    void* functionStack; // +0x0C: current function's argument stack or base
};

struct TValue {
    int type;        // +0x00: Lua type (2=lightuserdata, 3=number, 4=string, 6=function, 7=userdata)
    uint32 value;    // +0x04: union value (for userdata: pointer to Udata, for lightuserdata: pointer)
    // For userdata (type=7), actual object at value+0x10
};

// External functions (prototypes)
void tolua_gc(tolua_State* L, const char* msg);
void* tolua_gettype_3(); // returns pointer to type/value pair for number
void* tolua_gettype_4(); // for string
void* tolua_gettype_other(); // generic
void tolua_checktype(tolua_State* L, int index, int type);
void* tolua_pushvalue(tolua_State* L, uint32 v); // returns pointer to newly pushed TValue

uint32 FUN_0063bd90(tolua_State* L)
{
    uint32 storedValue;
    TValue* currentEntry;
    TValue* newEntry;
    TValue* result;
    TValue* stackSlot;

    // Get current entry from function stack (or argument list)
    currentEntry = (TValue*)L->functionStack;
    if ((currentEntry < (TValue*)L->stackTop) && (currentEntry != nullptr)) {
        if (currentEntry->type == 2) { // LUA_TLIGHTUSERDATA
            newEntry = (TValue*)currentEntry->value;
        }
        else if (currentEntry->type == 7) { // LUA_TUSERDATA
            // For userdata, the actual object is at value + 0x10
            newEntry = (TValue*)(currentEntry->value + 0x10);
        }
        else {
            newEntry = nullptr;
        }
    }
    else {
        newEntry = nullptr;
    }
    storedValue = newEntry->value; // save the pointer or object ID

    // Call gc (probably to manage reference)
    tolua_gc(L, "tolua_gc");

    // Manipulate stack: replace the current top with a new type/value
    stackSlot = (TValue*)L->stackTop;
    int typePrev = (int)(stackSlot[-1].type); // type of the top element before gc?
    // Actually it reads stackSlot[-2] and stackSlot[-1] (type and value of previous slot)
    if (stackSlot[-2].type == 3) { // LUA_TNUMBER
        // Check for integer float equality (type coercion)
        if ((float)(int)(*(float*)&stackSlot[-2].value) == *(float*)&stackSlot[-2].value) {
            result = (TValue*)tolua_gettype_3(); // treat as number
        } else {
            goto generic;
        }
    }
    else if (stackSlot[-2].type == 4) { // LUA_TSTRING
        result = (TValue*)tolua_gettype_4();
    }
    else {
generic:
        result = (TValue*)tolua_gettype_other();
    }
    // Write new type and value to stack slot
    stackSlot[-2].type = result->type;
    stackSlot[-2].value = result->value;

    // Push a new entry with type = 2 (lightuserdata) containing storedValue
    newEntry = (TValue*)L->stackTop;
    newEntry->type = 2;
    newEntry->value = storedValue;
    L->stackTop = (void*)((char*)L->stackTop + sizeof(TValue)); // advance top by 8

    // Now process the next entry (which was just pushed)
    stackSlot = (TValue*)L->stackTop;
    typePrev = stackSlot[-1].type; // type of the just-pushed entry
    if (typePrev == 3) {
        if ((float)(int)(*(float*)&stackSlot[-1].value) == *(float*)&stackSlot[-1].value) {
            result = (TValue*)tolua_gettype_3();
            goto writeType;
        }
    }
    else if (typePrev == 4) {
        result = (TValue*)tolua_gettype_4();
        goto writeType;
    }
    result = (TValue*)tolua_gettype_other();
writeType:
    stackSlot[-1].type = result->type;
    stackSlot[-1].value = result->value;

    // Check if the previous stack entry (two slots back) had type 6 (function)
    newEntry = (TValue*)L->stackTop;
    if ((newEntry - 2 != nullptr) && (newEntry[-2].type == 6)) {
        // Copy from functionStack (currentEntry) to stack
        TValue* funcPtr = (TValue*)L->functionStack;
        newEntry[-1].type = funcPtr->type;
        newEntry[-1].value = funcPtr->value;
        L->stackTop = (void*)((char*)L->stackTop + sizeof(TValue)); // advance top

        // Call a checker on a value at offset -0x10 from new top
        tolua_checktype(L, (int)((char*)L->stackTop - 0x10), 0); // second param is index, third is type? (0 maybe)

        // Push another lightuserdata with storedValue
        newEntry = (TValue*)L->stackTop;
        newEntry->type = 2;
        newEntry->value = storedValue;
        L->stackTop = (void*)((char*)L->stackTop + sizeof(TValue));

        // Push a nil or zero
        *(uint32*)L->stackTop = 0; // push as a raw integer? type not set
        L->stackTop = (void*)((char*)L->stackTop + sizeof(uint32)); // advance by 4? Actually typical push of value

        // Get a new stack slot from a helper (likely pushes a value and returns pointer)
        int slotIndex = (int)((char*)L->stackTop - 0x14); // computed index
        result = (TValue*)tolua_pushvalue(L, *(uint32*)((char*)L->stackTop - 8));
        // Write the type and value from the helper return
        *result = *(TValue*)((char*)L->stackTop - 8); // copy the pair

        // Adjust stack downward by 0x10 bytes (two slots)
        L->stackTop = (void*)((char*)L->stackTop - 0x10);
        L->stackTop = (void*)((char*)L->stackTop - 0x10);
        return 0;
    }

    // Otherwise, pop two slots (undo the push)
    L->stackTop = (void*)((char*)L->stackTop - 0x10);
    return 0;
}