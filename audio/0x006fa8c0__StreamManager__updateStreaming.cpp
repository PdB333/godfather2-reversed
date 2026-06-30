// FUNC_NAME: StreamManager::updateStreaming
void __thiscall StreamManager::updateStreaming(void *loadContext, void *loadableObject) {
    int iVar3;
    uint progress;
    char flag;
    CallbackEntry callbackEntry;
    int local_8;
    int local_4;

    // Check if the loadable object is already fully loaded
    iVar3 = isLoadableComplete(loadContext);
    if (iVar3 == 0) {
        // Not completely loaded yet
        if (this->currentLoadable == 0) {
            // No current loadable in progress; try to get the next one
            iVar3 = getNextLoadableAsync(loadContext);
            if (iVar3 == 0) {
                iVar3 = getNextLoadableSync(loadContext);
                if (iVar3 != 0) {
                    addRef(loadableObject);
                    this->currentLoadable = *(void**)(iVar3 + 0xc);
                }
            } else {
                addRef(loadableObject);
                this->currentLoadable = *(void**)(iVar3 + 0xc);
            }
            // Register this loadable for the load process
            registerLoadRequest(loadContext, loadableObject, 1);
            progress = this->loadProgress; // +0x34
            flag = 1;
            while (true) {
                if (progress < 0x300001) {
                    return; // Wait condition satisfied
                }
                if (flag == 0) break;
                flag = pollLoadProgress();
                progress = this->loadProgress; // +0x34
            }
            return;
        }
        // There is a current loadable
        int iVar3_2;
        if (this->loadListHead == 0) {
            iVar3_2 = 0;
        } else {
            iVar3_2 = this->loadListHead - 0x48; // offset to first node
        }
        if (loadableObject == iVar3_2) {
            return; // Already processing this one
        }
        // Begin new load
        startLoading(loadableObject);
        clearCallbackEntry(&callbackEntry);
        addRef(loadableObject);
    } else {
        // Loadable is complete
        *(uint8*)(iVar3 + 0x35) = 1;
        startLoading(loadableObject);
        clearCallbackEntry(&callbackEntry);
        if (loadableObject != 0 && loadableObject + 0x48 != 0) {
            // Insert into linked list
            local_4 = *(int*)(loadableObject + 0x4c);
            *(int**)(loadableObject + 0x4c) = &local_8;
            local_8 = loadableObject + 0x48;
        }
    }
    processCallbacks(loadContext);
    runCallbacks(&callbackEntry);
    if (local_8 != 0) {
        unlinkNode(&local_8);
    }
    if (callbackEntry.callbackPtr != 0) {
        callbackEntry.callbackPtr(callbackEntry.callbackData);
    }
    return;
}