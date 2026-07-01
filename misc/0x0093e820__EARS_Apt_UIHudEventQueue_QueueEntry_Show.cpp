// Xbox PDB: EARS_Apt_UIHudEventQueue_QueueEntry_Show
// FUNC_NAME: Building::stateMachineUpdate
// Address: 0x0093e820
// Role: State machine update for building/venue after takeover attack
// Class: Building (EARS engine, The Godfather 2)

class Building;

typedef void (__thiscall *EAStringDestructor)(void*); // destructor for EA::BasicString

void __thiscall Building::stateMachineUpdate() {
    // +0x12: timer/counter (16-bit)
    *(short*)((char*)this + 0x12) = *(short*)((char*)this + 0x12) + 1;

    switch (*(int*)((char*)this + 0x8)) { // +0x8: current state
        case 0: {
            // Enter initial state
            ((void (__thiscall*)(void*))0x0093c970)(*(void**)((char*)this + 0x20));
            return;
        }
        case 1:
        case 6: {
            // Transition to another state
            ((void (__thiscall*)(void*))0x0093e3b0)(*(void**)((char*)this + 0x20));
            break;
        }
        case 2: {
            // General update
            ((void (__thiscall*)(void*))0x00939a30)(*(void**)((char*)this + 0x20));
            // Timer expired check
            if (*(short*)((char*)this + 0x12) == 0) {
                ((void (__thiscall*)(void*))0x004d3bc0)(*(void**)((char*)this + 0x20));
                // Callback with debug return address (0x93e84e)
                ((void (__thiscall*)(void*, void*, void*, void*))0x00938890)(
                    *(void**)((char*)this + 0x20), (void*)0, (void*)0x93e84e, *(void**)((char*)this + 0x20)
                );
            }
            break;
        }
        case 3: {
            // Process action with two data pointers
            ((void (__thiscall*)(void*, void*))0x0093b1b0)(
                *(void**)((char*)this + 0x20), *(void**)((char*)this + 0x24)
            );
            return;
        }
        case 4: {
            // Check condition for summary screen
            if (((int (__thiscall*)(void*))0x006b0ee0)(*(void**)((char*)this + 0x20)) != 0) {
                // Build summary screen string
                struct EAString { char* ptr; int length; EAStringDestructor destructor; };
                EAString str = {0, 0, 0};

                const char* venueName = (const char*)0x0;
                void* venuePtr = *(void**)((int (__thiscall*)())0x006b2160)();
                if (venuePtr == 0) {
                    venueName = (const char*)&DAT_0120546e; // default empty string
                } else {
                    venueName = *(const char**)venuePtr;
                }

                // Format: {v:<venue name>}{$summary_screen_after_venue}
                ((void (__thiscall*)(EAString*, const char*, const char*))0x004d4ad0)(
                    &str, "{v:%s}{$summary_screen_after_venue}", venueName
                );

                const char* strPtr = str.ptr;
                if (str.ptr == 0) {
                    strPtr = (const char*)&DAT_0120546e;
                }
                ((void (__thiscall*)(const char*))0x0093e3b0)(strPtr);

                // Cleanup EAString
                if (str.ptr != 0) {
                    str.destructor(&str);
                }
            }
            break;
        }
        case 5: {
            // Final transition
            ((void (__thiscall*)(void*))0x0093e3b0)(*(void**)((char*)this + 0x20));
            return;
        }
    }
}