// FUNC_NAME: AnimationTimeline::getCurrentFrameValue
// Address: 0x005DC670
// Role: Retrieves a value from the current animation frame within a timeline.
// Uses external functions for state retrieval and assertion on failure.

#include <cassert>

// External functions (defined elsewhere in the EARS engine):
// Retrieves the current timeline and current frame pointers.
void __cdecl getCurrentFrameState(void** outTimeline, void** outFrame); // = FUN_005def60
// Fatal assertion handler.
void __cdecl assertFail(); // = FUN_00b97aea

class AnimationTimeline {
public:
    // Pointer to the timeline's frame list structure at offset +0x08.
    // The frame list contains:
    //   - array of frame data starting at +0x10
    //   - sentinel/end pointer at +0x1c
    void* mFrameList; // +0x08

    // Returns the data at offset +0x10 of the current frame, or nullptr if no valid frame.
    void* getCurrentFrameValue() {
        if (mFrameList != nullptr) {
            void* currentTimeline = nullptr;
            void* currentFrame = nullptr;
            getCurrentFrameState(&currentTimeline, &currentFrame); // sets locals

            // The frame list stores a sentinel pointer at offset +0x1c indicating the end.
            void* frameEndPtr = *(void**)((char*)mFrameList + 0x1c);

            if (currentTimeline == nullptr || currentTimeline != mFrameList) {
                assertFail(); // Timeline pointer mismatch
            }

            if (currentFrame != frameEndPtr) {
                if (currentTimeline == nullptr) {
                    assertFail();
                }
                if (currentFrame == *(void**)((char*)currentTimeline + 0x1c)) {
                    assertFail(); // Current frame equals the sentinel, invalid state
                }
                return *(void**)((char*)currentFrame + 0x10); // +0x10 is the data field in a frame struct
            }
        }
        return nullptr;
    }
};