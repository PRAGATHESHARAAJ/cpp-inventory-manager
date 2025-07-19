#include <iostream> #include <fstream> #include <vector> #include <string> #include <iomanip> #include <algorithm> #include <map> using namespace std;

class Product { public: int id; string name; string category; string supplier; int quantity; double price;

Product() {}
Product(int i, string n, string c, string s, int q, double p) :
    id(i), name(n), category(c), supplier(s), quantity(q), price(p) {}

void display() const {
    cout << left << setw(6) << id << setw(15) << name << setw(12)
         << category << setw(12) << supplier << setw(10)
         << quantity << "Rs." << fixed << setprecision(2) << price << endl;
}

};

bool authenticate() { string user, pass; cout << "\nLogin to Inventory System" << endl; cout << "Username: "; cin >> user; cout << "Password: "; cin >> pass; return user == "admin" && pass == "1234"; }

class InventoryManager { private: vector<Product> products; const string filename = "inventory.dat";

void loadFromFile() {
    ifstream file(filename, ios::binary);
    if (file.is_open()) {
        Product temp;
        while (file.read((char*)&temp, sizeof(Product))) {
            products.push_back(temp);
        }
        file.close();
    }
}

void saveToFile() {
    ofstream file(filename, ios::binary | ios::trunc);
    for (const auto& p : products) {
        file.write((char*)&p, sizeof(Product));
    }
    file.close();
}

public: InventoryManager() { loadFromFile(); }

~InventoryManager() {
    saveToFile();
}

void addProduct() {
    Product p;
    cout << "Enter Product ID: "; cin >> p.id;
    cout << "Name: "; cin >> ws; getline(cin, p.name);
    cout << "Category: "; getline(cin, p.category);
    cout << "Supplier: "; getline(cin, p.supplier);
    cout << "Quantity: "; cin >> p.quantity;
    cout << "Price: "; cin >> p.price;
    products.push_back(p);
    cout << "Product added successfully!\n";
}

void viewInventory() {
    cout << "\n--- Inventory List ---\n";
    cout << left << setw(6) << "ID" << setw(15) << "Name" << setw(12)
         << "Category" << setw(12) << "Supplier" << setw(10) << "Qty"
         << "Price" << endl;
    cout << string(60, '-') << endl;
    for (const auto& p : products) {
        p.display();
    }
}

void updateStock() {
    int id, qty;
    cout << "Enter Product ID to update: "; cin >> id;
    for (auto& p : products) {
        if (p.id == id) {
            cout << "Enter new quantity: "; cin >> qty;
            p.quantity = qty;
            cout << "Quantity updated successfully!\n";
            return;
        }
    }
    cout << "Product not found.\n";
}

void deleteProduct() {
    int id;
    cout << "Enter Product ID to delete: "; cin >> id;
    auto it = remove_if(products.begin(), products.end(), [&](Product& p) {
        return p.id == id;
    });
    if (it != products.end()) {
        products.erase(it, products.end());
        cout << "Product deleted.\n";
    } else {
        cout << "Product not found.\n";
    }
}

void lowStockAlert(int threshold = 5) {
    cout << "\n--- Low Stock Items ---\n";
    for (const auto& p : products) {
        if (p.quantity <= threshold) {
            p.display();
        }
    }
}

void generateReport() {
    double totalValue = 0;
    map<string, int> categoryCount;
    for (const auto& p : products) {
        totalValue += p.price * p.quantity;
        categoryCount[p.category]++;
    }
    cout << "\n--- Inventory Report ---\n";
    cout << "Total Inventory Value: Rs." << fixed << setprecision(2) << totalValue << endl;
    cout << "Category-wise count:\n";
    for (const auto& pair : categoryCount) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

};

int main() { if (!authenticate()) { cout << "Authentication Failed!\n"; return 1; } InventoryManager inv; int choice; do { cout << "\n--- Inventory Menu ---\n"; cout << "1. Add Product\n2. View Inventory\n3. Update Stock\n4. Delete Product\n"; cout << "5. Low Stock Alert\n6. Generate Report\n0. Exit\nChoice: "; cin >> choice; switch (choice) { case 1: inv.addProduct(); break; case 2: inv.viewInventory(); break; case 3: inv.updateStock(); break; case 4: inv.deleteProduct(); break; case 5: inv.lowStockAlert(); break; case 6: inv.generateReport(); break; case 0: cout << "Exiting...\n"; break; default: cout << "Invalid choice!\n"; } } while (choice != 0); return 0; }
