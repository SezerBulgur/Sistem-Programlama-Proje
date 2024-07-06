# 2023-2024 BAHAR SİSTEM PROGRAMLAMA PROJE ÖDEVİ

Bu projede, giriş dosyasından okunan komutlara göre çıkış dosyası oluşturan bir program C
dilinde geliştirilmiştir.

Programın algıladığı komutlar: "yaz:", "dur:", "sonagit:", "sil:".

Her satırda ilk başta komut aranır.

Komuttan sonra gelen veriler boşluklara göre ayırt edilir.

Gelen veriler integer ve karakter katarı olarak ele alınır. Integer değeri kadar katar yazdırılır. 

Özel katarlar: "\n" ve "\b"dir. "\n" katarı bulunursa verilen integer değeri kadar yeni satıra geçilir. "\b" katarı bulunursa verilen integer değeri kadar boşluk bırakılır.

Bu programda Prof. James S. Plank tarafından geliştirilen libfdr kütüphanesinden faydalanılmıştır. Libfdr'ye ait "fields.h" kütüphanesi sayesinde dosya okumak işlemleri, "dlllist.h" ve "jval.h" kütüphaneleriyle ise veri saklamak işlemleri daha kolay bir hale gelmiştir.

Program makefile üzerinden gcc ile derlenmektedir ve "program" isimli bir çalıştırılabilir dosya üretilmektedir. 

Program varsayılan olarak veri girişi için "giris.dat" dosyasını ve verilen komutlara uygun çıktı dosyası için "cikis.dat" dosyasını kullanmaktadır.

Program terminal üzerinden çalıştırılırken 2 adet parametre verildiği takdirde bu parametrelerden ilkini veri girişi için ikinci parametreyi ise çıktı dosyası için kullanmaktadır. Eğer sadece giriş dosyası verilmek isteniyorsa ikinci parametre olarak cikis.dat yazılabilir.


## Projeyi Geliştiren

- Sezer BULGUR - B201210060