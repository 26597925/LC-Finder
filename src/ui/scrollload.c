/* ***************************************************************************
* scrollload.c -- scroll loading, used to allow widget to automatically load 
* data when scrolling to the visible region.
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
* scrollload.c -- �������أ������ò������ڹ������ɼ�����ʱ�Զ���������.
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

#include <LCUI_Build.h>
#include <LCUI/LCUI.h>
#include <LCUI/gui/widget.h>
#include "scrollload.h"

static void OnScroll( LCUI_Widget w, LCUI_WidgetEvent e, void *arg )
{
	_DEBUG_MSG("on scroll\n");
}

ScrollLoading ScrollLoading_New( LCUI_Widget container )
{
	ScrollLoading ctx = NEW( ScrollLoadingRec, 1 );
	ctx->top = 0;
	ctx->top_child = NULL;
	ctx->container = container;
	ctx->event_id = LCUIWidget_AllocEventId();
	LCUIWidget_SetEventName( ctx->event_id, "scrollload" );
	Widget_BindEvent( container, "scroll", OnScroll, ctx, NULL );
	return ctx;
}

void ScrollLoading_Delete( ScrollLoading ctx )
{
	ctx->top = 0;
	ctx->top_child = NULL;
	Widget_UnbindEvent( ctx->container, "scroll", OnScroll );
	free( ctx );
}

void ScrollLoading_Reset( ScrollLoading ctx )
{
	ctx->top = 0;
	ctx->top_child = NULL;
}

int ScrollLoading_Update( ScrollLoading ctx )
{
	LCUI_Widget w;
	LinkedListNode *node;
	LCUI_WidgetEventRec e;
	int count = 0, top, bottom;
	e.type = ctx->event_id;
	e.cancel_bubble = TRUE;
	bottom = top = ctx->top;
	bottom += ctx->container->box.padding.height;
	if( !ctx->top_child ) {
		node = ctx->container->children_show.head.next;
		ctx->top_child = node->data;
	}
	if( !ctx->top_child ) {
		return 0;
	}
	if( ctx->top_child->box.border.top > bottom ) {
		node = Widget_GetNode( ctx->top_child );
		ctx->top_child = NULL;
		while( node ) {
			w = node->data;
			if( w->box.border.y < bottom ) {
				ctx->top_child = w;
				break;
			}
			node = node->prev;
		}
		if( !ctx->top_child ) {
			return 0;
		}
	}
	node = Widget_GetNode( ctx->top_child );
	while( node ) {
		w = node->data;
		if( w->box.border.y > bottom ) {
			break;
		}
		if( w->box.border.y + w->box.border.height >= top ) {
			Widget_PostEvent( w, &e, NULL, NULL );
			++count;
		}
		node = node->next;
	}
	return count;
}
