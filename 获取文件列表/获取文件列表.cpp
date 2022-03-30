// ��ȡ�ļ��б�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

void RecursiveFile(const wstring& strTarget,deque<wstring>& deqFiles)
{
	WIN32_FIND_DATA fd;
	wchar_t szTempFileFind[512] = { 0 };
	ZeroMemory(&fd, sizeof(WIN32_FIND_DATA));
	swprintf_s(szTempFileFind, L"%s\\*.*", strTarget.c_str());
	HANDLE hFind = FindFirstFile(szTempFileFind, &fd);
	if (hFind == INVALID_HANDLE_VALUE)
		return ;

	while(FindNextFileW(hFind, &fd))
	{
		if (_tcsicmp(fd.cFileName,L".")==0)
		{
			continue;						
		}
		else if (_tcsicmp(fd.cFileName,L"..")==0)
		{
			continue;
		}
		else
		{
			if ( (fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) == 0)//�ļ�
			{
				wstring strFile = strTarget + L"\\";
				strFile += fd.cFileName;				

				deqFiles.push_back(strFile);
			}
			else	//Ŀ¼
			{
				wstring strFolder = strTarget + L"\\";
				strFolder += fd.cFileName;				

				RecursiveFile(strFolder,deqFiles);
			}
		}
	}//while
	FindClose(hFind);
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		fprintf(stderr,"��������.\r\n");
		return -1;
	}

	wstring strTarget = argv[1];

	fprintf(stdout,"��ʼ����%sĿ¼�µ��ļ����ļ���,�����ĵȴ�\r\n",_A(strTarget));

	deque<wstring> deqFiles;

	RecursiveFile(strTarget,deqFiles);
	
	fprintf(stdout,"���ҵ�%d���ļ����ļ��б�\r\n",deqFiles.size());

	CMd5A theMd5;
	string strMd5;
	fprintf(stdout,"[\r\n");
	for (deque<wstring>::iterator itr=deqFiles.begin();itr!=deqFiles.end();itr++)
	{
		strMd5 = theMd5.MD5file(*itr);
		fprintf(stdout,"{\"file\":\"%s\",\"md5\":\"%s\"},\r\n",_A(*itr),strMd5.c_str());
	}
	fprintf(stdout,"]\r\n�ļ��б�������");
	return 0;
}

