#include "estructuras.h"

Node* Arbol::insert(Node* root, Piloto piloto) {
    if (root == nullptr) {
        Node* nodo = new Node;
        nodo->piloto = piloto;
        nodo->left = nullptr;
        nodo->right = nullptr;
        return nodo;
    }
    if (piloto.horas_de_vuelo < root->piloto.horas_de_vuelo) {
        root->left = insert(root->left, piloto);
    } else {
        root->right = insert(root->right, piloto);
    }
    return root;
}

Piloto* Arbol::getPiloto(Node* root, string vuelo) {
    if (root == nullptr) return nullptr;
    if (vuelo == root->piloto.vuelo) return &root->piloto;
    if (vuelo < root->piloto.vuelo) return getPiloto(root->left, vuelo);
    else return getPiloto(root->right, vuelo);
}

Piloto* Arbol::getPilotoId(Node* root, string numero_de_id) {
    if (root == nullptr) return nullptr;
    if (numero_de_id == root->piloto.numero_de_id) return &root->piloto;
    Piloto* piloto = getPilotoId(root->left, numero_de_id);
    if(piloto == nullptr) piloto = getPilotoId(root->right, numero_de_id);
    return piloto;
}

// Pre-order traversal
void Arbol::preOrder(Node* root) {
    if (root) {
        std::cout << root->piloto.nombre << " (" << root->piloto.horas_de_vuelo << " horas)\n";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// In-order traversal
void Arbol::inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        std::cout << root->piloto.nombre << " (" << root->piloto.horas_de_vuelo << " horas)\n";
        inOrder(root->right);
    }
}

// Post-order traversal
void Arbol::postOrder(Node* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        std::cout << root->piloto.nombre << " (" << root->piloto.horas_de_vuelo << " horas)\n";
    }
}

void Arbol::eliminar(Node* root, string numero_de_id) {
    if (root == nullptr) {
        return;
    }

    if (numero_de_id < root->piloto.numero_de_id) {
        eliminar(root->left, numero_de_id);
    } else if (numero_de_id > root->piloto.numero_de_id) {
        eliminar(root->right, numero_de_id);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        } else if (root->left == nullptr) {
            Node* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == nullptr) {
            Node* temp = root;
            root = root->left;
            delete temp;
        } else {
            Node* temp = findMin(root->right);
            root->piloto = temp->piloto;
            eliminar(root->right, temp->piloto.numero_de_id);
        }
    }
}
Node* Arbol::findMin(Node* root) {
    while (root->left != nullptr) root = root->left;
    return root;
}

void Arbol::exportToDOT(const std::string& archivo) {
    std::ofstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << archivo << " para escribir." << std::endl;
        return;
    }

    file << "digraph Arbol {\n";
    file << "node [shape=record];\n";
    int nodeId = 0;
    if (root != nullptr) {
        i = 0;
        exportToDOTHelper(file, root);
    }
    file << "}\n";
    file.close();
}

void Arbol::exportToDOTHelper(ofstream& file, Node* node) {
    int currentId = i++;
    file << "node" << currentId << " [label=\"";
    file << "<f1>| {Horas: " << node->piloto.horas_de_vuelo << " | Numero: " << node->piloto.numero_de_id << "}|<f2>\"];\n";
    if (node->left != nullptr){
        file << "node" << currentId << ":f1 -> node" << i << ";\n";
        exportToDOTHelper(file, node->left);
    }
    if (node->right != nullptr){
        file << "node" << currentId << ":f2 -> node" << i << ";\n";
        exportToDOTHelper(file, node->right);
    }
}