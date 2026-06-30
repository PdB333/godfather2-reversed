// FUNC_NAME: GameResourceManager::releaseResources
struct ContainerItem {
    void* object;
    void (*destroy)(void*);
};

extern int s_currentActiveIndex;
extern int* s_objectArrayBegin;
extern int* s_objectArrayEnd;

void AddRef(void* ptr);

int IsSystemActive(void);

void GetFirstContainerItem(ContainerItem* out);
void GetSecondContainerItem(ContainerItem* out);

void GameResourceManager::releaseResources(void* param1, void* param2)
{
    AddRef(param1);
    int systemState = IsSystemActive();
    if (systemState == 0) {
        // System is not shutting down – only clean if index within bounds
        if ((s_currentActiveIndex >= 0) && (s_currentActiveIndex < (s_objectArrayEnd - s_objectArrayBegin) / 4)) {
            AddRef(param2);
            AddRef(param1);

            ContainerItem firstItem, secondItem;
            GetFirstContainerItem(&firstItem);
            GetSecondContainerItem(&secondItem);

            if (firstItem.object) {
                firstItem.destroy(firstItem.object);
            }
            if (secondItem.object) {
                secondItem.destroy(secondItem.object);
            }
        }
    } else {
        // System shutting down – always clean
        AddRef(param2);
        AddRef(param1);

        ContainerItem firstItem, secondItem;
        GetSecondContainerItem(&firstItem);  // swapped order
        GetFirstContainerItem(&secondItem);

        if (firstItem.object) {
            firstItem.destroy(firstItem.object);
        }
        if (secondItem.object) {
            secondItem.destroy(secondItem.object);
        }
    }
}