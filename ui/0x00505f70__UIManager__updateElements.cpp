// FUNC_NAME: UIManager::updateElements

struct UIElement {
    UIElement* next;          // +0x00
    float posX;               // +0x04
    float posY;               // +0x08
    float halfWidth;          // +0x0C
    float halfHeight;         // +0x10
    float depth;              // +0x14
    int unknown1;             // +0x18
    void* stream;             // +0x1C (vtable pointer)
    int state1;               // +0x20
    int state2;               // +0x24
    int lastUpdateFrame;      // +0x28
    byte visible;             // +0x2E
};

struct StreamObject {
    int vtable;               // +0x00
    // methods: readData at vtable+0x1c, setMode at vtable+0x18
};

// Global variables (renamed based on usage)
extern float g_screenWidth;          // DAT_01218e40
extern float g_screenHeight;         // DAT_01218e42
extern float g_scaleX;               // DAT_01218e44
extern float g_scaleY;               // DAT_01218e48
extern float g_constantA;            // DAT_00e2b1a4
extern float g_constantB;            // DAT_00e2b04c
extern float g_constantC;            // DAT_00e2eff4
extern float g_constantD;            // DAT_00e2cd54
extern float g_constantE;            // DAT_00e44578
extern int g_frameCounter;           // DAT_0121a204? Actually used as local_44
extern int g_globalState;            // DAT_012058d0
extern int g_globalState2;           // DAT_00f15988
extern int g_globalState3;           // DAT_012058d4
extern int g_globalState4;           // DAT_00f1598c
extern int g_globalFlags;            // DAT_0121a290
extern int g_globalArray[];          // DAT_011eb8fc
extern int g_globalArray2[];         // DAT_011d912c
extern int g_globalPtr;              // DAT_012058e8
extern int g_globalInt;              // DAT_012058f0
extern int g_globalInt2;             // DAT_0121a310
extern int g_globalInt3;             // DAT_0121a314
extern int g_globalInt4;             // DAT_0121a318
extern int g_globalInt5;             // DAT_0121a374
extern int g_globalInt6;             // DAT_0121a370
extern int g_globalInt7;             // DAT_0121a200
extern int g_globalInt8;             // DAT_0121a204
extern int g_globalInt9;             // DAT_0121a1f0
extern float g_constantsArray[4];    // DAT_00e4493c, DAT_00e2b118 etc.

// Forward declarations
UIElement* getElementList();         // FUN_00505c90
void beginFrame();                   // FUN_004e3a70
void setTexture(int);                // FUN_0060a460
void resetState();                   // FUN_00536550
float* allocateVertices(int a, int b, int c, int d, int e); // FUN_0060cd00
void drawPrimitive();                // FUN_0060cde0
void updateInput();                  // FUN_00618d40
void setRenderState(int a, int b, int c); // FUN_00417cf0

void UIManager::updateElements() {
    int frameCounter = getElementList()->frameCounter; // local_44 from apiStack_28[1][4]
    UIElement* element = getElementList()->head;       // apiStack_28[1][0]
    getElementList()->frameCounter = frameCounter + 1;

    if (element != nullptr) {
        beginFrame();
        g_globalInt8 = g_globalInt5;
        g_globalInt7 = g_globalInt6;

        if (g_globalPtr == &g_globalInt9) {
            setTexture(g_globalInt5);
            setTexture(g_globalInt7);
        }

        // Clamp global state values
        if (g_globalState < 0x16) g_globalState = 0x16;
        if (0x16 < g_globalState2) g_globalState2 = 0x16;
        g_globalArray[0x3a30] = 1;

        if (g_globalState < 7) g_globalState = 7;
        if (7 < g_globalState2) g_globalState2 = 7;
        g_globalArray[0x39f4] = 1;

        if (g_globalState < 0xe) g_globalState = 0xe;
        if (0xe < g_globalState2) g_globalState2 = 0xe;
        g_globalArray[0x3a10] = 0;

        if (g_globalState < 0x19) g_globalState = 0x19;
        if (0x19 < g_globalState2) g_globalState2 = 0x19;
        g_globalArray[0x3a3c] = 5;

        if (g_globalState < 0x18) g_globalState = 0x18;
        if (0x18 < g_globalState2) g_globalState2 = 0x18;
        g_globalArray[0x3a38] = 0;

        if (g_globalState < 0xf) g_globalState = 0xf;
        if (0xf < g_globalState2) g_globalState2 = 0xf;
        g_globalArray[0x3a14] = 0;

        if (g_globalState < 0x1b) g_globalState = 0x1b;
        if (0x1a < g_globalState2) g_globalState2 = 0x1b;
        g_globalArray[0x3a44] = 0;

        if (g_globalState3 < 0xa8) g_globalState3 = 0xa8;
        if (0xa7 < g_globalState4) g_globalState4 = 0xa8;
        g_globalArray[0x3c78] = 0;

        if (g_globalState3 < 0xbe) g_globalState3 = 0xbe;
        if (0xbd < g_globalState4) g_globalState4 = 0xbe;
        g_globalArray[0x3cd0] = 0;

        resetState();

        // Constants for vertex positioning
        float constA = g_constantsArray[0]; // DAT_00e4493c
        float constB = g_constantsArray[1]; // DAT_00e2b118
        float constC = g_constantsArray[2]; // DAT_00e4493c
        float constD = g_constantsArray[3]; // DAT_00e2b118

        do {
            float data = 0.0f;

            if (element->lastUpdateFrame == 0 || (frameCounter - element->lastUpdateFrame < 2)) {
                StreamObject* stream = (StreamObject*)element->stream;
                int result = stream->vtable->readData(stream, &data, 4, 0);
                if (result == 0 || result == 1) {
                    // fall through to update
                } else {
                    goto skipUpdate;
                }
            } else {
                do {
                    StreamObject* stream = (StreamObject*)element->stream;
                    int result = stream->vtable->readData(stream, &data, 4, 1);
                    if (result == 0) break;
                } while (result == 1);
            }

            element->lastUpdateFrame = frameCounter;
            data = (float)((uint)element->visible * (int)data);

            // Check if element is within screen bounds
            float left = element->posX - element->halfWidth;
            float right = element->posX + element->halfWidth;
            float top = element->posY - element->halfHeight;
            float bottom = element->posY + element->halfHeight;

            if (left < 0.0f || right > g_screenWidth || top < 0.0f || bottom > g_screenHeight) {
                element->visible = 0;
            } else {
                element->visible = 1;
            }

            // Allocate vertex buffer (4 vertices, 5 floats each? Actually 4 floats per vertex)
            float* vertices = allocateVertices(5, 4, 0, 1, 0);
            if (vertices == nullptr) {
                float temp = 0.0f;
                element->state1 = 0;
            } else {
                StreamObject* stream = (StreamObject*)element->stream;
                stream->vtable->setMode(stream, 2);

                float scaleX = g_scaleX;
                float scaleY = g_scaleY;
                float constA2 = g_constantA;
                float constB2 = g_constantB;

                // Fill vertex data for 4 vertices
                for (int i = 0; i < 4; i++) {
                    float* v = vertices + i * 4;
                    v[0] = ((constA * frameCounter + element->posX) * scaleX * constB2) - constA2;
                    v[1] = ((constB * data - element->posY) * scaleY * constB2) + constA2;
                    v[2] = element->depth;
                    v[3] = constA2;
                }

                // Clamp values using g_constantC and g_constantA
                float minX = vertices[0];
                float maxX = vertices[12];
                float minY = vertices[1];
                float maxY = vertices[13];

                if (g_constantC < minX && minX < g_constantA) minX = g_constantC;
                if (g_constantC < maxX && maxX < g_constantA) maxX = g_constantC;
                if (g_constantC < minY && minY < g_constantA) minY = g_constantC;
                if (g_constantC < maxY && maxY < g_constantA) maxY = g_constantC;

                float slopeX = (maxX - minX) / (vertices[12] - vertices[0]);
                float slopeY = (maxY - minY) / (vertices[13] - vertices[1]);

                drawPrimitive();

                stream->vtable->setMode(stream, 1);

                float temp = g_constantA;
                float temp2 = g_constantB;
                float state2 = (float)element->state2;

                if (state2 > g_constantD) {
                    float temp3 = (float)(int)data;
                    if ((int)data < 0) temp3 += g_constantE;
                    float ratio = temp3 / state2;
                    float newVal = ratio * g_constantB;
                    if (newVal > 0.0f) {
                        if (newVal > g_constantA) newVal = g_constantA;
                    } else {
                        newVal = 0.0f;
                    }
                    element->state1 = (int)newVal;
                } else {
                    element->state1 = 0;
                }

                float diff = temp - (float)element->state1;
                element->state1 = (int)(temp - diff * diff);

                // Update state2 with some calculation
                float calc = vertices[0] * temp2 * element->halfWidth * temp2 * slopeX * constA;
                element->state2 = (int)calc;
            }

        } while ((element = element->next) != nullptr);

        if (g_globalFlags != 0) {
            uint flagIndex = g_globalFlags & 0xff;
            if (g_globalArray[g_globalInt8 * 0x10] != 0) {
                flagIndex += 0x10;
            }
            updateInput();
            g_globalArray2[flagIndex] = 0;
        }

        g_globalPtr = nullptr;
        g_globalInt = 0;
        g_globalInt2 = 0;
        g_globalInt3 = 0;
        g_globalInt4 = 0;

        // Repeat clamping (second pass)
        if (g_globalState < 0x16) g_globalState = 0x16;
        if (0x16 < g_globalState2) g_globalState2 = 0x16;
        g_globalArray[0x3a30] = 1;

        if (g_globalState < 7) g_globalState = 7;
        if (7 < g_globalState2) g_globalState2 = 7;
        g_globalArray[0x39f4] = 1;

        if (g_globalState < 0xe) g_globalState = 0xe;
        if (0xe < g_globalState2) g_globalState2 = 0xe;
        g_globalArray[0x3a10] = 1;

        if (g_globalState < 0x19) g_globalState = 0x19;
        if (0x19 < g_globalState2) g_globalState2 = 0x19;
        g_globalArray[0x3a3c] = 7;

        if (g_globalState < 0x18) g_globalState = 0x18;
        if (0x18 < g_globalState2) g_globalState2 = 0x18;
        g_globalArray[0x3a38] = 0;

        if (g_globalState < 0xf) g_globalState = 0xf;
        if (0xf < g_globalState2) g_globalState2 = 0xf;
        g_globalArray[0x3a14] = 0;

        if (g_globalState < 0x1b) g_globalState = 0x1b;
        if (0x1a < g_globalState2) g_globalState2 = 0x1b;
        g_globalArray[0x3a44] = 0;

        setRenderState(1, 5, 6);

        if (g_globalState3 < 0xa8) g_globalState3 = 0xa8;
        if (0xa7 < g_globalState4) g_globalState4 = 0xa8;
        g_globalArray[0x3c78] = 0xf;

        if (g_globalState3 < 0xbe) g_globalState3 = 0xbe;
        if (0xbd < g_globalState4) g_globalState4 = 0xbe;
        g_globalArray[0x3cd0] = 0xf;
    }

    getElementList()->head = nullptr;
    getElementList()->frameCounter = 0;
}