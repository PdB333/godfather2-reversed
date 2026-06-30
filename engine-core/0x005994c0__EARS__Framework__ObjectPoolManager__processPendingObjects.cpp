// FUNC_NAME: EARS::Framework::ObjectPoolManager::processPendingObjects
void __thiscall ObjectPoolManager::processPendingObjects(uint *this, uint bForce, uint param_3)
{
    byte idx;
    uint poolData;
    int *objPtr;
    byte *iterPtr;
    uint *poolIter;
    uint entry;

    // If bForce is set, call destroy on the primary manager object at +0x1C4
    if ((char)bForce != '\0') {
        (**(code **)(*(int *)this[0x71] + 0x10))();
    }

    // If the secondary manager (at +0x1C0) exists, call its methods
    if ((int *)this[0x70] != (int *)0x0) {
        (**(code **)(*(int *)this[0x70] + 0x18))(0);
        (**(code **)(*(int *)this[0x70] + 0x28))(0);
        (**(code **)(*(int *)this[0x70] + 0x38))(0);
        if ((char)bForce != '\0') {
            (**(code **)(*(int *)this[0x70] + 0x10))(0);
        }
    }

    // Process first pool (active objects list, indices at +0x59)
    if ((char)this[0x16] != '\0') {
        iterPtr = (byte *)((int)this + 0x59);
        do {
            idx = *iterPtr;
            poolData = this[0x6f];
            // If the object is not on free list (-2 sentinel), acquire lock
            if (*(int *)(*(int *)(poolData + 0x18) + (uint)idx * 4) != -2) {
                (**(code **)(*DAT_01205590 + 4))(); // lock
            }
            // Call vtable+0x44 (likely release/process) on the object
            (**(code **)(**(int **)(*(int *)(poolData + 0x14) + (uint)idx * 4) + 0x44))();
            entry = (uint)*iterPtr;
            poolData = this[0x6f];
            if (*(int *)(*(int *)(poolData + 0x18) + entry * 4) != -2) {
                (**(code **)(*DAT_01205590 + 4))(); // lock
            }
            // Add to free list if not already there (sentinel -2)
            if (*(int *)(*(int *)(poolData + 0x18) + entry * 4) == -2) {
                *(undefined4 *)(*(int *)(poolData + 0x18) + entry * 4) = *(undefined4 *)(poolData + 0x1c);
                *(uint *)(poolData + 0x1c) = entry;
            }
            iterPtr = iterPtr + 1;
        } while ((int)(iterPtr + (-0x59 - (int)this)) < (int)(uint)(byte)this[0x16]);
    }
    // Clear the active count
    *(undefined1 *)(this + 0x16) = 0;

    // Process second pool (pending objects list, indices at +0x7A)
    if (*(char *)((int)this + 0x79) != '\0') {
        iterPtr = (byte *)((int)this + 0x7a);
        do {
            idx = *iterPtr;
            poolData = this[0x6f];
            if (*(int *)(*(int *)(poolData + 0x24) + (uint)idx * 4) != -2) {
                (**(code **)(*DAT_01205590 + 4))(); // lock
            }
            (**(code **)(**(int **)(*(int *)(poolData + 0x20) + (uint)idx * 4) + 0x18))();
            entry = (uint)*iterPtr;
            poolData = this[0x6f];
            if (*(int *)(*(int *)(poolData + 0x24) + entry * 4) != -2) {
                (**(code **)(*DAT_01205590 + 4))(); // lock
            }
            if (*(int *)(*(int *)(poolData + 0x24) + entry * 4) == -2) {
                *(undefined4 *)(*(int *)(poolData + 0x24) + entry * 4) = *(undefined4 *)(poolData + 0x28);
                *(uint *)(poolData + 0x28) = entry;
            }
            iterPtr = iterPtr + 1;
        } while ((int)(iterPtr + (-0x7a - (int)this)) < (int)(uint)*(byte *)((int)this + 0x79));
    }
    *(undefined1 *)((int)this + 0x79) = 0;

    // Process third pool (special objects, indices at +0x9C)
    if (*(char *)((int)this + 0x9a) != '\0') {
        poolIter = this + 0x27; // points to byte array at +0x9C
        do {
            entry = *poolIter; // low byte used as index
            poolData = this[0x6f];
            if (*(int *)(*(int *)(poolData + 0x30) + (uint)(byte)entry * 4) != -2) {
                (**(code **)(*DAT_01205590 + 4))(); // lock
            }
            objPtr = *(int **)(*(int *)(poolData + 0x2c) + (uint)(byte)entry * 4);
            // Condition: if object's +0x2c byte is nonzero or bForce set, call vtable+0x18
            if ((*(char *)(this[1] + 0x2c) != '\0') || ((char)bForce != '\0')) {
                (**(code **)(*objPtr + 0x18))();
            }
            (**(code **)(*objPtr + 0x28))();
            entry = (uint)(byte)*poolIter;
            poolData = this[0x6f];
            if (*(int *)(*(int *)(poolData + 0x30) + entry * 4) != -2) {
                (**(code **)(*DAT_01205590 + 4))(); // lock
            }
            if (*(int *)(*(int *)(poolData + 0x30) + entry * 4) == -2) {
                *(undefined4 *)(*(int *)(poolData + 0x30) + entry * 4) = *(undefined4 *)(poolData + 0x34);
                *(uint *)(poolData + 0x34) = entry;
            }
            poolIter = (uint *)((int)poolIter + 1);
        } while ((-0x9c - (int)this) + (int)poolIter < (int)(uint)*(byte *)((int)this + 0x9a));
    }
    // Clear low bit of some flag
    *this = *this & 0xfffffffe;
    *(undefined1 *)((int)this + 0x9a) = 0;

    // Call the chained processing routine
    FUN_005974f0(bForce, param_3);
}