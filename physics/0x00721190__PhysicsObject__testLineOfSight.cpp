// FUNC_NAME: PhysicsObject::testLineOfSight
bool __fastcall PhysicsObject::testLineOfSight(void* thisPtr)
{
    // Check if physics world exists and is enabled
    void* world = *(void**)((char*)thisPtr + 0x8);
    if (world != nullptr && *(int*)((char*)world + 0xC4) != 0)
    {
        Vector3 start1; // offset 0x80 (12 bytes)
        Vector3 end1;   // offset 0x8C (12 bytes)
        start1 = *(Vector3*)((char*)thisPtr + 0x80);
        end1   = *(Vector3*)((char*)thisPtr + 0x8C);

        // Compute a scalar from a transform stored at +0xC
        float scalar = getTransformScalar(*(void**)((char*)thisPtr + 0xC));
        // Transform the two points into world space (or local space)
        transformPointsToWorld(&start1, &end1, scalar);

        // Set up raycast parameters
        RaycastQueryParams params; // local_e0 is a pointer to this? Actually local_e0 = &PTR_FUN_00e32a8c
        params.unknownTable = &gRaycastFunctionTable; // PTR_FUN_00e32a8c
        params.resultFlags  = 0;
        params.field_c0     = gStaticVar_00d5780c;
        params.field_bc     = -1;
        params.field_b0     = -1;
        params.field_90     = 0;
        params.field_dc     = gStaticVar_00d5780c;

        RaycastResult result; // local_70 (48 bytes)
        bool hit = executeRaycast(&result, &params);
        if (hit)
            return true;

        // Second line segment (offset 0x98, 0xA4)
        Vector3 start2 = *(Vector3*)((char*)thisPtr + 0x98);
        Vector3 end2   = *(Vector3*)((char*)thisPtr + 0xA4);
        scalar = getTransformScalar(*(void**)((char*)thisPtr + 0xC));
        transformPointsToWorld(&start2, &end2, scalar);

        // Reuse same params
        hit = executeRaycast(&result, &params);
        return hit;
    }
    return false;
}

// Helper functions (stubs for called functions)
float __fastcall getTransformScalar(void* transformPtr);
void  __fastcall transformPointsToWorld(Vector3* start, Vector3* end, float scalar);
bool  __fastcall executeRaycast(RaycastResult* result, RaycastQueryParams* params);

// Global variable
extern void* gRaycastFunctionTable; // PTR_FUN_00e32a8c
extern int   gStaticVar_00d5780c;   // _DAT_00d5780c