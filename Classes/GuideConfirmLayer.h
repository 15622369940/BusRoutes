#pragma once

#include "cocos2d.h"
#include "ui\UIText.h"
#include "ui\UITextField.h"
//#include "gbk2utf8.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "../external/win32-specific/icon/include/iconv.h"
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include "../../libiconv/include/iconv.h"
#endif

USING_NS_CC;
using namespace ui;
using namespace std;

class GuideConfirm : public cocos2d::Layer
{
private:
	Node* rootNode;
	bool nodeProcess();
	bool eventDispatch();
	virtual bool init();
public:
	CREATE_FUNC(GuideConfirm);
	void speak(const char* words);

	Sprite *confirm, *cancel;
	TextField *start,*end;
	Sprite *mode_fast, *wait_yes;

	int convert(char *from_charset, char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
	{
		iconv_t cd;
		const char* temp = inbuf;
		const char** pin = &temp;
		char** pout = &outbuf;
		memset(outbuf, 0, outlen);
		cd = iconv_open(to_charset, from_charset);
		if (cd == 0)
			return -1;
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			if (iconv(cd, pin, &inlen, pout, &outlen) == -1)
				return -1;
		#endif
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			if (iconv(cd, (char**)pin, &inlen, pout, &outlen) == -1)
				return -1;
		#endif
		return 0;
	}


	std::string GBKToUTF8(const char *inbuf) {
		size_t inleng = strlen(inbuf);
		char* outbuf = new char[inleng * 2 + 2];
		std::string strRet;
		if (convert("gb2312", "utf-8", inbuf, inleng, outbuf, inleng * 2 + 2) == 0)
			strRet = outbuf;
		delete[] outbuf;
		return strRet;
	}

};