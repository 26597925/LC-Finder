/* ***************************************************************************
* ui.c -- ui managment module
*
* Copyright (C) 2016 by Liu Chao <lc-soft@live.cn>
*
* This file is part of the LC-Finder project, and may only be used, modified,
* and distributed under the terms of the GPLv2.
*
* By continuing to use, modify, or distribute this file you indicate that you
* have read the license and understand and accept it fully.
*
* The LC-Finder project is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GPL v2 for more details.
*
* You should have received a copy of the GPLv2 along with this file. It is
* usually in the LICENSE.TXT file, If not, see <http://www.gnu.org/licenses/>.
* ****************************************************************************/

/* ****************************************************************************
* ui.c -- ͼ�ν������ģ��
*
* ��Ȩ���� (C) 2016 ������ ���� <lc-soft@live.cn>
*
* ����ļ��� LC-Finder ��Ŀ��һ���֣�����ֻ���Ը���GPLv2���Э����ʹ�á����ĺ�
* ������
*
* ����ʹ�á��޸Ļ򷢲����ļ����������Ѿ��Ķ�����ȫ���ͽ���������Э�顣
*
* LC-Finder ��Ŀ�ǻ���ʹ��Ŀ�Ķ�����ɢ���ģ��������κε������Σ�����û������
* �Ի��ض���;���������������������GPLv2���Э�顣
*
* ��Ӧ���յ������ڱ��ļ���GPLv2���Э��ĸ�������ͨ���� LICENSE �ļ��У����
* û�У���鿴��<http://www.gnu.org/licenses/>.
* ****************************************************************************/

#include <stdlib.h>
#include "finder.h"
#include <LCUI/timer.h>
#include <LCUI/display.h>
#include <LCUI/font/charset.h>
#include <LCUI/gui/builder.h>
#include "ui.h"
#include "thumbview.h"

#define XML_PATH "res/ui.xml"

static void onTimer( void *arg )
{
	Widget_PrintTree( NULL );
}

void UI_Init(void)
{
	LCUI_Widget box, root;
	LCUI_Init();
	LCUIWidget_AddThumbView();
	LCUIDisplay_SetMode( LCDM_WINDOWED );
	LCUIDisplay_SetSize( 960, 640 );
	//LCUIDisplay_ShowRectBorder();
	box = LCUIBuilder_LoadFile( XML_PATH );
	if( !box ) {
		return;
	}
	Widget_Top( box );
	Widget_Unwrap( box );
	root = LCUIWidget_GetRoot();
	Widget_SetTitleW( root, L"LC-Finder" );
	Widget_UpdateStyle( root, TRUE );
	UI_InitSidebar();
	UI_InitHomeView();
	UI_InitSettingsView();
	UI_InitFoldersView();
	UI_InitFileSyncTip();
	UI_InitPictureView();
	UI_InitSearchView();
	//LCUITimer_Set( 5000, onTimer, NULL, FALSE );
}

int UI_Run( void )
{
	return LCUI_Main();
}

void UI_Exit( void )
{
	UI_ExitHomeView();
	UI_ExitFolderView();
	UI_ExitPictureView();
}