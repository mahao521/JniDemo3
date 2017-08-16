
#include<stdio.h>
#include<stdlib.h>

#include "com_mahao_jnidemo2_bean_MyNative.h"

int compare(int *a, int *b);


//需要解决的问题

//1 :  解决Jint到jinString

//2 :  解决Jobject到JinString

/**
    obj --->  对象调用
	class ---> 静态方法，类的class文件
*/
JNIEXPORT jstring JNICALL Java_com_mahao_jnidemo2_bean_MyNative_accessCachString
(JNIEnv * env, jobject  obj) {

	//静态claa 只会创建一次；
	static jclass claa;
	if (claa == NULL) {

		printf("da ying l a --------\n");

		//第一种方式创建class
	//	claa = (*env)->FindClass(env, "com/mahao/jnidemo2/bean/MyNative");

		claa = (*env)->GetObjectClass(env, obj);
	}
	jmethodID methodId = (*env)->GetMethodID(env, claa, "getString", "()I");
	jthrowable throwable = (*env)->ExceptionOccurred(env);

	if (throwable != NULL) {

		(*env)->ExceptionDescribe(env);
		printf("Exception is occour\n");
	}

	//第二种方式获取object;
	jmethodID methoid = (*env)->GetMethodID(env, claa, "<init>", "()V");
	jobject object = (*env)->NewObject(env, claa, methoid);

	jint aa = (*env)->CallIntMethod(env, object, methodId);
	printf("call--- back from java aa = %d", aa);

	return NULL;
}


//int数组
JNIEXPORT void JNICALL Java_com_mahao_jnidemo2_bean_MyNative_getInArray
(JNIEnv *env , jobject obj , jintArray arr) {


	jboolean flag;
	jint* item = (*env)->GetIntArrayElements(env, arr, flag);
	if (item == NULL) {

		printf("not found the int array");
	}

	jint length = (*env)->GetArrayLength(env, arr);
	qsort(item, length, sizeof(jint), compare);

	//释放可能的内存
	//将数据写入内存中
	(*env)->ReleaseIntArrayElements(env, arr, item, JNI_COMMIT);
}

int compare(int *a, int *b) {

	return *a - *b;
}

//引用数组
JNIEXPORT jobjectArray JNICALL Java_com_mahao_jnidemo2_bean_MyNative_initStringArray
(JNIEnv * env, jobject object, jint aa) {

	//jclass claa  = (*env)->GetObjectClass(env, object);

	//构造数组
	jclass claz = (*env)->FindClass(env, "java/lang/string");
	jobjectArray objectArray = (*env)->NewObjectArray(env, aa, claz, object);

	//向数组赋值
	char* item_str;
	for (int i = 0; i < aa; i++) {

		item_str = malloc(sizeof(char)*100);
		sprintf(item_str, "wo shi %d", i);

		jstring str = (*env)->NewStringUTF(env, item_str);

		//引用数组
		(*env)->SetObjectArrayElement(env, objectArray, i, item_str);

		frre(item_str);
		item_str = NULL;
	}
	return objectArray;
}

//返回二维数组int[][];
JNIEXPORT jobjectArray JNICALL Java_com_mahao_jnidemo2_bean_MyNative_initInt2DArray
(JNIEnv *env, jobject obj, jint aa) {


	//生成一个二维数组 返回int[][];

	//1 :构造数组
	jint x = 5;
	jint y = 6;
	jclass clazz = (*env)->FindClass(env, "[I");

	if (clazz == NULL) {

		return NULL;
	}
	jobjectArray array = (*env)->NewObjectArray(env, x*y, clazz, obj);
	
	jint* tmp = (int*)malloc(sizeof(int)*x);
	for (int i = 0; i < x; i++) {

		jintArray intArr = (*env)->NewIntArray(env, y);

		for (int j = 0; j < y; j++) {

			tmp[j] = i + j;
		}
		(*env)->SetIntArrayRegion(env, intArr, 0, y, tmp);
		(*env)->SetObjectArrayElement(env, array, i, intArr);
		(*env)->DeleteLocalRef(env, intArr);
	}

	free(array);
	 return array;
}


//解析java中的二位数组
JNIEXPORT jint JNICALL Java_com_mahao_jnidemo2_bean_deal2Arr
(JNIEnv *env, jobject object, jobjectArray arr) {


	//博客地址
    //http://blog.csdn.net/gao1440156051/article/details/52026718


	//jint i = 3, j = 5;  //3
	jint aa[1024][1024];

	int size = (*env)->GetArrayLength(env, arr);

	//创建二维指针指向数组
	jint **bb = (int**)malloc(sizeof(int*)*size);

	for (int i = 0; i < size; i++) {

		//每一行的数组
		jarray horArr = (*env)->GetObjectArrayElement(env, arr, i);

		//每一行数组的长度
		int horNum =  (*env)->GetArrayLength(env, horArr);

		jboolean* flag;

		//获取每一个元素
		jint* horData = (*env)->GetIntArrayElements(env, horArr,flag);

		for (int j = 0; j < horNum; j++) {

			//每一行数组赋值
			bb[j] = malloc(sizeof(int)*horNum);

			bb[i][j] = horData[j];

		}

		//将每一行数组赋值到ARR中

		(*env)->ReleaseIntArrayElements(env, bb, bb[j], JNI_COMMIT);


	}



}





//Jni定义方式多样 findClass getObjectClass newObject newCharArray,newLocalRef
//释放方式，调用完成之后使用jvm自动释放，DeleteLocalref
JNIEXPORT void JNICALL Java_com_dongnao_alvin_Jni_1Test_localRef
(JNIEnv * env, jobject jobj) {

	for (int i = 0; i < 5; i++) {

		jclass class = (*env)->FindClass(env, "java/lang/Date");
		jmethodID methodId  = (*env)->GetMethodID(env, class, "<init>", "()V");
		jobject object = (*env)->NewObject(env, class, methodId);

		(*env)->DeleteLocalRef(env,object);
		(*env)->DeleteGlobalRef(env,class);
	 }
}



jstring string;
//创建全局引用
JNIEXPORT void JNICALL Java_com_mahao_jnidemo2_bean_MyNative_createGlobalRef
(JNIEnv *env, jobject object) {


	jstring str = (*env)->NewStringUTF(env, "aa");
	jobject object = (*env)->NewGlobalRef(env, str);

	(*env)->DeleteGlobalRef(env,object);
}


//获取全局引用
JNIEXPORT jstring JNICALL Java_com_mahao_jnidemo2_bean_MyNative_getglobalRef
(JNIEnv *env, jobject jobect) {

	return string;
}

//异常处理
JNIEXPORT void JNICALL Java_com_mahao_jnidemo2_bean_MyNative_exception
(JNIEnv * env, jobject object) {

	jclass claa = (*env)->GetObjectClass(env, object);
	jfieldID methodid = (*env)->GetFieldID(env, claa, "key", "java/lang/string");

	jthrowable throwable = (*env)->ExceptionOccurred(env);
	if (throwable != NULL) {

		//清除所有的异常
		(*env)->ExceptionClear(env);

		jclass classExce = (*env)->FindClass(env, "java/lang/IllegalArgumentException");

		jint exception = (*env)->ThrowNew(env, classExce, "this is a exception");
	}
}






