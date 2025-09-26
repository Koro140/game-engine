#pragma once

#include <stdbool.h>

typedef enum GFX_TYPES {
	GFX_FLOAT,
	GFX_INT,
	GFX_UNSIGNED_INT,
	GFX_DOUBLE,
}GFX_TYPES;

typedef struct VertexBuffer {
	unsigned int renderer_id;
	int size;
}VertexBuffer;

typedef struct IndexBuffer {
	unsigned int renderer_id;
	int count;
}IndexBuffer;

typedef struct VertexAttrib {
	unsigned int index;
	unsigned int count; // elements count .. used in glVertexAttribPointer as size
	GFX_TYPES type;
	bool normalized;
	unsigned int offset;	
}VertexAttrib;

typedef struct VertexLayout {
	VertexAttrib* attribs;
	unsigned int attribs_count;
	unsigned int attribs_capacity;
	unsigned int stride;
}VertexLayout;

typedef struct VertexArray {
	unsigned int renderer_id;
}VertexArray;

typedef struct Shader {
	unsigned int renderer_id;
	char* vertex_source;
	char* fragment_source;
}Shader;

// Vertex Buffer functions
VertexBuffer VertexBufferCreate(const void* data, int size);
void VertexBufferBind(VertexBuffer buffer);
void VertexBufferUnbind();
void VertexBufferDestroy(VertexBuffer buffer);

// Index Buffer functions
IndexBuffer IndexBufferCreate(const unsigned int* data,unsigned int count);
void IndexBufferBind(IndexBuffer buffer);
void IndexBufferUnbind();
void IndexBufferDestroy(IndexBuffer buffer);

// Vertex Layout functions
VertexLayout VertexLayoutCreate();
void VertexLayoutPush(VertexLayout* layout_ptr, GFX_TYPES type, unsigned int count, bool normalized);
void VertexLayoutDelete(VertexLayout* layout);

// Vertex Arrays Functions
VertexArray VertexArrayCreate();
void VertexArrayBind(VertexArray vao);
void VertexArrayUnbind(VertexArray vao);
void VertexArrayApplyLayout(VertexArray vao, VertexLayout* layout);

// Sahder Functions
Shader ShaderCreate(const char* vertex_path, const char* fragment_path);
void ShaderUse(Shader shader);