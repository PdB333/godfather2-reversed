// FUNC_NAME: releaseGlobalObjects
// Function at 0x007f9d50: called from FUN_006828a0, likely a cleanup/shutdown routine.
// Calls cleanupObject on a series of statically allocated global objects (51 instances).

void releaseGlobalObjects(void)
{
    // +0x00: cleanupObject (FUN_00408310) reduces reference count or calls destructor.
    cleanupObject(&DAT_0112c99c);
    cleanupObject(&DAT_0112c854);
    cleanupObject(&DAT_0112c994);
    cleanupObject(&DAT_0112d924);
    cleanupObject(&DAT_0112c834);
    cleanupObject(&DAT_0112d8dc);
    cleanupObject(&DAT_0112c984);
    cleanupObject(&DAT_0112c814);
    cleanupObject(&DAT_0112c9bc);
    cleanupObject(&DAT_0112d858);
    cleanupObject(&DAT_0112c9d4);
    cleanupObject(&DAT_0112c9e4);
    cleanupObject(&DAT_0112c98c);
    cleanupObject(&DAT_0112d904);
    cleanupObject(&DAT_0112ca6c);
    cleanupObject(&DAT_0112d8f4);
    cleanupObject(&DAT_0112c844);
    cleanupObject(&DAT_0112c97c);
    cleanupObject(&DAT_0112d8e4);
    cleanupObject(&DAT_0112ca64);
    cleanupObject(&DAT_0112c81c);
    cleanupObject(&DAT_0112d954);
    cleanupObject(&DAT_0112d93c);
    cleanupObject(&DAT_0112c9a4);
    cleanupObject(&DAT_0112c95c);
    cleanupObject(&DAT_0112d91c);
    cleanupObject(&DAT_0112d914);
    cleanupObject(&DAT_0112d92c);
    cleanupObject(&DAT_0112c824);
    cleanupObject(&DAT_0112d90c);
    cleanupObject(&DAT_0112c964);
    cleanupObject(&DAT_0112d9ec);
    cleanupObject(&DAT_0112d944);
    cleanupObject(&DAT_0112c84c);
    cleanupObject(&DAT_0112d9dc);
    cleanupObject(&DAT_0112c9dc);
    cleanupObject(&DAT_0112c96c);
    cleanupObject(&DAT_0112d8ec);
    cleanupObject(&DAT_0112c974);
    cleanupObject(&DAT_0112c9cc);
    cleanupObject(&DAT_0112c83c);
    cleanupObject(&DAT_0112c954);
    cleanupObject(&DAT_0112d934);
    cleanupObject(&DAT_0112c9ac);
    cleanupObject(&DAT_0112d8fc);
    cleanupObject(&DAT_0112d9d4);
    cleanupObject(&DAT_0112c9c4);
    cleanupObject(&DAT_0112c82c);
    cleanupObject(&DAT_0112d860);
    cleanupObject(&DAT_0112c9b4);
    cleanupObject(&DAT_0112d94c);
    return;
}