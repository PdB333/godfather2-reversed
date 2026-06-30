// FUNC_NAME: EntityManager::~EntityManager
void __fastcall EntityManager::~EntityManager(int this)
{
    int *pResource;         // +0x3c
    int *pListNode;         // from +0x6d4 (list head)
    int *pFirstNode;        // +0x10 of pListNode (first item in intrusive list)
    int nextNode;           // +4 of first node (next pointer)
    int containerFromNode;  // container = node - 0x48
    int callbackArgs[3];    // struct for callback (arg0, func ptr, arg2)
    code *callbackFunc;     // callback function pointer (uninitialized in disasm, likely set by FUN_006fa8c0)

    // Clear a flag at +0x38
    *(int *)(this + 0x38) = 0;

    pResource = (int *)(this + 0x3c);
    if (*pResource != 0) {
        // Free or release the resource object
        FUN_004daf90(pResource);
        *pResource = 0;
    }

    // If a list container is active (offset 0x6dc non-zero)
    if (*(int *)(this + 0x6dc) != 0) {
        pListNode = *(int **)(this + 0x6d4);
        // Destroy the list container's metadata or internal object
        FUN_004d3b50(pListNode);

        // Get the first node from the list (intrusive list at +0x10 of container)
        pFirstNode = (int *)*(int *)(pListNode + 0x10);
        nextNode = 0;
        if (pFirstNode != 0) {
            nextNode = *(int *)(pFirstNode + 4);
            // Redirect the first node's next pointer to the stack variable (unlinking)
            *(int **)(pFirstNode + 4) = &pFirstNode;
        }

        // Static cleanup (likely manager-wide)
        FUN_006f9d00();

        // Compute the containing object from the node offset
        if (pFirstNode == 0) {
            containerFromNode = 0;
        } else {
            containerFromNode = (int)pFirstNode - 0x48;
        }

        // Call a function that processes the container (e.g., finalize destruction)
        FUN_006fa8c0(callbackArgs, containerFromNode);

        if (pFirstNode != 0) {
            // Free the node itself (the list head was already detached)
            FUN_004daf90(&pFirstNode);
        }

        // Invoke optional callback (callbackFunc likely set inside FUN_006fa8c0 or elsewhere)
        if (callbackArgs[0] != 0) {
            callbackFunc(callbackArgs[0]);
        }
    }
}