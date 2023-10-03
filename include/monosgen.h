#pragma once 

#include "Defs/monosgenDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

	MonoDomain* mono_get_root_domain();
	MonoArray* mono_array_new(MonoDomain* domain, MonoClass* eclass, uintptr_t n);
	char* mono_array_addr_with_size(MonoArray* array, int size, uintptr_t idx);
	uintptr_t mono_array_length(MonoArray* array);
	MonoImage* mono_assembly_get_image(MonoAssembly* assembly);
	MonoClass* mono_class_from_name(MonoImage* image, const char* name_space, const char* name);
	MonoMethod* mono_class_get_method_from_name(MonoClass* klass, const char* name, int param_count);
	MonoMethod* mono_class_get_methods(MonoClass* klass, void** iter);
	MonoClassField* mono_class_get_field_from_name(MonoClass* klass, const char* name);
	MonoProperty* mono_class_get_property_from_name(MonoClass* klass, const char* name);
	const char* mono_method_get_name(MonoMethod* method);
	gpointer mono_aot_get_method(MonoDomain* domain, MonoMethod* method);
	MonoMethod* mono_property_get_get_method(MonoProperty* prop);
	MonoMethod* mono_property_get_set_method(MonoProperty* prop);
	void mono_field_set_value(MonoObject* obj, MonoClassField* field, void* value);
	void mono_field_get_value(MonoObject* obj, MonoClassField* field, void* value);
	MonoClass* mono_get_byte_class();
	MonoAssembly* mono_domain_assembly_open(MonoDomain* domain, const char* name);
	MonoObject* mono_runtime_invoke(MonoMethod* method, void* obj, void** params, MonoObject** exc);
	MonoString* mono_string_new(MonoDomain* domain, const char* text);
	char* mono_string_to_utf8(MonoString* string_obj);
	void* mono_object_unbox(MonoObject* obj);
	MonoObject* mono_object_new(MonoDomain* domain, MonoClass* Klass);
	void mono_runtime_object_init(MonoObject* this_obj);
	MonoThread* mono_thread_attach(MonoDomain* domain);
	MonoThread* mono_thread_current(void);
	MonoThread* mono_thread_get_main(void);
	void mono_thread_set_main(MonoThread* thread);
	void mono_thread_detach();
	MonoString* mono_object_to_string(MonoObject* obj, MonoObject** exc);

	MonoClass* mono_object_get_class(MonoObject* obj);
	const char* mono_class_get_name(MonoClass* klass);

#define mono_array_addr(array,type,index) ((type*)mono_array_addr_with_size ((array), sizeof (type), (index)))
#define mono_array_get(array,type,index) ( *(type*)mono_array_addr ((array), type, (index)) ) 
#define mono_array_set(array,type,index,value)	\
	do {	\
		type *__p = (type *) mono_array_addr ((array), type, (index));	\
		*__p = (value);	\
	} while (0)

#ifdef __cplusplus
}
#endif