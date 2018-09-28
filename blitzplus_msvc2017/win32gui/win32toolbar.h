
#ifndef WIN32TOOLBAR_H
#define WIN32TOOLBAR_H

#include "../gui/toolbar.h"

#include "win32gadget.h"

class Win32ToolBar : public BBToolBar,public Win32WndProc{
	Win32Gadget _gadget;
	HWND _tooltips;
protected:
	~Win32ToolBar();
public:
	Win32ToolBar( BBGroup *group,int style );

	void *query( int qid );

	void setFont( BBFont *font );
	void setText( BBString *text );
	void setShape( int x,int y,int w,int h );
	void setVisible( bool visible );
	void setEnabled( bool enabled );
	void activate();
	void setIconStrip( BBIconStrip *icons );

	void setItemEnabled( int n,bool e );
	void setTips( BBString *tips );

	LRESULT wndProc( HWND hwnd,UINT msg,WPARAM wp,LPARAM lp,WNDPROC proc );
};

#endif