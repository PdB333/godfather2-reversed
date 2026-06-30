// FUNC_NAME: TreeNode::TreeNode (copy constructor)
// Address: 0x004da9e0
// Role: Deep copy of a tree node structure (0x18 bytes) with recursive child copy.
// Structure layout (offsets):
// +0x00: undefined8 (8 bytes) - likely a pointer or 64-bit value
// +0x08: undefined2 (2 bytes) - short
// +0x0A: undefined1 (1 byte) - byte
// +0x0C: undefined4 (4 bytes) - int
// +0x10: undefined4 (4 bytes) - int
// +0x14: TreeNode* child (4 bytes) - pointer to child node

class TreeNode {
public:
    // Fields (size 0x18)
    /* +0x00 */ uint64_t field_0x00; // 8 bytes
    /* +0x08 */ uint16_t field_0x08; // 2 bytes
    /* +0x0A */ uint8_t  field_0x0A; // 1 byte
    /* +0x0C */ uint32_t field_0x0C; // 4 bytes
    /* +0x10 */ uint32_t field_0x10; // 4 bytes
    /* +0x14 */ TreeNode* child;     // 4 bytes

    // Copy constructor (deep copy)
    // param_1 = this, param_2 = source (const TreeNode&)
    // __thiscall
    TreeNode(const TreeNode& other) {
        // Copy all fields except child
        field_0x00 = other.field_0x00;
        field_0x08 = other.field_0x08;
        field_0x0A = other.field_0x0A;
        field_0x0C = other.field_0x0C;
        field_0x10 = other.field_0x10;
        child = nullptr; // Initialize to null

        // If source has a child, deep copy it
        if (other.child != nullptr) {
            // Allocate new node (size 0x18) - likely operator new
            TreeNode* newChild = (TreeNode*)FUN_009c8e50(0x18); // allocation function
            if (newChild != nullptr) {
                // Recursively copy the child node
                // Note: The decompiler shows a single-argument call, but it's actually:
                // newChild->TreeNode(*other.child);
                // We'll use placement new or direct copy constructor call.
                // For reconstruction, we assume the function is the copy constructor itself.
                // So we call it with newChild as 'this' and other.child as source.
                // In assembly, this would be: call FUN_004da9e0(newChild, other.child)
                // But the decompiler omitted the first argument (newChild) because it's the return value.
                // We'll write it as: new (newChild) TreeNode(*other.child);
                // However, since we are inside the copy constructor, we can't call it directly.
                // Instead, we'll assume the function is a static helper or the copy constructor is called recursively.
                // For clarity, we'll use a helper function or just show the intent.
                // Given the decompiled code, we'll reconstruct as:
                // newChild->TreeNode(*other.child); // recursive copy constructor
                // But that's not valid C++. We'll use a separate static function or assume the compiler generates it.
                // To match the decompiled code, we'll write:
                // newChild = new TreeNode(*other.child);
                // But that would call the copy constructor again, leading to infinite recursion? No, it's fine.
                // Actually, the decompiled code shows the function being called with only one argument (the source child).
                // That suggests the function is actually a copy constructor that takes a single argument (the source).
                // So the recursive call is: TreeNode newChild(*other.child); but that's a stack object.
                // The allocation is separate. So the code is:
                // TreeNode* newChild = (TreeNode*)operator new(0x18);
                // if (newChild) {
                //     newChild->TreeNode(*other.child); // call copy constructor on allocated memory
                // }
                // This is placement new. So we'll write:
                // newChild = new (newChild) TreeNode(*other.child);
                // But we don't have placement new defined. We'll just show the logic.
                // For the reconstruction, we'll use a helper function or assume the function is a static deep copy.
                // Given the decompiled code, the recursive call is: FUN_004da9e0(other.child);
                // That implies the function is a static function that takes a source pointer and returns a new copy.
                // But the function signature shows two parameters. This is confusing.
                // To resolve, we'll assume the function is a member function that takes a source reference.
                // The recursive call should be: newChild->TreeNode(*other.child);
                // We'll write it as: newChild = new TreeNode(*other.child);
                // But that would allocate again, leading to double allocation. The decompiled code shows allocation first, then recursive call.
                // So it's placement new. We'll write:
                // ::new (newChild) TreeNode(*other.child);
                // However, the decompiled code does not show the 'this' pointer being passed to the recursive call.
                // It only passes the source child. This suggests the function is actually a static function that takes a source pointer and returns a new copy.
                // But the function returns undefined8* and takes two parameters. The first parameter is the destination? 
                // Actually, looking at the code: 
                //   iVar1 = FUN_009c8e50(0x18);
                //   if (iVar1 != 0) {
                //     uVar2 = FUN_004da9e0(*(undefined4 *)((int)param_2 + 0x14));
                //     *(undefined4 *)((int)param_1 + 0x14) = uVar2;
                //   }
                // The recursive call returns a value that is stored in param_1->child. So the recursive call returns a pointer to the new child.
                // That means the function is a static function that takes a source pointer and returns a new copy.
                // But the function signature shows two parameters. Perhaps the first parameter is the destination, and the second is the source.
                // In the recursive call, only one argument is passed, which would be the source. That would mean the destination is implicit? No.
                // Given the ambiguity, we'll reconstruct the function as a static deep copy function:
                // static TreeNode* deepCopy(const TreeNode* source);
                // Then the recursive call would be: deepCopy(other.child);
                // And the function would allocate and copy. But the function currently takes two parameters.
                // The decompiler might have misidentified the calling convention. Let's assume the function is a copy constructor with an implicit 'this'.
                // Then the recursive call should be: new (newChild) TreeNode(*other.child);
                // But the decompiler shows only one argument. This is likely a decompilation bug.
                // For the reconstruction, we'll write it as a copy constructor with placement new.
                // We'll include a comment explaining the decompilation issue.
                // We'll use a helper function to avoid confusion.
                // Actually, the simplest is to assume the function is a static function that takes a source and returns a new copy.
                // But the function returns undefined8* and takes two parameters. The first parameter is the destination? 
                // Let's look at the beginning: *(undefined4 *)((int)param_1 + 0x14) = 0; // set child to null
                // Then it copies fields from param_2 to param_1. So param_1 is the destination, param_2 is the source.
                // So it's a copy assignment or copy constructor that takes a destination pointer as first argument.
                // That would be a static function: void copyNode(TreeNode* dest, const TreeNode* src);
                // Then the recursive call would be: copyNode(newChild, other.child);
                // But the decompiled code shows only one argument: FUN_004da9e0(other.child);
                // That is missing the destination. Possibly the destination is the return value of the allocation, which is stored in iVar1.
                // The code does: uVar2 = FUN_004da9e0(*(undefined4 *)((int)param_2 + 0x14));
                // Then stores uVar2 in param_1->child. So the recursive call returns a pointer to the new child.
                // That means the function takes a source and returns a new copy. So it's a factory function.
                // But the function also takes a destination? No, it returns a new pointer.
                // So the function is: TreeNode* copyNode(const TreeNode* src);
                // Then the recursive call is: copyNode(other.child);
                // And the allocation is done inside the function? But the allocation is done before the recursive call.
                // Actually, the allocation is done in the caller, not inside the recursive call.
                // So the function is not allocating; it's just copying into a pre-allocated buffer.
                // That means the function is: void copyNode(TreeNode* dest, const TreeNode* src);
                // And the recursive call should be: copyNode(newChild, other.child);
                // But the decompiled code shows only one argument. This is likely a decompilation error where the first argument (newChild) is omitted because it's the return value of the allocation? No.
                // Given the time, I'll reconstruct the function as a static deep copy function that takes a source and returns a new copy, with allocation done inside.
                // But the allocation is done outside. So I'll assume the function is a copy constructor that takes a source reference and the 'this' pointer is the destination.
                // Then the recursive call should be: newChild->TreeNode(*other.child);
                // But the decompiled code shows the recursive call with only one argument. I'll assume it's a bug and write it as:
                // newChild = new TreeNode(*other.child);
                // That would allocate again, but the allocation is already done. So it's wrong.
                // I'll write it as placement new: ::new (newChild) TreeNode(*other.child);
                // That matches the intent: allocate memory, then construct the object in place.
                // The decompiled code shows the allocation first, then the recursive call. So we'll do that.
                // We'll also need to handle the case where allocation fails.
                // For the reconstruction, we'll use a helper function or just show the logic.
                // I'll write it as:
                // TreeNode* newChild = (TreeNode*)operator new(0x18);
                // if (newChild) {
                //     new (newChild) TreeNode(*other.child); // placement new
                // }
                // But that would call the copy constructor again, which is fine.
                // However, the decompiled code shows the recursive call returning a value that is stored. That value is the new child pointer.
                // In placement new, the expression returns the pointer. So it's consistent.
                // So we'll write:
                // child = new (newChild) TreeNode(*other.child);
                // But that's not valid because placement new returns the pointer. Actually, placement new returns the pointer passed to it.
                // So we can do: child = new (newChild) TreeNode(*other.child);
                // That would set child to newChild, which is the same pointer.
                // The decompiled code stores the return value of the recursive call. In placement new, the return value is the pointer.
                // So we can write: child = new (newChild) TreeNode(*other.child);
                // But the recursive call is the copy constructor, which doesn't return anything. So it's not.
                // I think the function is actually a static function that returns a pointer to the new copy.
                // Given the confusion, I'll reconstruct the function as a static helper:
                // static TreeNode* deepCopy(const TreeNode* src);
                // Then the code becomes:
                // child = deepCopy(other.child);
                // And deepCopy allocates and copies.
                // But the function we are reconstructing is the copy constructor itself.
                // To avoid complexity, I'll assume the function is a copy constructor and the recursive call is a static function.
                // I'll define a static function deepCopyNode that does the allocation and copy.
                // But the decompiled code shows the same function being called recursively.
                // So I'll write the function as a static function that takes a source and returns a new copy.
                // Then the copy constructor would call that static function.
                // However, the function signature shows two parameters. I'll change the signature to match the decompiled code.
                // Given the time, I'll produce a reconstruction that matches the decompiled code as closely as possible, with comments.
                // I'll name the function "TreeNode::copyFrom" or "TreeNode::deepCopy".
                // I'll use the following reconstruction:
                // TreeNode* TreeNode::deepCopy(const TreeNode* source) {
                //     TreeNode* dest = (TreeNode*)operator new(0x18);
                //     if (dest) {
                //         dest->field_0x00 = source->field_0x00;
                //         ... etc.
                //         if (source->child) {
                //             dest->child = deepCopy(source->child);
                //         } else {
                //             dest->child = nullptr;
                //         }
                //     }
                //     return dest;
                // }
                // But the decompiled code shows the function taking two parameters and returning the first parameter.
                // So it's more like a copy assignment that returns the destination.
                // I'll go with that: it's a copy assignment operator that returns *this.
                // Then the recursive call would be: this->child = new TreeNode(*source->child);
                // But the decompiled code shows allocation and then recursive call with only one argument.
                // I'll assume the recursive call is actually: this->child = new TreeNode(*source->child);
                // And the allocation is done inside the new expression.
                // So the code would be:
                // if (source->child) {
                //     this->child = new TreeNode(*source->child);
                // } else {
                //     this->child = nullptr;
                // }
                // That matches the pattern: allocate (via new), then call copy constructor.
                // The decompiled code shows the allocation separately, but that's because the decompiler doesn't understand operator new.
                // So I'll reconstruct it as a copy constructor that uses new.
                // I'll write:
                // TreeNode(const TreeNode& other) {
                //     field_0x00 = other.field_0x00;
                //     field_0x08 = other.field_0x08;
                //     field_0x0A = other.field_0x0A;
                //     field_0x0C = other.field_0x0C;
                //     field_0x10 = other.field_0x10;
                //     if (other.child) {
                //         child = new TreeNode(*other.child);
                //     } else {
                //         child = nullptr;
                //     }
                // }
                // That is clean and matches the intent.
                // The decompiled code's allocation and recursive call are just the implementation of new.
                // So I'll go with that.
                // The function at 0x009c8e50 is likely operator new.
                // I'll include a comment.
            }
        }
    }
};

// Note: The decompiled code shows a recursive call with only one argument, which is likely a decompilation artifact.
// The actual C++ code would use operator new and placement new or a simple new expression.
// We assume the function is a copy constructor that uses new to allocate child nodes.
// The function at 0x009c8e50 is likely operator new (size 0x18).
// The function returns param_1 (this) after copying.

// To match the decompiled code exactly, we could write a static helper, but the above is more idiomatic.
// We'll output the copy constructor as above.

// However, the decompiled code shows the function returning undefined8* (which is this), so it's a copy constructor that returns this? No, copy constructors don't return anything. It might be an assignment operator that returns *this.
// The function sets child to 0 initially, then copies fields, then if source has child, it allocates and copies.
// That is typical of a copy assignment operator.
// But the function does not check for self-assignment. It could be a copy constructor.
// Since it sets child to 0 at the beginning, it's likely a copy constructor (initializing a new object).
// In a copy assignment, you would need to delete existing child first.
// So it's a copy constructor.
// We'll name it TreeNode(const TreeNode& other).

// Final reconstruction:

TreeNode::TreeNode(const TreeNode& other) {
    // Initialize child to null
    child = nullptr;

    // Copy all fields except child
    field_0x00 = other.field_0x00;
    field_0x08 = other.field_0x08;
    field_0x0A = other.field_0x0A;
    field_0x0C = other.field_0x0C;
    field_0x10 = other.field_0x10;

    // Deep copy child if present
    if (other.child != nullptr) {
        // Allocate new node (size 0x18) via operator new (FUN_009c8e50)
        // Then recursively copy the child node
        child = new TreeNode(*other.child);
    }
}

// Note: The decompiled code shows the allocation and recursive call separately, but that's due to how the decompiler handles operator new.
// The actual code uses the new operator, which internally calls FUN_009c8e50 and then the copy constructor.
// The function returns this (implicitly for copy constructor).// FUNC_NAME: TreeNode::TreeNode (copy constructor)
// Address: 0x004da9e0
// Role: Deep copy of a tree node structure (0x18 bytes) with recursive child copy.
// Structure layout (offsets):
// +0x00: uint64_t (8 bytes) - likely a pointer or 64-bit value
// +0x08: uint16_t (2 bytes) - short
// +0x0A: uint8_t  (1 byte) - byte
// +0x0C: uint32_t (4 bytes) - int
// +0x10: uint32_t (4 bytes) - int
// +0x14: TreeNode* child (4 bytes) - pointer to child node

class TreeNode {
public:
    /* +0x00 */ uint64_t field_0x00;
    /* +0x08 */ uint16_t field_0x08;
    /* +0x0A */ uint8_t  field_0x0A;
    /* +0x0C */ uint32_t field_0x0C;
    /* +0x10 */ uint32_t field_0x10;
    /* +0x14 */ TreeNode* child;

    // Copy constructor (deep copy)
    // __thiscall: param_1 = this, param_2 = source
    TreeNode(const TreeNode& other) {
        // Initialize child to null
        child = nullptr;

        // Copy all fields except child
        field_0x00 = other.field_0x00;
        field_0x08 = other.field_0x08;
        field_0x0A = other.field_0x0A;
        field_0x0C = other.field_0x0C;
        field_0x10 = other.field_0x10;

        // Deep copy child if present
        if (other.child != nullptr) {
            // Allocate new node (size 0x18) via operator new (FUN_009c8e50)
            // Then recursively copy the child node
            child = new TreeNode(*other.child);
        }
    }
};

// Note: The decompiled code shows the allocation and recursive call separately, but that's due to how the decompiler handles operator new.
// The actual code uses the new operator, which internally calls FUN_009c8e50 and then the copy constructor.
// The function returns this (implicitly for copy constructor).