#ifndef COBJECTS_H_
#define COBJECTS_H_

#include <stdio.h>

#define BEG_DEFINE_CLASS(T) \
typedef struct T##_Instance_struct *T;\
typedef struct T##_Class_struct {

#define END_DEFINE_CLASS(T) \
} T##Class;

#define BEG_DEFINE_INSTANCE(T, ...) \
extern T new##T(__VA_ARGS__);\
extern void delete##T(T); \
typedef struct T##_Instance_struct { \
	T##Class *clazz;

#define END_DEFINE_INSTANCE(T) \
} T##Instance; 

#define EXTENDS(T) T##_METHODS
#define IS_INSTANCE_OF(T) T##_ATTRIBUTES

#define DEFINE_BASE_TYPE(T, ...) \
BEG_DEFINE_CLASS(T) \
T##_METHODS \
END_DEFINE_CLASS(T) \
BEG_DEFINE_INSTANCE(T, __VA_ARGS__) \
T##_ATTRIBUTES \
END_DEFINE_INSTANCE(T)

#define DEFINE_EXTENDED_TYPE(T, E, ...) \
BEG_DEFINE_CLASS(T) EXTENDS(E) \
T##_METHODS \
END_DEFINE_CLASS(T) \
BEG_DEFINE_INSTANCE(T, __VA_ARGS__) IS_INSTANCE_OF(E) \
T##_ATTRIBUTES \
END_DEFINE_INSTANCE(T)

#ifndef NDEBUG
#define printDebug(msg, ...) \
	printf("In file %s, in function %s, at line %d\n\t", __FILE__, __func__, __LINE__); \
	printf(msg, __VA_ARGS__); \
	printf("\n");

#define assertEquals(x, y) \
	if ((x) != (y)) { \
		printDebug("Assert! Values are not Equal: %s != %s", #x, #y) \
		return; \
		}

#define assertFalse(x) \
	if ((x)) { \
		printDebug("Assert! Value is true: %s", #x) \
		return; \
		}

#define assertNotNull(x) \
	if ((x) == NULL) { \
		printDebug("Assert! Pointer is NULL: %s", #x) \
		return; \
		}

#define assertStringEquals(x, y) \
	if (strcmp((x), (y)) == 0) { \
		printDebug("Assert! Strings are not Equal: %s, %s", #x, #y) \
		return; \
		}
#else
#define printDebug(msg, ...)
#define assertEquals(x, y)
#define assertFalse(x)
#define assertNotNull(x)
#define assertStringEquals(x, y)
#endif

#define DECLARE_TEST(x) void x##Test(void *args, void *ret);

#define BEG_SUITE(x) void (*x[])(void*, void*) = {

#define ADD_TEST(x) x##Test,

#define END_SUITE(x) }; \
	extern void *args[sizeof(x)]; \
	extern void *ret[sizeof(x)];

#define RUN_SUITE(x) \
		void run_tests() { \
		for (int i = 0, i < sizeof(x), i++) \
			x[i](x##args[i],x##ret[i]); } 

void run_tests();

#endif /* COBJECTS_H_ */
