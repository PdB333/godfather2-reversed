// FUN_00562880: RenderObject::createScreenSpaceQuadMesh

int RenderObject::createScreenSpaceQuadMesh(void)
{
    // Vertex data for a full-screen quad tessellated? 8 vertices (two triangles? Actually full-screen quad is 4 vertices, but here 8 vertices might be a frustum or billboard with 2 quads)
    // Constants are float values from global addresses; likely representing screen space coordinates (e.g., -1, 0, 1) and texcoords.
    // Each vertex: float4 (x, y, z, w?) - 16 bytes stride.

    static const float s_constantA = *(float*)0x00e445a4;
    static const float s_constantB = *(float*)0x00e2b310;
    static const float s_constantC = *(float*)0x00e2b04c;
    static const float s_constantD = *(float*)0x00e44710;
    static const float s_constantE = *(float*)0x00e44750;
    static const float s_constantF = *(float*)0x00e44828;

    struct Vertex { float x, y, z, w; };
    Vertex vertexData[8];
    vertexData[0] = { s_constantA, s_constantB, s_constantC, 0.0f };
    vertexData[1] = { s_constantD, s_constantB, s_constantC, 0.0f };
    vertexData[2] = { s_constantA, s_constantB, s_constantE, 0.0f };
    vertexData[3] = { s_constantD, s_constantB, s_constantE, 0.0f };
    vertexData[4] = { s_constantA, s_constantF, s_constantC, 0.0f };
    vertexData[5] = { s_constantD, s_constantF, s_constantC, 0.0f };
    vertexData[6] = { s_constantA, s_constantF, s_constantE, 0.0f };
    vertexData[7] = { s_constantD, s_constantF, s_constantE, 0.0f };

    VertexBuffer* pVertexBuffer = nullptr; // output
    uint bufferSize = 0; // output
    uint vertexCount = 8;
    uint vertexStride = 0x10;

    // Create vertex buffer resource (likely IDirect3DVertexBuffer9*)
    // FUN_00a77320: CreateVertexBuffer(pData, &pBuffer, &size, usageFlags)
    CreateVertexBuffer(&vertexData, &pVertexBuffer, &bufferSize, 1);

    vertexCount = pVertexBuffer->size; // local_98 (size field of vertexbuffer)
    vertexStride = 0x10;
    VertexBuffer* pData = pVertexBuffer; // local_9c

    // TLS for resource manager?
    TlsGetValue(DAT_01139810);

    // Allocate a 0x60-byte object
    int newObject = (int)AllocMemory(0x60, 0x27);
    *(short*)(newObject + 4) = 0x60; // store allocation size at offset +4

    // Create a render mesh from vertex buffer
    // FUN_00c067b0: CreateMesh(pVertexBuffer, &bufferSize, globalTexture?)
    newObject = CreateMesh(&pVertexBuffer, &bufferSize, _DAT_00ef3a9c);
    *(int*)(newObject + 0x10) = _DAT_00e2fc48; // store some resource handle

    // Additional initialization
    InitMesh(newObject); // FUN_00562ad0

    // If the buffer was not preallocated (high bit check), free temporary data
    if ((bufferSize & 0x80000000) == 0)
    {
        TlsGetValue(DAT_01139810);
        FreeMemory((int)pVertexBuffer, bufferSize << 4, 0x17);
    }

    return newObject;
}