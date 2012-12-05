//
//  main.c
//  dynamicArrayTest
//
//  Created by Green2, David on 12/5/12.
//  Copyright (c) 2012 digital-worlds. All rights reserved.
//

#include <stdio.h>
#include "IntArray.h"
#include "StringArray.h"

int main(int argc, const char * argv[])
{
	// Test dynamic arrays of integers
	// Create an int array
	IntArrayRef intArray = IntArrayCreate(10);
	
	// Add some values to it
	for (int i = 0; i < 30; i++) {
		IntArrayAddValue(intArray, i);
	}
	
	// Report the added values
	printf("Added 30 values\n");
	for (int i = 0; i < IntArrayValuesCount(intArray); i++) {
		printf("Value at %d: %d\n", i, IntArrayValueAtIndex(intArray, i));
	}
	
	// Add some more values
	for (int i = 0; i < 20; i++) {
		IntArrayAddValue(intArray, i);
	}
	
	// Report the new, larger set of values
	printf("Added 20 values\n");
	for (int i = 0; i < IntArrayValuesCount(intArray); i++) {
		printf("Value at %d: %d\n", i, IntArrayValueAtIndex(intArray, i));
	}
	
	// Clear the values
	IntArrayClearValues(intArray);
	printf("Cleared array");
	
	// Add all new values, and more of them
	for (int i = 0; i < 100; i++) {
		IntArrayAddValue(intArray, i * 2);
	}
	
	// Report the new set of values
	printf("Added 100 values\n");
	const int *rawArray = IntArrayRawArray(intArray);
	for (int i = 0; i < IntArrayValuesCount(intArray); i++) {
		printf("Value at %d: %d\n", i, rawArray[i]);
	}
	
	// Make sure we clean everything up
	IntArrayDealloc(intArray);
	
	// Test dynamic arrays of C strings
	StringArrayRef stringArray = StringArrayCreate(8);
	
	// populate it with a few strings
	for (int i = 0; i < 8; i++) {
		char * string = NULL;
		asprintf(&string, "Sample string %d", i);
		StringArrayAddValue(stringArray, string);
	}
	
	// Show that the array contains the generated strings
	for (int i = 0; i < StringArrayValuesCount(stringArray); i++) {
		printf("Sample string %d: \"%s\"\n", i, StringArrayValueAtIndex(stringArray, i));
	}
	// Since we allocated the temporary strings, we need to free them prior to deallocating the array, otherwise we'll leak
	for (int i = 0; i < StringArrayValuesCount(stringArray); i++) {
		free(StringArrayValueAtIndex(stringArray, i));
	}
	StringArrayDealloc(stringArray);
	
    return 0;
}

