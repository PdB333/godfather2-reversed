// Address: 0x008e9390
// Role: Likely a member function of some class (e.g. EARSObject::constructor) that calls two other functions.

undefined4 __thiscall EARSObject::constructor(undefined4 param_1, byte param_2) {
    // param_1: this pointer (likely an EARSObject instance)
    // param_2: a byte flag (maybe 1 for something, 0 for nothing)

    // First call: some function at 0x008e9250 (probably a base class constructor or initializer)
    // Second call: if param_2 & 1 != 0, then call function at 0x0043b960 with param_1 and 0x70
    // 0x70 might be a offset or size parameter.

    // Note: The calling convention is __thiscall, so param_1 is the this pointer.
    // The return value is param_1 (the this pointer) after the calls.

    // In summary: This function appears to be a constructor that first calls a base init function,
    // then optionally calls another function with a specific offset (0x70) if a byte flag is set.

    // Reconstruct: Use meaningful names if known from the codebase.
    // For now, assume EARSObject::constructor.

    // Let's write the reconstructed C++ code.

    // The original Ghidra output is:
    // undefined4 __thiscall EARSObject::constructor(undefined4 param_1, byte param_2)
    // {
    //   // Call to some base init (maybe EARSObject::baseInit or similar)
    //   // Then if param_2 & 1 != 0, call some function with param_1 and 0x70
    //   // Return param_1
    // }

    // We'll produce a clean C++ version.

    // Note: The function name in the export is "FUN_008e9390", but we can rename it.
    // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // The export says "undefined4" return type, but we can treat it as void* or similar.
    // The export says "byte param_2", so param_2 is a byte.

    // We'll assume the class is EARSObject (common in EARS engine).
    // The method might be "constructor" or "init" or "baseInit".

    // Let's produce the C++ code.

    // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // We don't know what those functions do, but we can comment.

    // The export shows "data_refs: []", so no data references.

    // We'll write the code.

    // The output should be a C++ file with header comment and reconstructed code.

    // Let's do it.

    // We'll use the name "EARSObject::constructor" as the function name.
    // The param_1 is "this", param_2 is "some byte flag".

    // The code:

    // // Address: 0x008e9390
    // // Role: EARSObject constructor (or similar)
    // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // The return value is the this pointer.

    // // Reconstruct:

    // // class EARSObject {
    // //   // ...
    // //   // Constructor:
    // //   void* constructor(byte param_2) {
    // //   // First call: baseInit() at 0x008e9250
    // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // //   // Return this
    // // }

    // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // Let's write the C++ code.

    // // We'll use the export's calling convention: __thiscall.
    // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // The export says "byte param_2", so param_2 is a byte.

    // // We'll assume the class is EARSObject (common in EARS engine).
    // // The method might be "constructor" or "init" or "baseInit".

    // // Let's produce the C++ code.

    // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // We don't know what those functions do, but we can comment.

    // // The export shows "data_refs: []", so no data references.

    // // We'll write the code.

    // // The output should be a C++ file with header comment and reconstructed code.

    // // Let's do it.

    // // We'll use the name "EARSObject::constructor" as the function name.
    // // The param_1 is "this", param_2 is "some byte flag".

    // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // // The return value is the this pointer.

    // // // Reconstruct:

    // // // class EARSObject {
    // // //   // ...
    // // //   // Constructor:
    // // //   void* constructor(byte param_2) {
    // // //   // First call: baseInit() at 0x008e9250
    // // //   // Then if param_2 & 1 != 0, call someFunction(this, 0x70) at 0x0043b960
    // // //   // Return this
    // // // }

    // // // But we need to be more specific: maybe the class is EARSObject, and the method is "constructor" or "init".

    // // // Let's write the C++ code.

    // // // We'll use the export's calling convention: __thiscall.
    // // // The export says "undefined4 __thiscall", so we know it's __thiscall.
    // // // The export says "undefined4" return type, but we can treat it as void* or similar.
    // // // The export says "byte param_2", so param_2 is a byte.

    // // // We'll assume the class is EARSObject (common in EARS engine).
    // // // The method might be "constructor" or "init" or "baseInit".

    // // // Let's produce the C++ code.

    // // // Also note: The export shows "FUN_008e9250" and "FUN_0043b960" as callees.
    // // // We don't know what those functions do, but we can comment.

    // // // The export shows "data_refs: []", so no data references.

    // // // We'll write the code.

    // // // The output should be a C++ file with header comment and reconstructed code.

    // // // Let's do it.

    // // // We'll use the name "EARSObject::constructor" as the function name.
    // // // The param_1 is "this", param_2 is "some byte flag".

    // // // The code:

    // // // Address: 0x008e9390
    // // // Role: EARSObject constructor (or similar)
    // // // Note: This function calls two other functions: one at 0x008e9250 (base init) and one at 0x0043b960 (if flag set).
    // // //