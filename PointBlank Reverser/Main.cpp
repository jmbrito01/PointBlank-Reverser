#include "Includes.h"
#include "GUI\GUIIncludes.h"
#include "Helpers\AsmHelper.h"
#include "Helpers\FileHelper.h"
#include "Helpers\StringHelper.h"

unique_ptr<GUIForm> MainFrm;
unique_ptr<GUIObject> lblStatus;
unique_ptr<GUITextBox> txtPath;
unique_ptr<GUIProgressBar> pbMain;

LRESULT CALLBACK MainProc(HWND hWin,UINT uMsg,WPARAM wParam,LPARAM lParam);

//##################################################################
//[ ADITIONAL FUNCTIONS ]
vector<std::string> &split(const string &s, char delim, vector<std::string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}
vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}
//##################################################################


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MainFrm = unique_ptr<GUIForm>(new GUIForm(IDD_MAIN, (DLGPROC)MainProc));
	ExitProcess(0);
	return 0;
}

LRESULT CALLBACK MainProc(HWND hWin, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		EndDialog(hWin, 0);
		break;
	case WM_INITDIALOG:
		lblStatus = NEW_UNIQUE(GUIObject, GUIObject());
		lblStatus->SetHandle(hWin, IDC_STATUS);
		txtPath = NEW_UNIQUE(GUITextBox, GUITextBox(hWin, IDC_PATH));
		pbMain = NEW_UNIQUE(GUIProgressBar, GUIProgressBar(hWin, IDC_PROGRESS));
#ifdef ACE_DEBUG
		txtPath->SetText("C:\\Users\\jmbri\\Documents\\Dumped2503.exe");
#endif
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_LOAD:
			lblStatus->SetText("Loading file...");
			AsmHelper* pAsm = new AsmHelper();
			FileHelper* pFile = new FileHelper(txtPath->GetText());
			if (pFile->GetError() == ERROR_SUCCESS)
			{
				void* pCode = pFile->Read(pFile->GetCodeSection()->PointerToRawData, pFile->GetCodeSection()->SizeOfRawData);
				lblStatus->SetText("Analysing mnemonics...");
				pbMain->SetRange((DWORD)pCode, (DWORD)(pCode)+pFile->GetCodeSection()->SizeOfRawData);
				ofstream logg;
				logg.open("thiscall.txt", ios::out);
				
				DISASM MyDisasm = { 0 };
				int len, i = 0;
				int Error = 0;
				MyDisasm.EIP = (DWORD)pCode;
				while ((!Error) && (MyDisasm.EIP < (DWORD)(pCode) +pFile->GetCodeSection()->SizeOfRawData))
				{
					len = Disasm(&MyDisasm);
					if (len == UNKNOWN_OPCODE)
						len = 1;
					char* lpBuff = new char[MAX_PATH];
					ZeroMemory(lpBuff, MAX_PATH);
					sprintf(lpBuff, "Analysing address 0x%X / 0x%X", MyDisasm.EIP, (DWORD)(pCode)+pFile->GetCodeSection()->SizeOfRawData);
					lblStatus->SetText(lpBuff);
					delete lpBuff;
					vector<string> Command = split(string(MyDisasm.CompleteInstr), ' ');
					if (Command[0].compare("push") == 0)
					{
						string lpAddr = Command[1];
						lpAddr.erase(lpAddr.end() - 1);
						DWORD dwAddr = pFile->UpdateBaseInAddr(StringHelper::StringToHex(lpAddr));
						if (dwAddr == -1)
							continue;
						if (StringHelper::IsValidString(string((char*)dwAddr)))
						{
							string lpStr = string((char*)dwAddr);
							//CHECK IF THISCALL
							if (lpStr.find("__thiscall") != lpStr.npos && lpStr.find("::") != lpStr.npos)
							{
								logg << lpStr << endl;
							}
						}

					}
					pbMain->SetPos(MyDisasm.EIP);
					DefWindowProc(hWin, uMsg, wParam, lParam);
					MyDisasm.EIP += len;
				}
			}
			else
			{
				MessageBox(hWin, "ERROR CREATING THE FILE HELPER!", "ERROR", MB_ICONERROR + MB_OK);
			}
			break;
		}
		break;
	}
	return DefWindowProc(hWin, uMsg, wParam, lParam);
}