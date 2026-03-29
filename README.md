# Campus Route Finder

Intinya nyari jalan paling enak di kampus, bukan cuma yang paling pendek, tapi juga yang paling ga bikin ngos-ngosan.

---

## Latar Belakang

Pengalaman dari awal OSKM, kampus kita capek banget buat jalan. Jalan 200 meter tapi nanjak 30 derajat beda rasanya sama jalan 300 meter tapi datar. Program ini ngitung rute dengan mempertimbangkan dua hal sekaligus: _jarak_ dan _kemiringan/elevasi jalan_.

Algoritmanya Dijkstra, tapi weight functionnya dimodifikasi:

```
biaya = jarak + (slopeWeight * kemiringan)
```

`slopeWeight` ini yang nentuin seberapa _peka_ program ini sama tanjakan. Set ke 0 kalau mau jarak terpendek aja, naikin nilainya kalau mau rute yang lebih landai.

---

## How to Use

### Compile

```bash
g++ main.cpp -o [masukin nama yang kamu mau] && ./[masukin nama yang kamu mau]
```

### Input yang dibutuhkan

Program bakal nanya satu-satu:

```
Masukkan jumlah lokasi: 4

Lokasi ke-0:
  Nama      : Gerbang
  X (meter) : 0
  Y (meter) : 0
  Elevasi   : 800
```

Koordinat pakai X, Y dalam **meter** dari titik referensi (0.0).

```
Y
↑
│  [Gedung A]
│  [Persimpangan]
|  [Gerbang]  ←  (0, 0) titik referensi (misal)
----------------> X
```

Jarak antar titik dan kemiringannya **dihitung otomatis** dari koordinat yang diinput.

### Output

```
Rute terbaik dari Gerbang ke Gedung A:
  Gerbang (x=0, y=0) --> Persimpangan (x=100, y=50) --> Gedung A (x=200, y=150)
```

---

## Struktur Kode

```
main.cpp
├── struct Edge      — satu edge berisi: ke mana, berapa jauh, berapa curam
├── struct Node      — satu node berisi: nama, koordinat, elevasi, daftar jalan keluar
├── struct Graph     — keseluruhan peta + fungsi addNode/addEdge
├── struct State     — buat priority queue
└── dijkstra()       — fungsi utama pencarian rute
```

---

## Cara Kerja Singkat

1. Semua jarak diinisialisasi `∞` dulu
2. Mulai dari node awal, masukin ke priority queue
3. Tiap iterasi, ambil node dengan weight terkecil
4. Cek semua tetangganya (edges), kalau ketemu jalan yang lebih murah, update
5. Ulang sampai nyampe tujuan
6. Rekonstruksi rute dari belakang pakai array `prev[]`

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