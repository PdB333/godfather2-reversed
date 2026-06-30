// FUNC_NAME: TransformBufferManager::setBufferSize

// Function at 0x0049f5e0: Sets the size of a transformation matrix buffer, 
// distributing it to attached camera data objects. Deferred buffer freeing via task queue.
// Offsets: +0x80 = m_pTransformBuffer, +0x84 = m_bufferSize, +0x8C = m_pCameraDataArray, +0x90 = m_cameraDataCount
// Each camera data object (sizeof?) has at +0xA0 a pointer to transform data block, which gets +0x74 set to the buffer pointer.

// Global task queues for deferred operations (main vs render thread)
// Addresses: 0x0110bb88 (main), 0x01117bb0 (render)
struct TaskNode {
    void (*m_pFunction)(void*);      // +0x00
    void* m_pParam1;                 // +0x04
    void* m_pParam2;                 // +0x08
    TaskNode* m_pNext;               // +0x0C
};

struct TaskQueue {
    TaskNode* field_0x00;            // +0x00
    TaskNode* field_0x04;            // +0x04
    TaskNode* field_0x08;            // +0x08
    TaskNode* m_pHead;               // +0x0C
    TaskNode* m_pTail;               // +0x10
};

// Forward declarations for external functions
extern TaskQueue g_taskQueueMain;    // at 0x0110bb88
extern TaskQueue g_taskQueueRender;  // at 0x01117bb0
extern uint __stdcall GetThreadId(); // approximated; checks FS:[0x2C] + 0x34
extern uint __stdcall FreeBufferTask(void* param); // at LAB_00485300
extern uint __stdcall GetSomeIdentityValue(); // at 0x009c8f80, returns float/uint identity value

class TransformBufferManager {
public:
    float* m_pTransformBuffer;           // +0x80
    uint   m_bufferSize;                 // +0x84
    void*  m_pCameraDataArray;           // +0x8C (array of pointers to CameraData)
    uint   m_cameraDataCount;            // +0x90

    // +0x? no other fields used

    void __thiscall setBufferSize(uint newSize) {
        float* pOldBuffer = m_pTransformBuffer;

        // If we have an old buffer and the new size is larger, post a task to free the old buffer
        if (pOldBuffer != nullptr && m_bufferSize < newSize) {
            TaskQueue* pQueue;
            // Determine which task queue to use based on thread
            if (*(int*)(*(int**)(__readfsdword(0x2C)) + 0x34) != 0) {
                pQueue = &g_taskQueueRender;
            } else {
                pQueue = &g_taskQueueMain;
            }

            // Allocate a task node from the free list (bumps pool)
            uint idValue = GetSomeIdentityValue();
            TaskNode* pNode = pQueue->m_pHead;
            while (pNode == nullptr) {
                // Yield while waiting for free node
                Sleep(0); // approximated: FUN_00485280
                pNode = pQueue->m_pHead;
            }

            // Remove node from free list head
            pQueue->m_pHead = pNode->m_pNext;
            pNode->m_pNext = nullptr;

            // Set task data: function = FreeBufferTask, param1 = idValue, param2 = old buffer pointer
            pNode->m_pFunction = &FreeBufferTask;
            pNode->m_pParam1   = reinterpret_cast<void*>(idValue);
            pNode->m_pParam2   = pOldBuffer;

            // Insert at tail of the active task queue
            if (pQueue->m_pTail == nullptr) {
                pQueue->m_pHead = pNode;
            } else {
                pQueue->m_pTail->m_pNext = pNode;
            }
            pQueue->m_pTail = pNode;

            // Clear the buffer pointer; it's now owned by the task
            m_pTransformBuffer = nullptr;
        }

        // Store new size
        m_bufferSize = newSize;

        // If new size is nonzero and we don't have a buffer yet, allocate and initialize
        if (newSize != 0 && m_pTransformBuffer == nullptr) {
            uint idValue = GetSomeIdentityValue();
            // HeapAlloc? The allocation is done through a global function that takes size and flags
            struct AllocInfo {
                uint flags;
                uint align;
                uint unknown;
            };
            AllocInfo info;
            info.flags  = 2;
            info.align  = 0x40;
            info.unknown = 0;

            // This calls a virtual function through a global object (not shown here) to allocate
            m_pTransformBuffer = reinterpret_cast<float*>(
                (*(uint (__stdcall**)(uint, AllocInfo*))(*reinterpret_cast<uint**>(0x00e2b1a4)))(newSize * 0x40, &info)
            );

            // Propagate the buffer pointer to all camera data objects
            if (m_pCameraDataArray != nullptr) {
                // m_pCameraDataArray points to an array of structs, each at offset +0xA0 has pointer to transform data
                // Each transform data has +0x74 buffer pointer
                uint count = m_cameraDataCount;
                void** ppCamera = reinterpret_cast<void**>(m_pCameraDataArray);
                for (uint i = 0; i < count; ++i) {
                    void* pCamera = ppCamera[i];
                    if (pCamera != nullptr) {
                        // offset +0xA0 is a pointer to transform data
                        void* pTransformData = *reinterpret_cast<void**>(reinterpret_cast<char*>(pCamera) + 0xA0);
                        // offset +0x74 in transform data = buffer pointer
                        *reinterpret_cast<float**>(reinterpret_cast<char*>(pTransformData) + 0x74) = m_pTransformBuffer;
                    }
                }
            }

            // Initialize each 0x40-byte element (matrix) as identity with idValue on diagonal
            float* pBuffer = m_pTransformBuffer;
            uint idVal = idValue; // treat as float? In the original it's stored as undefined4
            for (uint i = 0; i < newSize; ++i) {
                // This sets a 4x4 matrix:
                // [idValue, 0, 0, 0]
                // [0, idValue, 0, 0]
                // [0, 0, idValue, 0]
                // [0, 0, 0, idValue]
                pBuffer[0]  = reinterpret_cast<float&>(idVal);
                pBuffer[1]  = 0.0f;
                pBuffer[2]  = 0.0f;
                pBuffer[3]  = 0.0f;
                pBuffer[4]  = 0.0f;
                pBuffer[5]  = reinterpret_cast<float&>(idVal);
                pBuffer[6]  = 0.0f;
                pBuffer[7]  = 0.0f;
                pBuffer[8]  = 0.0f;
                pBuffer[9]  = 0.0f;
                pBuffer[10] = reinterpret_cast<float&>(idVal);
                pBuffer[11] = 0.0f;
                pBuffer[12] = 0.0f;
                pBuffer[13] = 0.0f;
                pBuffer[14] = 0.0f;
                pBuffer[15] = reinterpret_cast<float&>(idVal);
                pBuffer += 16; // 16 floats per matrix = 0x40 bytes
            }
        }
    }
};