// FUNC_NAME: SetGlobalPropertyAndApplyToCurrentComponent
// Address: 0x00536ad0
// Purpose: Copies 32 bytes from input pointer to global storage, then conditionally copies first 8 bytes to a subclass member if current component matches a specific type.
// Global offsets:
//   g_CurrentComponentVtable  (0x012058e8) - vtable of current component being processed
//   g_StaticComponentVtable   (0x0121a1f0) - known vtable for a specific component class
//   g_PropertyVtable          (0x0121a200) - vtable of a property object
//   g_SubclassVtableA         (0x0121a350) - vtable for subclass A
//   g_SubclassVtableB         (0x0121a364) - vtable for subclass B
//   g_SubclassMemberOffsetA   (0x0121a320) - offset for member in subclass A (or pointer to it)
//   g_SubclassMemberOffsetB   (0x0121a324) - offset for member in subclass B
//   g_GlobalPropertyData      (0x0121a2d0) - array of 4 uint64 (8 bytes each) for temporary storage

void SetGlobalPropertyAndApplyToCurrentComponent(undefined8* pData)
{
    // Copy 32 bytes from pData to global storage (4×8 bytes)
    g_GlobalPropertyData[0] = pData[0];
    g_GlobalPropertyData[1] = pData[1];
    g_GlobalPropertyData[2] = pData[2];
    g_GlobalPropertyData[3] = pData[3];

    // Check if the current component's vtable matches the static component class
    if (g_CurrentComponentVtable == &g_StaticComponentVtable)
    {
        if (g_PropertyVtable == g_SubclassVtableA)
        {
            // Copy first 8 bytes to subclass A's member at the specified offset
            // FUN_0060ab00 is assumed to be a memcpy-like function: dest, src, size? Or (arg1, arg2, src, size)
            // Based on usage: FUN_0060ab00(propVtable, memberOffset, &g_GlobalPropertyData[0], 8)
            // We'll call it memcpyToComponentMember for clarity.
            memcpyToComponentMember(g_PropertyVtable, g_SubclassMemberOffsetA, &g_GlobalPropertyData[0], 8);
            return;
        }
        if (g_PropertyVtable == g_SubclassVtableB)
        {
            memcpyToComponentMember(g_PropertyVtable, g_SubclassMemberOffsetB, &g_GlobalPropertyData[0], 8);
        }
    }
    return;
}