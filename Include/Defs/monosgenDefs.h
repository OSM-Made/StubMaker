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

typedef struct _GPtrArray GPtrArray;
struct _GPtrArray {
	gpointer* pdata;
	guint len;
};

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
struct MonoCustomMod;
struct MonoClass;
struct MonoType;
struct MonoMethod;
struct MonoVTable;

typedef enum
{
	MONO_TYPE_END = 0x00,       /* End of List */
	MONO_TYPE_VOID = 0x01,
	MONO_TYPE_BOOLEAN = 0x02,
	MONO_TYPE_CHAR = 0x03,
	MONO_TYPE_I1 = 0x04,
	MONO_TYPE_U1 = 0x05,
	MONO_TYPE_I2 = 0x06,
	MONO_TYPE_U2 = 0x07,
	MONO_TYPE_I4 = 0x08,
	MONO_TYPE_U4 = 0x09,
	MONO_TYPE_I8 = 0x0a,
	MONO_TYPE_U8 = 0x0b,
	MONO_TYPE_R4 = 0x0c,
	MONO_TYPE_R8 = 0x0d,
	MONO_TYPE_STRING = 0x0e,
	MONO_TYPE_PTR = 0x0f,       /* arg: <type> token */
	MONO_TYPE_BYREF = 0x10,       /* arg: <type> token */
	MONO_TYPE_VALUETYPE = 0x11,       /* arg: <type> token */
	MONO_TYPE_CLASS = 0x12,       /* arg: <type> token */
	MONO_TYPE_VAR = 0x13,	   /* number */
	MONO_TYPE_ARRAY = 0x14,       /* type, rank, boundsCount, bound1, loCount, lo1 */
	MONO_TYPE_GENERICINST = 0x15,	   /* <type> <type-arg-count> <type-1> \x{2026} <type-n> */
	MONO_TYPE_TYPEDBYREF = 0x16,
	MONO_TYPE_I = 0x18,
	MONO_TYPE_U = 0x19,
	MONO_TYPE_FNPTR = 0x1b,	      /* arg: full method signature */
	MONO_TYPE_OBJECT = 0x1c,
	MONO_TYPE_SZARRAY = 0x1d,       /* 0-based one-dim-array */
	MONO_TYPE_MVAR = 0x1e,       /* number */
	MONO_TYPE_CMOD_REQD = 0x1f,       /* arg: typedef or typeref token */
	MONO_TYPE_CMOD_OPT = 0x20,       /* optional arg: typedef or typref token */
	MONO_TYPE_INTERNAL = 0x21,       /* CLR internal type */

	MONO_TYPE_MODIFIER = 0x40,       /* Or with the following types */
	MONO_TYPE_SENTINEL = 0x41,       /* Sentinel for varargs method signature */
	MONO_TYPE_PINNED = 0x45,       /* Local var that points to pinned object */

	MONO_TYPE_ENUM = 0x55        /* an enumeration */
} MonoTypeEnum;

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

typedef struct _MonoException MonoException;

struct _MonoException {
	MonoObject object;
	MonoType* type;
	char* message;
	MonoString* toString;
	MonoException* inner_ex;
	char* help_link;
	char* class_name;
	char* stack_trace;
	char* remote_stack_trace;
	int remote_stack_index;
	gpointer dynamic_methods;
	MonoObject* source;
	gpointer hresult;
	gpointer* data;
	MonoMethod* exception_ctor;
	gpointer unity_extended_info;
};

#define MONO_PUBLIC_KEY_TOKEN_LENGTH	17

struct MonoAssemblyName
{
	const char* name;
	const char* culture;
	const char* hash_value;
	const guint8* public_key;
	guchar public_key_token[MONO_PUBLIC_KEY_TOKEN_LENGTH];
	guint32 hash_alg;
	guint32 hash_len;
	guint32 flags;
	guint16 major, minor, build, revision;
};

/* This corresponds to System.Type */
struct MonoReflectionType 
{
	MonoObject object;
	MonoType* type;
};

struct MonoReflectionMethod 
{
	MonoObject object;
	MonoMethod* method;
	MonoString* name;
	MonoReflectionType* reftype;
};

struct MonoDelegate 
{
	MonoObject object;
	/* The compiled code of the target method */
	gpointer method_ptr;
	/* The invoke code */
	gpointer invoke_impl;
	MonoObject* target;
	MonoMethod* method;
	gpointer delegate_trampoline;
	/* Extra argument passed to the target method in llvmonly mode */
	gpointer extra_arg;
	/*
	 * If non-NULL, this points to a memory location which stores the address of
	 * the compiled code of the method, or NULL if it is not yet compiled.
	 */
	guint8** method_code;
	gpointer interp_method;
	/* Interp method that is executed when invoking the delegate */
	gpointer interp_invoke_impl;
	MonoReflectionMethod* method_info;
	MonoReflectionMethod* original_method_info;
	MonoObject* data;
	bool method_is_virtual;
};

typedef struct 
{
	guint32  flags;
	gint32   exvar_offset;
	gpointer try_start;
	gpointer try_end;
	gpointer handler_start;
	/*
	 * For LLVM compiled code, this is the index of the il clause
	 * associated with this handler.
	 */
	int clause_index;
	uint32_t try_offset;
	uint32_t try_len;
	uint32_t handler_offset;
	uint32_t handler_len;
	union {
		MonoClass* catch_class;
		gpointer filter;
		gpointer handler_end;
	} data;
} MonoJitExceptionInfo;

struct MonoJitInfo 
{
	/* NOTE: These first two elements (method and
	   next_jit_code_hash) must be in the same order and at the
	   same offset as in RuntimeMethod, because of the jit_code_hash
	   internal hash table in MonoDomain. */
	union {
		MonoMethod* method;
		MonoImage* image;
		void* aot_info;
		void* tramp_info;
	} d;
	union {
		MonoJitInfo* next_jit_code_hash;
		MonoJitInfo* next_tombstone;
	} n;
	gpointer    code_start;
	guint32     unwind_info;
	int         code_size;
	guint32     num_clauses : 15;
	/* Whenever the code is domain neutral or 'shared' */
	gboolean    domain_neutral : 1;
	gboolean    has_generic_jit_info : 1;
	gboolean    has_try_block_holes : 1;
	gboolean    has_arch_eh_info : 1;
	gboolean    has_thunk_info : 1;
	gboolean    has_unwind_info : 1;
	gboolean    from_aot : 1;
	gboolean    from_llvm : 1;
	gboolean    dbg_attrs_inited : 1;
	gboolean    dbg_hidden : 1;
	/* Whenever this jit info was loaded in async context */
	gboolean    async : 1;
	gboolean    dbg_step_through : 1;
	gboolean    dbg_non_user_code : 1;
	/*
	 * Whenever this jit info refers to a trampoline.
	 * d.tramp_info contains additional data in this case.
	 */
	gboolean    is_trampoline : 1;
	/* Whenever this jit info refers to an interpreter method */
	gboolean    is_interp : 1;

	/* FIXME: Embed this after the structure later*/
	gpointer    gc_info; /* Currently only used by SGen */

	gpointer    seq_points;

	MonoJitExceptionInfo clauses[MONO_ZERO_LEN_ARRAY];
	/* There is an optional MonoGenericJitInfo after the clauses */
	/* There is an optional MonoTryBlockHoleTableJitInfo after MonoGenericJitInfo clauses*/
	/* There is an optional MonoArchEHJitInfo after MonoTryBlockHoleTableJitInfo */
	/* There is an optional MonoThunkJitInfo after MonoArchEHJitInfo */
};
