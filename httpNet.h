#ifndef _HTTPNET_YY_H_
#define _HTTPNET_YY_H_


#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include <stdio.h> 
#include <windows.h> 
#include <WinInet.h>
#pragma comment(lib, "wininet.lib")

#define STRING_LEN	256

class CMyWinInet
{
public:
	CMyWinInet();
	virtual ~CMyWinInet();

public:
	bool Init(TCHAR* szUrl);
	bool Send();
	TCHAR* Recv();
	void Close();

public:
	inline TCHAR* GetUrl(){return m_szUrl;};
	inline TCHAR* GetData(){return m_szData;};
	inline TCHAR* GetHostName(){return m_szHostName;};
	inline TCHAR* GetUrlPath(){return m_szUrlPath;};

private:
	HINTERNET	m_hSession;
	HINTERNET	m_hConnect;
	HINTERNET	m_hRequest;

	TCHAR m_szUrl[STRING_LEN];
	TCHAR m_szData[STRING_LEN];
	TCHAR m_szHostName[STRING_LEN];
	TCHAR m_szUrlPath[STRING_LEN];
	URL_COMPONENTS		m_CrackedUrl;
};







#endif