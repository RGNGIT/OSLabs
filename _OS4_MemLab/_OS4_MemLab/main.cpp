#define _BLOCK struct
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

DWORD _MemoryTotal = NULL, _MemoryUsage = 0, _TraceStep = NULL, _CurrentProcID = 1;

_BLOCK Sector {

	BYTE Data;

	DWORD sID, pID;
	Sector * Next;
};

typedef Sector * sAddress;
sAddress Head = new Sector;

UINT Seek(sAddress __LADR) {
	for (UINT i = 0; i < (UINT)_MemoryTotal; i++) {
		if (__LADR->Data == NULL) { return i; } __LADR = __LADR->Next;
	}
}

void Proc(int ID) { // �������
	system("cls");
	sAddress LADR = Head;
	BYTE local; cout << "������� ������ (1 ����): "; cin >> local;
	DWORD dlocal; cout << "������� ���� ������: "; cin >> dlocal;
	if (dlocal > (_MemoryTotal - _MemoryUsage)) {
		cout << "������������ �����!\n";
		_getch(); return;
	}
	for (UINT i = Seek(LADR); i < (UINT)_MemoryTotal; i++) {
		if (LADR->Data == NULL && i % (UINT)_TraceStep == 0 && dlocal > 0) {
			LADR->pID = (DWORD)ID;
			LADR->Data = local;
			_MemoryUsage++; dlocal--;
		}
		LADR = LADR->Next;
	}
	_getch();
}

void AllocMem() { // ��������� ������ (������ �����)
	system("cls");
    DWORD Mem;
	cout << "������� ���-�� ������ ��� ��������� (����): "; cin >> Mem;
	sAddress LADR = Head;
	for (UINT i = 0; i < (UINT)Mem; i++) {
		LADR->Next = new Sector;
		LADR->sID = (DWORD)i;
		LADR->Data = NULL;
		LADR->pID = NULL;
		LADR = LADR->Next;
	}
	LADR->Next = NULL;
	_MemoryTotal = Mem;
	_getch();
}

void MemCheck() { // ��� ������
	system("cls");
	sAddress LADR = Head;
	cout << "1 - ������� ��� ������\n2 - ������� ������ ������ ��������\n\n";
	switch (_getch()) {
	case 49: 
		for (UINT i = 0; i < (UINT)_MemoryTotal; i++) {
			cout << "������ ������: " << LADR << '\n';
			cout << "ID: " << LADR->sID << '\n';
			cout << "ID ��������: " << LADR->pID << '\n';
			cout << "������: " << LADR->Data << "\n\n";
			LADR = LADR->Next;
		}
		break;
	case 50:
		DWORD localpid; cout << "������� ID: "; cin >> localpid;
		for (UINT i = 0; i < (UINT)_MemoryTotal; i++) {
			if (LADR->pID == localpid) {
				cout << "������ ������: " << LADR << '\n';
				cout << "ID: " << LADR->sID << '\n';
				cout << "ID ��������: " << LADR->pID << '\n';
				cout << "������: " << LADR->Data << "\n\n";
			}
			LADR = LADR->Next;
		}
		break;
	}
	_getch();
}

void GetInfo() {
	cout << "������� ����������:" << "\n������ (������������/�����): " << _MemoryUsage << " bytes/" << _MemoryTotal << " bytes\n��� �����������: " << _TraceStep << '\n';
}

int main() {
	setlocale(0, "");
	Head = new Sector;
	cout << "������� �������� �����������: "; cin >> _TraceStep;
	while (1) {
		system("cls");
		cout << "1 - �������� ������\n2 - ������� ������� ����������\n3 - ������� ������� ���������� ������\n";
		GetInfo();
		switch (_getch()) {
		case 49: AllocMem(); break;
		case 50: Proc(_CurrentProcID); _CurrentProcID++; break;
		case 51: MemCheck(); break;
		}
	}
	return 0;
}