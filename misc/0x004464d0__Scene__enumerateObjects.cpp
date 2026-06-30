// FUNC_NAME: Scene::enumerateObjects
// Address: 0x004464d0
// This function performs a depth-first traversal of all objects in the scene.
// It uses a linked tree structure: each node has a child list (offset +0x14) 
// and sibling link (offset +0x18). The scene also maintains a fallback array 
// of root objects at offset +0x70 (pointer) and +0x74 (count).
// A callback is invoked for each visited object.
// FUN_0043ab10 is called each iteration to process pending changes.
// FUN_00448be0 initializes the first cursor.

void __thiscall Scene::enumerateObjects(void (*callback)(int obj))
{
    int iVar1;
    uint index = 0; // index into root array
    int cursor;
    
    if (callback != (void (*)(int))0x0) {
        cursor = FUN_00448be0(); // get first root node
        if (cursor != 0) {
            do {
                while( true ) {
                    FUN_0043ab10(); // process deferred operations
                    // iterate through child list at offset +0x14
                    for (iVar1 = *(int *)(cursor + 0x14); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x10)) {
                        callback(iVar1); // invoke on each child
                    }
                    // advance to next sibling
                    cursor = *(int *)(cursor + 0x18);
                    // if no root array, we are done
                    if (*(int *)(this + 0x70) == 0) break;
                    // if no more siblings, try next root from array
                    if (cursor == 0) {
                        do {
                            if (*(uint *)(this + 0x74) <= index) goto LAB_00446549;
                            cursor = *(int *)(*(int *)(this + 0x70) + index * 4);
                            index = index + 1;
                        } while (cursor == 0);
                    }
                }
LAB_00446549:
                // continue outer loop if cursor is not null (another root)
            } while (cursor != 0);
        }
    }
    return;
}