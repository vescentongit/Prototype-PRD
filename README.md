# Campus Route Finder

Intinya nyari jalan paling enak di kampus, bukan cuma yang paling pendek, tapi juga yang paling ga bikin ngos-ngosan, dan sekarang udah ditambahin fitur bisa ngindarin jalan yang ga ada atapnya kalau lagi hujan.

---

## Latar Belakang

Pengalaman dari awal OSKM, kampus kita capek banget buat jalan. Jalan 200 meter tapi nanjak 30 derajat beda rasanya sama jalan 300 meter tapi datar. Belum lagi kalau hujan, jalan yang ga ada atapnya jadi mimpi buruk.

Program ini ngitung rute dengan mempertimbangkan tiga hal sekaligus: _jarak_, _kemiringan jalan_, dan _kondisi cuaca_.

Algoritmanya Dijkstra, tapi weight functionnya dimodifikasi:

```
biaya = jarak + roofPenalty + (slopeWeight * kemiringan) 
```

- `slopeWeight` — seberapa peka program sama tanjakan. Set ke 0 kalau mau jarak terpendek aja, naikin nilainya kalau mau rute yang lebih landai.
- `roofPenalty` — kalau hujan dan jalan tidak ada atapnya, dikasih penalty besar (99999) supaya Dijkstra otomatis menghindarinya.

---

## How to Use

### Compile

```bash
g++ -std=c++17 main.cpp -o [nama] && ./[nama]
```

### Input yang dibutuhkan

Program bakal nanya satu-satu, dimulai dari kondisi cuaca:

```
Kondisi cuaca (1=Hujan, 0=Cerah): 1
Mode aktif: Hujan — prioritas jalur beratap
```

Lalu input lokasi seperti biasa:

```
Masukkan jumlah lokasi: 4

Lokasi ke-1:
  Nama                        : Gerbang
  X (Kanan/Kiri)    (meter)   : 0
  Y (Depan/Belakang)(meter)   : 0
  Elevasi           (mdpl)    : 800
```

Koordinat pakai X, Y dalam **meter** dari titik referensi (0, 0).

```
Y
↑
│  [Gedung A]
│  [Persimpangan]
|  [Gerbang]  ←  (0, 0) titik referensi (misal)
----------------> X
```

Waktu input jalan, sekarang ada pertanyaan tambahan soal atap:

```
Jalan ke-1:
  Dari index               : 0
  Ke index                 : 1
  Ada atap? (1=Ya, 0=Tidak): 1
  Jarak  : 120.0 meter (otomatis)
  Slope  : 3.3% (otomatis)
  Atap   : Ada
```

Jarak dan kemiringan **dihitung otomatis** dari koordinat yang diinput.

### Output

```
Rute terbaik dari Gerbang ke Gedung A:
  Gerbang (x=0, y=0) --> Persimpangan (x=100, y=50) --> Gedung A (x=200, y=150)
```

Kalau hujan dan tidak ada rute beratap yang bisa dicapai, program tetap nampilin rute terpendek yang tersedia.

---

## Struktur Kode

```
├── main.cpp        — input/output + logika cuaca
└── mapAlgo.hpp
    ├── struct Edge     — ke mana, berapa jauh, berapa curam, ada atap atau tidak
    ├── struct Node     — nama, koordinat, elevasi, daftar jalan keluar
    ├── struct Graph    — keseluruhan peta + fungsi addNode/addEdge
    ├── struct State    — tiket buat priority queue
    └── dijkstra()      — fungsi utama pencarian rute
```

---

## Cara Kerja Singkat

1. User input kondisi cuaca di awal
2. Semua jarak diinisialisasi `∞` dulu
3. Mulai dari node awal, masukin ke priority queue
4. Tiap iterasi, ambil node dengan weight terkecil
5. Cek semua tetangganya — kalau hujan dan jalan tidak ada atap, langsung dikasih penalty besar
6. Kalau ketemu jalan yang lebih murah, update
7. Ulang sampai nyampe tujuan
8. Rekonstruksi rute dari belakang pakai array `prev[]`

---

## Anggota

| Nama                       | NIM      |
|----------------------------|----------|
| Muhammad Orkhan            | 18225091 |
| Agastya Tristan Dhaniswara | 18225093 |
| Tirta Wening Putri Harsono | 18225095 |
| Fayza Kamilia              | 18225097 |
| Lana Dzakira Cahyadi       | 18225099 |

---

## Lisensi

MIT