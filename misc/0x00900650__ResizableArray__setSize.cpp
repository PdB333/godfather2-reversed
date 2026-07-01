// FUNC_NAME: ResizableArray::setSize
// Address: 0x00900650
// Role: Resizes the managed array, initializing or destroying elements as needed.

static int g_defaultThirdValue = DAT_00d5ccf8; // Global default for third field of each element

// Element structure: 12 bytes each
struct Element {
    int first;   // +0x00: Possibly used as a handle/pointer; if non-zero, element is active
    int second;  // +0x04
    int third;   // +0x08: Initialized to g_defaultThirdValue
};

// Forward declarations
void* __cdecl reallocateArray(int newCount); // FUN_009004b0
void __thiscall destroyElement(Element* elem); // FUN_004daf90

class ResizableArray {
private:
    Element* mBuffer; // +0x00: pointer to array of Elements
    int mCount;       // +0x04: current number of elements

public:
    void __thiscall setSize(int newSize) {
        if (mCount < newSize) {
            // Need to grow: reallocate buffer
            reallocateArray(newSize);
            int oldCount = mCount;
            int elementsToAdd = newSize - oldCount;
            int offset = oldCount * sizeof(Element);
            for (int i = 0; i < elementsToAdd; i++) {
                Element* elem = reinterpret_cast<Element*>(reinterpret_cast<char*>(mBuffer) + offset);
                // Initialize new element
                elem->first = 0;
                elem->second = 0;
                elem->third = g_defaultThirdValue;
                offset += sizeof(Element);
            }
            mCount = newSize;
        } else if (mCount > newSize) {
            // Shrink: destroy elements from the end
            int elementsToDestroy = mCount - newSize;
            int offset = (mCount - 1) * sizeof(Element);
            for (int i = 0; i < elementsToDestroy; i++) {
                Element* elem = reinterpret_cast<Element*>(reinterpret_cast<char*>(mBuffer) + offset);
                if (elem->first != 0) {
                    destroyElement(elem);
                }
                offset -= sizeof(Element);
            }
            mCount = newSize;
        }
        // If equal, do nothing
    }
};