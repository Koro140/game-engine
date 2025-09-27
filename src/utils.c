#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Read file into NULL-terminated string .. needs to be freed.
char* read_file_string(const char* file_path) {	
	FILE* file = fopen(file_path, "r");
	char* result = NULL;

	if (file == NULL) {
		fprintf(stderr, "Failed to open %s: %s\n", file_path, strerror(errno));
		return result;
	}
	char line[1024];

	int count = 0;
	int capacity = 1024;
	char* memory = (char*)malloc(capacity * sizeof(char));

	if (memory == NULL) {
		fprintf(stderr, "Couldn't allocate memory for string");
		return result;
	}

	while (fgets(line, 1024, file)) {
		int line_len = strlen(line);

		// Resizing string block
		if (count + line_len >= capacity - 1) {
			char* new_memory = (char*)realloc(memory, capacity * 2);
			if (new_memory == NULL) {
				fprintf(stderr, "Couldn't allocate more memory for string");
				free(memory);
				return result;
			}

			capacity *= 2;
			memory = new_memory;
		}

		// Actual string parsing / copying
		memcpy(memory + count, line, line_len);
		count += line_len;
	}
	memory[count] = '\0';
	result = memory;

	fclose(file);
	return result;
}
