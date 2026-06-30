// FUNC_NAME: ThreadContext::getObjectOrientation
// Address: 0x00450170
// Purpose: Retrieves a 4-float orientation (quaternion) for a given object handle from thread-local storage.
//          Uses TLS slot 0 (fs:[0x2C]) to get per-thread context, then an offset from that context to index into
//          the object's transform data. Falls back to global defaults if transform pointer is null.

static float s_defaultOriX = DAT_00e4479c; // global default X component
static float s_defaultOriY = DAT_00e44798; // global default Y component

void __fastcall ThreadContext::getObjectOrientation(
    int unusedInECX,            // first __fastcall parameter (ECX), not used
    float outOri[4],            // output orientation (ordered X, Y, Z, W)
    int objectHandle)            // object identifier (handle or entity ID)
{
    // Retrieve pointer to thread-local storage array (first entry) + 8 gives an offset/index
    // This value is used as a byte offset into subsequent structures.
    int byteOffset = *(int*)( (int*)( __readfsdword(0x2C) )[0] + 8 );

    // Get a pointer from the object's data at offset 0x68, then add 4 + byteOffset to read a transform node pointer
    int* transformNodePtr = *(int**)(objectHandle + 0x68); // object->transformComponent +0x68? 
    int thisNode = *(int*)( (int)transformNodePtr + 4 + byteOffset );

    if (thisNode != NULL)
    {
        // Node has a data block at +0x18; orientation is stored starting at +0x20 + byteOffset
        float* orientSource = (float*)( *(int*)(thisNode + 0x18) + 0x20 + byteOffset );
        outOri[0] = orientSource[0];
        outOri[1] = orientSource[1];
        outOri[2] = orientSource[2];
        outOri[3] = orientSource[3];
        return;
    }

    // Fallback: use global defaults; note W is set to 0.0f
    outOri[0] = s_defaultOriX;
    outOri[1] = s_defaultOriY;
    outOri[2] = s_defaultOriX;  // same as default X
    outOri[3] = 0.0f;
}