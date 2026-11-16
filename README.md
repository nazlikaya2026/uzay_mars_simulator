# Mars Kolonisi Yaşam Destek Simülatörü

C ile yazdığım metin tabanlı bir hayatta kalma oyunu. Oyuncu Mars'ta tek başına kalmış bir mühendisi yönetiyor ve kurtarma ekibi gelene kadar 15 gün hayatta kalmaya çalışıyor. Algoritma ve Programlama dersi ödevi için yapıldı.

## Çalıştırma

```
gcc main.c -o mars
./mars
```

## Nasıl oynanır

Oyun başında zorluk seçilir: K (Kolay), N (Normal) veya Z (Zor). Zorluk arttıkça başlangıç suyu ve yedek parça azalır, modül hasarı ve kum fırtınasının süresi artar.

Sonra komutlar girilir. Büyük ya da küçük harf fark etmez.

- G: Keşfe çık. Enerji ve oksijen harcanır, su veya yedek parça bulunabilir.
- O: Su harcayarak oksijen üret. 2 su 3 oksijen yapar.
- T: Yedek parça harcayarak modül hasarını onar.
- D: Durum raporunu göster. Tur harcamaz.
- U: Uyu. Enerji ve sağlık artar.
- K: Kum fırtınası başlat.
- H: Hava kilidi şifresini dene. 3 hakkın var.
- Q: Çık.

Yanlış bir komut girersen uyarı verir ve tur harcamaz.

## Oyunun kuralları

Her 3 komutta bir gün geçer. Her yeni gün oksijen 8 azalır. Modül hasarı 70'in üzerindeyse ayrıca 5 sağlık gider.

Sağlık ya da oksijen 0 olursa oyunu kaybedersin. 15 günü tamamlarsan kurtarma ekibi gelir ve kazanırsın. Oyun bitince hayatta kalınan gün, toplam tur, son değerler ve puan yazdırılır.

Zar atılan her yerde atılan sayı ve eşik değeri ekrana yazılır, örneğin: Zar: 37 / Esik: 45 -> BASARILI

## Kullanılan yapılar

- switch-case: zorluk seçimi ve komutlar (büyük/küçük harf için fall-through)
- if, else if, else: tamir kademeleri, durum raporu, kaynak kontrolleri
- for: kum fırtınası (break ve continue ile)
- do-while: zorluk seçimi, ana oyun döngüsü, hava kilidi şifresi
- mod (%) operatörü: tek/çift su miktarı, çift numaralı fırtına turları, gün hesabı, günlük şifre
- srand(time(NULL)) ve rand() % 100: rastgelelik

## Puan

```
puan = (gun * 100) + (saglik * 2) + (oksijen * 2) + enerji + (su * 5) + (yedek_parca * 10) - modul_hasari
```

