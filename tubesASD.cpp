#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#define Nil NULL

typedef int infotype;
typedef struct tElmtlist *address;
typedef struct tElmtlist
{
    char task;
    infotype info;
    address next;
} ElmtList;
typedef struct
{
    address First;
} List;

/* Definisi list : */
/* List kosong : First(L) = Nil */
/* Setiap elemen dengan address P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list: jika addressnya Last, maka Next(Last)=First(L) */

/* Notasi Akses */
#define Task(P) (P)->task
#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) ((L).First)

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
bool IsEmpty(List L)
{
    /* Mengirim true jika list kosong. Lihat definisi di atas. */
    return (First(L) == Nil);
}
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty(List *L)
{
    /* I.S. L sembarang             */
    /* F.S. Terbentuk list kosong. Lihat definisi di atas. */
    First(*L) = Nil;
}
/****************** Manajemen Memori ******************/
address Alokasi(char task, infotype X)
{
    /* Mengirimkan address hasil alokasi sebuah elemen */
    /* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
    /* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
    /* Jika alokasi gagal, mengirimkan Nil */
    address P;
    P = (address)malloc(sizeof(address));
    if (P != Nil)
    {
        Task(P) = task;
        Info(P) = X;
        Next(P) = Nil;
    }
    return P;
}
/* I.S. P terdefinisi */
void Dealokasi(address P)
{
    /* F.S. P dikembalikan ke sistem */
    /* Melakukan dealokasi/pengembalian address P */
    free(P);
}
/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search(List L, infotype X)
{
    /* Mencari apakah ada elemen list dengan Info(P)= X */
    /* Jika ada, mengirimkan address elemen tersebut. */
    /* Jika tidak ada, mengirimkan Nil */
    address P;
    bool found = false;
    P = First(L);
    if (IsEmpty(L))
    {
        found = false;
    }
    else
    {
        if (Info(P) == X)
        {
            found = true;
        }
        else
        {
            P = Next(P);
            while (P != First(L) && !found)
            {
                if (Info(P) == X)
                {
                    found = true;
                }
                else
                    P = Next(P);
            }
        }
    }

    if (found)
    {
        return P;
    }
    else
    {
        return Nil;
    }
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst(List *L, address P)
{
    /* I.S. Sembarang, P sudah dialokasi  */
    /* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
    address Last;
    if (IsEmpty(*L))
    {
        Next(P) = P;
    }
    else
    {
        Last = First(*L);
        while (Next(Last) != First(*L))
        {
            Last = Next(Last);
        }
        Next(P) = First(*L);
        Next(Last) = P;
    }
    First(*L) = P;
}
void InsertAfter(List *L, address P, address Prec)
{
    /* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
    /*      P sudah dialokasi  */
    /* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
    Next(P) = Next(Prec);
    Next(Prec) = P;
}
void InsertLast(List *L, address P)
{
    /* I.S. Sembarang, P sudah dialokasi  */
    /* F.S. P ditambahkan sebagai elemen terakhir yang baru */
    address Last;
    if (IsEmpty(*L))
    {
        InsertFirst(L, P);
    }
    else
    {
        Last = First(*L);
        while (Next(Last) != First(*L))
        {
            Last = Next(Last);
        }
        InsertAfter(L, P, Last);
    }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst(List *L, char task, infotype X)
{
    /* I.S. L mungkin kosong */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
    address P;
    P = Alokasi(task, X);
    if (P != Nil)
    {
        InsertFirst(L, P);
    }
}
void InsVLast(List *L, char task, infotype X)
{
    /* I.S. L mungkin kosong */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menambahkan elemen list di akhir: elemen terakhir yang baru */
    /* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
    address P;
    P = Alokasi(task, X);
    if (P != Nil)
    {
        InsertLast(L, P);
    }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst(List *L, address *P)
{
    /* I.S. List tidak kosong */
    /* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
    /*      Elemen list berkurang satu (mungkin menjadi kosong) */
    /* First element yg baru adalah suksesor elemen pertama yang lama */
    address Last;

    *P = First(*L);
    if (Next(First(*L)) == First(*L))
    {
        First(*L) = Nil;
    }
    else
    {
        Last = First(*L);
        while (Next(Last) != First(*L))
        {
            Last = Next(Last);
        }
        First(*L) = Next(First(*L));
        Next(Last) = First(*L);
    }
    Next(*P) = Nil;
}
void DelAfter(List *L, address *Pdel, address Prec)
{
    /* I.S. List tidak kosong. Prec adalah anggota list  */
    /* F.S. Menghapus Next(Prec): */
    /*      Pdel adalah alamat elemen list yang dihapus  */
    if (Next(Prec) != First(*L))
    {
        *Pdel = Next(Prec);
        Next(Prec) = Next(Next(Prec));
        Next(*Pdel) = Nil;
    }
    else
    {
        *Pdel = Next(Prec);
        Next(Prec) = Next(Next(Prec));
        First(*L) = Prec;
        Next(*Pdel) = Nil;
    }
}
void DelLast(List *L, address *P)
{
    /* I.S. List tidak kosong */
    /* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
    /*      Elemen list berkurang satu (mungkin menjadi kosong) */
    /* Last element baru adalah predesesor elemen pertama yg lama, */
    /* jika ada */
    address Last, Prec;
    Last = First(*L);
    Prec = Nil;
    while (Next(Last) != First(*L))
    {
        Prec = Last;
        Last = Next(Last);
    }

    *P = Last;

    if (Prec == Nil)
    {
        First(*L) = Nil;
    }
    else
    {
        Next(Prec) = First(*L);
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst(List *L, infotype *X)
{
    /* I.S. List L tidak kosong  */
    /* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
    /*      dan alamat elemen pertama di-dealokasi */
    address P;
    DelFirst(L, &P);
    *X = Info(P);
    Dealokasi(P);
}
void DelVLast(List *L, infotype *X)
{
    /* I.S. list tidak kosong */
    /* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
    /*      dan alamat elemen terakhir di-dealokasi */
    address P;
    DelLast(L, &P);
    *X = Info(P);
    Dealokasi(P);
}
void DelP(List *L, infotype X)
{
    /* I.S. Sembarang */
    /* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
    /* Maka P dihapus dari list dan di-dealokasi */
    /* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
    /* List mungkin menjadi kosong karena penghapusan */
    address P, Prec;
    if (Search(*L, X) != Nil)
    {
        if (X == Info(First(*L)))
        {
            DelVFirst(L, &X);
        }
        else
        {
            Prec = First(*L);
            while (Info(Next(Prec)) != X)
            {
                Prec = Next(Prec);
            }

            P = Next(Prec);
            Next(Prec) = Next(Next(Prec));
            Next(P) = Nil;

            Dealokasi(P);
        }
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo(List L)
{
    /* I.S. List mungkin kosong */
    /* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
    /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
    /* Jika list kosong : menulis [] */
    /* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
    address P;
    P = First(L);
    if (IsEmpty(L))
    {
        cout << "[]" << endl;
    }
    else
    {
        cout << "[";
        cout << Task(P) << " " << Info(P);
        if (Next(P) == First(L))
        {
            cout << "]";
        }
        else
        {
            cout << ",";
        }

        P = Next(P);
        while (P != First(L))
        {
            cout << Task(P) << " " << Info(P);
            if (Next(P) == First(L))
            {
                cout << "]";
            }
            else
            {
                cout << ",";
            }
            P = Next(P);
        }
    }
}

void PrintTable(List L)
{
    cout << "+---------+---------+" << endl;
    cout << "| Data    | Quanta  |" << endl;
    cout << "+---------+---------+" << endl;
    address P;
    P = First(L);
    if (IsEmpty(L))
    {
    }
    else
    {
        cout << "|";
        cout << " " << Task(P) << "       | " << Info(P) << "       |" << endl;
        if (Next(P) == First(L))
        {
        }
        else
        {
            cout << "|";
        }

        P = Next(P);
        while (P != First(L))
        {
            cout << " " << Task(P) << "       | " << Info(P) << "       |" << endl;
            if (Next(P) == First(L))
            {
            }
            else
            {
                cout << "|";
            }
            P = Next(P);
        }
    }
    cout << "+---------+---------+" << endl;
}

void RRSchedulling(List L, int Quantum)
{
    cout << "+---------+---------+" << endl;
    cout << "| Data    | Quantum |" << endl;
    cout << "+---------+---------+" << endl;
    int totalProses, X;
    address P;
    P = First(L);
    while (!IsEmpty(L))
    {
        Info(P) -= 5;
        if (Info(P) <= 0)
        {
            cout << "| " << Task(P) << "       |       " << Quantum << " | >> " << Task(P) << " = " << Info(P) << ". Dispose " << Task(P) << endl;
            address delP = Next(P);
            address tmpP = First(L);
            if (IsEmpty(L) || Next(P) == P)
            {
                /* code */
            }
            else
            {
                /* code */
                cout << "| Switch  |       1 | " << endl;
                totalProses += 1;
            }
            if (P == First(L))
            {
                /* code */
                DelVFirst(&L, &Info(P));
            }
            else if (Next(P) == First(L))
            {
                /* code */
                DelLast(&L, &P);
            }
            else
            {
                /* code */
                while (Next(tmpP) != P)
                {
                    /* code */
                    tmpP = Next(tmpP);
                }
                DelAfter(&L, &P, tmpP);
            }
            P = delP;
        }
        else
        {
            cout << "| " << Task(P) << "       |       " << Quantum << " | >> " << Task(P) << " = " << Info(P) << endl;
            if (IsEmpty(L) || Next(P) == P)
            {
                /* code */
            }
            else
            {
                /* code */
                cout << "| Switch  |       1 | " << endl;
                totalProses += 1;
            }
            P = Next(P);
        }
        totalProses += Quantum;
    }
    cout << "+---------+---------+" << endl;
    cout << "| Total   |      " << totalProses << " |" << endl;
    cout << "+---------+---------+" << endl;
}

void insertnumber(List *L, char task, infotype X)
{
    cout << "flag";
    address predTemp, P;
    predTemp = Nil;
    P = First(*L);
    while (Next(P) != First(*L))
    {
        if ((int)Task(P) - (int)'0' > (int)task - (int)'0')
        {
            break;
        }
        else
        {
            predTemp = P;
            P = Next(P);
        }
    }
    if (IsEmpty(*L))
    {
        InsVFirst(&(*L), task, X);
    }
    else if (P == Nil)
    {
        InsVLast(&(*L), task, X);
    }
    else
    {
        InsertAfter(L, Alokasi(task, X), predTemp);
    }
}

int main()
{
    List Processor;
    CreateEmpty(&Processor);
    int jtask, quantum;
    infotype quanta;
    char task;

    cout << "Jumlah Data        : ";
    cin >> jtask;
    cout << "Quantum per proses : ";
    cin >> quantum;
    cout << endl;

    for (int i = 1; i <= jtask; i++)
    {
        /* code */
        cout << "Simpul #" << i << endl;
        cout << "Data   #" << i << " : ";
        cin >> task;
        cout << "Quanta #" << i << " : ";
        cin >> quanta;
        cout << endl;
        insertnumber(&Processor, task, quanta);
        // InsVLast(&Processor, task, quanta);
    }

    if (IsEmpty(Processor))
    {
        PrintTable(Processor);
        cout << " Tidak ada data yang di proses " << endl;
    }
    else
    {
        PrintTable(Processor);
        cout << endl;
        RRSchedulling(Processor, quantum);
    }

    return 0;
}
