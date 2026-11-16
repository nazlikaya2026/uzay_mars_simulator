ek olarak 5 sağlık kaybedilir. Değerlerin 0-100 aralığına çekilmesi bu hesaptan sonra yapılır.
Oyun sonu koşulları. Her turun sonunda şu kontroller yapılır:
•	Sağlık veya oksijen 0'a düşerse oyun kaybedilir.
•	gun > 15 olursa yani 15. gün tamamlanırsa kurtarma ekibi gelir ve oyun kazanılır.
•	Oyuncu Q girerse oyun, kazanma ya da kaybetme olmadan sonlanır.
Döngüden çıkınca, oyun nasıl biterse bitsin bir sonuç raporu yazdırılır: sonuç mesajı, hayatta kalınan gün, toplam tur ve son durum değerleri.
Puan formülü.
puan = (gun * 100) + (saglik * 2) + (oksijen * 2) + enerji
     + (su * 5) + (yedek_parca * 10) - modul_hasari;
Katsayıları şu mantıkla seçtim: hayatta kalınan gün en önemli ölçüt olduğu için 100 ile çarpılır. Sağlık ve oksijen hayatta kalmayı doğrudan belirlediği için ikişer katıdır. Artan su ve yedek parça gelecekteki dayanıklılığı gösterdiği için ek puan verir, modül hasarı ise puanı düşürür. Puan negatif olursa 0'a çekilir.
9. Örnek Çalışma ve GitHub Bağlantısı
Programı Normal seviyede çalıştırınca örneğin şöyle bir çıktı alınır. Aşağıdaki çıktı hava kilidi ve fırtına komutlarının birlikte nasıl çalıştığını gösteriyor. Kilit mühürlü olduğu için fırtınada oksijen kaybı 0'dır, buna rağmen sağlık düşer:
Sifre harfini girin (1/3): Hatali sifre! (-5 Enerji) Ipucu: Alfabede ILERI git.
Sifre harfini girin (2/3): Sifre dogrulandi! Hava kilidi MUHURLENDI.

DIKKAT! Kum firtinasi basladi! (5 tur surecek)
Firtina Turu 1 -> Zar: 70 / Esik: 50 -> BASARISIZ (Firtina vurdu!)
Hava kilidi muhurlu oldugu icin oksijen sizintisi onlendi!
...
--- FIRTINA OZETI ---
Hasar alinan tur: 3 | Kaybedilen Saglik: 20 | Kaybedilen Oksijen: 0
Komutların durum değişkenlerine etkisi özetle şöyledir:
•	G: 15 enerji ve 10 oksijen harcar. Su (+8) veya yedek parça (+2) bulunabilir ya da eli boş dönülür. Yaralanırsa sağlık 15 azalır.
•	O: 10 enerji harcar. İşlenen suyun yarısı kadar 3'lük oksijen üretilir, su depodan düşer.
•	T: 10 enerji harcar. Yedek parça ve modül hasarı azalır.
•	D: Sadece raporu yazdırır, tur harcamaz.
•	U: Enerji 25 artar, oksijen 10 azalır. Sağlık 10 artar; modül hasarı 70'in üzerindeyse 5 artar, oksijen 20'nin altındaysa 10 azalır.
•	K: Fırtına turlarında sağlık ve modül hasarı etkilenir. Hava kilidi mühürlü değilse oksijen de azalır.
•	H: Her yanlış denemede 5 enerji gider. Doğru şifrede kilit mühürlenir, 3 hata olursa modül hasarı 20 artar.
•	Q: Simülasyondan çıkılır ve sonuç raporu yazılır.
Videoda şu durumlar gösterilecektir: bütün komutların etkisi, geçersiz zorluk seviyesi girişi, tanımsız komut girişi (tur harcamıyor) ve bir kaybetme senaryosu.
