// FUNC_NAME: Entity::updateAreaQueryFlags

void __fastcall Entity::updateAreaQueryFlags(int this)
{
    int foundObject; // iVar1
    uint objectFlags; // uVar2

    // Read entity position at offsets 0x44, 0x48, 0x4c (likely x, y, z)
    // (offsets relative to this pointer)
    float posX = *(float *)(this + 0x44);
    float posY = *(float *)(this + 0x48);
    float posZ = *(float *)(this + 0x4c);

    // Compute vertical bounds around posY using global constants
    float maxY = posY + g_AreaRadiusMax;   // _DAT_00d5c458
    float minY = posY - g_AreaRadiusMin;   // _DAT_00d5780c

    // Build two identical points for the query rect? Possibly a 2D point (x,z) used as both min and max
    // The first point is at local_e0 (x) and local_d8 (z) but then local_d0 = local_e0 and local_c8 = local_d8
    // This suggests the function takes two points that are identical – maybe a point and a size?
    float queryPoint1X = posX;
    float queryPoint1Z = posZ;
    float queryPoint2X = queryPoint1X;
    float queryPoint2Z = queryPoint1Z;

    setQueryRect(&queryPoint1X, &queryPoint2X, 2, 0x80000000, 0, 0);

    // Initialize the area query system
    float initParam1 = -1.0f; // 0xffffffff as float
    float initParam2 = -1.0f; // 0xffffffff as float
    float initParam3 = g_AreaRadiusMin; // 0.0? Possibly a zero constant
    int initParam4 = 0;
    int queryResultCount = 0;

    initAreaQuery(local_60, local_c0); // 92-byte and 16-byte buffers

    if (queryResultCount == 0) {
        // No objects found – set flag 0x10 (bit 4) at +0x89
        *(byte *)(this + 0x89) |= 0x10;
    } else {
        // Objects found – clear flag 0x10
        *(byte *)(this + 0x89) &= 0xef;

        // Get first result from query
        foundObject = getFirstResult(local_c0);
        if (foundObject != 0) {
            objectFlags = *(uint *)(foundObject + 4);
            goto checkFlags;
        }
    }

    objectFlags = 0; // fallback if no object

checkFlags:
    if ((objectFlags & 0x800) != 0) {
        // Object has specific flag (e.g., is threat) – set bit 0x08 at +0x89 and bit 0x20 at +0x8a
        *(byte *)(this + 0x89) |= 8;
        *(byte *)(this + 0x8a) |= 0x20;
        return;
    }

    // No such object – clear bit 0x08 and set bit 0x20
    *(byte *)(this + 0x89) &= 0xf7;
    *(byte *)(this + 0x8a) |= 0x20;
}