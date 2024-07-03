#include "estructuras.h"

BTreeNode::BTreeNode(int t1, int m1, bool leaf1) {
    t = t1;
    m = m1;
    isLeaf = leaf1;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!isLeaf)
            children[i]->traverse();
        std::cout << " " << keys[i].numero_de_registro;
    }

    if (!isLeaf)
        children[i]->traverse();
}

BTreeNode* BTreeNode::search(const std::string& k) {
    int i = 0;
    while (i < keys.size() && k > keys[i].numero_de_registro)
        i++;

    if (i < keys.size() && keys[i].numero_de_registro == k)
        return this;

    if (isLeaf)
        return nullptr;

    return children[i]->search(k);
}

Avion* BTreeNode::getAvionRegistro(const std::string& k) {
    int i = 0;
    while (i < keys.size() && k > keys[i].numero_de_registro)
        i++;

    if (i < keys.size() && keys[i].numero_de_registro == k)
        return &keys[i];

    if (isLeaf)
        return nullptr;

    return children[i]->getAvionRegistro(k);
}
Avion* BTreeNode::getAvionVuelo(BTreeNode* node, const std::string& vuelo) {
    for (int i = 0; i <= m; ++i) {
        if (i < node->keys.size()) 
        if (node->keys[i].vuelo == vuelo) return &node->keys[i];
    }
    for (size_t i = 0; i <= node->keys.size(); ++i) {
        if (!node->isLeaf) {
            Avion* avion = getAvionVuelo(node->children[i], vuelo);
            if(avion != nullptr) return avion;
        }
    }
    return nullptr;
}
Avion* BTreeNode::getAvionDestino(BTreeNode* node, const std::string& destino) {
    for (int i = 0; i <= m; ++i) {
        if (i < node->keys.size()) 
        if (node->keys[i].ciudad_destino == destino) return &node->keys[i];
    }
    for (size_t i = 0; i <= node->keys.size(); ++i) {
        if (!node->isLeaf) {
            Avion* avion = getAvionDestino(node->children[i], destino);
            if(avion != nullptr) return avion;
        }
    }
    return nullptr;
}

void BTree::insert(const Avion& k) {
    if (root == nullptr) {
        root = new BTreeNode(t, m, true);
        root->keys.push_back(k);
        cout << "La aerolinea " << k.numero_de_registro << " se ha registrado. (Disponible)" << endl;
    } else {
        if (search(k.numero_de_registro) == nullptr){
            if (root->keys.size() == m) {
                BTreeNode* s = new BTreeNode(t, m, false);
                s->children.push_back(root);
                s->splitChild(0, root);

                int i = 0;
                if (s->keys[0].numero_de_registro < k.numero_de_registro)
                    i++;
                s->children[i]->insertNonFull(k);

                root = s;
            } else {
                root->insertNonFull(k);
            }
            cout << "La aerolinea " << k.numero_de_registro << " se ha registrado. (Disponible)" << endl;
        } else cout << "ERROR!! La aerolinea " << k.numero_de_registro << " ya esta registrada, saltando. (Disponible)" << endl;
    }
}

void BTreeNode::insertNonFull(const Avion& k) {
    int i = keys.size() - 1;

    if (isLeaf) {
        keys.push_back(k);
        while (i >= 0 && keys[i].numero_de_registro > k.numero_de_registro) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    } else {
        while (i >= 0 && keys[i].numero_de_registro > k.numero_de_registro)
            i--;

        if (children[i + 1]->keys.size() == m) {
            splitChild(i + 1, children[i + 1]);

            if (keys[i + 1].numero_de_registro < k.numero_de_registro)
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->m, y->isLeaf);
    for (int j = 0; j < t - 1; j++)
        z->keys.push_back(y->keys[j + t]);

    if (!y->isLeaf) {
        for (int j = 0; j < t; j++)
            z->children.push_back(y->children[j + t]);
    }

    y->keys.resize(t - 1);
    if (!y->isLeaf) {
        y->children.resize(t); // Esto asegura que solo mantenemos los primeros t hijos
    }
    y->children.resize(t);

    children.insert(children.begin() + i + 1, z);

    keys.insert(keys.begin() + i, y->keys[t - 1]);
    y->keys.pop_back();
}

void BTree::remove(const std::string& k) {
    if (!root) {
        std::cout << "El árbol está vacío\n";
        return;
    }

    root->remove(k);

    if (root->keys.size() == 0) {
        BTreeNode* tmp = root;
        if (root->isLeaf)
            root = nullptr;
        else
            root = root->children[0];

        delete tmp;
    }
}

void BTreeNode::remove(const std::string& k) {
    int idx = 0;
    while (idx < keys.size() && keys[idx].numero_de_registro < k)
        ++idx;

    if (idx < keys.size() && keys[idx].numero_de_registro == k) {
        if (isLeaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (isLeaf) {
            std::cout << "El número de registro " << k << " no existe en el árbol\n";
            return;
        }

        bool flag = (idx == keys.size());

        if (children[idx]->keys.size() < t)
            fill(idx);

        if (flag && idx > keys.size())
            children[idx - 1]->remove(k);
        else
            children[idx]->remove(k);
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    keys.erase(keys.begin() + idx);
}

void BTreeNode::removeFromNonLeaf(int idx) {
    std::string k = keys[idx].numero_de_registro;

    if (children[idx]->keys.size() >= t) {
        Avion pred = getPredecessor(idx);
        keys[idx] = pred;
        children[idx]->remove(pred.numero_de_registro);
    } else if (children[idx + 1]->keys.size() >= t) {
        Avion succ = getSuccessor(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ.numero_de_registro);
    } else {
        merge(idx);
        children[idx]->remove(k);
    }
}

Avion BTreeNode::getPredecessor(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->isLeaf)
        cur = cur->children[cur->keys.size()];

    return cur->keys[cur->keys.size() - 1];
}

Avion BTreeNode::getSuccessor(int idx) {
    BTreeNode* cur = children[idx + 1];
    while (!cur->isLeaf)
        cur = cur->children[0];

    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && children[idx - 1]->keys.size() >= t)
        borrowFromPrev(idx);
    else if (idx != keys.size() && children[idx + 1]->keys.size() >= t)
        borrowFromNext(idx);
    else {
        if (idx != keys.size())
            merge(idx);
        else
            merge(idx - 1);
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];

    child->keys.insert(child->keys.begin(), keys[idx - 1]);

    if (!child->isLeaf)
        child->children.insert(child->children.begin(), sibling->children[sibling->keys.size()]);

    keys[idx - 1] = sibling->keys[sibling->keys.size() - 1];
    sibling->keys.pop_back();

    if (!sibling->isLeaf)
        sibling->children.pop_back();
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);

    if (!child->isLeaf)
        child->children.push_back(sibling->children[0]);

    keys[idx] = sibling->keys[0];
    sibling->keys.erase(sibling->keys.begin());

    if (!sibling->isLeaf)
        sibling->children.erase(sibling->children.begin());
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);

    for (int i = 0; i < sibling->keys.size(); ++i)
        child->keys.push_back(sibling->keys[i]);

    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->keys.size(); ++i)
            child->children.push_back(sibling->children[i]);
    }

    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);

    delete sibling;
}

void BTree::exportToDOT(const std::string& archivo) {
    std::ofstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << archivo << " para escribir." << std::endl;
        return;
    }

    file << "digraph BTree {\n";
    file << "node [shape=record];\n";
    int nodeId = 0;
    if (root != nullptr) {
        exportToDOTHelper(file, root, nodeId);
    }
    file << "}\n";
    file.close();
}

void BTree::exportToDOTHelper(std::ofstream& file, BTreeNode* node, int& nodeId) {
    int currentId = nodeId++;
    file << "node" << currentId << " [label=\"";
    for (int i = 0; i <= m; ++i) {
        if (i > 0) file << "|";
        file << "<f" << i << ">";
        if (i < node->keys.size()) file << "| " << node->keys[i].numero_de_registro;
        else if(i < m) file << "| nullptr";
    }
    file << "\"];\n";

    for (size_t i = 0; i <= node->keys.size(); ++i) {
        if (!node->isLeaf) {
            int childId = nodeId;
            exportToDOTHelper(file, node->children[i], nodeId);
            file << "node" << currentId << ":f" << i << " -> node" << childId << ";\n";
        }
    }
}