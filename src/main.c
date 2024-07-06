#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dllist.h"
#include "fields.h"
#include "jval.h"
#include <ctype.h>
#include <math.h>
#include "fields.h"

//indexin gosterdigi yerden dllListesine eklemeye baslar index zaten gosterdigi icin dllListesinin verilmesine aslinda gerek yok
//listeye sayac kadar Jval eklenir
void yaz(int _sayac, Jval _tmpJval, Dllist _dllListesi, Dllist *_index)
{
    for (int i = 0; i < _sayac; i++)
    {
        dll_insert_a(*_index, _tmpJval);
        *_index = dll_next(*_index);
    }
    return;
}

//indexi verilen listenin sonunu gosterecek sekilde ayarlar
void sonaGit(Dllist _dllListesi, Dllist *_index)
{
    *_index = dll_last(_dllListesi);
    return;
}

//indexten geriye dogru taramaya baslar sayac kadar jval silinir sayac kadar yoksa olani siler
void sil(int _sayac, Jval _tmpJval, Dllist *_index)
{
    char *silinecekDeger = strdup(jval_s(_tmpJval));
    Dllist _tmp;
    Dllist silinecekDugum;
    int sil = 0;
    Dllist _tmpIndex = *_index;

    //
    dll_rtraverse(_tmp, (_tmpIndex))
    {
        *_index = (*_index)->blink;
        // dongunun devam etmesi icin silinecek dugum atlanip yeni dugume gecildikten sonra silme yapar
        if (sil == 1)
        {
            dll_delete_node(silinecekDugum);
            sil = 0;
        }

        if (_sayac == 0)
        {
            break;
        }

        char *guncelDeger = jval_s(_tmp->val);
        if (guncelDeger == NULL)
        {
            continue;
        }
        if (strcmp(silinecekDeger, guncelDeger) == 0)
        {
            sil = 1;
            silinecekDugum = _tmp;
            // alttaki gibi silinirse dongude sorun cikmakta
            //  dll_delete_node(_tmp);
            _sayac--;
        }
    }

    // dugum bittikten sonra eger ilk karakter silinmesi gerekn bir karakterse silinir
    if (sil == 1)
    {
        dll_delete_node(silinecekDugum);
        sil = 0;
    }
}

//verilen dllListesindeki degerlerin verilen dosyaIsmine yazar
void yazdir(Dllist _dllListesi, char *_fileName)
{
    FILE *_fout;
    _fout = fopen(_fileName, "w");
    if (_fout == NULL)
    {
        printf("hata: cikis.dat dosyasi olusturulamadi");
        exit(1);
    }

    Dllist _tmp;
    char *yazilacak;
    dll_traverse(_tmp, _dllListesi)
    {
        yazilacak = jval_s(_tmp->val);
        //if (yazilacak != NULL)
        {
            fputs(yazilacak, _fout);
        }
    }
}

int main(int argc, char *argv[])
{
    //yazilanlar Listesinin olusturulmasi ve bu listedeki islemlerde kullanilacak indexin olusturulmasi
    Dllist indexYazilanlar;
    Dllist yazilanlarListesi;
    yazilanlarListesi = new_dllist();
    indexYazilanlar = yazilanlarListesi;

    //dosyadan okuma islemleri sirasinda yazilacak degerleri listede saklamak icin kullanilacak tmpJval
    Jval tmpJval;

    //Dosya okuma islemleri icin IS ve yazilacak dosyanin adini tutacak cikisFolder
    IS is;
    const char *cikisFolder;

    //eger giris ve cikis degerleri terminalden verilmezse varsayilan olarak "giris.dat" ve "cikis.dat" kullanilir
    if (argc != 3)
    {
        fprintf(stderr, "giris ve cikis dosyalarinin adi komut satirindan verilmedi.\nprogram varsayilan olarak giris dosyasi icin \"giris.dat\" ve cikis dosyasi icin \"cikis.dat\" kullaniyor\n");
        is = new_inputstruct("giris.dat");
        cikisFolder = "cikis.dat";
    }
    //eger terminalden iki dosya adi girilmisse bunlari kullanir
    else
    {
        is = new_inputstruct(argv[1]);
        cikisFolder = argv[2];
    }

    //eger dosya acilamiyorsa hata verir
    if (is == NULL)
    {
        perror(argv[1]);
        exit(1);
    }

    //dosya okurken kullanilacak sayaclar
    int tmpSayac = 0;
    int sayac = 0;
    //dosyadan satir okudukca yapilacak islemler
    while (get_line(is) >= 0)
    {
        //her yeni satir okundugunda sayaclar sifirlanir
        tmpSayac = 0;
        sayac = 0;

        //satirdaki ilk kelime komut degiskenine atanir
        char *komut = strdup(is->fields[0]);

        //yaz: komutu bulundugu anda yapilacak islemler
        if (strcmp(komut, "yaz:") == 0)
        {
            //her bir input incelenir
            for (int i = 1; i < is->NF; i++)
            {
                tmpSayac = atoi(is->fields[i]);
                //input kontrol edilir eger atoi ile gelen deger 0 ise string bir input olarak isler 0 degilse inputu deger olarak alir.
                // tmpSayac 0 degilse sayaca atar. 0 ise parametre sayac kadar eklenir
                if (tmpSayac != 0)
                {
                    sayac = tmpSayac;
                }
                else
                {
                    //alinan input tmp degerinde saklanir
                    char *tmp = strdup(is->fields[i]);
                    //escape karakter kullanip kullanilmadigi kontrol edilir ve buna gore islem yapilir
                    if (tmp[0] == '\\')
                    {
                        if (tmp[1] == 'n')
                        {
                            tmp = "\n";
                        }
                        if (tmp[1] == 'b')
                        {
                            tmp = " ";
                        }
                    }
                    
                    //tmp degeri Jval degerine donusturulur ve listeye yazdirilmasi icin gerekli fonksiyon cagrilir
                    tmpJval = new_jval_s(strdup(tmp));
                    yaz(sayac, tmpJval, yazilanlarListesi, &indexYazilanlar);
                }
            }
        }

        //sil: komutu bulundugu anda yapilacak islemler
        else if (strcmp(komut, "sil:") == 0)
        {
            //her bir input incelenir
            for (int i = 1; i < is->NF; i++)
            {
                tmpSayac = atoi(is->fields[i]);
                //input kontrol edilir eger atoi ile gelen deger 0 ise string bir input olarak isler 0 degilse inputu deger olarak alir.
                // tmpSayac 0 degilse sayaca atar. 0 ise parametre sayac kadar eklenir
                if (tmpSayac != 0)
                {
                    sayac = tmpSayac;
                }
                else
                {
                    //inputtan gelen deger Jval degerine donusturulur ve listeden silinmesi icin gerekli fonksiyon cagrilir

                    tmpJval = new_jval_s(strdup(is->fields[i]));
                    // yaz(sayac, tmpJval, yazilanlarListesi, indexYazilanlar);
                    sil(sayac, tmpJval, &(indexYazilanlar));
                }
            }
        }

        //sonagit: komutu bulundugu anda yapilacak islemler
        else if (strcmp(komut, "sonagit:") == 0)
        {
            sonaGit(yazilanlarListesi, &(indexYazilanlar));
        }
        //dur: komutu bulundugu anda yapilacak islemler
        else if (strcmp(komut, "dur:") == 0)
        {
            //dur komutu bulundugunda once yazdir fonksiyonu ile listedeki degerler cikis dosyasina yazdirilir
            //ardindan program sonlandirilir
            yazdir(yazilanlarListesi, cikisFolder);
            return 0;
        }
        
        //ilk kelimede komut bulunamadiysa bir sey yapmaz diger satirdan devam eder
        else
        {
            continue;
        }
    }

    jettison_inputstruct(is);
    return 0;
}