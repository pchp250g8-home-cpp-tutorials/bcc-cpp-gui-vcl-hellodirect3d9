//---------------------------------------------------------------------------

#ifndef HelloDirect3DFormH
#define HelloDirect3DFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
protected:
    void __fastcall WMEraseBkgnd(Winapi::Messages::TWMEraseBkgnd &Message);
    BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(WM_ERASEBKGND, Winapi::Messages::TWMEraseBkgnd, WMEraseBkgnd)
    END_MESSAGE_MAP(TForm)
private:	// User declarations
    byte nRedColor;
	D3DPRESENT_PARAMETERS d3dpp;
	TComInterface <IDirect3D9> m_d3d9;
	TComInterface <IDirect3DDevice9> m_d3d_Device;
	bool InitializeDirect3D();
	void DestroyDirect3D();
	void RenderScene();
	void __fastcall ApplicationIDLE(TObject *Sender, bool &bFlag);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
