// FUNC_NAME: SystemManager::pollWorkQueue
int __thiscall SystemManager::pollWorkQueue(int thisPtr, int param2)
{
    WorkItem workItem;
    int result;

    do {
        workItem.field_0 = 0;
        workItem.field_4 = 0;
        workItem.field_8 = 0;

        // Call a function pointer stored at offset +0x37c04 (likely a "tryPopWork" or "processNextTask")
        // The first argument is (EAX << 5) where EAX is the return value of the previous call? Actually, in_EAX is the EAX register at entry,
        // which may be a small integer (e.g., a timeout or count). Shifting left by 5 multiplies by 32.
        result = (*(int (__thiscall **)(int, WorkItem*))(*(int**)thisPtr + 0x37c04 / 4))(in_EAX << 5, &workItem);
        if (result != 0) {
            return result;
        }

        // Sleep or yield execution, param2 might be a timeout or flags
    } while (FUN_0051eba0(param2) != 0);

    return 0;
}