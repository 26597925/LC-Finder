/* ***************************************************************************
* thumb_cache.h -- thumbnail data cache
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
* thumb_cache.h -- ����ͼ���ݻ���
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

#ifndef __THUMBNAIL_CACHE_H__
#define __THUMBNAIL_CACHE_H__

#ifndef __THUMBNAIL_CACHE_C__
typedef void* ThumbCache;
#endif

ThumbCache ThumbCache_New( size_t max_size, void( *on_remove )(void*) );

LCUI_Graph *ThumbCache_Get( ThumbCache cache, const char *path );

int ThumbCache_Delete( ThumbCache cache, const char *path );

LCUI_Graph *ThumbCache_Add( ThumbCache cache, const char *path,
			    LCUI_Graph *thumb, void *privdata );

#endif
