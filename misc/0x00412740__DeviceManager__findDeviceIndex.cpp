// FUNC_NAME: DeviceManager::findDeviceIndex
int __thiscall DeviceManager::findDeviceIndex(const char* filterName) const {
    int result = 0;
    int slotCount = *(int*)(g_globalManager + 0x124);               // +0x124: number of player/controller slots
    DeviceEntry** entryListBegin = (DeviceEntry**)(this + 0x20c);   // +0x20c: start of device entry pointer array
    int entryCount = *(int*)(this + 0x210);                         // +0x210: number of entries
    DeviceEntry** entryListEnd = entryListBegin + entryCount;

    for (DeviceEntry** it = entryListBegin; it != entryListEnd; ++it) {
        DeviceEntry* entry = *it;
        bool filterEmpty = (filterName == nullptr) || (*filterName == '\0');
        bool filterActive = !filterEmpty;
        bool compareResult; // uVar8, 0 means "match" or "no filter and entry unassigned"
        bool proceedToSlotCheck = false;

        if (entry->flags == 0) {
            // Entry not assigned a device name
            compareResult = filterActive; // true if filter provided, false if empty
            if (!compareResult && slotCount != 0) {
                proceedToSlotCheck = true;
            }
        } else {
            // Entry has a device name – only consider if filter is active
            if (filterActive) {
                // Compare entry name with filter string (2‑byte optimized strcmp)
                const char* entryName = entry->name;
                const char* filter = filterName;
                while (true) {
                    char c1 = *entryName;
                    char c2 = *filter;
                    if (c1 != c2) {
                        compareResult = (c1 < c2) ? 1 : -1; // actually (1 - (uint)bVar11) - (uint)(bVar11 != 0)
                        // Equivalent to strcmp result sign
                        break;
                    }
                    if (c1 == '\0') {
                        compareResult = 0;
                        break;
                    }
                    c1 = entryName[1];
                    c2 = filter[1];
                    if (c1 != c2) {
                        compareResult = (c1 < c2) ? 1 : -1;
                        break;
                    }
                    entryName += 2;
                    filter += 2;
                    if (c1 == '\0') {
                        compareResult = 0;
                        break;
                    }
                }
                if (compareResult == 0) {
                    proceedToSlotCheck = true;
                }
            }
        }

        if (proceedToSlotCheck) {
            // Search each player/controller slot for a match with this entry's device string
            PlayerSlot** slotArray = (PlayerSlot**)(g_globalManager + 0x24);  // +0x24: array of slot pointers
            for (int i = 0; i < slotCount; ++i) {
                PlayerSlot* slot = slotArray[i];
                if (slot != nullptr) {
                    // slot->nameField is at +0x24, entry->deviceString is at entry->deviceNameOffset + 8
                    char* slotName = *(char**)((char*)slot + 0x24);
                    char* deviceString = *(char**)(entry->deviceNameOffset + 8);
                    if (FUN_00411fd0(slotName, deviceString) != '\0') {
                        result = entry->deviceNameOffset + 8;
                        if (result != 0) {
                            return result;
                        }
                        break;
                    }
                }
            }
        }
    }
    return result;
}