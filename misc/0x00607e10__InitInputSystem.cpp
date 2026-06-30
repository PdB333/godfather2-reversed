// FUNC_NAME: InitInputSystem

// Function at 0x00607e10: One-time initialization of input/controller subsystem.
// Uses a global singleton at DAT_01205750 (likely InputDeviceManager or ControllerManager).
// Sets up callback arrays, initializes controller slots (16), clears buffers and state.

void InitInputSystem(void)
{
    int oldValue1, oldValue2;
    int *pEventData;
    int *pArrayBase;
    uint index;
    int counter;
    int *pCallbackArray;
    int **ppCallbackPtr;
    int *pStackVar1;
    int *pStackVar2;
    int *pStackVar3;
    int stackArg4;

    // Guard to run initialization only once
    if (g_bInitialized == '\0')
    {
        g_bInitialized = '\x01';

        // Process up to 5 event-driven initialization steps
        pEventData = (int *)0x0;
        do
        {
            // Retrieve old callback pair values (two ints per entry)
            oldValue1 = g_apEventCallbackPairs[(int)pEventData * 2];
            oldValue2 = g_apEventCallbackPairs_1[(int)pEventData * 2];
            g_apEventCallbackPairs[(int)pEventData * 2] = 0;
            g_apEventCallbackPairs_1[(int)pEventData * 2] = 0;

            // If the pair was previously set, perform corresponding initialization
            if ((oldValue1 != 0) || (oldValue2 != 0))
            {
                if (pEventData == (int *)&DAT_00000004) // index 4: finalize (probably audio)
                {
                    // Call vtable[0x9c] (e.g., "finalizeAudioInit") with placeholder args
                    g_pInputManager->finalizeAudioInit(0, g_pInputManager, (int *)0x607e6a);
                }
                else if (pEventData == (int *)0x0) // index 0: first initialization step
                {
                    // Call vtable[0x94] (e.g., "registerEventCallback") via internal helper
                    stackArg4 = 0x607e7d;
                    // FUN_00609260 likely allocates or registers something
                    FUN_00609260();
                    g_pInputManager->registerEventCallback(0, pEventData, g_pInputManager, (int *)0x607e88);
                    g_bSomeFlag = 1; // Mark first step complete
                }
                else // indices 1-3: intermediate steps
                {
                    // Call vtable[0x94] with current index (e.g., "registerEventCallback")
                    g_pInputManager->registerEventCallback(0, g_pInputManager, (int *)0x607ea3, pEventData);
                }
            }
            pEventData = (int *)((int)pEventData + 1);
        } while ((int)pEventData < 5);

        // Initialize 20 (0x14) entries of an array (probably device descriptors)
        for (index = 0; index < 0x14; index++)
        {
            // FUN_00618d40 likely creates/initializes each element
            FUN_00618d40();
            g_anDeviceDescriptors[index] = 0;
        }

        // Configure 16 controller slots (index 0 to 0x0F)
        for (counter = 0; counter < 0x10; counter++)
        {
            // Call vtable[0x104] (e.g., "configureControllerSlot") with slot index
            g_pInputManager->configureControllerSlot(0, g_pInputManager, (int *)0x607ef2, (int *)counter);
        }

        // Enable input system (vtable[0x1a0])
        g_pInputManager->enableInputSystem(0, g_pInputManager, (int *)0x607f0b);

        // For each controller slot, set device state to disabled (vtable[0x190] = 400)
        for (counter = 0; counter < 0x10; counter++)
        {
            g_pInputManager->setDeviceState(g_pInputManager, counter, 0);
        }

        // Flush input buffers (vtable[0x1ac])
        g_pInputManager->flushInputBuffers(0, g_pInputManager);

        // Disable device 0 (vtable[0x170])
        g_pInputManager->disableDevice(g_pInputManager, 0);

        // Finalize (vtable[0x9c])
        g_pInputManager->finalizeInputInit(g_pInputManager, 0);

        // If certain condition (stackVar1 non-null), perform cleanup for previous state
        if ((char)pStackVar1 != '\0')
        {
            ppCallbackPtr = &pStackVar2;
            pEventData = (int *)0x0;
            // Call vtable[0x48] (e.g., "createDevice") and vtable[0x94] (e.g., "registerCallback") with new device
            g_pInputManager->createDevice(g_pInputManager, 0, 0, 0, ppCallbackPtr);
            g_pInputManager->registerEventCallback(g_pInputManager, 0, ppCallbackPtr);
            // Delete the device object
            (**(code **)(*pEventData + 8))(pEventData); // pEventData is 0, likely a bug; assume previous device pointer

            // Release audio objects if they exist
            if (g_pAudioObject1 != (int *)0x0)
            {
                FUN_006065a0(g_pAudioObject1, 0);
            }
            g_pAudioObject1 = (int *)0x0;

            if (g_pAudioObject2 != (int *)0x0)
            {
                FUN_006065a0(g_pAudioObject2, 0);
            }
            g_pAudioObject2 = (int *)0x0;
        }

        // Process shutdown callback list in reverse order
        if (g_uShutdownCallbackCount != 0)
        {
            for (counter = g_uShutdownCallbackCount - 1; counter >= 0; counter--)
            {
                int *pFuncPtr = &g_apShutdownCallbacks[counter * 3];
                if ((code *)*pFuncPtr != (code *)0x0)
                {
                    (*(code *)*pFuncPtr)(pStackVar1);
                }
            }
        }

        // Clean up dynamically allocated objects (from a list of size g_uObjectCount)
        for (counter = 0; counter < g_uObjectCount; counter++)
        {
            // Each entry is 6 ints wide? Actually array stride seems 3 ints? We'll use offset 6 based on code.
            int *pObjPtr = (int *)*(&g_apObjects[counter * 6]);
            if (pObjPtr != (int *)0x0)
            {
                (**(code **)(*pObjPtr + 8))(pObjPtr); // delete
                *(&g_apObjects[counter * 6]) = 0;
            }
        }

        // Release global singleton object if present
        if (g_pSomeObject != (int *)0x0)
        {
            (**(code **)(*g_pSomeObject + 8))(g_pSomeObject);
            g_pSomeObject = (int *)0x0;
        }

        // Zero out four state counters
        g_nStateCounter1 = 0;
        g_nStateCounter2 = 0;
        g_nStateCounter3 = 0;
        g_nStateCounter4 = 0;

        // Clear large buffers with -1 (likely input device calibration data)
        _memset(&g_abInputCalibrationData1, -1, 0x100);     // 256 bytes
        _memset(&g_abInputCalibrationData2, -1, 0x1000);    // 4096 bytes
        _memset(&g_abInputCalibrationData3, -1, 0x1000);    // 4096 bytes
    }
}