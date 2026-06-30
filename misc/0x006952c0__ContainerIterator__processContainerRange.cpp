// FUNC_NAME: ContainerIterator::processContainerRange
void ContainerIterator::processContainerRange(void* this, void* array1, void* list1Head, void* list2Head, const char* debugStr1, const char* debugStr2, void (*callback1)(int), void (*callback2)(int))
{
    bool bFoundInList2 = false;
    int currentItem = 0;
    int lastItem = 0;

    if (!GetItemRange(this, &currentItem, &lastItem) || currentItem == lastItem) {
        return;
    }

    void* savedList2Head = list1Head;

    do {
        Lock(currentItem + 0x10);

        bool allValid = false;
        int index = 0;
        do {
            int valid = IsValidPointer(*(void**)((int)array1 + index * 8));
            if (valid == 0) {
                allValid = true;
                break;
            }
            index++;
        } while (index < 12);

        index = 0;
        void** ptrArray = (void**)((int)array1 + 0x70);
        do {
            if (allValid) { goto SKIP_VALIDATION; }
            int valid = IsValidPointer(*ptrArray);
            if (valid == 0) { goto SKIP_VALIDATION; }
            index++;
            ptrArray += 2;
        } while (index < 4);

        if (debugStr1 == nullptr) { debugStr1 = "default_string_1"; }
        if (gDebugCounter < 4) {
            gDebugFlags[gDebugCounter * 5] = 1;
            AddDebugMessage(debugStr1);
        }
        gDebugCounter++;

SKIP_VALIDATION:
        Lock(currentItem + 0x20);

        if (debugStr2 == nullptr) { debugStr2 = "default_string_2"; }
        LeaveCriticalSection(debugStr2);

        void** list1Iter = *(void***)((int)list1Head + 4);
        char flag = *(char*)((int)list1Iter[1] + 0x25);
        void** prevNode = list1Iter;
        void** node = (void**)list1Iter[1];
        while (flag == 0) {
            int cmp = ComparePointers(local_10);
            if (cmp < 0) {
                void** nextNode = (void**)node[2];
                node = prevNode;
            } else {
                nextNode = (void**)*node;
            }
            prevNode = node;
            node = nextNode;
            flag = *(char*)((int)nextNode + 0x25);
        }
        void** lastValidNodeInList1 = prevNode;
        if (prevNode == *(void***)((int)list1Head + 4) || ComparePointers(prevNode + 3) < 0) {
            void* struct1Head = *(void**)((int)list1Head + 4);
            int struct1Base = list1Head;
            piVar6 = &struct1Base;
        } else {
            piVar6 = &savedList2Head;
        }
        void** headFromStruct = piVar6[1];
        if (piVar6[0] == 0 || piVar6[0] != list1Head) {
            Assert();
        }
        if (headFromStruct == list1Iter) {
            if (debugStr2 == nullptr) { debugStr2 = "default_string_2"; }
            LeaveCriticalSection(debugStr2);

            void** list2Iter = *(void***)((int)list2Head + 4);
            bFoundInList2 = true;
            flag = *(char*)((int)list2Iter[1] + 0x29);
            prevNode = list2Iter;
            node = (void**)list2Iter[1];
            while (flag == 0) {
                int cmp = ComparePointers(local_20);
                if (cmp < 0) {
                    void** nextNode = (void**)node[2];
                    node = prevNode;
                } else {
                    nextNode = (void**)*node;
                }
                prevNode = node;
                node = nextNode;
                flag = *(char*)((int)nextNode + 0x29);
            }
            void** lastValidNodeInList2 = prevNode;
            int struct2Base = list2Head;
            if (prevNode == *(void***)((int)list2Head + 4) || ComparePointers(prevNode + 3) < 0) {
                void* struct2Head = *(void**)((int)list2Head + 4);
                piVar6 = &struct2Base;
            } else {
                piVar6 = &savedList2Head;
            }
            headFromStruct = piVar6[1];
            if (piVar6[0] == 0 || piVar6[0] != list2Head) {
                Assert();
            }
            if (headFromStruct == list2Iter) {
                allValid = true;
            }
        }

        if (bFoundInList2) {
            bFoundInList2 = false;
            if (local_20[0] != 0) {
                callback1(local_20[0]);
            }
        }
        if (local_10[0] != 0) {
            callback2(local_10[0]);
        }

        if (allValid) {
            if (debugStr1 == nullptr) { debugStr1 = "default_string_1"; }
            if (gDebugCounter < 4) {
                gDebugFlags[gDebugCounter * 5] = 1;
                AddDebugMessage(debugStr1);
            }
            gDebugCounter++;
        }

        if (debugStr2 != nullptr) {
            callback2(debugStr2);
        }
        if (debugStr1 != nullptr) {
            callback1(debugStr1);
        }

        currentItem = GetNextItem(currentItem);
    } while (currentItem != lastItem);
}