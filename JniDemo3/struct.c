
#include<stdio.h>
#include<stdlib.h>

#include "com_mahao_jnidemo2_bean_MyNative.h"

int compare(int *a, int *b);


//��Ҫ���������

//1 :  ���Jint��jinString

//2 :  ���Jobject��JinString

/**
    obj --->  �������
	class ---> ��̬���������class�ļ�
*/
JNIEXPORT jstring JNICALL Java_com_mahao_jnidemo2_bean_MyNative_accessCachString
(JNIEnv * env, jobject  obj) {

	//��̬claa ֻ�ᴴ��һ�Σ�
	static jclass claa;
	if (claa == NULL) {

		printf("da ying l a --------\n");

		//��һ�ַ�ʽ����class
	//	claa = (*env)->FindClass(env, "com/mahao/jnidemo2/bean/MyNative");

		claa = (*env)->GetObjectClass(env, obj);
	}
	jmethodID methodId = (*env)->GetMethodID(env, claa, "getString", "()I");
	jthrowable throwable = (*env)->ExceptionOccurred(env);

	if (throwable != NULL) {

		(*env)->ExceptionDescribe(env);
		printf("Exception is occour\n");
	}

	//�ڶ��ַ�ʽ��ȡobject;
	jmethodID methoid = (*env)->GetMethodID(env, claa, "<init>", "()V");
	jobject object = (*env)->NewObject(env, claa, methoid);

	jint aa = (*env)->CallIntMethod(env, object, methodId);
	printf("call--- back from java aa = %d", aa);

	return NULL;
}


//int����
JNIEXPORT void JNICALL Java_com_mahao_jnidemo2_bean_MyNative_getInArray
(JNIEnv *env , jobject obj , jintArray arr) {


	jboolean flag;
	jint* item = (*env)->GetIntArrayElements(env, arr, flag);
	if (item == NULL) {

		printf("not found the int array");
	}

	jint length = (*env)->GetArrayLength(env, arr);
	qsort(item, length, sizeof(jint), compare);

	//�ͷſ��ܵ��ڴ�
	//������д���ڴ���
	(*env)->ReleaseIntArrayElements(env, arr, item, JNI_COMMIT);
}

int compare(int *a, int *b) {

	return *a - *b;
}

//��������
JNIEXPORT jobjectArray JNICALL Java_com_mahao_jnidemo2_bean_MyNative_initStringArray
(JNIEnv * env, jobject object, jint aa) {

	//jclass claa  = (*env)->GetObjectClass(env, object);

	//��������
	jclass claz = (*env)->FindClass(env, "java/lang/string");
	jobjectArray objectArray = (*env)->NewObjectArray(env, aa, claz, object);

	//�����鸳ֵ
	char* item_str;
	for (int i = 0; i < aa; i++) {

		item_str = malloc(sizeof(char)*100);
		sprintf(item_str, "wo shi %d", i);

		jstring str = (*env)->NewStringUTF(env, item_str);

		//��������
		(*env)->SetObjectArrayElement(env, objectArray, i, item_str);

		frre(item_str);
		item_str = NULL;
	}
	return objectArray;
}

//���ض�ά����int[][];
JNIEXPORT jobjectArray JNICALL Java_com_mahao_jnidemo2_bean_MyNative_initInt2DArray
(JNIEnv *env, jobject obj, jint aa) {


	//����һ����ά���� ����int[][];

	//1 :��������
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


//����java�еĶ�λ����
JNIEXPORT jint JNICALL Java_com_mahao_jnidemo2_bean_deal2Arr
(JNIEnv *env, jobject object, jobjectArray arr) {


	//���͵�ַ
    //http://blog.csdn.net/gao1440156051/article/details/52026718


	//jint i = 3, j = 5;  //3
	jint aa[1024][1024];

	int size = (*env)->GetArrayLength(env, arr);

	//������άָ��ָ������
	jint **bb = (int**)malloc(sizeof(int*)*size);

	for (int i = 0; i < size; i++) {

		//ÿһ�е�����
		jarray horArr = (*env)->GetObjectArrayElement(env, arr, i);

		//ÿһ������ĳ���
		int horNum =  (*env)->GetArrayLength(env, horArr);

		jboolean* flag;

		//��ȡÿһ��Ԫ��
		jint* horData = (*env)->GetIntArrayElements(env, horArr,flag);

		for (int j = 0; j < horNum; j++) {

			//ÿһ�����鸳ֵ
			bb[j] = malloc(sizeof(int)*horNum);

			bb[i][j] = horData[j];

		}

		//��ÿһ�����鸳ֵ��ARR��

		(*env)->ReleaseIntArrayElements(env, bb, bb[j], JNI_COMMIT);


	}



}





//Jni���巽ʽ���� findClass getObjectClass newObject newCharArray,newLocalRef
//�ͷŷ�ʽ���������֮��ʹ��jvm�Զ��ͷţ�DeleteLocalref
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
//����ȫ������
JNIEXPORT void JNICALL Java_com_mahao_jnidemo2_bean_MyNative_createGlobalRef
(JNIEnv *env, jobject object) {


	jstring str = (*env)->NewStringUTF(env, "aa");
	jobject object = (*env)->NewGlobalRef(env, str);

	(*env)->DeleteGlobalRef(env,object);
}


//��ȡȫ������
JNIEXPORT jstring JNICALL Java_com_mahao_jnidemo2_bean_MyNative_getglobalRef
(JNIEnv *env, jobject jobect) {

	return string;
}

//�쳣����
JNIEXPORT void JNICALL Java_com_mahao_jnidemo2_bean_MyNative_exception
(JNIEnv * env, jobject object) {

	jclass claa = (*env)->GetObjectClass(env, object);
	jfieldID methodid = (*env)->GetFieldID(env, claa, "key", "java/lang/string");

	jthrowable throwable = (*env)->ExceptionOccurred(env);
	if (throwable != NULL) {

		//������е��쳣
		(*env)->ExceptionClear(env);

		jclass classExce = (*env)->FindClass(env, "java/lang/IllegalArgumentException");

		jint exception = (*env)->ThrowNew(env, classExce, "this is a exception");
	}
}






