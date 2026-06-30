// FUNC_NAME: BehaviorSystem::dispatchOperation
// Function address: 0x00626ed0
// This function dispatches based on an operation type (byte at this+0x04)
// and decrements a timer/health value at offset 0x34 from the context object (param_1)

void __fastcall BehaviorSystem::dispatchOperation(int param_1) // in_EAX = this, param_1 in edx
{
    // DAT_012059e0 is a global function pointer (probably update routine)
    extern void (*g_globalBehaviorFunc)();
    int* timerPtr; // used to decrement a counter

    switch (*(char*)(this + 4)) // operationType at this+0x04
    {
    case 4: // Operation type 4: decrement by (value at this+0x0C) + 17
        {
            int decrement = *(int*)(this + 0x0C) + 0x11;
            (*g_globalBehaviorFunc)();
            if (param_1 != 0)
            {
                // param_1 points to a context structure with a sub-object at +0x10
                // that sub-object has a timer/health at +0x24
                timerPtr = (int*)(*(int*)(param_1 + 0x10) + 0x24);
                *timerPtr -= decrement;
            }
            break;
        }
    case 5: // Operation type 5: call specific behavior
        FUN_00637ce0(param_1); // possibly follow/attack behavior
        return;
    case 6: // Operation type 6: global behavior without context
        FUN_00638460(); // possibly idle/roam behavior
        return;
    case 7: // Operation type 7: decrement by (value at this+0x0C) + 16
        {
            int decrement = *(int*)(this + 0x0C) + 0x10;
            (*g_globalBehaviorFunc)();
            if (param_1 != 0)
            {
                timerPtr = (int*)(*(int*)(param_1 + 0x10) + 0x24);
                *timerPtr -= decrement;
            }
            break;
        }
    case 8: // Operation type 8: call specific behavior with context
        FUN_00627810(param_1); // possibly flee/hide behavior
        return;
    case 9: // Operation type 9: global behavior without context
        FUN_00638370(); // possibly patrol/guard behavior
        return;
    case 10: // Operation type 10: decrement by 20
        (*g_globalBehaviorFunc)();
        if (param_1 != 0)
        {
            timerPtr = (int*)(*(int*)(param_1 + 0x10) + 0x24);
            *timerPtr -= 0x14; // subtract 20
        }
        break;
    default: // No operation
        break;
    }
}