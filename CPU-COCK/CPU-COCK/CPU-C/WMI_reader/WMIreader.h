#pragma once
#include<iostream>
#include <vector>
#include <type_traits>
#include <concepts>

#include<combaseapi.h>
#include <comdef.h>
#include <Wbemidl.h>

//#pragma comment(lib, "wbemuuid.lib")


//todo:
	//2. handle exeptions
//docs:
	//1.Call constructor with namespace you want to query further.
	//2. Call method Query(const wchar_t* wqlQuery) with the wql query.
	// This will execute the query and store the result in private member.
	//3. Call method GetProperty(const wchar_t* property).
	// This will return the value of the property.
class WMIreader {
public:
	WMIreader() = delete;
	WMIreader(const wchar_t* _namespace_path) {
		Init(_namespace_path);
	}
	~WMIreader();
	void Query(const char* wqlQuery);
	template <class T>
	requires (std::same_as<T, int> || std::same_as<T, float> || std::same_as<T, std::wstring>)
	std::vector<T> GetProperty(const wchar_t* propertyName);
private:
	IEnumWbemClassObject* pEnumerator = 0;
	IWbemLocator* pLoc = 0;
	IWbemServices* pSvc = 0;
	void Init(const wchar_t* _namespace_path);
};

template <class T>
requires (std::same_as<T, int> || std::same_as<T, float> || std::same_as<T, std::wstring>)
std::vector<T> WMIreader::GetProperty(const wchar_t* propertyName) {
	HRESULT hr;
	IWbemClassObject* pclsObj = 0;
	ULONG uReturn = 0;
	std::vector<T> vec;

	while (pEnumerator) {
		hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

		if (0 == uReturn)
			break;

		VARIANT vtProp;
		VariantInit(&vtProp);
		hr = pclsObj->Get(propertyName, 0, &vtProp, 0, 0);

		if (SUCCEEDED(hr)) {
			if constexpr (std::is_integral<T>::value) {
				vec.push_back(static_cast<T>(vtProp.intVal));
			}
			else if constexpr (std::is_floating_point<T>::value) {
				vec.push_back(static_cast<T>(vtProp.fltVal));
			}
			else if constexpr (std::is_same_v<T, std::wstring>) {
				vec.emplace_back(vtProp.bstrVal);
			}
			else std::cout << "error type\n";
		}

		VariantClear(&vtProp);
		pclsObj->Release();
	}
	return vec;
}