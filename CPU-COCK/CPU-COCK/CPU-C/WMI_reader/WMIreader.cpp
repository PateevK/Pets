#include "WMIreader.h"

#define CHECKHR(z, x) if(z<0) std::cerr << (x); 

void WMIreader::Init(const wchar_t* _namespace_path) {
	HRESULT hr;
	hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	CHECKHR(hr, "Failed to initialize COM library.\n");
	hr = CoInitializeSecurity(0, -1, 0, 0, RPC_C_AUTHN_LEVEL_DEFAULT,
		RPC_C_IMP_LEVEL_IMPERSONATE, 0, EOAC_NONE, 0);
	CHECKHR(hr, "Failed to initialize security.\n");
	hr = CoCreateInstance(CLSID_WbemLocator, 0,
		CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	CHECKHR(hr, "Failed to create IWbemLocator object.\n");
	hr = pLoc->ConnectServer(BSTR(_namespace_path), 0, 0, 0, 0, 0, 0, &pSvc);
	CHECKHR(hr, "Could not connect.\n");
	hr = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
		RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	CHECKHR(hr, " Could not set proxy blanket.\n");
	//std::cout << "Connected to WMI\n";
}

void WMIreader::Query(const char* wqlQuery) {
	HRESULT hr;
	hr = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(wqlQuery),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);
	CHECKHR(hr, "Query failed.\n");
}



WMIreader::~WMIreader() {
	pSvc->Release();
	pLoc->Release();
	pEnumerator->Release();
	CoUninitialize();
}



