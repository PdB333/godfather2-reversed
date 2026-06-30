// FUNC_NAME: Camera::Camera
// Address: 0x00753890
// Constructor for a Camera class, likely part of the camera system.
// Sets up vtable, copies data from a global camera manager, adjusts for mode,
// and registers in a linked list of cameras.

// Global variables (inferred)
extern int gCameraMode;            // DAT_0112ae70
extern int gCameraListHead;        // DAT_0112ae84
extern int gCameraScaleSinglePlayer; // DAT_00e446f4
extern int gCameraScaleMultiplayer;  // DAT_00e446bc
extern int gSomeGlobal;            // DAT_0112afb8

// Forward declarations of helper functions
void Camera_BaseConstructor(int param2, int param3); // FUN_004ac120
void* CameraManager_GetInstance();                   // FUN_00471610
void MemoryAllocate(int size);                       // FUN_007f63e0 (0x36)
void ListRemove(int* node);                          // FUN_004daf90
void* GetSomeObject(int global);                     // FUN_0043b870
void AudioSetListener(int mode);                     // FUN_0078b270
void AudioSetSomething(int val, int p1, int p2);     // FUN_0078b4b0
void CameraApplyScale(void* data, void* data2, void* stack, int scale); // FUN_004a0370

class Camera {
public:
    // Vtable pointer at +0x00
    // Offset layout (from this):
    // +0x48: int* m_pSomething
    // +0x50: int* m_pBase (base class pointer)
    // +0x54: float m_cameraData[3]; // copied from manager offset 0x30 (3 ints)
    // +0x60: int m_cameraExtra;     // from manager offset 0x38
    // +0x64: float m_viewportData[3]; // copied from manager offset 0x20
    // +0x70: int* m_pNext; // linked list node (next)
    // +0x74: int* m_pPrev; // previous
    // +0x78: int m_mode;
    // +0x7C to +0xA0: zeros
    // +0x9C: int* m_pFreePtr; // a pointer that may be freed

    Camera* __thiscall constructor(int param2, int param3) {
        Camera* this = this;
        Camera_BaseConstructor(param2, param3); // call base class constructor

        this->vtable = &CameraVTable; // PTR_LAB_00d64bc4

        int* pNext = &this->m_pNext; // offset +0x1c
        *pNext = 0;
        this->m_pPrev = 0;            // +0x1d

        int* pFreePtr = &this->m_pFreePtr; // offset +0x27
        *pFreePtr = 0;
        this->some0 = 0; // +0x28
        this->some1 = 0; // +0x29

        int baseOffset;
        if (this->m_pSomething == 0) { // +0x12
            baseOffset = 0;
        } else {
            baseOffset = this->m_pSomething - 0x48; // offset conversion
        }
        this->m_pBase = baseOffset; // +0x14

        this->m_next = 0; // +0x18

        void* cameraManager = CameraManager_GetInstance(); // FUN_00471610
        // Copy data from manager at offsets 0x30, 0x34, 0x38 to this's offsets 0x54, 0x58, 0x5C?
        // Actually: *(undefined8 *)(param_1 + 0x15) = *(undefined8 *)(iVar4 + 0x30);
        // That copies 8 bytes (two ints) to offsets +0x54 and +0x58, then single int at +0x5C from +0x38.
        this->m_cameraData[0] = *(int*)((char*)cameraManager + 0x30);
        this->m_cameraData[1] = *(int*)((char*)cameraManager + 0x34);
        this->m_cameraData[2] = *(int*)((char*)cameraManager + 0x38);

        MemoryAllocate(0x36); // possibly allocate something

        // Call virtual function on base object: offset 0x290
        (**(code**)(*(int*)this->m_pBase + 0x290))(0, 0x20);

        // Zero out a range from +0x1f to +0x26 (7 ints)
        this->m_zeroZone[0] = 0; // +0x1f
        this->m_zeroZone[1] = 0; // +0x20
        this->m_zeroZone[2] = 0; // +0x21
        this->m_zeroZone[3] = 0; // +0x22
        this->m_zeroZone[4] = 0; // +0x23
        this->m_zeroZone[5] = 0; // +0x24
        this->m_zeroZone[6] = 0; // +0x25
        this->m_zeroZone[7] = 0; // +0x26

        if (*pFreePtr != 0) { // +0x27
            ListRemove(pFreePtr);
            *pFreePtr = 0;
        }
        this->some1 = 0; // +0x29

        // Conditional audio setup
        if (this->m_pBase != 0) {
            int* obj = GetSomeObject(gSomeGlobal); // DAT_0112afb8
            if (obj != 0) {
                int someField = *(int*)(obj + 0x1c); // offset 0x1c of that object
                if (someField != 0 && someField != 0x3c) {
                    AudioSetListener(3);
                    AudioSetSomething(*(int*)(someField + 0x24), 1, 1);
                }
            }
        }

        // Copy another set of data from manager
        void* cameraManager2 = CameraManager_GetInstance(); // (actually same pointer)
        int* pViewport = &this->m_viewportData; // +0x19
        *pViewport = *(int*)((char*)cameraManager2 + 0x20);
        this->m_viewportData[1] = *(int*)((char*)cameraManager2 + 0x24);
        this->m_viewportData[2] = *(int*)((char*)cameraManager2 + 0x28);

        // Adjust for camera mode (1 or 2)
        if (gCameraMode == 1 || gCameraMode == 2) {
            int scale;
            if (gCameraMode == 2) {
                scale = gCameraScaleMultiplayer; // DAT_00e446bc
            } else {
                scale = gCameraScaleSinglePlayer; // DAT_00e446f4
            }
            CameraApplyScale(pViewport, pViewport, &someStackVar, scale);
        }

        // Insert this camera into global linked list
        int* listHead = gCameraListHead;
        if (pNext != &gCameraListHead && *pNext != gCameraListHead) {
            if (*pNext != 0) {
                ListRemove(pNext);
            }
            *pNext = listHead;
            if (listHead != 0) {
                this->m_pPrev = *(int**)(listHead + 4);
                *(int**)(listHead + 4) = pNext;
            }
        }

        if (gCameraListHead == 0) {
            this->m_mode = gCameraMode;
            return this;
        }

        // If list head exists, free it and replace? Likely only one camera.
        ListRemove(&gCameraListHead);
        gCameraListHead = 0;
        this->m_mode = gCameraMode;
        return this;
    }

    // Dummy vtable pointer
    static const int CameraVTable; // defined elsewhere
};