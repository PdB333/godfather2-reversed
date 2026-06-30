// FUNC_NAME: EARSQuad::createFromStaticData

// Function address: 0x00418600
// This function creates a quad (rectangle) from four static global float values.
// The global floats define the bounding box: (xMin, yMin, xMax, yMax) in the order:
//   DAT_01128590 = xMin
//   DAT_01128594 = yMin
//   DAT_01128598 = xMax
//   DAT_0112859c = yMax
// The allocated buffer stores 8 floats representing the four vertices of the quad:
//   [xMin, yMin, xMax, yMin, xMax, yMax, xMin, yMax]
// This is the standard vertex order for a rectangle: top-left, top-right, bottom-right, bottom-left.

// The calling convention is __fastcall (ECX = this), but it behaves like a __thiscall member function.

// Known callees:
// - FUN_0060cd00: Allocates memory (type 0xd, count 4, flags 0,1,0). Returns pointer to buffer.
// - FUN_0060cde0: Registers/finalizes the allocated buffer (likely increments refcount or adds to render list).

#include <cstdint>

// Globals (defined elsewhere in the game)
extern float g_quadVertexData_xMin;   // DAT_01128590
extern float g_quadVertexData_yMin;   // DAT_01128594
extern float g_quadVertexData_xMax;   // DAT_01128598
extern float g_quadVertexData_yMax;   // DAT_0112859c

// Forward declarations
void* __fastcall allocateQuadMemory(int allocType, int elementCount, int unk0, int unk1, int unk2); // FUN_0060cd00
void  __fastcall registerQuadBuffer(void* buffer); // FUN_0060cde0

class EARSQuad
{
public:
    // Virtual function table offset 0x3c: called before allocation
    void preAllocate(void); // VTable[0x3c/4]

    void createFromStaticData(void) // __fastcall with this in ECX
    {
        // Call virtual pre-allocate hook
        this->preAllocate();

        // Allocate buffer for 8 floats (2 floats per vertex, 4 vertices)
        float* vertexBuffer = (float*)allocateQuadMemory(13, 4, 0, 1, 0);
        if (vertexBuffer != nullptr)
        {
            // Fill with predefined quad vertices
            vertexBuffer[0] = g_quadVertexData_xMin; // Top-left x
            vertexBuffer[1] = g_quadVertexData_yMin; // Top-left y
            vertexBuffer[2] = g_quadVertexData_xMax; // Top-right x
            vertexBuffer[3] = g_quadVertexData_yMin; // Top-right y
            vertexBuffer[4] = g_quadVertexData_xMax; // Bottom-right x
            vertexBuffer[5] = g_quadVertexData_yMax; // Bottom-right y
            vertexBuffer[6] = g_quadVertexData_xMin; // Bottom-left x
            vertexBuffer[7] = g_quadVertexData_yMax; // Bottom-left y

            // Register the allocated buffer (e.g., add to render list, store pointer)
            registerQuadBuffer(vertexBuffer);
        }
    }
};