// FUNC_NAME: MultiplayerScenarioManager::updateScenarioSlots
void __fastcall MultiplayerScenarioManager::updateScenarioSlots(int thisPtr)
{
    // Iterate over 3 scenario slots (0, 1, 2), each slot is 0x5C bytes
    for (int slotIdx = 0; slotIdx < 3; slotIdx++)
    {
        int slotBase = slotIdx * 0x5C + thisPtr; // +0x00..0x5B per slot

        // Get entity handle from slot +0x88
        int* entityPtr = (int*)resolveHandle(slotBase + 0x88, 0);
        if (entityPtr != nullptr)
        {
            int* childComponent = nullptr;
            // vtable+0x10: find child by hash (0x254cce9 -> likely "VehicleComponent")
            bool found = (**(code**)(*entityPtr + 0x10))(0x254cce9, &childComponent);
            entityPtr = childComponent; // use child component as the primary pointer

            if (found && childComponent != nullptr)
            {
                // vtable+0x154: check if component is active/valid
                bool componentValid = (**(code**)(*childComponent + 0x154))();
                if (componentValid)
                {
                    int vehiclePtr = (**(code**)(*childComponent + 0x160))(); // vtable+0x160: get vehicle base
                    (**(code**)(*childComponent + 0x150))(); // vtable+0x150: release/update component

                    if (vehiclePtr != 0)
                    {
                        setVehicleFlag(0);
                        // Clear bit 19 (0x80000) at vehicle +0x5C (likely a "destroyed" flag)
                        *(uint*)(vehiclePtr + 0x5C) &= 0xFFF7FFFF;

                        int stateArg;
                        if (thisPtr == 0)
                            stateArg = 0;
                        else
                            stateArg = thisPtr + 0x50; // +0x50: some manager state offset
                        setScenarioState(stateArg);

                        if (slotIdx == 0) // First slot (e.g. primary scenario)
                        {
                            // Check manager state (thisPtr+0xcc) is 0 or 0x48, and vehicle health (vehiclePtr+0x78) < 1
                            if ((*(int*)(thisPtr + 0xCC) == 0 || *(int*)(thisPtr + 0xCC) == 0x48) &&
                                *(int*)(vehiclePtr + 0x78) < 1)
                            {
                                destroyVehicle(vehiclePtr);
                            }
                        }
                        else // slotIdx 1 or 2
                        {
                            if (*(char*)(thisPtr + 0x1A4) != '\0') // some manager flag
                            {
                                // Check slot flags at slotBase+0xC0: bit0 and bit1 must be clear
                                if (((*(byte*)(slotBase + 0xC0) & 1) == 0) &&
                                    ((*(uint*)(slotBase + 0xC0) >> 1 & 1) == 0))
                                {
                                    playAudio(0);
                                }
                                stopAudio(0);
                            }
                        }
                    }
                }
            }
        }

        // Clear slot flags at +0xC0
        *(undefined4*)(slotBase + 0xC0) = 0;

        // Free slot pointer at +0xC4
        if (*(int*)(slotBase + 0xC4) != 0)
        {
            deleteObject((undefined4*)(slotBase + 0xC4));
            *(undefined4*)(slotBase + 0xC4) = 0;
        }

        // Free slot pointer at +0xCC
        if (*(int*)(slotBase + 0xCC) != 0)
        {
            deleteObject((undefined4*)(slotBase + 0xCC));
            *(undefined4*)(slotBase + 0xCC) = 0;
        }

        // Free slot pointer at +0xD4; uses manager-level removal
        if (*(int*)(slotBase + 0xD4) != 0)
        {
            removeFromManager(thisPtr); // FUN_006b3f50(thisPtr)
            *(undefined4*)(slotBase + 0xD4) = 0;
        }
    }
}