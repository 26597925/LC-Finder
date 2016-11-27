/* ***************************************************************************
 * LCUIRenderer.h -- UWP display support for LCUI
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
 * LCUIRenderer.h -- LCUi �� UWP ��ͼ�����֧��
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

#pragma once

#include <LCUI_Build.h>
#include <LCUI/LCUI.h>
#include <LCUI/display.h>

#include <mutex>
#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"

namespace UWP {

class LCUIRenderer {
public:
	LCUIRenderer( const std::shared_ptr<DX::DeviceResources>& deviceResources );
	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();
	void ReleaseDeviceDependentResources();
	void Update( DX::StepTimer const& timer );
	void Render();
	void SwapFrames();
	void LockFrames();
	void UnlockFrames();
	bool m_frameSwapable;
	D2D1_SIZE_U m_frameSize;

private:
	std::mutex m_frameMutex;
	std::shared_ptr<DX::DeviceResources> m_deviceResources;
	Microsoft::WRL::ComPtr<ID2D1DrawingStateBlock1> m_stateBlock;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bmp;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_backBmp;
};

}

LCUI_DisplayDriver LCUI_CreateUWPDisplay( void );
