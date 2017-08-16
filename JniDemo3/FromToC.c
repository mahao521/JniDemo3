
#include<stdio.h>
#include "com_mahao_jnidemo2_GetFromC.h"
#include <string.h>
#include "stdafx.h"
#include "targetver.h"
#include <Windows.h>
#include <string.h>


/**
      C����java�ľ�̬����
*/
JNIEXPORT jstring JNICALL  Java_com_mahao_jnidemo2_GetFromC_dynamicLog
(JNIEnv *env, jclass jclass) {

	jmethodID methodId = (*env)->GetStaticMethodID(env, jclass, "printStaticNum", "(I)I");
	jint aa = (*env)->CallStaticIntMethod(env, jclass, methodId,20);
	return (*env)->NewStringUTF(env, "��������CŶ");
}



/* C����java---��ͨ����
* Class:     com_mahao_jnidemo2_GetFromC
* Method:    getSubmit
* Signature: (I)I   
*/  
JNIEXPORT jint JNICALL Java_com_mahao_jnidemo2_GetFromC_getSubmit
(JNIEnv *env, jobject jb, jint aa) {

//	printf("C random: %d \n", aa);
	jclass cla = (*env)->GetObjectClass(env, jb);

	if (cla == NULL) {

		printf("class is null");
	}
	jmethodID methodId = (*env)->GetMethodID(env, cla, "printfNum","(I)I");

	if (methodId == NULL) {

		printf("methodId is null");
	}

	if ((*env)->ExceptionCheck(env)) {  // ���JNI�����Ƿ��������쳣
		(*env)->ExceptionDescribe(env);
		(*env)->ExceptionClear(env);        // ����������쳣����Java�㲻���ӡ�쳣�Ķ�ջ��Ϣ
		(*env)->ThrowNew(env, (*env)->FindClass(env, "java/lang/Exception"), "JNI�׳����쳣��");
	}

	(*env)->CallIntMethod(env, jb, methodId,10);
	//printf("mahao%d",bb);
	return  aa + 100;
}


/*  C���� ����java������
* Class:     com_mahao_jnidemo2_GetFromC
* Method:    getUserCalendar
* Signature: ()Ljava/util/Calendar;
*/
JNIEXPORT jobject JNICALL Java_com_mahao_jnidemo2_GetFromC_getUserCalendar
(JNIEnv *env, jclass job) {

	//Ҫ�ҵ�date�࣬����dete.getTime()������

	jclass class = (*env)->FindClass(env, "java/util/Date");
	jmethodID methodId  = (*env)->GetMethodID(env, class, "<init>", "()V");
	jobject jobject = (*env)->NewObject(env, class, methodId);
	
	//���ø�date�����getTime����
	jmethodID timeMid = (*env)->GetMethodID(env, class, "getTime", "()J");
	jlong longtime = (*env)->CallLongMethod(env, jobject, timeMid);

	printf("ʱ����:%l\n", longtime);

	return jobject;
}



/*
      C ���Է���java������
* Class:     com_mahao_jnidemo2_GetFromC
* Method:    stringAndInt
* Signature: (ILjava/lang/String;)I
*/
JNIEXPORT jint JNICALL Java_com_mahao_jnidemo2_GetFromC_stringAndInt
(JNIEnv *env, jclass jcla, jint aa, jstring bb) {


	jclass cla = (*env)->FindClass(env, "java/lang/String");
	jmethodID methodId = (*env)->GetMethodID(env, cla, "<init>", "([BLjava/lang/String;)V");

	char* text = "����ѧϰ";
	jbyteArray byteArray = (*env)->NewByteArray(env, strlen(text));
	(*env)->SetByteArrayRegion(env, byteArray, 0, strlen(text), text);

	jstring jscode = (*env)->NewStringUTF(env, "GB2312");
	jobject jobj = (*env)->NewObject(env, cla, methodId,byteArray, jscode);
	printf("ʱ����:%zd", strlen(text));
	return 10;

}





/* ��̬��Ա����
* Class:     com_mahao_jnidemo2_GetFromC
* Method:    staticLog
* Signature: (II)I
*/
JNIEXPORT jint JNICALL Java_com_mahao_jnidemo2_GetFromC_staticLog
(JNIEnv *env, jclass obj, jint a, jint b) {


	return a + b;

}


/*   C����java---��ͨ����
* Class:     com_mahao_jnidemo2_GetFromC
* Method:    commonField
* Signature: ()Ljava/lang/String;
*/
JNIEXPORT jstring JNICALL Java_com_mahao_jnidemo2_GetFromC_commonField
(JNIEnv *env, jobject job) {

	jclass jcla = (*env)->GetObjectClass(env, job);
	jfieldID field = (*env)->GetFieldID(env, jcla, "age", "I");
	jint value = (*env)->GetIntField(env, job, field);

	value++;

	return (*env)->NewStringUTF(env,".....");
}


/*  C����java---��̬����
* Class:     com_mahao_jnidemo2_GetFromC
* Method:    staticField
* Signature: ()V
*/
JNIEXPORT void JNICALL Java_com_mahao_jnidemo2_GetFromC_staticField
(JNIEnv *env , jobject job) {

	jclass class = (*env)->GetObjectClass(env, job);
	if (class == NULL)
	{
		printf("class is null");
	}
	jfieldID fileId = (*env)->GetStaticFieldID(env, class, "times", "I");
	
	jlong ll = (*env)->GetStaticLongField(env, class, fileId);
	ll++;

	(*env)->SetStaticLongField(env, class, fileId, ll);
}
