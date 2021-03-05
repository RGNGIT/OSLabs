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

void Proc(int ID) { // Процесс
	system("cls");
	sAddress LADR = Head;
	BYTE local; cout << "Введите данные (1 байт): "; cin >> local;
	DWORD dlocal; cout << "Сколько байт занять: "; cin >> dlocal;
	if (dlocal > (_MemoryTotal - _MemoryUsage)) {
		cout << "Переполнение стека!\n";
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

void AllocMem() { // Выделение памяти (сборка стека)
	system("cls");
    DWORD Mem;
	cout << "Введите кол-во памяти для выделения (байт): "; cin >> Mem;
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

void MemCheck() { // Чек памяти
	system("cls");
	sAddress LADR = Head;
	cout << "1 - Вывести все ячейки\n2 - Вывести ячейки одного процесса\n\n";
	switch (_getch()) {
	case 49: 
		for (UINT i = 0; i < (UINT)_MemoryTotal; i++) {
			cout << "Ячейка памяти: " << LADR << '\n';
			cout << "ID: " << LADR->sID << '\n';
			cout << "ID процесса: " << LADR->pID << '\n';
			cout << "Данные: " << LADR->Data << "\n\n";
			LADR = LADR->Next;
		}
		break;
	case 50:
		DWORD localpid; cout << "Введите ID: "; cin >> localpid;
		for (UINT i = 0; i < (UINT)_MemoryTotal; i++) {
			if (LADR->pID == localpid) {
				cout << "Ячейка памяти: " << LADR << '\n';
				cout << "ID: " << LADR->sID << '\n';
				cout << "ID процесса: " << LADR->pID << '\n';
				cout << "Данные: " << LADR->Data << "\n\n";
			}
			LADR = LADR->Next;
		}
		break;
	}
	_getch();
}

void GetInfo() {
	cout << "Текущая статистика:" << "\nПамять (использовано/всего): " << _MemoryUsage << " bytes/" << _MemoryTotal << " bytes\nШаг трассировки: " << _TraceStep << '\n';
}

int main() {
	setlocale(0, "");
	Head = new Sector;
	cout << "Введите диапазон трассировки: "; cin >> _TraceStep;
	while (1) {
		system("cls");
		cout << "1 - Выделить память\n2 - Вызвать процесс заполнения\n3 - Вывести секторы выделенной памяти\n";
		GetInfo();
		switch (_getch()) {
		case 49: AllocMem(); break;
		case 50: Proc(_CurrentProcID); _CurrentProcID++; break;
		case 51: MemCheck(); break;
		}
	}
	return 0;
}