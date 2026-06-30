// FUNC_NAME: findHandlerForID
// Function at 0x00596f50: Finds first handler in global list that matches given ID.
// Iterates g_handlerList[0..g_handlerCount), calls vtable function at offset 0x2c
// on object at handler+0x30. Returns handler pointer if vtable function returns 0.

#include <cstddef>

// Global data
extern int* g_handlerList;       // Actually array of pointers at DAT_0119c6d0
extern int g_handlerCount;       // DAT_01205594
extern void* g_handlerVTableBase; // DAT_01205590 (points to a class instance with vtable)

// The virtual function type at vtable offset 0x2c (index 0x2c/4 = 11)
typedef int (__thiscall* MatchFunc)(void* obj, int id);

void* findHandlerForID(int id)
{
    if (id == 0)
        return 0;

    for (int i = 0; i < g_handlerCount; i++)
    {
        void* handler = (void*)g_handlerList[i];
        if (handler != 0)
        {
            // Offset to the actual object that has the vtable
            void* obj = (char*)handler + 0x30;

            // Get the vtable pointer from the global base class instance
            void** vtable = *(void***)g_handlerVTableBase;

            // The virtual function at offset 0x2c in the vtable
            MatchFunc canHandle = (MatchFunc)vtable[0x2c / 4];

            if (canHandle(obj, id) == 0)
                return handler;
        }
    }
    return 0;
}