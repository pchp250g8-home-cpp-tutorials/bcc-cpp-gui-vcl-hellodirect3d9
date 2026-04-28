//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HelloDirect3DForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	nRedColor = 0;
    if (!InitializeDirect3D())
	{
		Application->MessageBox(_T("Error Loading DirectX"), _T("Error"));
	}
	Application->OnIdle = ApplicationIDLE;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
    RenderScene();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    DestroyDirect3D();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ApplicationIDLE(TObject *Sender, bool &bFlag)
{
    Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WMEraseBkgnd(Winapi::Messages::TWMEraseBkgnd &Message)
{
    // Option A: Simply prevent flicker (do nothing, return true)
	Message.Result = 1;
    // Option B: Custom background drawing
    // HDC dc = Message.DC;
    // // Perform GDI drawing here using dc...
    // Message.Result = 1; // Tell Windows we handled it
}
//---------------------------------------------------------------------------
bool TForm1::InitializeDirect3D()
{
    D3DDISPLAYMODE d3ddm;
	HRESULT hr;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	ZeroMemory(&d3ddm, sizeof(d3ddm));
	m_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_d3d9 == nullptr) return FALSE;
	hr = m_d3d9->GetAdapterDisplayMode(0, &d3ddm);
	if (FAILED(hr)) return FALSE;
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	hr = m_d3d9->CreateDevice
	(
		0,
		D3DDEVTYPE_HAL,
		Handle,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_d3d_Device
	);
	if (FAILED(hr)) return false;
	return true;
}
//---------------------------------------------------------------------------
void TForm1::DestroyDirect3D()
{
    m_d3d_Device.Release();
	m_d3d9.Release();
}
//---------------------------------------------------------------------------
void TForm1::RenderScene()
{
    if (m_d3d9 == nullptr) return;
	if (m_d3d_Device == nullptr) return;
	m_d3d_Device->Clear
	(
		0,
		nullptr,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(nRedColor++, 0, 0),
		0, 0
	);
	m_d3d_Device->BeginScene();
	m_d3d_Device->EndScene();
	m_d3d_Device->Present(nullptr, nullptr, 0, nullptr);
}
