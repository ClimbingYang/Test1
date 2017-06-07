#include "stdafx.h"
#include "httpNet.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////


CMyWinInet::CMyWinInet()
{
	m_hSession = NULL;
	m_hRequest = NULL;
	m_hConnect = NULL;

	memset(m_szUrl, 0, STRING_LEN);
	memset(m_szData, 0, STRING_LEN);
	memset(m_szHostName, 0, STRING_LEN);
	memset(m_szUrlPath, 0, STRING_LEN);
};


CMyWinInet::~CMyWinInet()
{
	Close();
}


//////////////////////////////////////////////////////////////////////////


bool CMyWinInet::Init(TCHAR* szUrl)
{
	try
	{
		memcpy(m_szUrl, szUrl, STRING_LEN);
		
		memset((void*)&m_CrackedUrl, 0, sizeof(URL_COMPONENTS));
		m_CrackedUrl.dwStructSize = sizeof(URL_COMPONENTS);	
		m_CrackedUrl.lpszHostName = (LPTSTR)m_szHostName;
		m_CrackedUrl.dwHostNameLength = sizeof(m_szHostName);
		m_CrackedUrl.lpszUrlPath = (LPTSTR)m_szUrlPath;
		m_CrackedUrl.dwUrlPathLength = sizeof(m_szUrlPath);

		return	::InternetCrackUrl(m_szUrl, static_cast<DWORD>(_tcslen(m_szUrl)), 0, &m_CrackedUrl);
	}
	catch (...)
	{
		//日志：创建失败

		return false;
	}

}

/*
nicole@sina.cn
623251    
*/

bool CMyWinInet::Send()
{	
	bool bRet = false;
	try
	{
		do
		{
			PCTSTR rgpszAcceptTypes[] = {_T("text/*"), NULL};
			//TCHAR* szContent = _T("email=nicole@sina.cn&password=623251&content=1");
			//TCHAR* szContent = _T("username=nicole@sina.cn&password=623251|hash=MD5(nicole@sina.cn|0FB142BAA7CBCAAABA60BF071A914FA7|DaYeZaiCi)");
			
	//		TCHAR* szContent = _T("username=kangyun&password=CAC6D294364761C1B4BB4D5B7B3F6D5E|hash=MD5(kangyun|CAC6D294364761C1B4BB4D5B7B3F6D5E|DaYeZaiCi)");

	//		TCHAR* szContent = _T("username=nicole@sina.cn|password=CAC6D294364761C1B4BB4D5B7B3F6D5E|hash=56DD65AE41F8087BB854744EBF8FC6BA");

	//		TCHAR* szContent = _T("username=babayaga3578|password=DFC2C8FC23D7F39A11DB2B7596954D80|hash=MD5(babayaga3578|DFC2C8FC23D7F39A11DB2B7596954D80|DaYeZaiCi)");
			//TCHAR* szContent = _T("username=babayaga3578&password=DFC2C8FC23D7F39A11DB2B7596954D80&hash=d9b40dca59cf32434f32f97246a0cbdc");
			  TCHAR* szContent = _T("username=babayaga3578&password=DFC2C8FC23D7F39A11DB2B7596954D80&hash=D9B40DCA59CF32434F32F97246A0CBDC");
			

			m_hSession = ::InternetOpen(_T("App"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
			if(m_hSession == NULL)
			{
				break;
			}		

			m_hConnect = ::InternetConnect(m_hSession, m_CrackedUrl.lpszHostName,
											m_CrackedUrl.nPort, NULL,
											NULL, INTERNET_SERVICE_HTTP,
											0, 0);
			if(m_hConnect == NULL)
			{
				break;
			}

			m_hRequest = ::HttpOpenRequest(m_hConnect, _T("POST"),
											m_CrackedUrl.lpszUrlPath, NULL,
											NULL, rgpszAcceptTypes,
											INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE/*| INTERNET_FLAG_SECURE*/ , 0);
			if(m_hRequest == NULL)
			{
				break;
			}

			TCHAR szHeaderBuff[200] = "";
			int nHeaderSize = sprintf(szHeaderBuff, "%s", "Content-Type:application/x-www-form-urlencoded");   

			int len = _tcslen(szContent);
	
			if(!::HttpSendRequest(m_hRequest, szHeaderBuff, nHeaderSize, 
									szContent, len))
			{
				int a = GetLastError();
				break;
			}
	
/*
			if(!::HttpSendRequest(m_hRequest, NULL, 0, 
									szContent, len))
			{
				int a = GetLastError();
				break;
			}
			*/

			bRet = true;
		}
		while(0);

		return bRet;
	}
	catch( ... )
	{

		return false;
	}
}

TCHAR* CMyWinInet::Recv()
{
	if(m_hRequest == NULL)
	{
		return NULL;
	}

	try
	{
		while(1)
		{
			ULONG lNumberOfBytesRead;
			BOOL bRet = ::InternetReadFile(m_hRequest, m_szData, sizeof(m_szData), &lNumberOfBytesRead);
			if(bRet == FALSE)
			{
				return NULL;
			}
			return m_szData;
		}
	}
	catch(...)
	{

		return NULL;
	}
}

void CMyWinInet::Close()
{
	if(m_hSession)
	{
		InternetCloseHandle(m_hSession);
	}

	if(m_hConnect)
	{
		InternetCloseHandle(m_hConnect);
	}

	if(m_hRequest)
	{
		InternetCloseHandle(m_hRequest);
	}

	memset(m_szUrl, 0, STRING_LEN);
	memset(m_szData, 0, STRING_LEN);
	memset(m_szHostName, 0, STRING_LEN);
	memset(m_szUrlPath, 0, STRING_LEN);
}
