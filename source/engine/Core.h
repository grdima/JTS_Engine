#ifndef _CORE_H
#define _CORE_H

#include "Common.h"

class CRender;
class CInput;

class CCore : public IEngineCore
{
	TProcDelegate		_clDelProcess,
						_clDelRender,
						_clDelInit,
						_clDelFree,
						_clDelMLoop;
	TMsgProcDelegate	_clDelMProc;
	fstream				_clLogFile;
	
	IMainWindow			*_pMainWindow;
	CRender				*_pRender;
	CInput				*_pInput;

	uint				_uiProcessInterval;
	uint64				_ui64TimeOld;

	bool _bDoExit;

	void _MainLoop();
	void _MessageProc(const TWinMessage &stMsg);

	static void CALLBACK _s_MainLoop(void *pParametr);
	static void CALLBACK _s_MessageProc(void *pParametr, const TWinMessage &stMsg);

public:

	CCore();
	~CCore();

	inline	TMsgProcDelegate* pDMessageProc() {return &_clDelMProc;}
	inline	TProcDelegate* pDMLoopProc() {return &_clDelMLoop;}
	IMainWindow* GetWindow() const;

	HRESULT CALLBACK InitializeEngine(uint uiResX, uint uiResY, const char* pcApplicationName, E_ENGINE_INIT_FLAGS eInitFlags);
	HRESULT CALLBACK SetProcessInterval(uint uiProcessInterval);	
	HRESULT CALLBACK AddProcedure(E_ENGINE_PROCEDURE_TYPE eProcType, void (CALLBACK *pProc)(void *pParametr), void *pParametr);
	HRESULT CALLBACK RemoveProcedure(E_ENGINE_PROCEDURE_TYPE eProcType, void (CALLBACK *pProc)(void *pParametr), void *pParametr);
	HRESULT CALLBACK QuitEngine();
	HRESULT CALLBACK AddToLog(const char *pcTxt, bool bError = false);
	HRESULT CALLBACK GetInput(IInput *&pInput);

	IJTS_BASE_IMPLEMENTATION(IEngineCore);
};

#endif //_CORE_H