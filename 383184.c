/* SEFA ALPER - 383184
   OĞUZ ELBAŞOĞLU -
   */
#include <stdio.h>
#include <stdlib.h>
int takim_sayisi,galibiyet_puani,beraberlik_puani,maglubiyet_puani,oynananmaclar=0;
struct tkm{
  char kod,orijinal_hal[13];
  int averaj,puan;
  unsigned int mac,g,b,m,atilan,yenilen;
};
struct oynanan_yer{
  char ev_sahibi,deplasman;
};
struct oynanan_yer *oynanan_maclar;
struct tkm takimlar [26];
void takim_oku();
void menu_goster();
char buyuk(char o);
void ayarlar_oku();
void maclar_oku_klavye();
void maclar_oku_dosya();
void puan_tablosu_goruntule();
void alayini_buyult();
void koda_gore_sirala();
void takim_siralama();
void isme_gore_siralama();
int karsilastirma(char *string1,char *string2);
int mekan_kontrol(char ev,char dplsmn);
void menu_goster(){
  int secenek=1;
  printf("TÜRKİYE SANAL FUTBOL LİGİNE HOŞGELDİNİZ\n");
  while(secenek){ // menüyü döngü içine alıyoruz böylelikle kullanıcı çıkmak istemediği sürece işlemini tamamladığı zaman tekrar menüye yönlendirilecek. secenek  = 1 olduğu sürece çalışacak.
    int islem;
    printf("\n\n");

    printf("İşlemler\n1:Puan tablosu Görüntüleme\n2:Maç Sonucu Girme\n3:Puana Göre Sıralama\n4:Dosyadan Maç Okuma\n5:İsme Göre Sıralama\n6:Koda Göre Sıralama\n7:İsimleri Büyük Yazdır\n8:Çıkış Yapma\n\n\n\n");
    printf("İşlemi seçiniz: ");
    scanf(" %d",&islem);
    switch(islem){
      case 1:
        puan_tablosu_goruntule();
        break;
      case 2:
        maclar_oku_klavye();
        break;
      case 3:
        takim_siralama();
        break;
      case 4:
        maclar_oku_dosya();
        break;
      case 5:
        isme_gore_siralama();
        break;
      case 6:
        koda_gore_sirala();
        break;
      case 7:
        alayini_buyult();
        break;
      case 8:
        secenek = 0; // kullanıcı 7'i tuşlarsa secenek = 0 olacak böylelikle while döngüsü için koşul sağlanmamış olacak ve program kapanacak.
        break;
      default:
        printf("Yanlış tuşlama yaptınız.\n");
  }
  }
}
void ayarlar_oku(){
  FILE *ayar = fopen("ayarlar.txt", "r");
     char a;
     int sa=0,su=0;
     char ayarlar[4][3];
     while ((a = fgetc(ayar)) != EOF)
     {
        if(a != '\n'){
          ayarlar[sa][su++] = a;
        }
        else{
          sa++;
          su=0;
        }
     }
     fclose(ayar);
     takim_sayisi =  atoi(ayarlar[0]); // takım sayısını tutuyor. atoi fonksiyonu stringi int yapıyor.
     galibiyet_puani = atoi(ayarlar[1]); // galibiyet puanını tutuyor.
     beraberlik_puani = atoi(ayarlar[2]); // beraberlik puanını tutuyor.
     maglubiyet_puani = atoi(ayarlar[3]); // mağlubiyrt puanını tutuyor.

}

void takim_oku(){

  FILE *takim = fopen("takimlar.txt", "r"); // dosyayı okuyor.

  char t,tkm,str=0,karakter=0,takim_adi[13];

  while ((t = fgetc(takim)) != EOF) // t değikeni doyadan karakter tutuyor
  {
     if(karakter<12 && t != '\n'){ // takım isminin toplamda 12 karakteri geçmemesi için
       takim_adi[karakter++] = t;
     }
     else if(t == '\n'){
       takim_adi[karakter] = '\0';
       takimlar[str].kod = 65 + str; // takımları A,B gibi kod isimlerle tutmak için
       for(int i = 0; i <= karakter;i++){
         takimlar[str].orijinal_hal[i] = takim_adi[i];
       }
       // başlangıç değerlerini sıfıra atıyor.
       takimlar[str].mac = 0;
       takimlar[str].g = 0;
       takimlar[str].b = 0;
       takimlar[str].m = 0;
       takimlar[str].atilan =0;
       takimlar[str].yenilen = 0;
       takimlar[str].averaj = 0;
       takimlar[str].puan = 0;
       karakter = 0;
       str++;
          }
  }
  fclose(takim);
}
void puan_tablosu_goruntule(){
  // Puan tablosunu kusursuz hale getirebilmek için aşağıdaki gibi bir kod yazdık.
  printf("\n");
  printf("%-4s\t|","Kod" );
  printf("%-14s\t|","Takımlar");
  printf("%-16s\t|","Oynanmış Maçlar");
  printf("%-10s\t|","Galibiyet");
  printf("%-12s\t|","Beraberlik");
  printf("%-12s\t|","Mağlubiyet");
  printf("%-18s\t|","Atılan Gol Sayısı");
  printf("%-20s\t|","Yenilen Gol Sayısı");
  printf("%-6s\t|","Averaj");
  printf("%s\n","Puan Durumu");
printf("____________________________________________________________________________________________________________________________________________________________________\n");
  for(int f=0;f<takim_sayisi;f++) {
    printf("%-4c\t|", takimlar[f].kod);
    printf("%-14s\t|",takimlar[f].orijinal_hal);
    printf("%-16u\t|", takimlar[f].mac);
    printf("%-10u\t|",takimlar[f].g);
    printf("%-12u\t|",takimlar[f].b);
    printf("%-12u\t|",takimlar[f].m);
    printf("%-18u\t|",takimlar[f].atilan);
    printf("%-20u\t|",takimlar[f].yenilen);
    printf("%-6d\t|",takimlar[f].averaj);
    printf("%d\n",takimlar[f].puan);
  }
  printf("\n");
}
void maclar_oku_klavye(){
  char evsahibi,deplasmanekibi;
  int evsahibigol,deplasmangol,b;
  printf("UYARI: Lütfen maçın sonucunu takımların kod adı ile yazınız.\n\n");
  printf("Maç skorunu giriniz:\n");
  scanf(" %c %d %c %d",&evsahibi,&evsahibigol,&deplasmanekibi,&deplasmangol);
  if(evsahibi == deplasmanekibi){
    printf("Böyle bir maç oynanamaz.Lütfen kontrol edip tekrar giriniz.\n\n");
  }
  else {
  for(b=0;b<oynananmaclar;b++){
    if(evsahibi == oynanan_maclar[b].ev_sahibi && deplasmanekibi == oynanan_maclar[b].deplasman){
      printf("UYARI: Bu maç daha önce oynandı. Lütfen kontrol edip tekrar giriniz.\n\n\n\n");
      return;
    }
  }
  oynanan_maclar[oynananmaclar].ev_sahibi = evsahibi;
  oynanan_maclar[oynananmaclar++].deplasman = deplasmanekibi;
  for(int t1 = 0; t1 < takim_sayisi; t1++){
    if(takimlar[t1].kod == evsahibi){
      if(evsahibigol > deplasmangol){ // ev sahibinin galibiyeti durumunda ev sahibine galibiyet puanını atıyor.
         takimlar[t1].g++;
          takimlar[t1].puan += galibiyet_puani;
      }else if(evsahibigol < deplasmangol){ // deplasman ekibinin galibiyeti durumunda ev sahibine mağlubiyet puanını atıyor.
          takimlar[t1].puan += maglubiyet_puani;
          takimlar[t1].m++;
      }else{
        takimlar[t1].puan += beraberlik_puani; // beraberlik durumunda beraberlik puanını artırıyor.
        takimlar[t1].b++;
      }
      takimlar[t1].mac++;
        takimlar[t1].averaj += evsahibigol - deplasmangol;
        takimlar[t1].atilan += evsahibigol;
        takimlar[t1].yenilen += deplasmangol;
    }else if(takimlar[t1].kod == deplasmanekibi){
      if(deplasmangol > evsahibigol){
         takimlar[t1].g++;
          takimlar[t1].puan += galibiyet_puani;
      }else if(deplasmangol < evsahibigol){
          takimlar[t1].puan += maglubiyet_puani;
          takimlar[t1].m++;
      }else{
        takimlar[t1].puan += beraberlik_puani;
        takimlar[t1].b++;
      }
      takimlar[t1].mac++;
      takimlar[t1].averaj += deplasmangol - evsahibigol;
      takimlar[t1].atilan += deplasmangol;
      takimlar[t1].yenilen += evsahibigol;
    }
  }
  }
}

  void maclar_oku_dosya(){
    FILE *maclar1 = fopen("maclar1.txt", "r");
    char m;
    int satir=0,sutun=0;
    char ev,dplsmn;
    char maclar[4][3];
    while ((m = fgetc(maclar1)) != EOF)
    {
       if(m == '\n'){
         satir=0;
         sutun=0;
         ev = maclar[0][0];
         dplsmn = maclar[2][0];
         int ev_sahibi_gol = atoi(maclar[1]), deplasman_gol = atoi(maclar[3]);
           if(mekan_kontrol(ev,dplsmn)){
             oynanan_maclar[oynananmaclar].ev_sahibi = ev;
             oynanan_maclar[oynananmaclar++].deplasman = dplsmn;
             for(int t1 = 0; t1 < takim_sayisi; t1++){
               if(takimlar[t1].kod == ev){
                 if(ev_sahibi_gol > deplasman_gol){
                    takimlar[t1].g++;
                     takimlar[t1].puan += galibiyet_puani;
                 }else if(ev_sahibi_gol < deplasman_gol){
                     takimlar[t1].puan += maglubiyet_puani;
                     takimlar[t1].m++;
                 }else{
                   takimlar[t1].puan += beraberlik_puani;
                   takimlar[t1].b++;
                 }
                 takimlar[t1].mac++;
                   takimlar[t1].averaj += ev_sahibi_gol - deplasman_gol;
                   takimlar[t1].atilan += ev_sahibi_gol;
                   takimlar[t1].yenilen += deplasman_gol;
               }else if(takimlar[t1].kod == dplsmn){
                 if(deplasman_gol > ev_sahibi_gol){
                    takimlar[t1].g++;
                     takimlar[t1].puan += galibiyet_puani;
                 }else if(deplasman_gol < ev_sahibi_gol){
                     takimlar[t1].puan += maglubiyet_puani;
                     takimlar[t1].m++;
                 }else{
                   takimlar[t1].puan += beraberlik_puani;
                   takimlar[t1].b++;
                 }
                 takimlar[t1].mac++;
                 takimlar[t1].averaj += deplasman_gol - ev_sahibi_gol;
                 takimlar[t1].atilan += deplasman_gol;
                 takimlar[t1].yenilen += ev_sahibi_gol;
               }
             }
       }
     }
               else if(m ==' '){
         satir++;
         sutun=0;
       }
       else{
         maclar[satir][sutun++] = m;
       }
    }
    fclose(maclar1);
  }
int mekan_kontrol(char ev,char dplsmn){

  for(int m1=0;m1<oynananmaclar;m1++){
    if(ev == oynanan_maclar[m1].ev_sahibi && dplsmn == oynanan_maclar[m1].deplasman){
      return 0;
    }
}
  return 1;
}
void takim_siralama(){
  for (int i = 1 ; i < takim_sayisi; i++) {
    int j = i;

    while (j > 0) {
      if(takimlar[j-1].puan > takimlar[j].puan) // takımların puanlarını karşılaştırıyor.
        break;
      if(takimlar[j-1].puan == takimlar[j].puan && takimlar[j-1].averaj >= takimlar[j].averaj) // puanların eşit olması durumund averaj devreye giriyor ve ona göre sıralamaya geçiyor.
      break;
      struct tkm eleman = takimlar[j]; // tkm struct'ına ait eleman tanımlanıyor ve bu değer karşılaştırma sırasında bizim pivotumuz olacak.
      takimlar[j]   = takimlar[j-1];
      takimlar[j-1] = eleman;
      j--;
    }
  }
}
void isme_gore_siralama(){
  int i,j;
  for (i = 1 ; i <= takim_sayisi; i++) {
    j = i;
    while ( j-- > 0 ){
      if(karsilastirma(takimlar[j].orijinal_hal,takimlar[j-1].orijinal_hal)){ // aşağıda yazdığımız karşılaştırma fonksiyonunu çağırıyoruz. Böylelikle takımların isimlerindeki tüm harfleri karşılaştırarak sıralıyor.

        struct tkm eleman  = takimlar[j]; // tkm struct'ına ait eleman tanımlıyoruz ve bu pivot değerimiz oluyor.
        takimlar[j]    = takimlar[j-1]; // ardından sırayla atamalar yapılıyor.
        takimlar[j-1] = eleman;
      }
    }
  }
}
int karsilastirma(char *string1,char *string2){
  int s=-1;
  while(string1[++s] != '\0' && string2[s] != '\0'){
    if(buyuk(string1[s]) == buyuk(string2[s])){
      continue;
    }
    else break;
  }
  if(buyuk(string1[s]) == buyuk(string2[s])) return 0;
  if(buyuk(string1[s]) < buyuk(string2[s])) return 1;
  return 0;
}
char buyuk(char o){
  if(o >= 97 && o<=122){
    return o-32; // küçük harfleri büyük harf yapıyor.
  }
  return o; // yukarıdaki koşul sağlanmazsa yani sayı zaten büyük harfse direkt olarak onu dönüyor.
}
void koda_gore_sirala(){ // insertion sort algoritmasını uyguladık. Böylece isteğe bağlı olarak tekrar kod isimlerine göre sıralayabiliyoruz.
  for (int i = 1 ; i < takim_sayisi; i++) {
    int j = i;
    while (j > 0) {
      if(takimlar[j-1].kod < takimlar[j].kod)
        break;
      struct tkm eleman = takimlar[j];
      takimlar[j]   = takimlar[j-1];
      takimlar[j-1] = eleman;
      j--;
    }
  }
}
void alayini_buyult(){ // Takım isimlerinin tamamını büyültüyor.
  for (int i = 0 ; i < takim_sayisi; i++) {
    for(int j=0;takimlar[i].orijinal_hal[j] != '\0';j++)
    takimlar[i].orijinal_hal[j] = buyuk(takimlar[i].orijinal_hal[j] ); // daha önce kullandığımız büyültme fonksiyonunu çağırarak küçük harfleri algılayıp büyük hale getiriyoruz.
  }

}
int main(){
  takim_oku();
  ayarlar_oku();
  oynanan_maclar = (struct oynanan_yer*)malloc(((takim_sayisi - 1) * takim_sayisi + 1) * sizeof(struct oynanan_yer));
  menu_goster();
}
