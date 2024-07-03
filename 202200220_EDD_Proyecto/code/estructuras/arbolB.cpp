#include "estructuras.h"

BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys = new Avion[t - 1];
    C = new BTreeNode *[t];

    n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i].numero_de_registro;
    }

    if (leaf == false)
        C[i]->traverse();
}

BTreeNode* BTreeNode::search(const std::string& numero_de_registro) {
    int i = 0;
    while (i < n && numero_de_registro > keys[i].numero_de_registro)
        i++;

    if (keys[i].numero_de_registro == numero_de_registro)
        return this;

    if (leaf == true)
        return NULL;

    return C[i]->search(numero_de_registro);
}

Avion* BTreeNode::getAvionRegistro(const std::string& k) {
    int i = 0;
    while (i < n && k > keys[i].numero_de_registro)
        i++;

    if (i < n && keys[i].numero_de_registro == k)
        return &keys[i];

    if (leaf)
        return nullptr;

    return C[i]->getAvionRegistro(k);
}
Avion* BTreeNode::getAvionVuelo(BTreeNode* node, const std::string& vuelo) {
    for (int i = 0; i < (t - 1); ++i) {
        if (node->keys[i].vuelo == vuelo) return &node->keys[i];
    }
    int i = 0;
    for (size_t i = 0; i < (t); ++i) {
        if (!node->leaf) {
            Avion* avion = getAvionVuelo(node->C[i], vuelo);
            if(avion != nullptr) return avion;
        }
    }
    return nullptr;
}
Avion* BTreeNode::getAvionDestino(BTreeNode* node, const std::string& destino) {
    for (int i = 0; i < (t - 1); ++i) {
        if (node->keys[i].ciudad_destino == destino) return &node->keys[i];
    }
    for (size_t i = 0; i < (t); ++i) {
        if (!node->leaf) {
            Avion* avion = getAvionDestino(node->C[i], destino);
            if(avion != nullptr) return avion;
        }
    }
    return nullptr;
}

void BTree::insert(const Avion& k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
        cout << "La aerolinea " << k.numero_de_registro << " se ha registrado. (Disponible)" << endl;
    } else {
        if (search(k.numero_de_registro) == nullptr){
            if (root->n == t - 1) {
                BTreeNode *s = new BTreeNode(t, false);

                s->C[0] = root;

                s->splitChild(0, root);

                int i = 0;
                if (s->keys[0].numero_de_registro < k.numero_de_registro)
                    i++;
                s->C[i]->insertNonFull(k);

                root = s;
            } else {
                root->insertNonFull(k);
            }
            cout << "La aerolinea " << k.numero_de_registro << " se ha registrado. (Disponible)" << endl;
        } else cout << "ERROR!! La aerolinea " << k.numero_de_registro << " ya esta registrada, saltando. (Disponible)" << endl;
    }
}

void BTreeNode::insertNonFull(const Avion& k) {
    int i = n - 1;

    if (leaf == true) {
    while (i >= 0 && keys[i].numero_de_registro > k.numero_de_registro) {
        keys[i + 1] = keys[i];
        i--;
    }

    keys[i + 1] = k;
    n = n + 1;
    } else {
    while (i >= 0 && keys[i].numero_de_registro > k.numero_de_registro)
        i--;

    if (C[i + 1]->n == t - 1) {
        splitChild(i + 1, C[i + 1]);

        if (keys[i + 1].numero_de_registro < k.numero_de_registro)
        i++;
    }
    C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
    z->keys[j] = y->keys[j + t];

    if (y->leaf == false) {
    for (int j = 0; j < t; j++)
        z->C[j] = y->C[j + t];
    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
    C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
    keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n = n + 1;
}

int BTreeNode::findKey(string k) {
  int idx = 0;
  while (idx < n && keys[idx].numero_de_registro < k)
    ++idx;
  return idx;
}

void BTreeNode::deletion(string numero_de_registro) {
  int idx = findKey(numero_de_registro);

  if (idx < n && keys[idx].numero_de_registro == numero_de_registro) {
    if (leaf)
      removeFromLeaf(idx);
    else
      removeFromNonLeaf(idx);
  } else {
    if (leaf) {
      cout << "La llave " << numero_de_registro << " no existe en el arbol\n";
      return;
    }

    bool flag = ((idx == n) ? true : false);

    if (C[idx]->n < t)
      fill(idx);

    if (flag && idx > n)
      C[idx - 1]->deletion(numero_de_registro);
    else
      C[idx]->deletion(numero_de_registro);
  }
  return;
}

// Remove from the leaf
void BTreeNode::removeFromLeaf(int idx) {
  for (int i = idx + 1; i < n; ++i)
    keys[i - 1] = keys[i];

  n--;

  return;
}

// Delete from non leaf node
void BTreeNode::removeFromNonLeaf(int idx) {
  Avion k = keys[idx];

  if (C[idx]->n >= t) {
    Avion pred = getPredecessor(idx);
    keys[idx] = pred;
    C[idx]->deletion(pred.numero_de_registro);
  }

  else if (C[idx + 1]->n >= t) {
    Avion succ = getSuccessor(idx);
    keys[idx] = succ;
    C[idx + 1]->deletion(succ.numero_de_registro);
  }

  else {
    merge(idx);
    C[idx]->deletion(k.numero_de_registro);
  }
  return;
}

Avion BTreeNode::getPredecessor(int idx) {
  BTreeNode *cur = C[idx];
  while (!cur->leaf)
    cur = cur->C[cur->n];

  return cur->keys[cur->n - 1];
}

Avion BTreeNode::getSuccessor(int idx) {
  BTreeNode *cur = C[idx + 1];
  while (!cur->leaf)
    cur = cur->C[0];

  return cur->keys[0];
}

void BTreeNode::fill(int idx) {
  if (idx != 0 && C[idx - 1]->n >= t)
    borrowFromPrev(idx);

  else if (idx != n && C[idx + 1]->n >= t)
    borrowFromNext(idx);

  else {
    if (idx != n)
      merge(idx);
    else
      merge(idx - 1);
  }
  return;
}

// Borrow from previous
void BTreeNode::borrowFromPrev(int idx) {
  BTreeNode *child = C[idx];
  BTreeNode *sibling = C[idx - 1];

  for (int i = child->n - 1; i >= 0; --i)
    child->keys[i + 1] = child->keys[i];

  if (!child->leaf) {
    for (int i = child->n; i >= 0; --i)
      child->C[i + 1] = child->C[i];
  }

  child->keys[0] = keys[idx - 1];

  if (!child->leaf)
    child->C[0] = sibling->C[sibling->n];

  keys[idx - 1] = sibling->keys[sibling->n - 1];

  child->n += 1;
  sibling->n -= 1;

  return;
}

// Borrow from the next
void BTreeNode::borrowFromNext(int idx) {
  BTreeNode *child = C[idx];
  BTreeNode *sibling = C[idx + 1];

  child->keys[(child->n)] = keys[idx];

  if (!(child->leaf))
    child->C[(child->n) + 1] = sibling->C[0];

  keys[idx] = sibling->keys[0];

  for (int i = 1; i < sibling->n; ++i)
    sibling->keys[i - 1] = sibling->keys[i];

  if (!sibling->leaf) {
    for (int i = 1; i <= sibling->n; ++i)
      sibling->C[i - 1] = sibling->C[i];
  }

  child->n += 1;
  sibling->n -= 1;

  return;
}

// Merge
void BTreeNode::merge(int idx) {
  BTreeNode *child = C[idx];
  BTreeNode *sibling = C[idx + 1];

  child->keys[t - 1] = keys[idx];

  for (int i = 0; i < sibling->n; ++i)
    child->keys[i + t] = sibling->keys[i];

  if (!child->leaf) {
    for (int i = 0; i <= sibling->n; ++i)
      child->C[i + t] = sibling->C[i];
  }

  for (int i = idx + 1; i < n; ++i)
    keys[i - 1] = keys[i];

  for (int i = idx + 2; i <= n; ++i)
    C[i - 1] = C[i];

  child->n += sibling->n + 1;
  n--;

  delete (sibling);
  return;
}

void BTree::remove(const string& k) {
  if (!root) {
    cout << "El arbol esta vacio\n";
    return;
  }

  root->deletion(k);

  if (root->n == 0) {
    BTreeNode *tmp = root;
    if (root->leaf)
      root = NULL;
    else
      root = root->C[0];

    delete tmp;
  }
  return;
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
    for (int i = 0; i <= node->t- 1; ++i) {
        if (i > 0) file << "|";
        file << "<f" << i << ">";
        if (i < node->n) file << "| " << node->keys[i].numero_de_registro;
        else file << "| nullptr";
    }
    file << "\"];\n";

    for (size_t i = 0; i < node->t; ++i) {
        if (!node->leaf) {
            int childId = nodeId;
            exportToDOTHelper(file, node->C[i], nodeId);
            file << "node" << currentId << ":f" << i << " -> node" << childId << ";\n";
        }
    }
}