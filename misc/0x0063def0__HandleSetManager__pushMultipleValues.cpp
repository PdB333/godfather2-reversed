// FUNC_NAME: HandleSetManager::pushMultipleValues

struct ExternalItem {
    int field0; // +0x00
    int field2; // +0x04
    int field4; // +0x08
};

struct ListData {
    void* baseObject; // +0x00
    // +0x04-0x14: unknown
    int valueToSet; // +0x18 (listData[6])
    // +0x1c-0x30: unknown
    int count; // +0x34 (listData[0xd])
    // +0x38-0x2b4: unknown
    int handles[]; // +0x2b8 (listData[0xae])
};

class HandleSetManager {
public:
    void __thiscall pushMultipleValues(int count) {
        // this pointer is passed in EAX during call; here it's the implied this.
        ListData* listData = *(ListData**)((char*)this + 0x1c);
        int oldCount = listData->count;
        listData->count += count;

        if (count != 0) {
            // The loop writes the same value (listData->valueToSet) to the second field of
            // each external item identified by handles from the old count onward.
            ExternalItem* externalArray = *(ExternalItem**)((char*)listData->baseObject + 0x18);
            for (int i = 0; i < count; i++) {
                int index = oldCount + i;
                int handle = listData->handles[index];
                externalArray[handle].field2 = listData->valueToSet;
            }
        }
    }
};