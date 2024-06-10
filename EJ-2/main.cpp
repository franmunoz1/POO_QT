#include <iostream>
#include <windows.h>

typedef void (*HelloFunc)();

int main() {
    // Cargar la librería
    HMODULE hLib = LoadLibrary("mylibrary.dll");
    if (!hLib) {
        std::cerr << "No se pudo cargar la librería" << std::endl;
        return 1;
    }

    // Obtener la dirección de la función
    HelloFunc hello = (HelloFunc)GetProcAddress(hLib, "helloFromLibrary");
    if (!hello) {
        std::cerr << "No se pudo obtener la dirección de la función" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }

    // Llamar a la función
    hello();

    // Liberar la librería
    FreeLibrary(hLib);

    return 0;
}
