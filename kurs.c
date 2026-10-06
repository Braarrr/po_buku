#include <stdio.h>

#define MAX_MEM 100
#define ONGKIR 15000.0f

float usd = 17975;
float pound = 23792;
float sgd = 14038;
float euro = 20323;

float dat[MAX_MEM];
int n = 0;

char *nm[] = {"", "USD", "Pound", "SGD", "Euro"};


int inputInt(const char *message, int *value) {
    int ch;

    printf("%s", message);

    if (scanf("%d", value) != 1) {
        *value = -1;

        while ((ch = getchar()) != '\n' && ch != EOF);

        return 0;
    }

    return 1;
}


int inputFloat(const char *message, float *value) {
    int ch;

    printf("%s", message);

    if (scanf("%f", value) != 1) {
        *value = -1;

        while ((ch = getchar()) != '\n' && ch != EOF);

        return 0;
    }

    return 1;
}


int choice() {
    int c;

    inputInt(
        "\n============================\n"
        "       MENU UTAMA\n"
        "============================\n"
        "0. Exit\n"
        "1. Input PO Buku\n"
        "2. Show Memori\n"
        "3. Hapus Memori\n"
        "Choice: ",
        &c
    );

    return c;
}


float rate(int kode) {

    if (kode == 1)
        return usd;

    if (kode == 2)
        return pound;

    if (kode == 3)
        return sgd;

    if (kode == 4)
        return euro;

    return 0;
}


int pilihCurrency() {
    int kode;

    do {
        printf("\nPilih Currency\n");
        printf("1. USD\n");
        printf("2. Pound\n");
        printf("3. SGD\n");
        printf("4. Euro\n");

        inputInt("Choice: ", &kode);

        if (kode < 1 || kode > 4) {
            printf("Currency tidak valid. Silakan ulang.\n");
        }

    } while (kode < 1 || kode > 4);

    return kode;
}


int inputJumlahBuku() {
    int jumlahBuku;

    do {
        inputInt("\nBerapa buku yang ingin dipesan? ", &jumlahBuku);

        if (jumlahBuku <= 0 || jumlahBuku > 100) {
            printf("Jumlah buku harus 1 - 100.\n");
        }

    } while (jumlahBuku <= 0 || jumlahBuku > 100);

    return jumlahBuku;
}


float inputBuku(
    int jumlahBuku,
    char judul[][100],
    int currency[],
    float harga[],
    float hargaIDR[]
) {
    float totalBuku = 0;

    for (int i = 0; i < jumlahBuku; i++) {

        printf("\n----------------------------\n");
        printf("         BUKU %d\n", i + 1);
        printf("----------------------------\n");

        printf("Judul buku: ");
        scanf(" %[^\n]", judul[i]);

        currency[i] = pilihCurrency();

        do {
            inputFloat(
                "Harga buku: ",
                &harga[i]
            );

            if (harga[i] < 0) {
                printf("Harga tidak boleh negatif.\n");
            }

        } while (harga[i] < 0);

        hargaIDR[i] = harga[i] * rate(currency[i]);

        totalBuku += hargaIDR[i];
    }

    return totalBuku;
}


float receipt(
    int jumlahBuku,
    char judul[][100],
    int currency[],
    float harga[],
    float hargaIDR[],
    float totalBuku
) {
    float total;

    printf("\n");
    printf("========================================\n");
    printf("              PO RECEIPT\n");
    printf("========================================\n");

    for (int i = 0; i < jumlahBuku; i++) {

        printf("\n%d. %s\n", i + 1, judul[i]);

        printf("   %s %.2f\n",
               nm[currency[i]],
               harga[i]);

        printf("   = Rp %.2f\n",
               hargaIDR[i]);
    }

    total = totalBuku + ONGKIR;

    printf("\n----------------------------------------\n");
    printf("Total Buku : Rp %.2f\n", totalBuku);
    printf("Ongkir     : Rp %.2f\n", ONGKIR);
    printf("----------------------------------------\n");
    printf("TOTAL      : Rp %.2f\n", total);
    printf("========================================\n");

    return total;
}


void simpan(float x) {

    if (n < MAX_MEM) {

        dat[n] = x;
        n++;

    } else {

        for (int i = 1; i < MAX_MEM; i++) {
            dat[i - 1] = dat[i];
        }

        dat[MAX_MEM - 1] = x;
    }
}


void mem() {

    printf("\n============================\n");
    printf("       MEMORI TRANSAKSI\n");
    printf("============================\n");

    if (n == 0) {
        printf("Memori kosong.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("PO %d : Rp %.2f\n", i + 1, dat[i]);
    }
}


void hapusMemori() {

    n = 0;

    for (int i = 0; i < MAX_MEM; i++) {
        dat[i] = 0;
    }

    printf("\nMemori kosong.\n");
}


void hitung() {

    int jumlahBuku;

    jumlahBuku = inputJumlahBuku();

    /*
       Array dibuat berdasarkan jumlah buku
       yang dimasukkan user.
    */

    char judul[jumlahBuku][100];
    int currency[jumlahBuku];
    float harga[jumlahBuku];
    float hargaIDR[jumlahBuku];

    float totalBuku;
    float total;

    totalBuku = inputBuku(
        jumlahBuku,
        judul,
        currency,
        harga,
        hargaIDR
    );

    total = receipt(
        jumlahBuku,
        judul,
        currency,
        harga,
        hargaIDR,
        totalBuku
    );

    simpan(total);
}


int main() {

    while (1) {

        switch (choice()) {

            case 0:
                printf("\nProgram selesai.\n");
                return 0;


            case 1: {
                char lagi;

                do {

                    hitung();

                    printf("\nMau melakukan PO lagi? (y/n): ");
                    scanf(" %c", &lagi);

                } while (lagi == 'y' || lagi == 'Y');

                break;
            }


            case 2:
                mem();
                break;


            case 3:
                hapusMemori();
                break;


            default:
                printf("\nWrong choice, ulang.\n");
                break;
        }
    }

    return 0;
}