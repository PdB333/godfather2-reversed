// FUNC_NAME: DataRef::Constructor (0x004cef60)
// Reconstruction: Object that holds a reference to a data source with an ID.
// this+0x10 stores the data source pointer, this+0x14 stores the computed ID.

int __thiscall DataRef::DataRef(int this, int *pDataSource, int nId)
{
    undefined4 computedId;
    int *pTemp = pDataSource;

    // Virtual call to vtable[2] (likely some initialization on the data source)
    (*(void (__thiscall **)(int*))(*pDataSource + 8))(pDataSource);

    // If an ID is provided, compute it; otherwise zero
    if (nId == 0) {
        computedId = 0;
    } else {
        computedId = FUN_004265d0(nId, pTemp);   // e.g., getIDFromDataSource(nId, pDataSource)
    }

    // Register the computed ID with the data source
    FUN_004cf330(pTemp, computedId);                // e.g., pDataSource->setID(computedId)

    // Store the data source at this+0x10
    *(int **)(this + 0x10) = pDataSource;

    // Virtual call to vtable[2] again (likely after binding)
    (*(void (__thiscall **)(int*))(*pDataSource + 8))(pDataSource);

    if (nId != 0) {
        // Re-compute ID now using the stored pointer (should yield same result)
        computedId = FUN_004265d0(nId, *(int *)(this + 0x10));
        *(int *)(this + 0x14) = computedId;              // Store final ID at this+0x14

        // Virtual call to vtable[1] with (nId, 0) – e.g., setCount or setActive
        (*(void (__thiscall **)(int*, int, int))(*pDataSource + 4))(pDataSource, nId, 0);

        // Virtual call to vtable[3] – e.g., finalize or release
        (*(void (__thiscall **)(int*))(*pDataSource + 12))(pDataSource);

        return this;
    }

    // No ID branch: store zero and call vtable[3]
    *(int *)(this + 0x14) = 0;
    (*(void (__thiscall **)(int*))(*pDataSource + 12))(pDataSource);

    return this;
}