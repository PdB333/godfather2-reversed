// FUNC_NAME: ControllerManager::processInputEvents
// Function at 0x008af190
void __thiscall ControllerManager::processInputEvents(void* thisPtr, void* unkParam2, bool flushFlag, void* inputArray, uint count)
{
    // +0x60 = pointer to active input buffer or state
    if (*(int*)((int)thisPtr + 0x60) != 0)
    {
        // Enter a lock or critical section (FUN_004bb690)
        inputLockEnter();

        uint index = 0;
        if (count != 0)
        {
            int elementOffset = 0;
            do
            {
                // Each input packet is 0x34 bytes
                uint* packet = (uint*)((int)inputArray + elementOffset);

                // Local context for event dispatching
                struct {
                    void** pContext;   // local_1c
                    int field4;        // local_18
                    int field8;        // local_14
                    void (*callback)();// local_10
                    int field10;       // local_4
                    uint data0;        // local_c
                    uint data2;        // local_8
                } context = {0};

                context.data0 = packet[0];   // first DWORD of packet
                context.data2 = packet[2];   // third DWORD (offset 0x08)

                // Allocate a temporary buffer (FUN_004bb600)
                void* allocPtr = tempAlloc();
                // The allocation pointer is stored temporarily then overwritten by &context

                // Process input data (FUN_004d3e20)
                processInputData();

                context.field10 = packet[12]; // 13th DWORD (offset 0x30)

                // Dispatch the event (FUN_008add00) with pointer to context
                void* dispatchResult = dispatchInputEvent(&context);

                // If a callback was registered, call it
                if (context.callback != 0)
                {
                    context.callback();
                }

                index++;
                elementOffset += 0x34;
            } while (index < count);
        }

        if (flushFlag != '\0')
        {
            // Set a pending flush flag (bit 0x100 at +0x7c)
            *(uint*)((int)thisPtr + 0x7c) |= 0x100;

            // Leave the lock (FUN_004bb740)
            inputLockExit();

            // Flush queued events (FUN_008a9f60)
            flushEventQueue();

            // Finalize state (FUN_004bc280)
            finalizeUpdate();

            return;
        }

        // Process pending queued events (FUN_008a9d20)
        processQueuedEvents();
    }

    // Always called: finalize (FUN_004bc280)
    finalizeUpdate();
}