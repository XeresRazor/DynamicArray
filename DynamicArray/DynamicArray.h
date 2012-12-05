//
//  DynamicArray.h
//  dynamicArrayTest
//
//  Created by Green2, David on 12/5/12.
//  Copyright (c) 2012 digital-worlds. All rights reserved.
//

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#ifndef dynamicArrayTest_DynamicArray_h
#define dynamicArrayTest_DynamicArray_h

// Dynamic arrays for a specifc type are defined by calling DynamicArrayCreate(ArrayName, MemberType)
// This will generate the approriate structs, types, and functions for a custom dynamic array
// Before calling DynamicArrayCreate, you must create the opaque reference type you wish to use with a line such as:
// typedef struct ArrayName * ArrayNameRef;
// struct ArrayName will have been generated at build time by the DynamicArrayCreate macro

// The following methods are created:
// ArrayNameRef ArrayNameCreate(uint32_t capacity)
// MemberType const * ArrayNameRawArray(ArrayNameRef arrayRef)
// void ArrayNameAddValue(ArrayNameRef arrayRef, MemberType value)
// int ArrayNameValuesCount(ArrayNameRef arrayRef)
// MemberType ArrayNameValueAtIndex(ArrayNameRef arrayRef, uint32_t index)
// void ArrayNameClearValues(ArrayNameRef arrayRef)
// void ArrayNameDealloc(ArrayNameRef arrayRef)

#if !defined(MAX)
#define MAX(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __b : __a; })
#endif

// Generates the arrays data structure
#define _DASourceStruct(arrayName, memberType) struct arrayName {\
uint32_t count;\
uint32_t capacity;\
memberType *values;\
};

// Generates the arrays resize function
#define _DASourceResize(arrayName, memberType) static inline void arrayName##Resize(arrayName##Ref array, uint32_t newCapacity) {\
array->capacity = MAX(newCapacity, array->count);\
array->values = realloc(array->values, array->capacity * sizeof(memberType));\
}

// Generates the create array function
#define _DAHeaderCreate(arrayName, memberType) arrayName##Ref arrayName##Create(uint32_t capacity);
#define _DASourceCreate(arrayName, memberType) arrayName##Ref arrayName##Create(uint32_t capacity) { \
arrayName##Ref _newArray_ = malloc(sizeof(struct arrayName));\
_newArray_->count = 0;\
_newArray_->values = NULL;\
arrayName##Resize(_newArray_, MAX(capacity, 16u));\
return _newArray_;\
}

// Generates the raw array accessor function
#define _DAHeaderRawArray(arrayName, memberType) memberType const * arrayName##RawArray(arrayName##Ref array);
#define _DASourceRawArray(arrayName, memberType) memberType const * arrayName##RawArray(arrayName##Ref array) {\
return array->values;\
}

// Generates the add value function
#define _DAHeaderAddValue(arrayName, memberType) void arrayName##AddValue(arrayName##Ref array, memberType value);
#define _DASourceAddValue(arrayName, memberType) void arrayName##AddValue(arrayName##Ref array, memberType value) {\
if (array->count >= array->capacity) {\
arrayName##Resize(array, array->capacity * 2);\
}\
array->values[array->count++] = value;\
}

// Generates the value count function
#define _DAHeaderValuesCount(arrayName, memberType) int arrayName##ValuesCount(arrayName##Ref array);
#define _DASourceValuesCount(arrayName, memberType) int arrayName##ValuesCount(arrayName##Ref array) {\
return array->count;\
}

// Generates the value accessor function
#define _DAHeaderValueAtIndex(arrayName, memberType) memberType arrayName##ValueAtIndex(arrayName##Ref array, uint32_t index);
#define _DASourceValueAtIndex(arrayName, memberType) memberType arrayName##ValueAtIndex(arrayName##Ref array, uint32_t index) {\
assert(index < array->count);\
return array->values[index];\
}

// Generates the clear values function
#define _DAHeaderClearValues(arrayName, memberType) void arrayName##ClearValues(arrayName##Ref array);
#define _DASourceClearValues(arrayName, memberType) void arrayName##ClearValues(arrayName##Ref array) {\
array->count = 0;\
arrayName##Resize(array, 16);\
}

// Generates the dealloc function
#define _DAHeaderDealloc(arrayName, memberType) void arrayName##Dealloc(arrayName##Ref array);
#define _DASourceDealloc(arrayName, memberType) void arrayName##Dealloc(arrayName##Ref array) {\
if (array) {\
if (array->values) {\
free(array->values);\
array->values = NULL;\
}\
free(array);\
}\
}



// Generates the header file contents
#define DynamicArrayCreateHeader(arrayName, memberType) \
typedef struct arrayName * arrayName##Ref;\
_DAHeaderCreate(arrayName, memberType)\
_DAHeaderRawArray(arrayName, memberType)\
_DAHeaderAddValue(arrayName, memberType)\
_DAHeaderValuesCount(arrayName, memberType)\
_DAHeaderValueAtIndex(arrayName, memberType)\
_DAHeaderClearValues(arrayName, memberType)\
_DAHeaderDealloc(arrayName, memberType)

#define DynamicArrayCreateSource(arrayName, memberType) \
_DASourceStruct(arrayName, memberType)\
_DASourceResize(arrayName, memberType)\
_DASourceCreate(arrayName, memberType)\
_DASourceRawArray(arrayName, memberType)\
_DASourceAddValue(arrayName, memberType)\
_DASourceValuesCount(arrayName, memberType)\
_DASourceValueAtIndex(arrayName, memberType)\
_DASourceClearValues(arrayName, memberType)\
_DASourceDealloc(arrayName, memberType)


#endif
