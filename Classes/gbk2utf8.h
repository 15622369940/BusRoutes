#ifndef __GBK2UTF8_H__
#define __GBK2UTF8_H__

#include "cocos2d.h"
USING_NS_CC;

/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <dlfcn.h>
#endif

	const char* gbk2utf8(const char* gb2312)
	{
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			int len = MultiByteToWideChar(0, 0, gb2312, -1, NULL, 0);
			wchar_t* wstr = new wchar_t[len + 1];
			memset(wstr, 0, len + 1);
			MultiByteToWideChar(0, 0, gb2312, -1, wstr, len);
			len = WideCharToMultiByte(65001, 0, wstr, -1, NULL, 0, NULL, NULL);
			char* str = new char[len + 1];
			memset(str, 0, len + 1);
			WideCharToMultiByte(65001, 0, wstr, -1, str, len, NULL, NULL);
			if (wstr) delete[] wstr;
			return str;
		#endif

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			if (ucnv_convert == NULL)
			{
				openIcuuc();
			}
			if (ucnv_convert)
			{
				int err_code = 0;
				int len = strlen(gb2312);
				char* str = new char[len * 2 + 10];
				memset(str, 0, len * 2 + 10);
				ucnv_convert("utf-8", "gb2312", str, len * 2 + 10, gb2312, len, &err_code);
				if (err_code == 0)
				{
					return str;
				}
			}
			char test[256] = "gb23122utf8 error";
			char* str = new char[30];
			strcpy(str, test);
			return str;
		#endif

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			return gb2312;
		#endif
	}

	

	
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		void(*ucnv_convert)(const char *, const char *, char *, int32_t, const char *, int32_t, int32_t*) = 0;

		bool openIcuuc()
		{
			void* libFile = dlopen("/system/lib/libicuuc.so", RTLD_LAZY);
			if (libFile)
			{
				ucnv_convert = (void(*)(const char *, const char *, char *, int32_t, const char *, int32_t, int32_t*))dlsym(libFile, "ucnv_convert_3_8");

				int index = 0;
				char fun_name[64];
				while (ucnv_convert == NULL)
				{
					sprintf(fun_name, "ucnv_convert_4%d", index++);
					ucnv_convert = (void(*)(const char *, const char *, char *, int32_t, const char *, int32_t, int32_t*))dlsym(libFile, fun_name);
					if (ucnv_convert)
						return true;
					if (++index > 11)
						break;
				}
				dlclose(libFile);
			}
			return false;
		}
	#endif	
*/

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
class GBK2UTF {
public:
	static const char* gb23122utf8(const char* gb2312)
	{
		int len = MultiByteToWideChar(0, 0, gb2312, -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(0, 0, gb2312, -1, wstr, len);
		len = WideCharToMultiByte(65001, 0, wstr, -1, NULL, 0, NULL, NULL);
		char* str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(65001, 0, wstr, -1, str, len, NULL, NULL);
		if (wstr) delete[] wstr;
		return str;
	}
};		
#endif 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
#include <dlfcn.h> 
class GBK2UTF {
	void(*ucnv_convert)(const char *, const char *, char *, int32_t, const char *, int32_t, int32_t*) = 0;

	bool openIcuuc()
	{
		void* libFile = dlopen("/system/lib/libicuuc.so", RTLD_LAZY);
		if (libFile)
		{
			ucnv_convert = (void(*)(const char *, const char *, char *, int32_t, const char *, int32_t, int32_t*))dlsym(libFile, "ucnv_convert_3_8");

			int index = 0;
			char fun_name[64];
			while (ucnv_convert == NULL)
			{
				sprintf(fun_name, "ucnv_convert_4%d", index++);
				ucnv_convert = (void(*)(const char *, const char *, char *, int32_t, const char *, int32_t, int32_t*))dlsym(libFile, fun_name);
				if (ucnv_convert)
					return true;
				if (++index > 11)
					break;
			}
			dlclose(libFile);
		}
		return false;
	}
public:
	const char* gbk2utf8(const char * gb2312)
	{
		if (ucnv_convert == NULL)
		{
			openIcuuc();
		}
		if (ucnv_convert)
		{
			int err_code = 0;
			int len = strlen(gb2312);
			char* str = new char[len * 2 + 10];
			memset(str, 0, len * 2 + 10);
			ucnv_convert("utf-8", "gb2312", str, len * 2 + 10, gb2312, len, &err_code);
			if (err_code == 0)
			{
				return str;
			}
		}
		char test[256] = "gb23122utf8 error";
		char* str = new char[30];
		strcpy(str, test);
		return str;
	}
};
#endif

#endif
