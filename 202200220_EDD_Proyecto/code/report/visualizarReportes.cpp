#include "../menu.h"

void visualizarReportes() {
    string dotFile, pngFile;
    // Reporte aviones arbol
    dotFile = ".\\code\\out\\arbolAviones.dot";
    pngFile = ".\\code\\out\\arbolAviones.png";
    arbolAviones->exportToDOT(dotFile);
    generarGrafico(dotFile, pngFile);
    // Reporte aviones lista
    dotFile = ".\\code\\out\\listaAviones.dot";
    pngFile = ".\\code\\out\\listaAviones.png";
    listaAviones->exportToDOT(dotFile);
    generarGrafico(dotFile, pngFile);
    // Reporte pilotos arbol
    dotFile = ".\\code\\out\\arbolPilotos.dot";
    pngFile = ".\\code\\out\\arbolPilotos.png";
    arbolPilotos->exportToDOT(dotFile);
    generarGrafico(dotFile, pngFile);
    // Reporte pilotos hash
    dotFile = ".\\code\\out\\hashPilotos.dot";
    pngFile = ".\\code\\out\\hashPilotos.png";
    hashPilotos.exportToDOT(dotFile);
    generarGrafico(dotFile, pngFile);
    // Reporte rutos grafo
    dotFile = ".\\code\\out\\grafoRutas.dot";
    pngFile = ".\\code\\out\\grafoRutas.png";
    grafoRutas->exportToDOT(dotFile);
    generarGrafico(dotFile, pngFile);
    // Reporte matriz
    dotFile = ".\\code\\out\\matrizDispersa.dot";
    pngFile = ".\\code\\out\\matrizDispersa.png";
    matrizDispersa->exportToDOT(dotFile);
    generarGrafico(dotFile, pngFile);
}

void generarGrafico(string dotFile, string pngFile){
    cout << "Reporte generado: " << pngFile << std::endl;
    string command = ".\\code\\Graphviz\\bin\\dot.exe -Tpng " + dotFile + " -o " + pngFile;
    system(command.c_str());
    system(pngFile.c_str());
}