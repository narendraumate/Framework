//
//  NativeWindow.h
//  Framework
//
//  Created by Narendra Umate on 7/17/16.
//
//

#ifndef NativeWindow_h
#define NativeWindow_h

#include "AbstractWindow.h"

struct Parameters;

class NativeWindow : public AbstractWindow {

public:
	NativeWindow(Parameters& parameters);
	virtual ~NativeWindow() = 0;

	void handlePollEvent();

	virtual void setSwapInterval(const int& syncInterval);
	virtual void swapWindow();

private:
	void initializeNative();
	void initializeOpenGL();
	void initializeOther();
	void deinitializeNative();
	void deinitializeNativeimage();
	void deinitializeNativettf();
	void deinitializeOpenGL();

	void handleWindowEvent();
	void handleKeyUpEvent();
	void handleKeyDownEvent();

	////Native_Event m_nativeEvent;
	////Native_Window* m_nativeWindow;
	////Native_GLContext m_nativeContext;
};

#endif /* NativeWindow_h */
