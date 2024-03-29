#pragma once

typedef int            gboolean;
typedef int            gint;
typedef unsigned int   guint;
typedef short          gshort;
typedef unsigned short gushort;
typedef long           glong;
typedef unsigned long  gulong;
typedef void* gpointer;
typedef const void* gconstpointer;
typedef char           gchar;
typedef unsigned char  guchar;

typedef int8_t              gint8;
typedef uint8_t             guint8;
typedef int16_t             gint16;
typedef uint16_t            guint16;
typedef int32_t             gint32;
typedef uint32_t            guint32;
typedef int64_t             gint64;
typedef uint64_t            guint64;
typedef float               gfloat;
typedef double              gdouble;
typedef uint16_t            gunichar2;

typedef guint32 mono_array_size_t;
typedef gint32 mono_array_lower_bound_t;

#define MONO_ZERO_LEN_ARRAY 1

#if defined(_MSC_VER) && defined(PLATFORM_IPHONE_XCOMP)
#   define USE_UINT8_BIT_FIELD(type, field) guint8 field 
#else
#   define USE_UINT8_BIT_FIELD(type, field) type field
#endif

struct MonoDomain;
struct MonoAssembly;
struct MonoImage;

struct MonoMethodSignature;
struct MonoMethodDesc;
struct MonoClassField;
struct MonoProperty;
struct MonoEvent;
struct MonoThreadsSync;
struct MonoThread;
struct MonoRuntimeGenericContext;
struct MonoMarshalType;
struct MonoGenericClass;
struct MonoGenericContainer;
struct MonoClassRuntimeInfo;
struct MonoClassExt;
struct MonoArrayType;
struct MonoGenericParam;
typedef int MonoTypeEnum;

struct MonoCustomMod;
struct MonoClass;
struct MonoType;
struct MonoMethod;
struct MonoVTable;

struct MonoCustomMod {
	unsigned int required : 1;
	unsigned int token : 31;
};

struct MonoType {
	union {
		MonoClass* klass; /* for VALUETYPE and CLASS */
		MonoType* type;   /* for PTR */
		MonoArrayType* array; /* for ARRAY */
		MonoMethodSignature* method;
		MonoGenericParam* generic_param; /* for VAR and MVAR */
		MonoGenericClass* generic_class; /* for GENERICINST */
	} data;
	unsigned int attrs : 16; /* param attributes or field flags */
	MonoTypeEnum type : 8;
	unsigned int num_mods : 6;  /* max 64 modifiers follow at the end */
	unsigned int byref : 1;
	unsigned int pinned : 1;  /* valid when included in a local var signature */
	MonoCustomMod modifiers[MONO_ZERO_LEN_ARRAY]; /* this may grow */
};

struct MonoClass {
	/* element class for arrays and enum basetype for enums */
	MonoClass* element_class;
	/* used for subtype checks */
	MonoClass* cast_class;

	/* for fast subtype checks */
	MonoClass** supertypes;
	guint16     idepth;

	/* array dimension */
	guint8     rank;

	int        instance_size; /* object instance size */

	USE_UINT8_BIT_FIELD(guint, inited          : 1);
	/* We use init_pending to detect cyclic calls to mono_class_init */
	USE_UINT8_BIT_FIELD(guint, init_pending    : 1);

	/* A class contains static and non static data. Static data can be
	* of the same type as the class itselfs, but it does not influence
	* the instance size of the class. To avoid cyclic calls to
	* mono_class_init (from mono_class_instance_size ()) we first
	* initialise all non static fields. After that we set size_inited
	* to 1, because we know the instance size now. After that we
	* initialise all static fields.
	*/
	USE_UINT8_BIT_FIELD(guint, size_inited     : 1);
	USE_UINT8_BIT_FIELD(guint, valuetype       : 1); /* derives from System.ValueType */
	USE_UINT8_BIT_FIELD(guint, enumtype        : 1); /* derives from System.Enum */
	USE_UINT8_BIT_FIELD(guint, blittable       : 1); /* class is blittable */
	USE_UINT8_BIT_FIELD(guint, unicode         : 1); /* class uses unicode char when marshalled */
	USE_UINT8_BIT_FIELD(guint, wastypebuilder  : 1); /* class was created at runtime from a TypeBuilder */
	/* next byte */
	guint8 min_align;
	/* next byte */
	USE_UINT8_BIT_FIELD(guint, packing_size    : 4);
	USE_UINT8_BIT_FIELD(guint, has_unity_native_intptr : 1); // This class has a IntPtr that points to a native class with an asset reference
	/* still 3 bits free */
	/* next byte */
	USE_UINT8_BIT_FIELD(guint, ghcimpl         : 1); /* class has its own GetHashCode impl */
	USE_UINT8_BIT_FIELD(guint, has_finalize    : 1); /* class has its own Finalize impl */
	USE_UINT8_BIT_FIELD(guint, marshalbyref    : 1); /* class is a MarshalByRefObject */
	USE_UINT8_BIT_FIELD(guint, contextbound    : 1); /* class is a ContextBoundObject */
	USE_UINT8_BIT_FIELD(guint, delegate        : 1); /* class is a Delegate */
	USE_UINT8_BIT_FIELD(guint, gc_descr_inited : 1); /* gc_descr is initialized */
	USE_UINT8_BIT_FIELD(guint, has_cctor       : 1); /* class has a cctor */
	USE_UINT8_BIT_FIELD(guint, has_references  : 1); /* it has GC-tracked references in the instance */
	/* next byte */
	USE_UINT8_BIT_FIELD(guint, has_static_refs : 1); /* it has static fields that are GC-tracked */
	USE_UINT8_BIT_FIELD(guint, no_special_static_fields : 1); /* has no thread/context static fields */
	/* directly or indirectly derives from ComImport attributed class.
	* this means we need to create a proxy for instances of this class
	* for COM Interop. set this flag on loading so all we need is a quick check
	* during object creation rather than having to traverse supertypes
	*/
	USE_UINT8_BIT_FIELD(guint, is_com_object   : 1);
	USE_UINT8_BIT_FIELD(guint, nested_classes_inited : 1); /* Whenever nested_class is initialized */
	USE_UINT8_BIT_FIELD(guint, interfaces_inited : 1); /* interfaces is initialized */
	USE_UINT8_BIT_FIELD(guint, simd_type       : 1); /* class is a simd intrinsic type */
	USE_UINT8_BIT_FIELD(guint, is_generic      : 1); /* class is a generic type definition */
	USE_UINT8_BIT_FIELD(guint, is_inflated     : 1); /* class is a generic instance */

	guint8     exception_type;	/* MONO_EXCEPTION_* */

	/* Additional information about the exception */
	/* Stored as property MONO_CLASS_PROP_EXCEPTION_DATA */
	//void       *exception_data;

	MonoClass* parent;
	MonoClass* nested_in;

	MonoImage* image;
	const char* name;
	const char* name_space;

	guint32    type_token;
	int        vtable_size; /* number of slots */

	guint16     interface_count;
	guint16     interface_id;        /* unique inderface id (for interfaces) */
	guint16     max_interface_id;

	guint16     interface_offsets_count;
	MonoClass** interfaces_packed;
	guint16* interface_offsets_packed;
	guint8* interface_bitmap;

	MonoClass** interfaces;

	union {
		int class_size; /* size of area for static fields */
		int element_size; /* for array types */
		int generic_param_token; /* for generic param types, both var and mvar */
	} sizes;

	/*
	* From the TypeDef table
	*/
	guint32    flags;
	struct {
		guint32 first, count;
	} field, method;

	/* loaded on demand */
	MonoMarshalType* marshal_info;

	/*
	* Field information: Type and location from object base
	*/
	MonoClassField* fields;

	MonoMethod** methods;

	/* used as the type of the this argument and when passing the arg by value */
	MonoType this_arg;
	MonoType byval_arg;

	MonoGenericClass* generic_class;
	MonoGenericContainer* generic_container;

	void* reflection_info;

	void* gc_descr;

	MonoClassRuntimeInfo* runtime_info;

	/* next element in the class_cache hash list (in MonoImage) */
	MonoClass* next_class_cache;

	/* Generic vtable. Initialized by a call to mono_class_setup_vtable () */
	MonoMethod** vtable;

	/* Rarely used fields of classes */
	MonoClassExt* ext;
};

struct MonoVTable {
	MonoClass* klass;
	/*
	* According to comments in gc_gcj.h, this should be the second word in
	* the vtable.
	*/
	void* gc_descr;
	MonoDomain* domain;  /* each object/vtable belongs to exactly one domain */
	gpointer    data; /* to store static class data */
	gpointer    type; /* System.Type type for klass */
	guint8* interface_bitmap;
	guint16     max_interface_id;
	guint8      rank;
	USE_UINT8_BIT_FIELD(guint, remote      : 1); /* class is remotely activated */
	USE_UINT8_BIT_FIELD(guint, initialized : 1); /* cctor has been run */
	USE_UINT8_BIT_FIELD(guint, init_failed : 1); /* cctor execution failed */
	guint32     imt_collisions_bitmap;
	MonoRuntimeGenericContext* runtime_generic_context;
	/* do not add any fields after vtable, the structure is dynamically extended */
	gpointer    vtable[MONO_ZERO_LEN_ARRAY];
};


struct MonoObject {
	MonoVTable* vtable;
	MonoThreadsSync* synchronisation;
};
struct MonoString {
	MonoObject object;
	gint32 length;
	gunichar2 chars[MONO_ZERO_LEN_ARRAY];
};

struct MonoArrayBounds {
	mono_array_size_t length;
	mono_array_lower_bound_t lower_bound;
};

struct MonoArray {
	MonoObject obj;
	/* bounds is NULL for szarrays */
	MonoArrayBounds* bounds;
	/* total number of elements of the array */
	mono_array_size_t max_length;
	double vector[MONO_ZERO_LEN_ARRAY];
};

struct MonoMethod {
	guint16 flags;  /* method flags */
	guint16 iflags; /* method implementation flags */
	guint32 token;
	MonoClass* klass;
	MonoMethodSignature* signature;
	/* name is useful mostly for debugging */
	const char* name;
	/* this is used by the inlining algorithm */
	unsigned int inline_info : 1;
	unsigned int inline_failure : 1;
	unsigned int wrapper_type : 5;
	unsigned int string_ctor : 1;
	unsigned int save_lmf : 1;
	unsigned int dynamic : 1; /* created & destroyed during runtime */
	unsigned int is_generic : 1; /* whenever this is a generic method definition */
	unsigned int is_inflated : 1; /* whether we're a MonoMethodInflated */
	unsigned int skip_visibility : 1; /* whenever to skip JIT visibility checks */
	unsigned int verification_success : 1; /* whether this method has been verified successfully.*/
	/* TODO we MUST get rid of this field, it's an ugly hack nobody is proud of. */
	unsigned int is_mb_open : 1;		/* This is the fully open instantiation of a generic method_builder. Worse than is_tb_open, but it's temporary */
	signed int slot : 17;

	/*
	* If is_generic is TRUE, the generic_container is stored in image->property_hash,
	* using the key MONO_METHOD_PROP_GENERIC_CONTAINER.
	*/
};

typedef void MonoMethodHeader;

struct MonoMethodNormal {
	MonoMethod method;
	MonoMethodHeader* header;
};

struct MonoMethodPInvoke {
	MonoMethod method;
	gpointer addr;
	/* add marshal info */
	guint16 piflags;  /* pinvoke flags */
	guint16 implmap_idx;  /* index into IMPLMAP */
};


struct MonoGenericInst {
	guint id;			/* unique ID for debugging */
	guint type_argc : 22;	/* number of type arguments */
	guint is_open : 1;	/* if this is an open type */
	MonoType* type_argv[MONO_ZERO_LEN_ARRAY];
};

struct MonoGenericContext {
	MonoGenericInst* class_inst;
	MonoGenericInst* method_inst;
};

struct MonoMethodInflated {
	union {
		MonoMethod method;
		MonoMethodNormal normal;
		MonoMethodPInvoke pinvoke;
	} method;
	MonoMethod* declaring;		/* the generic method definition. */
	MonoGenericContext context;	/* The current instantiation */
};
