#include "GFXAPI.h"

#include <utils.h>
#include <renderer.h>

#include <stdlib.h>
#include <stdio.h>

#include <assert.h>
#define static_assert _Static_assert

static GLenum MapGFXTypesGL(GFX_TYPES types) {
	switch (types)
	{
	case GFX_FLOAT:			return GL_FLOAT;
	case GFX_INT:			return GL_INT;
	case GFX_UNSIGNED_INT:	return GL_UNSIGNED_INT;
	case GFX_DOUBLE:		return GL_DOUBLE;
	default:				return GL_FLOAT;
	}
}
static unsigned int MapGFXTypesSize(GFX_TYPES types) {
	switch (types)
	{
	case GFX_FLOAT:			return sizeof(float);
	case GFX_INT:			return sizeof(int);
	case GFX_UNSIGNED_INT:	return sizeof(unsigned int);
	case GFX_DOUBLE:		return sizeof(double);
	default:				return sizeof(float);
	}
}

//////////

///	VertexBuffer functions

/////////

VertexBuffer VertexBufferCreate(const void* data,int size) {
	
	VertexBuffer buffer = {
		.renderer_id = 0,
		.size = size,
	};

	GLCALL(glGenBuffers(1, &buffer.renderer_id));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer.renderer_id));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, buffer.size, data, GL_STATIC_DRAW));

	return buffer;
}

void VertexBufferDestroy(VertexBuffer buffer) {
	GLCALL(glDeleteBuffers(1, &buffer.renderer_id));
}

void VertexBufferBind(VertexBuffer buffer) {
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer.renderer_id));
}

void VertexBufferUnbind() {
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}


//////////

///	IndexBuffer functions

/////////
IndexBuffer IndexBufferCreate(const unsigned int* data, unsigned int count) {
	static_assert(sizeof(GLuint) == sizeof(unsigned int), "Unsigend int size doesnt equal GLuint");

	IndexBuffer buffer = {
		.renderer_id = 0,
		.count = count,
	};
	GLCALL(glGenBuffers(1, &buffer.renderer_id));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.renderer_id));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.count * sizeof(unsigned int), data, GL_STATIC_DRAW));

	return buffer;
}

void IndexBufferBind(IndexBuffer buffer) {
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.renderer_id));
}

void IndexBufferUnbind() {
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBufferDestroy(IndexBuffer buffer) {
	GLCALL(glDeleteBuffers(1, &buffer.renderer_id));
}

//////////

///	VertexLayout functions

/////////
#define INITIAL_VERTEX_LAYOUT_CAP 40

VertexLayout VertexLayoutCreate() {
	VertexLayout layout = {
		.attribs = 0,
		.attribs_capacity = 0,
		.attribs_count = 0,
		.stride = 0,
	};

	layout.attribs = malloc(INITIAL_VERTEX_LAYOUT_CAP * sizeof(VertexAttrib));
	if (layout.attribs == NULL) {
		fprintf(stderr, "Error : Couldn't create VertexLayout\n");
		return layout;
	}

	layout.attribs_capacity = INITIAL_VERTEX_LAYOUT_CAP;
	return layout;
}

void VertexLayoutPush(VertexLayout* layout_ptr, GFX_TYPES type,unsigned int count, bool normalized) {
	// Resize layout if full
	if (layout_ptr->attribs_count == layout_ptr->attribs_capacity) {
		VertexAttrib* new_attribs_memory = (VertexAttrib*)realloc(layout_ptr->attribs, layout_ptr->attribs_capacity * 2 * sizeof(VertexAttrib));
		if (new_attribs_memory == NULL) {
			fprintf(stderr, "Couldn't allocate more memory for VertexLayout");
			return;
		}

		layout_ptr->attribs_capacity *= 2;
		layout_ptr->attribs = new_attribs_memory;
	}

	// the actual push
	VertexAttrib attrib = {
		.index = layout_ptr->attribs_count,
		.count = count,
		.type = type,
		.normalized = normalized,
		.offset = layout_ptr->stride
	};

	layout_ptr->stride += attrib.count * MapGFXTypesSize(attrib.type);
	layout_ptr->attribs[layout_ptr->attribs_count++] = attrib;
	return;
}

void VertexLayoutDelete(VertexLayout* layout) {
	if (layout->attribs != NULL) {
		free(layout->attribs);
		layout->attribs = NULL;
	}

	layout->attribs_capacity = 0;
	layout->attribs_count = 0;
	layout->stride = 0;
}

VertexArray VertexArrayCreate() {
	VertexArray vao = {
		.renderer_id = 0,
	};

	GLCALL(glGenVertexArrays(1, &vao.renderer_id));
	GLCALL(glBindVertexArray(vao.renderer_id));

	return vao;
}

void VertexArrayBind(VertexArray vao) {
	GLCALL(glBindVertexArray(vao.renderer_id));
}

void VertexArrayUnbind(VertexArray vao) {
	GLCALL(glBindVertexArray(0));
}

void VertexArrayApplyLayout(VertexArray vao, VertexLayout* layout) {
	GLCALL(glBindVertexArray(vao.renderer_id));
	for (int i = 0; i < layout->attribs_count; i++) {
		GLCALL(glEnableVertexAttribArray(layout->attribs[i].index));
		GLCALL(glVertexAttribPointer(layout->attribs[i].index, layout->attribs[i].count, MapGFXTypesGL(layout->attribs[i].type), layout->attribs[i].normalized, layout->stride, (void*)layout->attribs[i].offset));
	}
}


//////////

///	Shader functions

/////////


Shader ShaderCreate(const char* vertex_path, const char* fragment_path) {

	Shader shader = {
		.vertex_source = NULL,
		.fragment_source = NULL,
	};

	char* vertex_shader = read_file_string(vertex_path);
	char* fragment_shader = read_file_string(fragment_path);

	if (vertex_path == NULL || fragment_shader == NULL)
	{
		fprintf(stderr, "Couldn't create Shader Program");
		return shader;
	}

	unsigned int program = 0;
	GLCALL(program = glCreateProgram());

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	const char* vs_src[] = { vertex_shader };
	glShaderSource(vs, 1, vs_src, NULL);
	glCompileShader(vs);

	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fs_src[] = { fragment_shader };
	glShaderSource(fs, 1, fs_src, NULL);
	glCompileShader(fs);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	
	shader.fragment_source = fragment_shader;
	shader.vertex_source = vertex_shader;
	shader.renderer_id = program;
	
	return shader;
}

void ShaderUse(Shader shader) {
	GLCALL(glUseProgram(shader.renderer_id));
	return;
}
