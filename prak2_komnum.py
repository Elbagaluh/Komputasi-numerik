
import math


def f(x):
    return math.sin(x)  # ganti dengan fungsi yang diinginkan


def trapesium(a, b, n):
    h = (b - a) / n
    total = f(a) + f(b)
    for i in range(1, n):
        total += 2 * f(a + i * h)
    return (h / 2) * total


def romberg(a, b, iter_n):
    R = [[0.0 for _ in range(iter_n)] for _ in range(iter_n)]

    # Kolom pertama (k=0): hasil trapesium dengan jumlah sub-interval 2^i
    for i in range(iter_n):
        n = 2 ** i
        R[i][0] = trapesium(a, b, n)

    # Kolom selanjutnya: ekstrapolasi Richardson
    for k in range(1, iter_n):
        for i in range(k, iter_n):
            R[i][k] = (4**k * R[i][k - 1] - R[i - 1][k - 1]) / (4**k - 1)

    hasil_akhir = R[iter_n - 1][iter_n - 1]
    return R, hasil_akhir


def cetak_tabel(R, iter_n):
    lebar_kolom = 18
    header = "i".center(4) + "|"
    for k in range(iter_n):
        header += f"R(i,{k})".center(lebar_kolom) + "|"

    garis = "-" * len(header)

    print(garis)
    print(header)
    print(garis)

    for i in range(iter_n):
        baris = str(i).center(4) + "|"
        for k in range(iter_n):
            if k <= i:
                nilai = f"{R[i][k]:.10f}"
            else:
                nilai = ""
            baris += nilai.center(lebar_kolom) + "|"
        print(baris)
    print(garis)


def main():
    print("=" * 50)
    print("   PROGRAM INTEGRASI NUMERIK - METODE ROMBERG")
    print("=" * 50)

    a = float(input("Masukkan batas bawah (a)   : "))
    b = float(input("Masukkan batas atas  (b)   : "))
    iter_n = int(input("Masukkan jumlah iterasi    : "))

    if iter_n < 1:
        print("Jumlah iterasi harus minimal 1.")
        return

    R, hasil = romberg(a, b, iter_n)

    print("\nTabel Iterasi Romberg:")
    cetak_tabel(R, iter_n)

    print(f"\nHasil integral f(x) dari {a} sampai {b} (iterasi ke-{iter_n}):")
    print(f"Integral = {hasil:.10f}")


if __name__ == "__main__":
    main()