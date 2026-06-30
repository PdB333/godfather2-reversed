// Function address: 0x0040fd70
// Role: Main controller update loop - processes all connected controllers,
// handles connection/disconnection events, auto-selects primary movement/camera controllers,
// and updates controller state for the frame.

// This is part of a controller manager class (likely CControllerManager).
// Structure layout (offsets from 'this'):
// +0x2c: Base of controller slot array (16 slots, each 0x44 bytes)
// +0x3e: Byte in slot: flag indicating controller is connected? (slot offset 0x12)
// +0x38: Float array for accelerometer/gyro data? (incremented by 0x44? Actually used as float* starting at +0x38)
// +0x4dc: Function pointer callback (controller connected/disconnected)
// +0x4e0: Pointer to another manager/device
// +0x4ec: Pointer to something
// +0x52c: Flag: auto-select controller
// +0x52d: Byte array[16]: whether each slot is active
// +0x53d: Current slot index
// +0x566: Best movement controller slot (byte)
// +0x567: Best camera controller slot (byte)
// +0x568: Current primary slot (byte)
// +0x56c: Timestamp of last activity
// +0x574: Flag: controller is engaged
// +0x584: Function pointer (something)
// +0x588: Function pointer (something)

// Constants (global data)
extern float DAT_00e44714;        // threshold for something
extern float DAT_00e3ac58;        // another threshold
extern float DAT_00e35654;        // maybe a time threshold
extern uint DAT_00e44680;          // bitmask for axis flags
extern undefined4 DAT_012069fc;   // some constant for event
extern char DAT_0120524a;         // debug flag?
extern char DAT_0110acca;         // another flag

// Forward declarations of engine functions with hypothetical names
void __thiscall UpdateControllerState(); // 0x00b92e50
void __thiscall UpdateInputSystem();     // 0x00b95be0
int  __thiscall GetNumActiveControllers(); // 0x00b92e60
void* __thiscall GetControllerInfo(int slot); // 0x00b94a40
void* __thiscall GetControllerType(int slot); // 0x00b94a20
void* __thiscall GetControllerDevice(int slot); // 0x00b94a80
void __thiscall ActivateControllerSlot(int slot); // 0x004105f0
void __thiscall SendControllerConnectedEvent(void* data, int param); // 0x00408a00
void __thiscall ResetControllerState(void* data, int size); // 0x00b932c0
char __thiscall CheckControllerOverride(int slot, int param1, int param2); // 0x00410280
void __thiscall DeactivateControllerSlot(int slot); // 0x00410840
void __thiscall UpdateControllerVelocity(); // 0x00411460
void __thiscall ApplyControllerDeadZones(); // 0x00410c90
void __thiscall ProcessControllerActions(); // 0x004109f0
void __thiscall UpdateControllerVibration(); // 0x0040fb40

void __thiscall CControllerManager::UpdateControllers()
{
    // Local array to store previous slot state (button history)?
    // 16 slots, each 4 dwords (16 dwords total)
    uint prevSlotState[64]; // actually 65 declared, but only 64 used
    uint* pDest = prevSlotState;
    // Source: each slot's +0x3e offset? Actually puVar3 starts at this+0x3e (first slot offset 0x12 within slot)
    uint16* pSrc = (uint16*)((char*)this + 0x3e);
    int slotIdx;
    for (slotIdx = 0; slotIdx < 16; slotIdx++)
    {
        // Copy a dword from pSrc[-1] to pSrc (shift previous state to current?)
        *pSrc = *(pSrc - 1);
        // Copy 4 dwords from source+2 to destination
        *pDest = *(uint*)(pSrc + 2);
        pDest[1] = *(uint*)(pSrc + 4);
        pDest[2] = *(uint*)(pSrc + 6);
        pDest[3] = *(uint*)(pSrc + 8);
        // Advance source by 0x22? (34 bytes) - but slot size is 0x44, so this is suspicious
        // Possibly the source is a different array of 34-byte structures
        pSrc = (uint16*)((char*)pSrc + 0x22);
        pDest += 4;
    }

    // Call engine to update raw input state
    UpdateControllerState(); // 0x00b92e50
    UpdateInputSystem();     // 0x00b95be0

    uint slot = 0;
    int numControllers = GetNumActiveControllers(); // 0x00b92e60
    if (numControllers != 0)
    {
        // Pointers to first slot's connection flag and data array
        char* slotActiveFlag = (char*)this + 0x6a; // offset 0x3e within slot? Actually slot base +0x2c, so +0x6a = +0x3e within slot
        int* slotDataPtr = (int*)((char*)this + 0x4ec); // pointer to something per slot

        do
        {
            void* controllerInfo = GetControllerInfo(slot); // 0x00b94a40
            bool isConnected = (*(int*)controllerInfo + 4) == 1; // check connection state

            if (isConnected)
            {
                void* controllerType = GetControllerType(slot); // 0x00b94a20
                bool isEngaged = isConnected; // local_146, initially same as connected
                if (controllerType != nullptr)
                {
                    uint currentSlot = slot;
                    UpdateControllerState(); // maybe? Actually called with slot? 0x00b92e50(slot) from decompiled? Called without args originally
                    void* device = GetControllerDevice(currentSlot); // 0x00b94a80
                    if (device != nullptr)
                    {
                        // Check vtable function at offset 100 for device status
                        int status = (**(int (__thiscall**)(void*))(*(int*)device + 100))(device);
                        if (status == -0x7ff8ffe2 || status == -0x7ff8fff4)
                        {
                            isEngaged = false; // device is in a pending/error state
                        }
                    }
                    // Check if type field indicates no connection (maybe keyboard instead of gamepad)
                    if (*(int*)((char*)controllerType + 4) == 0)
                    {
                        isConnected = isConnected && isEngaged;
                    }
                }

                if (!isConnected) // was local_145 == false
                    goto SkipDisconnect;

                controllerType = GetControllerType(slot); // redundant? but ok
                float controllerTypeValue;
                if (controllerType == nullptr)
                {
                    controllerTypeValue = 5.60519e-45f; // tiny number representing no type
                }
                else
                {
                    controllerTypeValue = *(float*)((char*)controllerType + 4);
                }

                byte slotByte = (byte)slot;
                // If the slot is not already active
                if (*slotActiveFlag == '\0')
                {
                    if (slotByte < 0x10)
                    {
                        // Mark slot as active (set flag at +0x3e within slot)
                        *(char*)((char*)this + 0x6a + slot * 0x44) = 1;
                        ActivateControllerSlot(slot); // 0x004105f0
                        // Send connected event
                        undefined4 eventData = DAT_012069fc;
                        // Build a structure on stack
                        struct {
                            undefined4 field0;
                            uint slot;
                            undefined4 pad;
                        } event;
                        event.field0 = DAT_012069fc;
                        event.slot = slot & 0xff;
                        event.pad = 0;
                        SendControllerConnectedEvent(&event, 0); // 0x00408a00
                    }
                    // Call connection callback if present
                    if (*(void (__thiscall**)(uint,int,int,int))((char*)this + 0x4dc) != nullptr)
                    {
                        (*(void (__thiscall**)(uint,int,int,int))((char*)this + 0x4dc))(slot, 1, slot, 0);
                    }
                }

                // If the slot has data (slotDataPtr != 0)
                if (*slotDataPtr != 0)
                {
                    // Check if we need to auto-select this controller for movement
                    if ((*(char*)((char*)this + 0x574) == '\0') && (isEngaged != false) &&
                        (controllerTypeValue == 4.2039e-45f)) // maybe value for certain type?
                    {
                        // Reset state with 0x10 bytes?
                        char resetBuffer[16] = {0}; // actually declared as undefined1+undefined8 etc.
                        ResetControllerState(resetBuffer, 0x10); // 0x00b932c0
                        *(bool*)((char*)this + 0x574) = isEngaged; // set engagement flag
                    }

                    char* slotPtr = slotActiveFlag - 0x3e; // back to slot base? Actually offset within slot changes
                    // Call vtable function at offset 4 of device manager
                    (**(void (__thiscall**)(void*, void*, char*))(*(int*)*slotDataPtr + 4))(controllerInfo, controllerType, slotPtr);

                    // Determine if we should apply deadzone/override
                    bool applyOverride = true;
                    if (DAT_0120524a == '\0') // if debug flag off
                    {
                        if (controllerTypeValue == 2.8026e-45f || controllerTypeValue == 4.2039e-45f)
                            applyOverride = false;
                        else
                            applyOverride = true;
                    }
                    else
                    {
                        applyOverride = false;
                    }
                    // applyOverride = (DAT_0120524a == 0) && (controllerTypeValue not those values)
                    bool apply = (DAT_0110acca == '\0') & applyOverride;
                    if (apply)
                    {
                        (**(void (__thiscall**)(char*))(*(int*)*slotDataPtr + 0x20))(slotPtr); // call some override function
                    }
                    else if (controllerTypeValue == 0.0f)
                    {
                        char check = CheckControllerOverride(slot, 0xffff, 2); // 0x00410280
                        if (check != '\0' ||
                            // Check if any axis values exceed threshold
                            (*(float*)((char*)this + 0x2c + slot * 0x44 + 0x00) & DAT_00e44680) > DAT_00e35654 ||
                            (*(float*)((char*)this + 0x2c + slot * 0x44 + 0x04) & DAT_00e44680) > DAT_00e35654 ||
                            (*(float*)((char*)this + 0x2c + slot * 0x44 + 0x08) & DAT_00e44680) > DAT_00e35654 ||
                            (*(float*)((char*)this + 0x2c + slot * 0x44 + 0x0c) & DAT_00e44680) > DAT_00e35654)
                        {
                            // Update primary slot and timestamp
                            uint timestamp = *(uint*)((char*)controllerInfo + 0xc);
                            if (*(byte*)((char*)this + 0x568) == 0x12) // 0x12 means no primary?
                            {
                                *(byte*)((char*)this + 0x568) = slotByte;
                                *(uint*)((char*)this + 0x56c) = timestamp;
                            }
                            else if (slotByte == *(byte*)((char*)this + 0x568))
                            {
                                *(uint*)((char*)this + 0x56c) = timestamp;
                            }
                            else if (*(uint*)((char*)this + 0x56c) + 0x3cU < timestamp)
                            {
                                *(byte*)((char*)this + 0x568) = slotByte;
                                *(uint*)((char*)this + 0x56c) = timestamp;
                            }
                        }
                    }
                    else if ((isEngaged == false) &&
                             (controllerTypeValue == 2.8026e-45f || controllerTypeValue == 4.2039e-45f))
                    {
                        *(char*)((char*)this + 0x574) = 0;
                        (**(void (__thiscall**)(char*))(*(int*)*slotDataPtr + 0x20))(slotPtr);
                    }
                }
            }
            else
            {
SkipDisconnect:
                // If slot was active, deactivate it
                if (*slotActiveFlag != '\0')
                {
                    *slotActiveFlag = '\0';
                    DeactivateControllerSlot(slot, slot); // 0x00410840
                }
            }

            // Move to next slot
            slotDataPtr++;
            slotActiveFlag += 0x44;
            slot++;
        } while (slot < (uint)numControllers);
    }

    // Auto-select best movement and camera controllers
    if (*(char*)((char*)this + 0x52c) != '\0') // auto-select flag
    {
        // Clear the current primary slot data (assume slot at index given by +0x53d)
        void* dst = (char*)this + 0x2c + (uint)*(byte*)((char*)this + 0x53d) * 0x44;
        memset(dst, 0, 0x44);
        *(char*)((char*)dst + 0x3e) = 1; // mark as connected

        float* pFloat = (float*)((char*)this + 0x38); // start of accelerometer/gyro data per slot?
        float bestMoveRange = 0.0f;
        float bestCamRange = 0.0f;
        int bestMoveSlot = 0x12; // invalid index
        int bestCamSlot = 0x12;
        uint slotIdx = 0;

        do
        {
            // Check if this slot is active AND its connection flag is set
            if ((*(char*)((char*)this + 0x52d + slotIdx) != '\0') &&
                (*(char*)((float*)pFloat + 0x32) != '\0')) // offset within pFloat? Actually 0x32 bytes from pFloat base? Possibly wrong.
            {
                void* controllerType = GetControllerType(slotIdx);
                float threshold = DAT_00e44714; // default threshold
                if (controllerType != nullptr)
                {
                    switch (*(int*)((char*)controllerType + 4))
                    {
                        case 0: // gamepad?
                        case 1:
                            threshold = DAT_00e3ac58;
                            break;
                        case 2:
                        case 3:
                            threshold = 0.0f;
                            break;
                    }
                }

                // Compute squared lengths of two vectors (movement and camera?)
                float moveLenSq = pFloat[-3] * pFloat[-3] + pFloat[-2] * pFloat[-2];
                if ((threshold * threshold < moveLenSq) && (bestMoveRange < moveLenSq))
                {
                    bestMoveSlot = slotIdx & 0xff;
                    bestMoveRange = moveLenSq;
                }

                float camLenSq = pFloat[-1] * pFloat[-1] + pFloat[0] * pFloat[0];
                if ((threshold * threshold < camLenSq) && (bestCamRange < camLenSq))
                {
                    bestCamSlot = slotIdx & 0xff;
                    bestCamRange = camLenSq;
                }

                UpdateControllerVelocity(); // 0x00411460
            }

            slotIdx++;
            pFloat += 0x11; // stride of 17 floats? (0x44 bytes)
        } while (slotIdx != 0x10);

        if (bestMoveSlot != 0x12)
        {
            *(char*)((char*)this + 0x566) = (char)bestMoveSlot;
        }
        if (bestCamSlot != 0x12)
        {
            *(char*)((char*)this + 0x567) = (char)bestCamSlot;
        }

        ApplyControllerDeadZones(); // 0x00410c90
    }

    // Final processing
    ProcessControllerActions();    // 0x004109f0
    UpdateControllerVibration();   // 0x0040fb40

    // Call some optional callbacks
    if (*(void (__thiscall**)(void*,int))((char*)this + 0x584) != nullptr)
    {
        (*(void (__thiscall**)(void*,int))((char*)this + 0x584))((char*)this + 0x2c, 0);
    }
    if (*(void (__thiscall**)(void*,int))((char*)this + 0x588) != nullptr)
    {
        (*(void (__thiscall**)(void*,int))((char*)this + 0x588))((char*)this + 0x2c, 0);
    }

    // If there's a device manager, call its update
    if (*(int**)((char*)this + 0x4e0) != nullptr)
    {
        (**(void (__thiscall**)(void*,int))(*(int*)this + 4))((char*)this + 0x2c, 0x10); // vtable offset 4
    }
}