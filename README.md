# Tarsau Arşiv Programı

Tarsau, Sistem Programlama dersi kapsamında C dili kullanılarak geliştirilmiş sıkıştırmasız bir arşivleme programıdır. Program Linux/Unix ortamında çalışmak üzere tasarlanmıştır.

Bu uygulama, birden fazla ASCII metin dosyasını tek bir `.sau` arşiv dosyasında birleştirir. Daha sonra oluşturulan `.sau` arşivi tekrar açılarak dosyalar belirtilen dizine geri çıkarılabilir. Program dosya içeriklerinin yanında dosya izinlerini de korur.

---

## Özellikler

- Birden fazla metin dosyasını tek bir `.sau` arşiv dosyasında birleştirme
- `.sau` arşiv dosyasını istenen dizine açma
- Varsayılan arşiv adı desteği: `a.sau`
- En fazla 32 giriş dosyası desteği
- Toplam 200 MB dosya boyutu sınırı
- ASCII metin dosyası kontrolü
- Hatalı veya bozuk arşiv dosyası kontrolü
- Dosya izinlerini koruma
- Göreceli ve mutlak dizin desteği
- Makefile ile kolay derleme
- Valgrind ile bellek sızıntısı testi

---

## Proje Klasör Yapısı

```text
tarsau-proje/
├── include/
│   └── tarsau.h
├── src/
│   ├── main.c
│   ├── archive.c
│   ├── extract.c
│   └── utils.c
├── testfiles/
├── docs/
├── Makefile
└── README.md
```

---

## Derleme

Projeyi derlemek için:

```bash
make
```

Oluşturulan çalıştırılabilir dosyayı ve arşiv dosyalarını temizlemek için:

```bash
make clean
```

---

## Kullanım

### Arşiv Oluşturma

```bash
./tarsau -b testfiles/t1.txt testfiles/t2.txt -o s1.sau
```

Bu komut `testfiles/t1.txt` ve `testfiles/t2.txt` dosyalarını `s1.sau` adlı arşiv dosyasında birleştirir.

### Varsayılan Arşiv Adı ile Arşiv Oluşturma

```bash
./tarsau -b testfiles/t1.txt testfiles/t2.txt
```

Bu kullanımda çıktı dosyası varsayılan olarak `a.sau` adıyla oluşturulur.

### Arşiv Açma

```bash
./tarsau -a s1.sau output
```

Bu komut `s1.sau` arşivini `output` dizinine açar.

### Geçerli Dizine Arşiv Açma

```bash
./tarsau -a s1.sau
```

Dizin adı verilmezse arşiv geçerli dizine açılır.

---

## Örnek Test

```bash
echo "System Programming" > testfiles/t1.txt
echo "Tarsau Archive Test" > testfiles/t2.txt

./tarsau -b testfiles/t1.txt testfiles/t2.txt -o s1.sau
./tarsau -a s1.sau output

cat output/t1.txt
cat output/t2.txt
```

Beklenen çıktı:

```text
System Programming
Tarsau Archive Test
```

---

## Dosya İzinleri Testi

```bash
chmod 755 testfiles/t1.txt
chmod 644 testfiles/t2.txt

./tarsau -b testfiles/t1.txt testfiles/t2.txt -o s1.sau
./tarsau -a s1.sau output

ls -l testfiles/t1.txt testfiles/t2.txt
ls -l output
```

Bu test sonucunda arşivden çıkarılan dosyaların izinlerinin orijinal dosya izinleriyle aynı olduğu görülür.

---

## Mutlak Dizin Testi

```bash
chmod 755 testfiles/t1.txt
chmod 644 testfiles/t2.txt

./tarsau -b testfiles/t1.txt testfiles/t2.txt -o s1.sau
mkdir -p /tmp/tarsau_abs_test
./tarsau -a s1.sau /tmp/tarsau_abs_test

ls -l /tmp/tarsau_abs_test
cat /tmp/tarsau_abs_test/t1.txt
cat /tmp/tarsau_abs_test/t2.txt
```

Bu test ile arşivin mutlak bir dizine başarıyla açılabildiği ve dosya izinlerinin korunduğu doğrulanır.

---

## Hatalı Dosya Formatı Testi

Binary formatta bir dosya arşivlenmeye çalışıldığında program hata mesajı verir.

```bash
printf '\x89PNG\x00\x01' > fake.bin
./tarsau -b fake.bin
```

Beklenen çıktı:

```text
fake.bin giris dosyasinin formati uyumsuzdur!
```

---

## Bozuk Arşiv Testi

```bash
echo "abcd" > fake.sau
./tarsau -a fake.sau output
```

Beklenen çıktı:

```text
Arsiv dosyasi uygunsuz veya bozuk!
```

---

## Dosya Sayısı Sınırı Testi

Program en fazla 32 giriş dosyasını kabul eder.

```bash
mkdir manyfiles

for i in {1..35}
do
    echo "test" > manyfiles/file$i.txt
done

./tarsau -b manyfiles/*
```

Beklenen çıktı:

```text
En fazla 32 dosya arsivlenebilir!
```

---

## Valgrind Bellek Testi

Programın bellek sızıntısı kontrolü Valgrind ile yapılmıştır.

```bash
valgrind --leak-check=full ./tarsau -b testfiles/t1.txt testfiles/t2.txt -o s1.sau
valgrind --leak-check=full ./tarsau -a s1.sau output_valgrind
```

Test sonucunda bellek sızıntısı bulunmamıştır.

Örnek sonuç:

```text
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors
```

---

## GitHub Geliştirme Süreci

Proje geliştirme süreci GitHub üzerinden yürütülmüştür. Geliştirme aşamaları düzenli commitler ile takip edilmiştir. Proje iki kişilik ekip çalışmasına uygun şekilde GitHub collaborator yapısı kullanılarak geliştirilmiştir.

---

## Ders Bilgisi

```text
Bilgisayar Mühendisliği
Sistem Programlama Dersi
2025–2026 Bahar Dönemi Projesi
```