#include <stdio.h>
#include <string.h>

#define MAX_PRODUK 50
#define MAX_NAMA 50

/* =========================
   DEKLARASI ARRAY
   ========================= */
char namaProduk[MAX_PRODUK][MAX_NAMA];
int harga[MAX_PRODUK];
int stok[MAX_PRODUK];
int terjual[MAX_PRODUK];

int jumlahProduk = 5;


/* =========================
   FUNGSI INPUT INTEGER
   ========================= */
int inputInteger(char pesan[]) {
    int nilai;

    printf("%s", pesan);
    scanf("%d", &nilai);

    return nilai;
}


/* =========================
   MENAMPILKAN PRODUK
   ========================= */
void tampilProduk() {
    int i;

    printf("\n===============================================\n");
    printf("              DAFTAR PRODUK KANTIN\n");
    printf("===============================================\n");

    printf("%-5s %-20s %-12s %-10s %-10s\n",
           "No", "Nama Produk", "Harga", "Stok", "Terjual");

    printf("---------------------------------------------------------------\n");

    for (i = 0; i < jumlahProduk; i++) {
        printf("%-5d %-20s Rp%-10d %-10d %-10d\n",
               i + 1,
               namaProduk[i],
               harga[i],
               stok[i],
               terjual[i]);
    }

    printf("---------------------------------------------------------------\n");
}


/* =========================
   TAMBAH PRODUK
   ========================= */
void tambahProduk() {
    if (jumlahProduk >= MAX_PRODUK) {
        printf("\nKapasitas produk sudah penuh!\n");
        return;
    }

    printf("\n=== TAMBAH PRODUK ===\n");

    getchar();

    printf("Nama produk : ");
    fgets(namaProduk[jumlahProduk], MAX_NAMA, stdin);

    /* Menghapus newline dari fgets */
    namaProduk[jumlahProduk][strcspn(
        namaProduk[jumlahProduk], "\n")] = '\0';

    harga[jumlahProduk] =
        inputInteger("Harga produk : ");

    while (harga[jumlahProduk] < 0) {
        printf("Harga tidak boleh negatif!\n");
        harga[jumlahProduk] =
            inputInteger("Masukkan harga lagi : ");
    }

    stok[jumlahProduk] =
        inputInteger("Stok produk : ");

    while (stok[jumlahProduk] < 0) {
        printf("Stok tidak boleh negatif!\n");
        stok[jumlahProduk] =
            inputInteger("Masukkan stok lagi : ");
    }

    terjual[jumlahProduk] = 0;

    jumlahProduk++;

    printf("\nProduk berhasil ditambahkan!\n");
}


/* =========================
   CARI PRODUK
   ========================= */
int cariProduk() {
    char cari[MAX_NAMA];
    int i;

    getchar();

    printf("\n=== CARI PRODUK ===\n");
    printf("Masukkan nama produk : ");
    fgets(cari, MAX_NAMA, stdin);

    cari[strcspn(cari, "\n")] = '\0';

    for (i = 0; i < jumlahProduk; i++) {
        if (strcmp(namaProduk[i], cari) == 0) {
            return i;
        }
    }

    return -1;
}


/* =========================
   UBAH PRODUK
   ========================= */
void ubahProduk() {
    int nomor;

    tampilProduk();

    nomor = inputInteger("\nMasukkan nomor produk yang ingin diubah : ");

    if (nomor < 1 || nomor > jumlahProduk) {
        printf("Nomor produk tidak ditemukan!\n");
        return;
    }

    nomor--;

    printf("\nProduk : %s\n", namaProduk[nomor]);

    harga[nomor] =
        inputInteger("Harga baru : ");

    while (harga[nomor] < 0) {
        printf("Harga tidak boleh negatif!\n");
        harga[nomor] =
            inputInteger("Harga baru : ");
    }

    stok[nomor] =
        inputInteger("Stok baru : ");

    while (stok[nomor] < 0) {
        printf("Stok tidak boleh negatif!\n");
        stok[nomor] =
            inputInteger("Stok baru : ");
    }

    printf("\nData produk berhasil diubah!\n");
}


/* =========================
   TAMBAH STOK
   ========================= */
void tambahStok() {
    int nomor;
    int jumlah;

    tampilProduk();

    nomor = inputInteger(
        "\nMasukkan nomor produk : ");

    if (nomor < 1 || nomor > jumlahProduk) {
        printf("Nomor produk tidak ditemukan!\n");
        return;
    }

    jumlah = inputInteger(
        "Jumlah stok yang ditambahkan : ");

    if (jumlah <= 0) {
        printf("Jumlah stok harus lebih dari 0!\n");
        return;
    }

    stok[nomor - 1] += jumlah;

    printf("\nStok berhasil ditambahkan!\n");
    printf("Stok %s sekarang: %d\n",
           namaProduk[nomor - 1],
           stok[nomor - 1]);
}


/* =========================
   TRANSAKSI PENJUALAN
   ========================= */
void transaksiPenjualan() {
    int nomor;
    int jumlahBeli;
    int subtotal;
    int total = 0;
    char lagi;

    printf("\n================================\n");
    printf("       TRANSAKSI PENJUALAN\n");
    printf("================================\n");

    do {
        tampilProduk();

        nomor = inputInteger(
            "\nMasukkan nomor produk : ");

        if (nomor < 1 || nomor > jumlahProduk) {
            printf("Nomor produk tidak ditemukan!\n");
        } else {
            jumlahBeli = inputInteger(
                "Jumlah pembelian : ");

            if (jumlahBeli <= 0) {
                printf("Jumlah pembelian harus lebih dari 0!\n");
            }
            else if (jumlahBeli > stok[nomor - 1]) {
                printf("Stok tidak mencukupi!\n");
                printf("Stok tersedia: %d\n",
                       stok[nomor - 1]);
            }
            else {
                subtotal =
                    harga[nomor - 1] * jumlahBeli;

                stok[nomor - 1] -= jumlahBeli;

                terjual[nomor - 1] += jumlahBeli;

                total += subtotal;

                printf("\nProduk     : %s\n",
                       namaProduk[nomor - 1]);
                printf("Harga      : Rp%d\n",
                       harga[nomor - 1]);
                printf("Jumlah     : %d\n",
                       jumlahBeli);
                printf("Subtotal   : Rp%d\n",
                       subtotal);

                printf("\nProduk berhasil dibeli!\n");
            }
        }

        printf("\nTambah produk lain? (y/n): ");
        scanf(" %c", &lagi);

    } while (lagi == 'y' || lagi == 'Y');

    printf("\n================================\n");
    printf("TOTAL PEMBAYARAN : Rp%d\n", total);
    printf("================================\n");
}


/* =========================
   CEK STOK MENIPIS
   ========================= */
void cekStokMenipis() {
    int i;
    int ditemukan = 0;

    printf("\n=== STOK MENIPIS (< 5) ===\n");

    for (i = 0; i < jumlahProduk; i++) {
        if (stok[i] < 5) {
            printf("%d. %s - Stok: %d\n",
                   i + 1,
                   namaProduk[i],
                   stok[i]);

            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("Tidak ada produk dengan stok kurang dari 5.\n");
    }
}


/* =========================
   LAPORAN PENJUALAN
   ========================= */
void laporanPenjualan() {
    int i;
    int totalUnit = 0;
    int totalPendapatan = 0;

    int produkTerlaris = 0;

    printf("\n=========================================\n");
    printf("           LAPORAN PENJUALAN\n");
    printf("=========================================\n");

    printf("%-20s %-10s %-15s\n",
           "Produk", "Terjual", "Pendapatan");

    printf("-----------------------------------------\n");

    for (i = 0; i < jumlahProduk; i++) {

        int pendapatan =
            harga[i] * terjual[i];

        printf("%-20s %-10d Rp%-12d\n",
               namaProduk[i],
               terjual[i],
               pendapatan);

        totalUnit += terjual[i];
        totalPendapatan += pendapatan;

        if (terjual[i] >
            terjual[produkTerlaris]) {

            produkTerlaris = i;
        }
    }

    printf("-----------------------------------------\n");

    printf("Total unit terjual : %d\n",
           totalUnit);

    printf("Total pendapatan   : Rp%d\n",
           totalPendapatan);

    if (totalUnit > 0) {
        printf("Produk terlaris    : %s (%d unit)\n",
               namaProduk[produkTerlaris],
               terjual[produkTerlaris]);
    } else {
        printf("Produk terlaris    : Belum ada penjualan\n");
    }
}


/* =========================
   SORTING HARGA TERMURAH
   ========================= */
void urutHarga() {
    int i, j;

    char tempNama[MAX_NAMA];
    int tempHarga;
    int tempStok;
    int tempTerjual;

    for (i = 0; i < jumlahProduk - 1; i++) {

        for (j = 0; j < jumlahProduk - i - 1; j++) {

            if (harga[j] > harga[j + 1]) {

                strcpy(tempNama,
                       namaProduk[j]);

                strcpy(namaProduk[j],
                       namaProduk[j + 1]);

                strcpy(namaProduk[j + 1],
                       tempNama);

                tempHarga = harga[j];
                harga[j] = harga[j + 1];
                harga[j + 1] = tempHarga;

                tempStok = stok[j];
                stok[j] = stok[j + 1];
                stok[j + 1] = tempStok;

                tempTerjual = terjual[j];
                terjual[j] = terjual[j + 1];
                terjual[j + 1] = tempTerjual;
            }
        }
    }

    printf("\nProduk berhasil diurutkan berdasarkan harga termurah.\n");
}


/* =========================
   SORTING TERJUAL TERBANYAK
   ========================= */
void urutTerjual() {
    int i, j;

    char tempNama[MAX_NAMA];
    int tempHarga;
    int tempStok;
    int tempTerjual;

    for (i = 0; i < jumlahProduk - 1; i++) {

        for (j = 0; j < jumlahProduk - i - 1; j++) {

            if (terjual[j] < terjual[j + 1]) {

                strcpy(tempNama,
                       namaProduk[j]);

                strcpy(namaProduk[j],
                       namaProduk[j + 1]);

                strcpy(namaProduk[j + 1],
                       tempNama);

                tempHarga = harga[j];
                harga[j] = harga[j + 1];
                harga[j + 1] = tempHarga;

                tempStok = stok[j];
                stok[j] = stok[j + 1];
                stok[j + 1] = tempStok;

                tempTerjual = terjual[j];
                terjual[j] = terjual[j + 1];
                terjual[j + 1] = tempTerjual;
            }
        }
    }

    printf("\nProduk berhasil diurutkan berdasarkan jumlah terjual terbanyak.\n");
}


/* =========================
   MENU PENGURUTAN
   ========================= */
void menuUrutkan() {
    int pilihan;

    printf("\n=== MENU URUTKAN PRODUK ===\n");
    printf("1. Harga termurah\n");
    printf("2. Terjual terbanyak\n");
    printf("0. Kembali\n");

    pilihan = inputInteger("Pilihan : ");

    if (pilihan == 1) {
        urutHarga();
        tampilProduk();
    }
    else if (pilihan == 2) {
        urutTerjual();
        tampilProduk();
    }
    else if (pilihan == 0) {
        printf("Kembali ke menu utama.\n");
    }
    else {
        printf("Pilihan tidak tersedia!\n");
    }
}


/* =========================
   DATA AWAL
   ========================= */
void dataAwal() {

    strcpy(namaProduk[0], "Nasi Goreng");
    harga[0] = 15000;
    stok[0] = 10;
    terjual[0] = 0;

    strcpy(namaProduk[1], "Mie Ayam");
    harga[1] = 12000;
    stok[1] = 8;
    terjual[1] = 0;

    strcpy(namaProduk[2], "Es Teh");
    harga[2] = 5000;
    stok[2] = 20;
    terjual[2] = 0;

    strcpy(namaProduk[3], "Kopi");
    harga[3] = 8000;
    stok[3] = 15;
    terjual[3] = 0;

    strcpy(namaProduk[4], "Roti Bakar");
    harga[4] = 10000;
    stok[4] = 6;
    terjual[4] = 0;
}


/* =========================
   MENU UTAMA
   ========================= */
void menuUtama() {
    int pilihan;

    do {
        printf("\n");
        printf("==============================================\n");
        printf("       SISTEM STOK DAN PENJUALAN KANTIN\n");
        printf("==============================================\n");

        printf("1. Lihat Daftar Produk\n");
        printf("2. Tambah Produk\n");
        printf("3. Ubah Produk\n");
        printf("4. Transaksi Penjualan\n");
        printf("5. Tambah Stok\n");
        printf("6. Cari Produk\n");
        printf("7. Urutkan Produk\n");
        printf("8. Laporan Penjualan\n");
        printf("9. Cek Stok Menipis\n");
        printf("0. Keluar\n");

        printf("==============================================\n");

        pilihan = inputInteger("Pilihan menu : ");

        switch (pilihan) {

            case 1:
                tampilProduk();
                break;

            case 2:
                tambahProduk();
                break;

            case 3:
                ubahProduk();
                break;

            case 4:
                transaksiPenjualan();
                break;

            case 5:
                tambahStok();
                break;

            case 6: {
                int hasil = cariProduk();

                if (hasil == -1) {
                    printf("\nProduk tidak ditemukan!\n");
                } else {
                    printf("\nProduk ditemukan!\n");
                    printf("Nama   : %s\n",
                           namaProduk[hasil]);
                    printf("Harga  : Rp%d\n",
                           harga[hasil]);
                    printf("Stok   : %d\n",
                           stok[hasil]);
                    printf("Terjual: %d\n",
                           terjual[hasil]);
                }

                break;
            }

            case 7:
                menuUrutkan();
                break;

            case 8:
                laporanPenjualan();
                break;

            case 9:
                cekStokMenipis();
                break;

            case 0:
                printf("\nProgram selesai. Terima kasih!\n");
                break;

            default:
                printf("\nPilihan menu tidak tersedia!\n");
        }

    } while (pilihan != 0);
}


/* =========================
   MAIN
   ========================= */
int main() {

    dataAwal();

    menuUtama();

    return 0;
}
