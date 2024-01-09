#include <stdio.h>
#include <Windows.h>

int main()
{
    char dllPath[] = "C:\\hackudao.dll";
    int pID = 19732;

    // 1- Abrindo processo
    HANDLE hProcess = OpenProcess(
        PROCESS_ALL_ACCESS, 
        FALSE, 
        pID
    );

    // 2- Alocando memória no processo remoto
    LPVOID pAddress = VirtualAllocEx(
        hProcess, 
        0, 
        sizeof(dllPath), 
        MEM_COMMIT | MEM_RESERVE, 
        PAGE_READWRITE
    );
    
    printf("\nMemoria remota alocada no endereco: 0x%p", pAddress);
    printf("\nPressione enter para continuar...");
    getchar();

    // 3- Escrevendo o path da DLL na memória alocada do processo remoto
    WriteProcessMemory(
        hProcess, 
        pAddress, 
        dllPath, 
        sizeof(dllPath), 
        NULL
    );
    
    printf("\nPath da DLL escrito no processo remoto.");
    printf("\nPressione enter para continuar...");

    getchar();

    // 4- Inicializando a thread remota para executar a DLL
    printf("\n[*] Iniciando Thread.");
    printf("\nPressione enter para continuar...");
    HANDLE hThread = CreateRemoteThread(
        hProcess, 
        NULL, 
        0, 
        (LPTHREAD_START_ROUTINE)LoadLibraryA, 
        pAddress, 
        0, 
        NULL
    );
    
    getchar();

    // 5- Fechando o handle e liberando memoria
    CloseHandle(hProcess);
    
    VirtualFreeEx(
        hProcess, 
        pAddress, 
        0, 
        MEM_RELEASE
    );
    
}
