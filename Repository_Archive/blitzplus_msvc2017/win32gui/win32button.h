
#ifndef WIN32BUTTON_H
#define WIN32BUTTON_H

#include "../gui/button.h"

#include "win32gadget.h"

class Win32Button : public BBButton,public Win32WndProc{
	Win32Gadget _gadget;
	typedef BBButton super;
public:
	Win32Button( BBGroup *group,int style );

	void *query( int qid );

	void setFont( BBFont *font );
	void setText( BBString *text );
	void setShape( int x,int y,int w,int h );
	void setVisible( bool visible );
	void setEnabled( bool enabled );
	void activate();

	int  state();
	void setState( int state );

	LRESULT wndProc( HWND hwnd,UINT msg,WPARAM wp,LPARAM lp,WNDPROC proc );
};

#endif