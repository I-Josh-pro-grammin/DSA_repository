// Munezero Impano Christella
// Izere Joshua
// Ndanyuzwe Uhirwa Shami Melissa

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Node {
    string name;
    bool isFile;
    vector<Node*> children;
    Node* parent;

    Node(string name, bool isFile) {
        this->name = name;
        this->isFile = isFile;
        this->parent = nullptr;
    }
};

// ---------------- CREATE FILE SYSTEM ----------------
Node* createFileSystem() {
    Node* root = new Node("/", false);

    Node* documents = new Node("Documents", false);
    Node* pictures = new Node("Pictures", false);

    root->children.push_back(documents);
    documents->parent = root;

    root->children.push_back(pictures);
    pictures->parent = root;

    return root;
}

// ---------------- PRINT TREE ----------------
void printTree(Node* node, string indent = "") {
    cout << indent << node->name << endl;
    for (Node* child : node->children) {
        printTree(child, indent + "  ");
    }
}

// ---------------- DIR ----------------
void dir(Node* current) {
    if (current->children.empty()) {
        cout << "Empty directory\n";
        return;
    }

    for (Node* child : current->children) {
        cout << (child->isFile ? "[FILE] " : "[DIR]  ")
             << child->name << endl;
    }
}

// ---------------- MKDIR ----------------
void mkdir(Node* current, string name) {
    for (Node* child : current->children) {
        if (child->name == name) {
            cout << "Already exists!\n";
            return;
        }
    }

    Node* folder = new Node(name, false);
    folder->parent = current;
    current->children.push_back(folder);
}

// ---------------- TOUCH ----------------
void touch(Node* current, string name) {
    for (Node* child : current->children) {
        if (child->name == name) {
            cout << "File already exists!\n";
            return;
        }
    }

    Node* file = new Node(name, true);
    file->parent = current;
    current->children.push_back(file);
}

// ---------------- FIND CHILD ----------------
Node* findChild(Node* current, string name) {
    for (Node* child : current->children) {
        if (child->name == name)
            return child;
    }
    return nullptr;
}

// ---------------- CD (PATH SUPPORT) ----------------
Node* cd(Node* current, string path) {
    stringstream ss(path);
    string part;

    Node* temp = current;

    while (getline(ss, part, '/')) {
        if (part == "" || part == ".") continue;

        if (part == "..") {
            if (temp->parent != nullptr)
                temp = temp->parent;
        } else {
            Node* next = findChild(temp, part);
            if (next && !next->isFile) {
                temp = next;
            } else {
                cout << "Invalid path!\n";
                return current;
            }
        }
    }

    return temp;
}

// ---------------- PWD ----------------
string getPath(Node* current) {
    if (current->parent == nullptr)
        return "/";

    return getPath(current->parent) +
           (current->parent->parent == nullptr ? "" : "/") +
           current->name;
}

// ---------------- DELETE ----------------
void removeNode(Node* current, string name) {
    for (int i = 0; i < current->children.size(); i++) {
        if (current->children[i]->name == name) {
            delete current->children[i];
            current->children.erase(current->children.begin() + i);
            cout << "Deleted: " << name << endl;
            return;
        }
    }
    cout << "Not found!\n";
}

// ---------------- MAIN ----------------
int main() {
    Node* root = createFileSystem();
    Node* current = root;   // IMPORTANT: persistent current directory

    int choice;

    while (true) {
        cout << "\n==== FILE SYSTEM MENU ====\n";
        cout << "1. View File System\n";
        cout << "2. Navigate File System\n";
        cout << "3. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        if (choice == 1) {
            printTree(root);
        }

        else if (choice == 2) {

    cout << "\n--- NAVIGATION MODE ---\n";
    cout << "Available commands:\n";
    cout << "  dir           -> list current directory\n";
    cout << "  cd <folder>   -> enter folder or '..'\n";
    cout << "  mkdir <name>  -> create folder\n";
    cout << "  touch <name>  -> create file\n";
    cout << "  rm <name>     -> delete file/folder\n";
    cout << "  pwd           -> show current path\n";
    cout << "  tree          -> show full structure\n";
    cout << "  back          -> return to main menu\n\n";

    string command;

    while (true) {
        cout << getPath(current) << "> ";
        cin >> command;

        if (command == "dir") {
            dir(current);
        }

        else if (command == "cd") {
            string path;
            cin >> path;
            current = cd(current, path);
        }

        else if (command == "mkdir") {
            string name;
            cin >> name;
            mkdir(current, name);
        }

        else if (command == "touch") {
            string name;
            cin >> name;
            touch(current, name);
        }

        else if (command == "rm") {
            string name;
            cin >> name;
            removeNode(current, name);
        }

        else if (command == "pwd") {
            cout << getPath(current) << endl;
        }

        else if (command == "tree") {
            printTree(root);
        }

        else if (command == "back") {
            cout << "Returning to main menu...\n";
            break;
        }

        else {
            cout << "Unknown command!\n";
        }
    }
}


        else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
