// FUNC_NAME: Debug::drawDebugSegment

void __fastcall Debug::drawDebugSegment(void)
{
    // this (ECX) is a Debug object
    // EBX holds a global render device pointer (set by caller)

    // Offsets:
    // +0x58: debug line attribute (e.g., line color or flags)
    // +0x10c: pointer to a shape/geometry object with a vtable
    // +0x14c: current index into shape's point list

    int index = *(int*)((char*)this + 0x14c);
    int lineData = *(int*)((char*)this + 0x58);
    void* shape = *(void**)((char*)this + 0x10c);

    // Virtual function at vtable+0x0C returns a point (or coordinate) given an index
    typedef int (__thiscall *GetPointFunc)(void*, int);
    GetPointFunc getPoint = *(GetPointFunc*)(*(int**)shape + 0x0C);

    int startPoint = getPoint(shape, index);
    int endPoint = getPoint(shape, index + 1);

    // Retrieve debug color/data associated with this index
    int debugColor = getDebugColor(index); // FUN_00757900

    // Render a line segment from startPoint to endPoint using global device (EBX) and lineData
    drawDebugPrimitive(*(int*)0, lineData, debugColor, startPoint, endPoint); // FUN_00752aa0
}