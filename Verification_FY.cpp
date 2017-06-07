// Verification_FY.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "httpNet.h" 
#include <iostream>
#include <string> 
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	CMyWinInet MyWinInet;
	//TCHAR* url = _T("https://www.infiplay.ru/p/user/login.htm");
	//char* url = "http://www.baidu.com/";
	//TCHAR* url = _T("https://www.infiplay.ru/i/?c=api&m=login");
	TCHAR* url = _T("http://www.infiplay.ru/i/?c=api&m=login");
	
	//TCHAR* url = _T("https://www.infiplay.ru/p/user/api.htm?call=getAccountByUsernamePassword");


	
	if(MyWinInet.Init(url) == false)
	{
		return 0;
	}

	if(MyWinInet.Send() == false)
	{
		return 0;
	}
		
	TCHAR* p = MyWinInet.Recv();
	if(p == NULL)
	{
		return 0;
	}

	_tprintf(p);
	
/*{"status":0,"data":{"profileid":"4123834","email":"123836@infiplay.com","nickname":"babayaga3578"}}*/

	return 0;
}

