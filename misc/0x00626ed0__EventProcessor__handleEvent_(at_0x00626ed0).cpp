// FUNC_NAME: EventProcessor::handleEvent (at 0x00626ed0)
// Role: Dispatches event processing based on event type stored at this+0x04, with event data at this+0x0C.
//       Modifies a counter in *context+0x10 +0x24 depending on event type and optional context pointer.
//       Global function pointer at DAT_012059e0 is called before modifications.

void __fastcall EventProcessor::handleEvent(int context) // __fastcall: first param (context) in ECX? Actually uses EAX as this
{
    int* piVar1;
    int this = in_EAX; // EAX holds the 'this' pointer (object with event data)
    int eventType = *(char*)(this + 4);
    int dataValue = *(int*)(this + 0xC);
    int adjustment;

    // Global function pointer (likely a vtable-based process or update)
    void (*g_pfnBeforeModify)() = (void (*)())(DAT_012059e0); // replace with proper type if known

    switch (eventType) {
    case 4:
        adjustment = dataValue + 0x11;
        break;
    case 5:
        FUN_00637ce0(context); // processEventType5(context)
        return;
    case 6:
        FUN_00638460(); // processEventType6()
        return;
    case 7:
        adjustment = dataValue + 0x10;
        break;
    case 8:
        FUN_00627810(context); // processEventType8(context)
        return;
    case 9:
        FUN_00638370(); // processEventType9()
        return;
    case 10:
        // Direct fixed subtract
        g_pfnBeforeModify();
        if (context != 0) {
            piVar1 = (int*)(*(int*)(context + 0x10) + 0x24); // context->[0x10] + 0x24 (some counter)
            *piVar1 -= 0x14;
        }
        return;
    default:
        return;
    }

    // Common path for cases 4 and 7
    g_pfnBeforeModify();
    if (context != 0) {
        piVar1 = (int*)(*(int*)(context + 0x10) + 0x24); // context->[0x10] + 0x24 (counter)
        *piVar1 -= adjustment;
    }
}