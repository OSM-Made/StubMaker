#pragma once

#include "Defs/monosgenDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

	// ============================================================================
	// Domain Functions
	// ============================================================================

	MonoDomain* mono_get_root_domain();
	MonoDomain* mono_domain_get(void);
	gboolean mono_domain_set(MonoDomain* domain, gboolean force);
	MonoDomain* mono_domain_create_appdomain(char* friendly_name, char* configuration_file);
	void mono_domain_unload(MonoDomain* domain);
	GPtrArray* mono_domain_get_assemblies(MonoDomain* domain, gboolean refonly);

	// ============================================================================
	// Assembly Functions
	// ============================================================================

	MonoAssembly* mono_assembly_open(const char* filename, void* status);
	MonoAssembly* mono_domain_assembly_open(MonoDomain* domain, const char* name);
	MonoImage* mono_assembly_get_image(MonoAssembly* assembly);
	const char* mono_image_get_name(MonoImage* image);
	MonoAssembly* mono_image_get_assembly(MonoImage* image);
	MonoAssemblyName* mono_assembly_get_name(MonoAssembly* assembly);
	const char* mono_assembly_name_get_name(MonoAssemblyName* aname);
	const char* mono_assembly_name_get_culture(MonoAssemblyName* aname);
	uint16_t mono_assembly_name_get_version(MonoAssemblyName* aname, uint16_t* minor, uint16_t* build, uint16_t* revision);

	// ============================================================================
	// Class Functions
	// ============================================================================

	MonoClass* mono_class_from_name(MonoImage* image, const char* name_space, const char* name);
	MonoClass* mono_class_from_mono_type(MonoType* type);
	const char* mono_class_get_name(MonoClass* klass);
	const char* mono_class_get_namespace(MonoClass* klass);
	MonoImage* mono_class_get_image(MonoClass* klass);
	MonoClass* mono_class_get_parent(MonoClass* klass);
	MonoClass* mono_class_get_element_class(MonoClass* klass);
	MonoClass* mono_class_get_nested_types(MonoClass* klass, gpointer* iter);
	MonoClass* mono_class_get_interfaces(MonoClass* klass, void** iter);
	guint32 mono_class_get_flags(MonoClass* klass);
	MonoVTable* mono_class_vtable(MonoDomain* domain, MonoClass* klass);
	MonoType* mono_class_get_type(MonoClass* klass);
	MonoType* mono_class_enum_basetype(MonoClass* klass);
	int32_t mono_class_value_size(MonoClass* klass, uint32_t* align);

	// Class checks
	gboolean mono_class_is_valuetype(MonoClass* klass);
	gboolean mono_class_is_enum(MonoClass* klass);
	gboolean mono_class_is_primitive(MonoClass* klass);
	gboolean mono_class_is_subclass_of(MonoClass* klass, MonoClass* klassc, gboolean check_interfaces);

	// Class member access
	MonoMethod* mono_class_get_method_from_name(MonoClass* klass, const char* name, int param_count);
	MonoMethod* mono_class_get_methods(MonoClass* klass, void** iter);
	MonoClassField* mono_class_get_field_from_name(MonoClass* klass, const char* name);
	MonoProperty* mono_class_get_property_from_name(MonoClass* klass, const char* name);

	// Special class getters
	MonoClass* mono_get_byte_class();

	// ============================================================================
	// Object Functions
	// ============================================================================

	MonoObject* mono_object_new(MonoDomain* domain, MonoClass* Klass);
	void mono_runtime_object_init(MonoObject* this_obj);
	MonoClass* mono_object_get_class(MonoObject* obj);
	MonoDomain* mono_object_get_domain(MonoObject* obj);
	unsigned int mono_object_get_size(MonoObject* obj);
	int mono_object_hash(MonoObject* obj);
	MonoObject* mono_object_clone(MonoObject* obj);
	MonoString* mono_object_to_string(MonoObject* obj, MonoObject** exc);

	// Boxing and unboxing
	MonoObject* mono_value_box(MonoDomain* domain, MonoClass* klass, void* val);
	void* mono_object_unbox(MonoObject* obj);

	// Type checking and casting
	MonoObject* mono_object_isinst(MonoObject* obj, MonoClass* klass);
	MonoObject* mono_object_castclass_mbyref(MonoObject* obj, MonoClass* klass);

	// GC handle functions
	uint32_t mono_gchandle_new(MonoObject* obj, gboolean pinned);
	MonoObject* mono_gchandle_get_target(uint32_t gchandle);
	void mono_gchandle_free(uint32_t gchandle);

	// ============================================================================
	// Method Functions
	// ============================================================================

	const char* mono_method_get_name(MonoMethod* method);
	MonoClass* mono_method_get_class(MonoMethod* method);
	MonoMethodSignature* mono_method_signature(MonoMethod* method);
	uint32_t mono_method_get_flags(MonoMethod* method, uint32_t* iflags);

	// Method invocation
	MonoObject* mono_runtime_invoke(MonoMethod* method, void* obj, void** params, MonoObject** exc);
	void* mono_compile_method(MonoMethod* method);
	gpointer mono_aot_get_method(MonoDomain* domain, MonoMethod* method);

	// Signature functions
	uint32_t mono_signature_get_param_count(MonoMethodSignature* sig);

	// ============================================================================
	// Property Functions
	// ============================================================================

	const char* mono_property_get_name(MonoProperty* prop);
	MonoClass* mono_property_get_parent(MonoProperty* prop);
	MonoMethod* mono_property_get_get_method(MonoProperty* prop);
	MonoMethod* mono_property_get_set_method(MonoProperty* prop);

	// ============================================================================
	// Field Functions
	// ============================================================================

	const char* mono_field_get_name(MonoClassField* field);
	MonoClass* mono_field_get_parent(MonoClassField* field);
	MonoType* mono_field_get_type(MonoClassField* field);
	uint32_t mono_field_get_offset(MonoClassField* field);
	uint32_t mono_field_get_flags(MonoClassField* field);

	// Instance field access
	void mono_field_get_value(MonoObject* obj, MonoClassField* field, void* value);
	void mono_field_set_value(MonoObject* obj, MonoClassField* field, void* value);

	// Static field access
	void mono_field_static_get_value(MonoVTable* vt, MonoClassField* field, void* value);
	void mono_field_static_set_value(MonoVTable* vt, MonoClassField* field, void* value);

	// ============================================================================
	// String Functions
	// ============================================================================

	MonoString* mono_string_new(MonoDomain* domain, const char* text);
	char* mono_string_to_utf8(MonoString* string_obj);
	int mono_string_length(MonoString* s);

	// ============================================================================
	// Array Functions
	// ============================================================================

	MonoArray* mono_array_new(MonoDomain* domain, MonoClass* eclass, uintptr_t n);
	uintptr_t mono_array_length(MonoArray* array);
	char* mono_array_addr_with_size(MonoArray* array, int size, uintptr_t idx);
	void mono_array_setref(MonoArray* array, uintptr_t index, MonoObject* object);

	// Array access macros
#define mono_array_addr(array,type,index) ((type*)mono_array_addr_with_size ((array), sizeof (type), (index)))
#define mono_array_get(array,type,index) ( *(type*)mono_array_addr ((array), type, (index)) )
#define mono_array_set(array,type,index,value)	\
	do {	\
		type *__p = (type *) mono_array_addr ((array), type, (index));	\
		*__p = (value);	\
	} while (0)

	// ============================================================================
	// Type Functions
	// ============================================================================

	char* mono_type_get_name(MonoType* type);
	int mono_type_get_type(MonoType* type);
	gboolean mono_type_is_byref(MonoType* type);
	gboolean mono_type_is_pointer(MonoType* type);

	// ============================================================================
	// Delegate Functions
	// ============================================================================

	MonoObject* mono_ftnptr_to_delegate(MonoClass* klass, gpointer ftn);
	MonoDelegate* mono_delegate_ctor(MonoObject* this_obj, MonoObject* target, gpointer addr);

	// ============================================================================
	// Thread Functions
	// ============================================================================

	MonoThread* mono_thread_attach(MonoDomain* domain);
	void mono_thread_detach(MonoThread* thread);
	MonoThread* mono_thread_current(void);
	MonoThread* mono_thread_get_main(void);
	void mono_thread_set_main(MonoThread* thread);

	// ============================================================================
	// Exception Functions
	// ============================================================================

	MonoImage* mono_get_corlib(void);
	MonoException* mono_exception_from_name_msg(MonoImage* image, const char* name_space, const char* name, const char* msg);
	void mono_raise_exception(MonoException* ex);

	// ============================================================================
	// Utility Functions
	// ============================================================================

	void mono_free(void* obj);

	MonoJitInfo* mono_jit_info_table_find(MonoDomain * domain, gpointer addr);
	
#ifdef __cplusplus
}
#endif
