/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import java.io.UnsupportedEncodingException;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;

import com.iflytek.cloud.SpeechConstant;
import com.iflytek.cloud.SpeechError;
import com.iflytek.cloud.SpeechSynthesizer;
import com.iflytek.cloud.SpeechUtility;
import com.iflytek.cloud.SynthesizerListener;

public class AppActivity extends Cocos2dxActivity {
	
	
	private static SynthesizerListener mSyn;
	private static SpeechSynthesizer mTts;
	
	@Override
	protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        SpeechUtility.createUtility(AppActivity.this, SpeechConstant.APPID+"=58a2c88a");
        initSpeak();
    }
	
	public static void speak(String words){
		mTts.startSpeaking(words,mSyn);
	}
	
	private void initSpeak(){
		
		mSyn = new com.iflytek.cloud.SynthesizerListener() {
				
				@Override
				public void onSpeakResumed() {
					// TODO Auto-generated method stub
					
				}
				
				@Override
				public void onSpeakProgress(int arg0, int arg1, int arg2) {
					// TODO Auto-generated method stub
					
				}
				
				@Override
				public void onSpeakPaused() {
					// TODO Auto-generated method stub
					
				}
				
				@Override
				public void onSpeakBegin() {
					// TODO Auto-generated method stub
					
				}
				
				@Override
				public void onEvent(int arg0, int arg1, int arg2, Bundle arg3) {
					// TODO Auto-generated method stub
					
				}
				
				@Override
				public void onCompleted(SpeechError arg0) {
					// TODO Auto-generated method stub
					
				}
				
				@Override
				public void onBufferProgress(int arg0, int arg1, int arg2, String arg3) {
					// TODO Auto-generated method stub
					
				}
			};
		
		mTts = SpeechSynthesizer.createSynthesizer(AppActivity.getContext(), null);
		mTts.setParameter(SpeechConstant.VOICE_NAME, "xiaoyan");
		mTts.setParameter(SpeechConstant.SPEED, "50");
		mTts.setParameter(SpeechConstant.VOLUME, "100");
		mTts.setParameter(SpeechConstant.STREAM_TYPE, "2");
		mTts.setParameter(SpeechConstant.ENGINE_TYPE, SpeechConstant.TYPE_CLOUD);
	}
}
