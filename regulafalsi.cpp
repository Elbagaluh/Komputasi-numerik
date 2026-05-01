#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PangkatMax 10 
double f(double x, int derajat, double koefisien[]) {
    double hasil = 0.0;
    for (int i = 0; i <= derajat; i++) {
        hasil += koefisien[i] * pow(x, i);
    }
    return hasil;
}
void tulis_angka_indo(FILE *fp, double angka) {
    char buffer[50];
    sprintf(buffer, "%lf", angka); 
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '.') {
            buffer[i] = ',';
        }
    }
    fprintf(fp, "%s", buffer); 
}
void generate_graph_data(double start, double end, double step, int derajat, double koefisien[]) {
    FILE *fp = fopen("grafik_regula_falsi_dinamis.csv", "w");
    if (fp == NULL) {
        printf("Gagal membuat file grafik!\n");
        return;
    }

    fprintf(fp, "x;f(x)\n");
    
    for (double x = start; x <= end; x += step) {
        tulis_angka_indo(fp, x);
        fprintf(fp, ";");
        tulis_angka_indo(fp, f(x, derajat, koefisien));
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("\n[INFO] Data grafik disimpan di 'grafik_regula_falsi_dinamis.csv'.\n");
}

int main() {
    double a, b, c, fa, fb, fc, toleransi;
    int iter = 1, max_iter, derajat;
    double koefisien[PangkatMax + 1]; 
    printf("=== PROGRAM METODE REGULA FALSI (FUNGSI DINAMIS) ===\n\n");
    printf("Masukkan derajat polinomial tertinggi (maksimal %d): ", PangkatMax);
    scanf("%d", &derajat);

    if (derajat < 0 || derajat > PangkatMax) {
        printf("[ERROR] Derajat tidak valid!\n");
        return 1;
    }

    printf("\nMasukkan koefisien untuk masing-masing pangkat:\n");
    for (int i = derajat; i >= 0; i--) {
        printf("Koefisien untuk x^%d : ", i);
        scanf("%lf", &koefisien[i]);
    }
    printf("\nMasukkan batas bawah (a): ");
    scanf("%lf", &a);
    printf("Masukkan batas atas (b): ");
    scanf("%lf", &b);
    printf("Masukkan nilai toleransi error (contoh: 0.0001): ");
    scanf("%lf", &toleransi);
    printf("Masukkan iterasi maksimal: ");
    scanf("%d", &max_iter);
    fa = f(a, derajat, koefisien);
    fb = f(b, derajat, koefisien);
    if (fa * fb > 0.0) {
        printf("\n[ERROR] Batas yang Anda masukkan tidak mengurung akar (f(a) dan f(b) memiliki tanda yang sama).\n");
        return 1;
    }
    printf("\nMenampilkan Proses Iterasi Numerik:\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf(" Iter |      a      |      b      |      c      |     f(a)    |     f(b)    |     f(c)    \n");
    printf("------------------------------------------------------------------------------------------------\n");
    do {
        fa = f(a, derajat, koefisien);
        fb = f(b, derajat, koefisien);
        c = (a * fb - b * fa) / (fb - fa);
        fc = f(c, derajat, koefisien);

        printf(" %4d | %11.6lf | %11.6lf | %11.6lf | %11.6lf | %11.6lf | %11.6lf \n", 
               iter, a, b, c, fa, fb, fc);
        if (fa * fc < 0.0) {
            b = c; 
        } else {
            a = c; 
        }

        iter++;
    } while (fabs(fc) > toleransi && iter <= max_iter);
    printf("------------------------------------------------------------------------------------------------\n");
    printf("\nAkar persamaan aproksimasi yang ditemukan: %.6lf\n", c);
    generate_graph_data(c - 2.0, c + 2.0, 0.1, derajat, koefisien);
    return 0;
}
