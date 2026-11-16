#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

	srand(time(NULL));

	int saglik = 100;
	int enerji = 100;
	int oksijen = 100;
	int su = 0;
	int yedek_parca = 0;
	int modul_hasari = 0;
	int kilit_muhurlu = 0;
	int gun = 1;
	int tur = 1;
	int toplam_tur = 0;
	char zorluk;
	char komut;
	int firtina_turu = 3;
	int firtina_hasar = 5;   /* firtinada bir basarisiz turda temel hasar */
	int zorluk_secildi = 0;

	do {
		printf("Zorluk seviyesi secin (K: Kolay, N: Normal, Z: Zor) ");
		if (scanf(" %c", &zorluk) != 1) {
			printf("\nGirdi okunamadi. Program sonlandiriliyor.\n");
			return 0;
		}

		switch (zorluk) {
			case 'k':
			case 'K':
				su = 30;
				yedek_parca = 6;
				modul_hasari = 10;
				firtina_turu = 3;
				firtina_hasar = 3;
				zorluk_secildi = 1;
				printf("Kolay seviye secildi.\n");
				break;

			case 'n':
			case 'N':
				su = 20;
				yedek_parca = 4;
				modul_hasari = 20;
				firtina_turu = 5;
				firtina_hasar = 5;
				zorluk_secildi = 1;
				printf("Normal seviye secildi.\n");
				break;

			case 'z':
			case 'Z':
				su = 12;
				yedek_parca = 2;
				modul_hasari = 35;
				firtina_turu = 7;
				firtina_hasar = 8;
				zorluk_secildi = 1;
				printf("Zor seviye secildi.\n");
				break;

			default:
				printf("Gecersiz giris! Lutfen K, N veya Z giriniz.\n");
				break;
		}
	} while (zorluk_secildi == 0);

	int oyun_devam = 1;

	do {
		int tur_artir = 1;

		printf("\n---------------------------------\n");
		printf("GUN: %d | TUR: %d\n", gun, tur);
		printf("Komutlar: G:Kesif, O:Oksijen, T:Tamir, D:Durum, U:Uyu, K:Firtina, H:Kilit, Q:Cikis\n");
		printf("Komutunuz: ");
		if (scanf(" %c", &komut) != 1) {
			printf("\nGirdi okunamadi, simulasyon sonlandiriliyor.\n");
			break;
		}

		switch (komut) {
			case 'd':
			case 'D':
				printf("\n--- DURUM RAPORU ---\n");
				printf("Saglik: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji, oksijen);
				printf("Su: %d | Yedek Parca: %d | Modul Hasari: %d\n", su, yedek_parca, modul_hasari);
				if (kilit_muhurlu == 1) {
					printf("Hava Kilidi Durumu: MUHURLU\n");
				} else {
					printf("Hava Kilidi Durumu: ACIK\n");
				}

				if (oksijen < 25) {
					printf("UYARI: Oksijen kritik seviyede!\n");
				}
				if (saglik < 30) {
					printf("UYARI: Saglik kritik seviyede!\n");
				}
				if (enerji < 25) {
					printf("UYARI: Enerji kritik seviyede!\n");
				}
				if (modul_hasari > 70) {
					printf("UYARI: Modul hasari kritik seviyede!\n");
				}
				if (oksijen >= 25 && saglik >= 30 && modul_hasari <= 70 && enerji >= 25) {
					printf("TUM SISTEMLER NORMAL\n");
				}

				tur_artir = 0;
				break;

			case 'g':
			case 'G':
				if (enerji < 15 || oksijen <= 10) {
					printf("Yetersiz enerji veya oksijen! Kesif gorevi iptal edildi.\n");
					tur_artir = 0;
				} else {
					enerji = enerji - 15;
					oksijen = oksijen - 10;

					int zar = rand() % 100;
					int esik;

					if (enerji > 40 && oksijen > 30) {
						esik = 65;
					} else {
						esik = 35;
					}

					if (zar < esik) {
						printf("Zar: %d / Esik: %d -> BASARILI\n", zar, esik);

						if (zar % 2 == 0) {
							su = su + 8;
							printf("Kesif basarili! Buz tabakasi bulundu. (+8 Su)\n");
						} else {
							yedek_parca = yedek_parca + 2;
							printf("Kesif basarili! Eski bir uydu parcasi bulundu. (+2 Yedek Parca)\n");
						}
					} else {
						printf("Zar: %d / Esik: %d -> BASARISIZ\n", zar, esik);
						printf("Kesiften eli bos dondunuz.\n");
					}

					if (zar < 10 || modul_hasari > 70) {
						saglik = saglik - 15;
						printf("DIKKAT: Kesif sirasinda yaralandiniz! (-15 Saglik)\n");
					}
				}
				break;

			case 'o':
			case 'O':
				if (enerji < 10) {
					printf("Yetersiz enerji! Oksijen uretimi icin en az 10 enerji gerekli.\n");
					tur_artir = 0;
				} else if (su < 2) {
					printf("Yetersiz su! Oksijen uretimi icin en az 2 birim su gerekli.\n");
					tur_artir = 0;
				} else if (oksijen >= 100) {
					printf("Oksijen deposu zaten dolu!\n");
					tur_artir = 0;
				} else {
					int kullanilacak_su = 0;
					printf("Mevcut su: %d. Kullanilacak su miktarini girin: ", su);

					if (scanf("%d", &kullanilacak_su) != 1) {
						printf("Gecersiz giris! Sayi girmelisiniz. Islem iptal edildi.\n");
						tur_artir = 0;
					} else {

						if (kullanilacak_su <= 0 || kullanilacak_su > su) {
							printf("Gecersiz veya yetersiz su miktari! Islem iptal edildi.\n");
							tur_artir = 0;
						} else {
							int kalan_su = kullanilacak_su % 2;
							int islenen_su = kullanilacak_su - kalan_su;

							if (islenen_su == 0) {
								printf("En az 2 birim su girmelisiniz! Islem iptal edildi.\n");
								tur_artir = 0;
							} else {
								int uretilen_oksijen = (islenen_su / 2) * 3;
								int bosluk = 100 - oksijen;

								if (uretilen_oksijen > bosluk) {
									int cift_sayisi = (bosluk + 2) / 3;
									islenen_su = cift_sayisi * 2;
									uretilen_oksijen = bosluk;
									kalan_su = kullanilacak_su - islenen_su;
									printf("Oksijen 100'u asamaz! Islenen su %d birime dusuruldu.\n", islenen_su);
								}

								su = su - islenen_su;
								enerji = enerji - 10;
								oksijen = oksijen + uretilen_oksijen;

								printf("%d birim su islendi, +%d oksijen uretildi. (Kullanilmayan su: %d)\n",
									   islenen_su, uretilen_oksijen, kalan_su);
							}
						}
					}
				}
				break;

			case 't':
			case 'T':
				if (modul_hasari == 0) {
					printf("Modulde hic hasar yok, tamire gerek duyulmadi.\n");
					tur_artir = 0;
				} else if (yedek_parca <= 0) {
					printf("Yedek parca yok! Tamir yapilamadi.\n");
					tur_artir = 0;
				} else if (enerji < 10) {
					printf("Yetersiz enerji! Tamir icin en az 10 enerji gerekli.\n");
					tur_artir = 0;
				} else {
					if (modul_hasari <= 30) {
						yedek_parca = yedek_parca - 1;
						modul_hasari = modul_hasari - 15;
						enerji = enerji - 10;
						printf("Hafif hasar onarildi. (1 parca kullanildi, -15 hasar)\n");
					} else if (modul_hasari <= 70) {
						if (yedek_parca >= 2) {
							yedek_parca = yedek_parca - 2;
							modul_hasari = modul_hasari - 30;
							enerji = enerji - 10;
							printf("Orta seviye hasar onarildi. (2 parca kullanildi, -30 hasar)\n");
						} else {
							yedek_parca = yedek_parca - 1;
							modul_hasari = modul_hasari - 15;
							enerji = enerji - 10;
							printf("Yetersiz parca nedeniyle kismi tamir yapildi. (1 parca kullanildi, -15 hasar)\n");
						}
					} else {
						if (yedek_parca >= 3) {
							yedek_parca = yedek_parca - 3;
							modul_hasari = modul_hasari - 45;
							enerji = enerji - 10;
							printf("Agir hasar onarildi! (3 parca kullanildi, -45 hasar)\n");
						} else {
							printf("Agir hasar onarimi icin en az 3 yedek parca gerekiyor!\n");
							tur_artir = 0;
						}
					}
				}
				break;

			case 'u':
			case 'U':
				enerji = enerji + 25;
				oksijen = oksijen - 10;

				if (oksijen < 20) {
					saglik = saglik - 10;
					printf("Dinlendiniz (+25 enerji), ancak dusuk oksijen nedeniyle saglik kaybettiniz! (-10 saglik)\n");
				} else {
					if (modul_hasari > 70) {
						saglik = saglik + 5;
						printf("Gurultulu ve hasarli modulde dinlendiniz. (+25 enerji, +5 saglik, -10 oksijen)\n");
					} else {
						saglik = saglik + 10;
						printf("Iyi bir uyku cektiniz. (+25 enerji, +10 saglik, -10 oksijen)\n");
					}
				}
				break;

			case 'k':
			case 'K': {
				int hasar_alinan_tur = 0;
				int toplam_saglik_kaybi = 0;
				int toplam_oksijen_kaybi = 0;
				int i;

				printf("\nDIKKAT! Kum firtinasi basladi! (%d tur surecek)\n", firtina_turu);

				for (i = 1; i <= firtina_turu; i++) {
					int zar = rand() % 100;
					int esik = 50;
					int carpan = 1;

					/* Modul agir hasarliysa korunma sansi duser */
					if (modul_hasari > 70) {
						esik = 35;
					}

					/* Cift numarali turlarda ruzgar siddetlenir */
					if (i % 2 == 0) {
						carpan = 2;
					}

					printf("Firtina Turu %d -> ", i);

					if (zar < esik) {
						printf("Zar: %d / Esik: %d -> BASARILI (Firtinadan korundunuz)\n", zar, esik);
					} else {
						printf("Zar: %d / Esik: %d -> BASARISIZ (Firtina vurdu!)\n", zar, esik);
						hasar_alinan_tur++;

						int can_kaybi = firtina_hasar * carpan;
						int hasar_artisi = firtina_hasar * carpan;
						saglik = saglik - can_kaybi;
						modul_hasari = modul_hasari + hasar_artisi;
						toplam_saglik_kaybi = toplam_saglik_kaybi + can_kaybi;

						if (kilit_muhurlu == 1) {
							printf("Hava kilidi muhurlu oldugu icin oksijen sizintisi onlendi!\n");
							if (saglik <= 0) {
								saglik = 0;
								printf("Kritik durum! Firtina sirasinda yasam destegi coktu!\n");
								break;
							}
							continue;
						}

						int oksijen_kaybi = (firtina_hasar + 1) * carpan;
						oksijen = oksijen - oksijen_kaybi;
						toplam_oksijen_kaybi = toplam_oksijen_kaybi + oksijen_kaybi;
					}

					if (saglik <= 0 || oksijen <= 0) {
						if (saglik < 0) saglik = 0;
						if (oksijen < 0) oksijen = 0;
						printf("Kritik durum! Firtina sirasinda yasam destegi coktu!\n");
						break;
					}
				}

				printf("--- FIRTINA OZETI ---\n");
				printf("Hasar alinan tur: %d | Kaybedilen Saglik: %d | Kaybedilen Oksijen: %d\n",
					   hasar_alinan_tur, toplam_saglik_kaybi, toplam_oksijen_kaybi);
				break;
			}

			case 'h':
			case 'H': {
				if (kilit_muhurlu == 1) {
					printf("Hava kilidi zaten muhurlu!\n");
					tur_artir = 0;
				} else if (enerji < 5) {
					printf("Yetersiz enerji! Hava kilidi sifresi denemek icin en az 5 enerji gerekli.\n");
					tur_artir = 0;
				} else {
					char gizli_sifre = 'A' + (gun % 26);
					char girilen_sifre = ' ';
					int deneme = 0;

					printf("\n--- HAVA KILIDI GUVENLIK SISTEMI ---\n");
					printf("Ipucu: Sifre, Ingiliz alfabesinde 'A' harfinden bugunun gun sayisi (%d) kadar ilerideki harftir.\n", gun);

					do {
						printf("Sifre harfini girin (%d/3): ", deneme + 1);
						if (scanf(" %c", &girilen_sifre) != 1) {
							girilen_sifre = ' ';
						}

						if (girilen_sifre >= 'a' && girilen_sifre <= 'z') {
							girilen_sifre = girilen_sifre - ('a' - 'A');
						}

						deneme++;

						if (girilen_sifre != gizli_sifre) {
							enerji = enerji - 5;
							if (enerji < 0) enerji = 0;
							printf("Hatali sifre! (-5 Enerji) ");
							if (girilen_sifre < gizli_sifre) {
								printf("Ipucu: Alfabede ILERI git.\n");
							} else {
								printf("Ipucu: Alfabede GERI git.\n");
							}
						}
					} while (girilen_sifre != gizli_sifre && deneme < 3);

					if (girilen_sifre == gizli_sifre) {
						kilit_muhurlu = 1;
						printf("Sifre dogrulandi! Hava kilidi MUHURLENDI.\n");
					} else {
						modul_hasari = modul_hasari + 20;
						printf("3 deneme de basarisiz! Guvenlik kilitlendi ve +20 Modul Hasari olustu.\n");
					}
				}
				break;
			}

			case 'q':
			case 'Q':
				printf("Simulasyondan cikis yapiliyor...\n");
				oyun_devam = 0;
				tur_artir = 0;
				break;

			default:
				printf("Tanimsiz komut! Gecerli bir harf giriniz.\n");
				tur_artir = 0;
				break;
		}

		/* Zaman akisi: her gecerli komut 1 tur harcar, her 3 turda yeni gun */
		if (tur_artir == 1 && oyun_devam == 1) {
			tur++;
			toplam_tur++;
			if (toplam_tur % 3 == 0) {
				gun++;
				tur = 1;

				if (gun <= 15) {
					oksijen = oksijen - 8;
					printf("\n>>> YENI GUN BASLADI (GUN: %d)! Gunluk -8 Oksijen.\n", gun);

					if (modul_hasari > 70) {
						saglik = saglik - 5;
						printf(">>> UYARI: Yuksek modul hasari nedeniyle ek -5 Saglik kaybettiniz!\n");
					}
				}
			}
		}

		/* Sinirlandirma: gun basi cezalarindan SONRA yapilir ki negatif deger kalmasin */
		if (saglik > 100) saglik = 100;
		if (saglik < 0) saglik = 0;
		if (enerji > 100) enerji = 100;
		if (enerji < 0) enerji = 0;
		if (oksijen > 100) oksijen = 100;
		if (oksijen < 0) oksijen = 0;
		if (modul_hasari > 100) modul_hasari = 100;
		if (modul_hasari < 0) modul_hasari = 0;

		/* Oyun sonu kontrolleri */
		if (saglik <= 0 || oksijen <= 0) {
			oyun_devam = 0;
		}
		if (gun > 15) {
			oyun_devam = 0;
		}

	} while (oyun_devam == 1);

	int gosterilen_gun = gun;
	if (gun > 15) {
		gosterilen_gun = 15;
	}

	printf("\n========================================\n");
	printf("          SIMULASYON SONA ERDI          \n");
	printf("========================================\n");

	if (saglik <= 0) {
		printf("SONUC: Sagliginiz tukendi! Koloni gorevi basarisiz.\n");
	} else if (oksijen <= 0) {
		printf("SONUC: Oksijeniniz tukendi! Koloni gorevi basarisiz.\n");
	} else if (gun > 15) {
		printf("SONUC: TEBRIKLER! 15 gun boyunca Mars'ta hayatta kalmayi basardiniz!\n");
	} else {
		printf("SONUC: Gorev oyuncu tarafindan sonlandirildi.\n");
	}

	printf("\n--- FINAL ISTATISTIKLERI ---\n");
	printf("Hayatta Kalinan Gun: %d | Toplam Tur: %d\n", gosterilen_gun, toplam_tur);
	printf("Kalan Saglik: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji, oksijen);
	printf("Kalan Su: %d | Yedek Parca: %d | Modul Hasari: %d\n", su, yedek_parca, modul_hasari);

	int puan = (gosterilen_gun * 100) + (saglik * 2) + (oksijen * 2) + enerji + (su * 5) + (yedek_parca * 10) - modul_hasari;
	if (puan < 0) puan = 0;

	printf("\nTOPLAM HAYATTA KALMA PUANI: %d\n", puan);

	return 0;
}

