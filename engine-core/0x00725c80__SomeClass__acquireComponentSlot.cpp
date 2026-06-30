// FUNC_NAME: SomeClass::acquireComponentSlot
// Address: 0x00725c80
// The function iterates over a list of available component nodes (starting at this+0xec) and attempts to acquire one that is not already attached and can be attached to this object.
// If successful, it stores the found node at this+0x128, detaches it from the free list (at this+0x12c/0x130) and returns 0 (false).
// If no suitable component is found, it returns 1 (true) unless the current slot is empty or already occupied by a placeholder (0x48).

#include <cstdint>

typedef int* ComponentNode;
typedef int* ComponentNodeList;

// Forward declarations of external functions
extern void FUN_004daf90(void* ptr);  // likely a deallocation routine
extern void FUN_00446100(void* container, void* current); // iterator
extern void FUN_00725230(void* temp); // some initialization

bool __fastcall SomeClass::acquireComponentSlot(int thisPtr)
{
    // Interpret this as an SomeClass pointer
    SomeClass* _this = reinterpret_cast<SomeClass*>(thisPtr);

    // Clear current component pointer
    _this->m_pComponent = 0; // offset 0x128

    // If the slot at +0x12c is non-zero, free it
    if (_this->m_pFreeListHead != 0) {
        FUN_004daf90(_this->m_pFreeListHead);
        _this->m_pFreeListHead = 0;
    }

    bool result = false; // local_15
    ComponentNodeList iterListStart = nullptr;
    int someCounter = 0; // local_4

    // Start iterating over the component container at +0xec
    ComponentNode node = reinterpret_cast<ComponentNode>(FUN_00446100(&_this->m_componentContainer, 0));

    while (true) {
        if (node == nullptr) {
            // End of list
            if (_this->m_pFreeListHead == 0 || _this->m_pFreeListHead == reinterpret_cast<ComponentNode>(0x48)) {
                // If free list is empty or has a placeholder, call initialization function
                FUN_00725230(&iterListStart);
            }
            if (_this->m_pFreeListHead != 0 && _this->m_pFreeListHead != reinterpret_cast<ComponentNode>(0x48)) {
                result = true; // There is an active slot needed
            }
            // Clean up temporary iter list if allocated
            if (iterListStart != nullptr) {
                FUN_004daf90(&iterListStart);
            }
            return result;
        }

        ComponentNode candidate = nullptr;
        // vtable+0x10: method that checks component compatibility by a hash and outputs a node
        bool isMatch = (*(bool (**)(void*))(*node + 0x10))(0x3a8fda85, &candidate);

        if (isMatch && candidate != nullptr) {
            // vtable+0x14: method that checks if the node can be attached to this object
            bool canAttach = (*(bool (**)(void*))(*candidate + 0x14))(thisPtr);
            if (canAttach) {
                // vtable+0x10 with argument 0 checks if the node is currently free
                bool isFree = (*(bool (**)(void*))(*candidate + 0x10))(0);
                if (!isFree) {
                    // Node occupies a slot – take ownership
                    _this->m_pComponent = candidate; // offset 0x128

                    ComponentNodeList listPtr = &_this->m_pFreeListHead; // offset 0x12c
                    ComponentNode targetNode = node + 0x12; // get the node's "next" pointer

                    if (_this->m_pFreeListHead != targetNode) {
                        if (_this->m_pFreeListHead != nullptr) {
                            FUN_004daf90(listPtr);
                        }
                        _this->m_pFreeListHead = targetNode;
                        if (targetNode != nullptr) {
                            _this->m_pFreeListPrev = node[0x13]; // offset 0x130 stores previous
                            node[0x13] = reinterpret_cast<int>(listPtr); // update node's previous to point to our list
                        }
                    }
                    goto EndLoop;
                }

                // Node is free; handle temporary list
                if (iterListStart == nullptr || iterListStart == reinterpret_cast<ComponentNode>(0x48)) {
                    // Start a new temporary list
                    ComponentNodeList tempList = reinterpret_cast<ComponentNodeList>(&iterListStart);
                    ComponentNode tempNode = node + 0x12; // same pattern

                    if (iterListStart != tempNode) {
                        if (iterListStart != nullptr) {
                            FUN_004daf90(&iterListStart);
                        }
                        iterListStart = tempNode;
                        if (tempNode != nullptr) {
                            someCounter = node[0x13];
                            node[0x13] = reinterpret_cast<int>(&iterListStart);
                        }
                    }
                }
            }
        }

        // Move to next node
        node = reinterpret_cast<ComponentNode>(FUN_00446100(&_this->m_componentContainer, node));
    }

EndLoop:
    // After taking ownership, check conditions similar to above
    if (_this->m_pFreeListHead == 0 || _this->m_pFreeListHead == reinterpret_cast<ComponentNode>(0x48)) {
        FUN_00725230(&iterListStart);
    }
    if (_this->m_pFreeListHead != 0 && _this->m_pFreeListHead != reinterpret_cast<ComponentNode>(0x48)) {
        result = true;
    }
    if (iterListStart != nullptr) {
        FUN_004daf90(&iterListStart);
    }
    return result; // false if a slot was acquired, true if there is pending slot
}