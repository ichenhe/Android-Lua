#ifndef LUA_JNI_H
#define LUA_JNI_H

#define LUASTATE_CLASS "org/keplerproject/luajava/LuaState"
#define CPTR_CLASS_PATH "Lorg/keplerproject/luajava/CPtr;"
#define OBJECT_CLASS_PATH "Ljava/lang/Object;"
#define STRING_CLASS_PATH "Ljava/lang/String;"


#include <jni.h>
#include "log.h"

void jni_luajavaOpen (JNIEnv * env , jobject jobj , jobject cptr , jint stateId );
jobject jni_getObjectFromUserdata  (JNIEnv * env , jobject jobj , jobject cptr , jint index );
jboolean jni_isObject (JNIEnv * env , jobject jobj , jobject cptr , jint index );
void jni_pushJavaObject  (JNIEnv * env , jobject jobj , jobject cptr , jobject obj );
void jni_pushJavaFunction  (JNIEnv * env , jobject jobj , jobject cptr , jobject obj );
jboolean jni_isJavaFunction  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jobject jni_open  (JNIEnv * env , jobject jobj);
void jni_openBase  (JNIEnv * env , jobject jobj , jobject cptr);
void jni_openTable  (JNIEnv * env , jobject jobj , jobject cptr);
void jni_openIo  (JNIEnv * env , jobject jobj , jobject cptr);
void jni_openOs  (JNIEnv * env , jobject jobj , jobject cptr);
void jni_openString  (JNIEnv * env , jobject jobj , jobject cptr);
void jni_openMath  (JNIEnv * env , jobject jobj , jobject cptr);
void jni_openDebug  (JNIEnv * env, jobject jobj , jobject cptr);
void jni_openPackage  (JNIEnv * env, jobject jobj , jobject cptr);
void jni_openLibs  (JNIEnv * env, jobject jobj , jobject cptr);
void jni_close  (JNIEnv * env , jobject jobj , jobject cptr);
jobject jni_newthread  (JNIEnv * env , jobject jobj , jobject cptr);
jint jni_getTop  (JNIEnv * env , jobject jobj , jobject cptr);
void jni_setTop  (JNIEnv * env , jobject jobj , jobject cptr , jint top);
void jni_pushValue  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
void jni_remove  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
void jni_insert  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
void jni_replace  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_checkStack  (JNIEnv * env , jobject jobj , jobject cptr , jint sz);
void jni_xmove  (JNIEnv * env , jobject jobj , jobject from , jobject to , jint n);
jint jni_isNumber  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_isString  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_isFunction  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_isCFunction  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_isUserdata  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_isTable  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_isBoolean  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_isNil  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_isNone  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_isNoneOrNil  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_type  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jstring jni_typeName  (JNIEnv * env , jobject jobj , jobject cptr , jint tp);
jint jni_equal  (JNIEnv * env , jobject jobj , jobject cptr , jint idx1 , jint idx2);
jint jni_rawequal  (JNIEnv * env , jobject jobj , jobject cptr , jint idx1 , jint idx2);
jint jni_lessthan  (JNIEnv * env , jobject jobj , jobject cptr , jint idx1 , jint idx2);
jdouble jni_toNumber  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_toInteger  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_toBoolean  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jstring jni_toString  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_strlen  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_objlen  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jobject jni_toThread  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
void jni_pushNil  (JNIEnv * env , jobject jobj , jobject cptr);
void jni_pushNumber  (JNIEnv * env , jobject jobj , jobject cptr , jdouble number);
void jni_pushInteger  (JNIEnv * env , jobject jobj , jobject cptr , jint i);
void jni_pushString  (JNIEnv * env , jobject jobj , jobject cptr , jstring str);
void jni_pushString2  (JNIEnv * env , jobject jobj , jobject cptr , jbyteArray bytes , jint n);
void jni_pushBoolean  (JNIEnv * env , jobject jobj , jobject cptr , jint jbool);
void jni_getTable  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
void jni_getField  (JNIEnv * env , jobject jobj , jobject cptr , jint idx , jstring k);
void jni_rawGet  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
void jni_rawGetI  (JNIEnv * env , jobject jobj , jobject cptr , jint idx, jint n);
void jni_createTable  (JNIEnv * env , jobject jobj , jobject cptr , jint narr , jint nrec);
void jni_newTable  (JNIEnv * env , jobject jobj , jobject cptr);
jint jni_getMetaTable  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
void jni_setTable  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
void jni_setField  (JNIEnv * env , jobject jobj , jobject cptr , jint idx , jstring k);
void jni_rawSet  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
void jni_rawSetI  (JNIEnv * env , jobject jobj , jobject cptr , jint idx, jint n);
jint jni_setMetaTable  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
void jni_call  (JNIEnv * env , jobject jobj , jobject cptr , jint nArgs , jint nResults);
jint jni_pcall  (JNIEnv * env , jobject jobj , jobject cptr , jint nArgs , jint nResults , jint errFunc);
jint jni_yield  (JNIEnv * env , jobject jobj , jobject cptr , jint nResults);
jint jni_resume  (JNIEnv * env , jobject jobj , jobject cptr, jobject cptrFrom, jint nArgs);
jint jni_status  (JNIEnv * env , jobject jobj , jobject cptr);
jint jni_gc  (JNIEnv * env , jobject jobj , jobject cptr , jint what , jint data);
jint jni_next  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
jint jni_error  (JNIEnv * env , jobject jobj , jobject cptr);
void jni_concat  (JNIEnv * env , jobject jobj , jobject cptr , jint n);
void jni_pop  (JNIEnv * env , jobject jobj , jobject cptr , jint idx);
void jni_setGlobal  (JNIEnv * env , jobject jobj , jobject cptr , jstring name);
void jni_getGlobal  (JNIEnv * env , jobject jobj , jobject cptr , jstring name);
jint jni_LdoFile  (JNIEnv * env , jobject jobj , jobject cptr , jstring fileName);
jint jni_LdoString  (JNIEnv * env , jobject jobj , jobject cptr , jstring str);
jint jni_LgetMetaField  (JNIEnv * env , jobject jobj , jobject cptr , jint obj , jstring e);
jint jni_LcallMeta  (JNIEnv * env , jobject jobj , jobject cptr , jint obj , jstring e);
jint jni_LargError  (JNIEnv * env , jobject jobj , jobject cptr , jint numArg , jstring extraMsg);
jstring jni_LcheckString  (JNIEnv * env , jobject jobj , jobject cptr , jint numArg);
jstring jni_LoptString  (JNIEnv * env , jobject jobj , jobject cptr , jint numArg , jstring def);
jdouble jni_LcheckNumber  (JNIEnv * env , jobject jobj , jobject cptr , jint numArg);
jdouble jni_LoptNumber  (JNIEnv * env , jobject jobj , jobject cptr , jint numArg , jdouble def);
jint jni_LcheckInteger  (JNIEnv * env , jobject jobj , jobject cptr , jint numArg);
jint jni_LoptInteger  (JNIEnv * env , jobject jobj , jobject cptr , jint numArg , jint def);
void jni_LcheckStack  (JNIEnv * env , jobject jobj , jobject cptr , jint sz , jstring msg);
void jni_LcheckType  (JNIEnv * env , jobject jobj , jobject cptr , jint nArg , jint t);
void jni_LcheckAny  (JNIEnv * env , jobject jobj , jobject cptr , jint nArg);
jint jni_LnewMetatable  (JNIEnv * env , jobject jobj , jobject cptr , jstring tName);
void jni_LgetMetatable  (JNIEnv * env , jobject jobj , jobject cptr , jstring tName);
void jni_Lwhere  (JNIEnv * env , jobject jobj , jobject cptr , jint lvl);
jint jni_Lref  (JNIEnv * env , jobject jobj , jobject cptr , jint t);
void jni_LunRef  (JNIEnv * env , jobject jobj , jobject cptr , jint t , jint ref);
jint jni_LloadFile  (JNIEnv * env , jobject jobj , jobject cptr , jstring fileName);
jint jni_LloadBuffer  (JNIEnv * env , jobject jobj , jobject cptr , jbyteArray buff , jlong sz , jstring n);
jint jni_LloadString  (JNIEnv * env , jobject jobj , jobject cptr , jstring str);
jstring jni_Lgsub  (JNIEnv * env , jobject jobj , jobject cptr , jstring s , jstring p , jstring r);
jint jni_registryIndex(JNIEnv * env);

static JNINativeMethod jni_methods[] = {
		{"_luajavaOpen", "("CPTR_CLASS_PATH"I)V", (void*)jni_luajavaOpen},
		{"_getObjectFromUserdata", "("CPTR_CLASS_PATH"I)"OBJECT_CLASS_PATH, (void*)jni_getObjectFromUserdata},
		{"_isObject", "("CPTR_CLASS_PATH"I)Z", (void*)jni_isObject},
		{"_pushJavaObject", "("CPTR_CLASS_PATH""OBJECT_CLASS_PATH")V", (void*)jni_pushJavaObject},
		{"_pushJavaFunction", "("CPTR_CLASS_PATH""OBJECT_CLASS_PATH")V", (void*)jni_pushJavaFunction},
		{"_isJavaFunction", "("CPTR_CLASS_PATH"I)Z", (void*)jni_isJavaFunction},
		{"_open", "()"OBJECT_CLASS_PATH, (void*)jni_open},
		{"_openBase", "("CPTR_CLASS_PATH")V", (void*)jni_openBase},
		{"_openTable", "("CPTR_CLASS_PATH")V", (void*)jni_openTable},
		{"_openIo", "("CPTR_CLASS_PATH")V", (void*)jni_openIo},
		{"_openOs", "("CPTR_CLASS_PATH")V", (void*)jni_openOs},
		{"_openString", "("CPTR_CLASS_PATH")V", (void*)jni_openString},
		{"_openMath", "("CPTR_CLASS_PATH")V", (void*)jni_openMath},
		{"_openDebug", "("CPTR_CLASS_PATH")V", (void*)jni_openDebug},
		{"_openPackage", "("CPTR_CLASS_PATH")V", (void*)jni_openPackage},
		{"_openLibs", "("CPTR_CLASS_PATH")V", (void*)jni_openLibs},
		{"_close", "("CPTR_CLASS_PATH")V", (void*)jni_close},
		{"_newthread", "("CPTR_CLASS_PATH")"OBJECT_CLASS_PATH, (void*)jni_newthread},
		{"_getTop", "("CPTR_CLASS_PATH")I", (void*)jni_getTop},
		{"_setTop", "("CPTR_CLASS_PATH"I)V", (void*)jni_setTop},
		{"_pushValue", "("CPTR_CLASS_PATH"I)V", (void*)jni_pushValue},
		{"_remove", "("CPTR_CLASS_PATH"I)V", (void*)jni_remove},
		{"_insert", "("CPTR_CLASS_PATH"I)V", (void*)jni_insert},
		{"_replace", "("CPTR_CLASS_PATH"I)V", (void*)jni_replace},
		{"_checkStack", "("CPTR_CLASS_PATH"I)I", (void*)jni_checkStack},
		{"_xmove", "("CPTR_CLASS_PATH""CPTR_CLASS_PATH"I)V", (void*)jni_xmove},
		{"_isNumber", "("CPTR_CLASS_PATH"I)I", (void*)jni_isNumber},
		{"_isString", "("CPTR_CLASS_PATH"I)I", (void*)jni_isString},
		{"_isFunction", "("CPTR_CLASS_PATH"I)I", (void*)jni_isFunction},
		{"_isCFunction", "("CPTR_CLASS_PATH"I)I", (void*)jni_isCFunction},
		{"_isUserdata", "("CPTR_CLASS_PATH"I)I", (void*)jni_isUserdata},
		{"_isTable", "("CPTR_CLASS_PATH"I)I", (void*)jni_isTable},
		{"_isBoolean", "("CPTR_CLASS_PATH"I)I", (void*)jni_isBoolean},
		{"_isNil", "("CPTR_CLASS_PATH"I)I", (void*)jni_isNil},
		{"_isNone", "("CPTR_CLASS_PATH"I)I", (void*)jni_isNone},
		{"_isNoneOrNil", "("CPTR_CLASS_PATH"I)I", (void*)jni_isNoneOrNil},
		{"_type", "("CPTR_CLASS_PATH"I)I", (void*)jni_type},
		{"_typeName", "("CPTR_CLASS_PATH"I)"STRING_CLASS_PATH, (void*)jni_typeName},
		{"_equal", "("CPTR_CLASS_PATH"II)I", (void*)jni_equal},
		{"_rawequal", "("CPTR_CLASS_PATH"II)I", (void*)jni_rawequal},
		{"_lessthan", "("CPTR_CLASS_PATH"II)I", (void*)jni_lessthan},
		{"_toNumber", "("CPTR_CLASS_PATH"I)D", (void*)jni_toNumber},
		{"_toInteger", "("CPTR_CLASS_PATH"I)I", (void*)jni_toInteger},
		{"_toBoolean", "("CPTR_CLASS_PATH"I)I", (void*)jni_toBoolean},
		{"_toString", "("CPTR_CLASS_PATH"I)"STRING_CLASS_PATH, (void*)jni_toString},
		{"_strlen", "("CPTR_CLASS_PATH"I)I", (void*)jni_strlen},
		{"_objlen", "("CPTR_CLASS_PATH"I)I", (void*)jni_objlen},
		{"_toThread", "("CPTR_CLASS_PATH"I)"OBJECT_CLASS_PATH, (void*)jni_toThread},
		{"_pushNil", "("CPTR_CLASS_PATH")V", (void*)jni_pushNil},
		{"_pushNumber", "("CPTR_CLASS_PATH"D)V", (void*)jni_pushNumber},
		{"_pushInteger", "("CPTR_CLASS_PATH"I)V", (void*)jni_pushInteger},
		{"_pushString", "("CPTR_CLASS_PATH""STRING_CLASS_PATH")V", (void*)jni_pushString},
		{"_pushString2", "("CPTR_CLASS_PATH"[BI)V", (void*)jni_pushString2},
		{"_pushBoolean", "("CPTR_CLASS_PATH"I)V", (void*)jni_pushBoolean},
		{"_getTable", "("CPTR_CLASS_PATH"I)V", (void*)jni_getTable},
		{"_getField", "("CPTR_CLASS_PATH"I"STRING_CLASS_PATH")V", (void*)jni_getField},
		{"_rawGet", "("CPTR_CLASS_PATH"I)V", (void*)jni_rawGet},
		{"_rawGetI", "("CPTR_CLASS_PATH"II)V", (void*)jni_rawGetI},
		{"_createTable", "("CPTR_CLASS_PATH"II)V", (void*)jni_createTable},
		{"_newTable", "("CPTR_CLASS_PATH")V", (void*)jni_newTable},
		{"_getMetaTable", "("CPTR_CLASS_PATH"I)I", (void*)jni_getMetaTable},
		{"_setTable", "("CPTR_CLASS_PATH"I)V", (void*)jni_setTable},
		{"_setField", "("CPTR_CLASS_PATH"I"STRING_CLASS_PATH")V", (void*)jni_setField},
		{"_rawSet", "("CPTR_CLASS_PATH"I)V", (void*)jni_rawSet},
		{"_rawSetI", "("CPTR_CLASS_PATH"II)V", (void*)jni_rawSetI},
		{"_setMetaTable", "("CPTR_CLASS_PATH"I)I", (void*)jni_setMetaTable},
		{"_call", "("CPTR_CLASS_PATH"II)V", (void*)jni_call},
		{"_pcall", "("CPTR_CLASS_PATH"III)I", (void*)jni_pcall},
		{"_yield", "("CPTR_CLASS_PATH"I)I", (void*)jni_yield},
		{"_resume", "("CPTR_CLASS_PATH""CPTR_CLASS_PATH"I)I", (void*)jni_resume},
		{"_status", "("CPTR_CLASS_PATH")I", (void*)jni_status},
		{"_gc", "("CPTR_CLASS_PATH"II)I", (void*)jni_gc},
		{"_next", "("CPTR_CLASS_PATH"I)I", (void*)jni_next},
		{"_error", "("CPTR_CLASS_PATH")I", (void*)jni_error},
		{"_concat", "("CPTR_CLASS_PATH"I)V", (void*)jni_concat},
		{"_pop", "("CPTR_CLASS_PATH"I)V", (void*)jni_pop},
		{"_setGlobal", "("CPTR_CLASS_PATH""STRING_CLASS_PATH")V", (void*)jni_setGlobal},
		{"_getGlobal", "("CPTR_CLASS_PATH""STRING_CLASS_PATH")V", (void*)jni_getGlobal},
		{"_LdoFile", "("CPTR_CLASS_PATH""STRING_CLASS_PATH")I", (void*)jni_LdoFile},
		{"_LdoString", "("CPTR_CLASS_PATH""STRING_CLASS_PATH")I", (void*)jni_LdoString},
		{"_LgetMetaField", "("CPTR_CLASS_PATH"I"STRING_CLASS_PATH")I", (void*)jni_LgetMetaField},
		{"_LcallMeta", "("CPTR_CLASS_PATH"I"STRING_CLASS_PATH")I", (void*)jni_LcallMeta},
		{"_LargError", "("CPTR_CLASS_PATH"I"STRING_CLASS_PATH")I", (void*)jni_LargError},
		{"_LcheckString", "("CPTR_CLASS_PATH"I)"STRING_CLASS_PATH, (void*)jni_LcheckString},
		{"_LoptString", "("CPTR_CLASS_PATH"I"STRING_CLASS_PATH")"STRING_CLASS_PATH, (void*)jni_LoptString},
		{"_LcheckNumber", "("CPTR_CLASS_PATH"I)D", (void*)jni_LcheckNumber},
		{"_LoptNumber", "("CPTR_CLASS_PATH"ID)D", (void*)jni_LoptNumber},
		{"_LcheckInteger", "("CPTR_CLASS_PATH"I)I", (void*)jni_LcheckInteger},
		{"_LoptInteger", "("CPTR_CLASS_PATH"II)I", (void*)jni_LoptInteger},
		{"_LcheckStack", "("CPTR_CLASS_PATH"I"STRING_CLASS_PATH")V", (void*)jni_LcheckStack},
		{"_LcheckType", "("CPTR_CLASS_PATH"II)V", (void*)jni_LcheckType},
		{"_LcheckAny", "("CPTR_CLASS_PATH"I)V", (void*)jni_LcheckAny},
		{"_LnewMetatable", "("CPTR_CLASS_PATH""STRING_CLASS_PATH")I", (void*)jni_LnewMetatable},
		{"_LgetMetatable", "("CPTR_CLASS_PATH""STRING_CLASS_PATH")V", (void*)jni_LgetMetatable},
		{"_Lwhere", "("CPTR_CLASS_PATH"I)V", (void*)jni_Lwhere},
		{"_Lref", "("CPTR_CLASS_PATH"I)I", (void*)jni_Lref},
		{"_LunRef", "("CPTR_CLASS_PATH"II)V", (void*)jni_LunRef},
		{"_LloadFile", "("CPTR_CLASS_PATH""STRING_CLASS_PATH")I", (void*)jni_LloadFile},
		{"_LloadBuffer", "("CPTR_CLASS_PATH"[BJ"STRING_CLASS_PATH")I", (void*)jni_LloadBuffer},
		{"_LloadString", "("CPTR_CLASS_PATH""STRING_CLASS_PATH")I", (void*)jni_LloadString},
		{"_Lgsub", "("CPTR_CLASS_PATH""STRING_CLASS_PATH""STRING_CLASS_PATH""STRING_CLASS_PATH")"STRING_CLASS_PATH, (void*)jni_Lgsub},
		{"_registryIndex", "()I", (void*)jni_registryIndex},
};

#endif //LUA_JNI_H
