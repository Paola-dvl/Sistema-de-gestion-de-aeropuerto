#include "../menu.h"

HashTable::HashTable(int size) : size(size) {
    table = new HashNode*[size];
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < size; ++i) {
        HashNode* entry = table[i];
        while (entry != nullptr) {
            HashNode* prev = entry;
            entry = entry->next;
            delete prev;
        }
    }
    delete[] table;
}

int HashTable::hashFunction(const std::string& key) {
    int numKey = std::stoi(key.substr(1));
    return numKey % size;
}

bool HashTable::insert(Piloto piloto) {
    int index = hashFunction(piloto.numero_de_id);
    HashNode* newNode = new HashNode(piloto);

    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        HashNode* entry = table[index];
        while (entry->next != nullptr) {
            entry = entry->next;
        }
        entry->next = newNode;
    }
    return true;
}

void HashTable::eliminar(Piloto* piloto) {
    int index = hashFunction(piloto->numero_de_id);
    HashNode* entry = table[index];
    HashNode* prev = nullptr;

    while (entry != nullptr) {
        if (entry->piloto.numero_de_id == piloto->numero_de_id) {
            if (prev == nullptr) {
                table[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            delete entry;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}


void HashTable::exportToDOT(const string& archivo) {
    std::ofstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << archivo << " para escribir." << std::endl;
        return;
    }


    file << "digraph HashTable {\n";
    file << "  node [shape=record];\n";

    for (int i = 0; i < size; ++i) {
        file << "  node" << i << " [label=\"<f0> " << i << "\"];\n";
        HashNode* entry = table[i];
        int count = 0;
        while (entry != nullptr) {
            file << "  node" << i << "f" << count << " [label=\"{ " << entry->piloto.numero_de_id << " | " << entry->piloto.nombre << " }\"];\n";
            if (count == 0) {
                file << "  node" << i << " -> node" << i << "f" << count << ";\n";
            } else {
                file << "  node" << i << "f" << (count-1) << " -> node" << i << "f" << count << ";\n";
            }
            entry = entry->next;
            count++;
        }
    }

    file << "}\n";
    file.close();
}