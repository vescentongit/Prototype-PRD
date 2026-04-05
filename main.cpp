#include <bits/stdc++.h>
#include <mapAlgo.hpp>
using namespace std;

int main(){
    Graph campus;

    // ===== Input Cuaca =====
    int cuacaInput;
    cout << "Kondisi cuaca (1=Hujan, 0=Cerah): ";
    cin >> cuacaInput;
    bool isRaining = (cuacaInput == 1);
    cout << "Mode aktif: " << (isRaining ? "Hujan — prioritas jalur beratap\n" : "Cerah — prioritas jarak & slope\n");
    cin.ignore();

    // ===== Input Node (Lokasi) =====
    int jumlahNode;
    cout << "\nMasukkan jumlah lokasi: ";
    cin >> jumlahNode;
    cin.ignore();

    cout << "\n--- Input Lokasi ---\n";
    cout << "(Titik referensi = pojok ujung kiri kampus = 0, 0)\n\n";

    for(int i = 0; i < jumlahNode; i++){
        string nama;
        double x, y, elev;

        cout << "Lokasi ke-" << i+1 << ":\n";
        cout << "  Nama                        : "; getline(cin, nama);
        cout << "  X (Kanan/Kiri)    (meter)   : "; cin >> x;
        cout << "  Y (Depan/Belakang)(meter)   : "; cin >> y;
        cout << "  Elevasi           (mdpl)    : "; cin >> elev;
        cin.ignore();
        cout << endl;

        campus.addNode(nama, x, y, elev);
    }

    // ===== Input Edge (Jalan) =====
    int jumlahEdge;
    cout << "--- Daftar Lokasi ---\n";
    for(int i = 0; i < (int)campus.nodes.size(); i++){
        cout << "  [" << i << "] " << campus.nodes[i].name << "\n";
    }

    cout << "\nMasukkan jumlah jalan (edges): ";
    cin >> jumlahEdge;

    cout << "\n--- Input Jalan ---\n";
    for(int i = 0; i < jumlahEdge; i++){
        int from, to, roofInput;
        cout << "Jalan ke-" << i+1 << ":\n";
        cout << "  Dari index               : "; cin >> from;
        cout << "  Ke index                 : "; cin >> to;
        cout << "  Ada atap? (1=Ya, 0=Tidak): "; cin >> roofInput;
        bool hasRoof = (roofInput == 1);

        campus.addEdge(from, to, hasRoof);
        campus.addEdge(to, from, hasRoof);

        cout << "  Jarak  : " << campus.hitungJarak(from, to) << " meter (otomatis)\n";
        cout << "  Slope  : " << campus.hitungSlope(from, to) << "% (otomatis)\n";
        cout << "  Atap   : " << (hasRoof ? "Ada" : "Tidak ada") << "\n\n";
    }

    // ===== Pencarian Route =====
    string startName, goalName;
    cin.ignore();
    cout << "--- Pencarian Rute ---\n";
    cout << "Dari  : "; getline(cin, startName);
    cout << "Ke    : "; getline(cin, goalName);

    int start = campus.findNode(startName);
    int goal  = campus.findNode(goalName);

    if(start == -1 || goal == -1){
        cout << "Location not found!\n";
        return 1;
    }

    double slopeWeight;
    cout << "Slope weight (0-10 | Kecuraman Tidak Penting-Pilih Jalur Paling Landai): ";
    cin >> slopeWeight;

    vector<int> path = dijkstra(campus, start, goal, slopeWeight, isRaining);

    cout << "\nRute terbaik dari " << startName << " ke " << goalName << ":\n";
    for(int node : path){
        if(node != path.back()){
            cout << campus.nodes[node].name
                << " (x=" << campus.nodes[node].x
                << ", y=" << campus.nodes[node].y
                << ") --> ";
        } else {
            cout << campus.nodes[node].name
                << " (x=" << campus.nodes[node].x
                << ", y=" << campus.nodes[node].y
                << ")" << endl;
        }
    }

    return 0;
}