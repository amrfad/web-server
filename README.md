# Proyek Web Server Nihilon

## Ringkasan Proyek
Nihilon adalah implementasi web server berkinerja tinggi yang ditulis dalam bahasa C, dirancang untuk mendemonstrasikan konsep-konsep pemrograman sistem tingkat lanjut termasuk komunikasi antar-proses, pemrograman socket jaringan, dan penanganan permintaan yang efisien menggunakan arsitektur process pool.

## Fitur Utama Proyek
- **Dukungan Protokol HTTP**
  - Metode yang Didukung: GET, POST, HEAD
  - Mendukung versi protokol HTTP/1.0 dan HTTP/1.1
  - Parsing permintaan dan generasi respons yang handal

- **Optimasi Kinerja**
  - Arsitektur process pool untuk penanganan klien secara bersamaan
  - Dukungan kompresi Gzip
  - Pemrosesan permintaan dengan overhead rendah
  - Manajemen memori yang efisien

- **Kemampuan Teknis Utama**
  - Pemrograman socket TCP
  - Penyajian file dinamis
  - Penanganan kesalahan yang fleksibel
  - Mekanisme logging
  - Kompatibilitas lintas platform Linux

## Persyaratan Sistem
- **Sistem Operasi**: Distribusi Linux
- **Kompiler**: GCC
- **Dependensi**: 
  - zlib (untuk kompresi Gzip)
  - Utilitas Make
- **Perangkat Keras yang Direkomendasikan**: 
  - Prosesor multicore
  - RAM minimal 512MB

## Langkah Instalasi

### 1. Prasyarat
Pastikan Anda telah menginstal:
```bash
sudo apt-get update
sudo apt-get install build-essential zlib1g-dev
```

### 2. Kloning Repositori
```bash
git clone https://github.com/amrfad/web-server.git
cd web-server
```

### 3. Kompilasi Proyek
```bash
make all
```

### 4. Jalankan Server
```bash
./bin/nihilon
```

## Konfigurasi
- **Port Default**: 8080
- **Direktori Root Web**: ./www
- **Direktori Log**: ./logs

## Metrik Kinerja
Berdasarkan pengujian Apache Benchmark:
- **Permintaan yang Ditangani**: 10.000
- **Klien Bersamaan**: 16
- **Throughput**: ~3.023 permintaan/detik
- **Tingkat Kegagalan**: 0%

## Debugging dan Logging
- Logging kesalahan komprehensif
- Pelacakan permintaan/respons detail
- Dukungan mode kompilasi debug

## Penulis
- Amr Fadhilah Abiyyu Alif Basysyar

## Ucapan Terima Kasih
- Politeknik Negeri Bandung
- Dosen Mata Kuliah Sistem Operasi

## Disclaimer
Proyek ini merupakan implementasi akademis dan tidak boleh digunakan di lingkungan produksi tanpa tinjauan keamanan dan pengerasan yang signifikan.

---

**Dikembangkan sebagai bagian dari Proyek Praktikum Mata Kuliah Sistem Operasi, Desember 2024**
