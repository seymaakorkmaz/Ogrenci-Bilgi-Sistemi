#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dos.h>

typedef struct ogrenci{
	char ad[20];
	char soyad[20];
	int derssayisi;
	int toplamkredi;
	int no;
	struct ogrenci *next;
	struct ogrenci *prev;

} STUDENT;

typedef struct kayit{
	int numara;
	char derskodu[20];
	char tarih[20];
	int ogr;
	char bilgi[20];
	struct kayit *next;
}KAYIT;
typedef struct ders{
	char kod[10];
	char ad[40];
	int kredi;
	int kontenjan;
	int kayitlikisi;
	int *list;
	struct ders *next;
}DERS;

void DersListeAl(DERS **headd, KAYIT **headk);
void OgrenciListeAl(STUDENT **heads);
void DersKayitListeAl(KAYIT **headk);
void OgrenciDersKayitYazdir(KAYIT *headk);
void OgrenciListeYaz(STUDENT *heads);
void OgrenciEkle(STUDENT **heads);
void OgrenciSil(STUDENT **heads,DERS ** headd,KAYIT **headk,char tarih[]);
void DersListeYaz(DERS *headd);
void DersEkle(DERS **headd,char tarih[]);
void DersKapat(DERS **headd, KAYIT **headk,STUDENT **heads,char tarih[]);
void DosyayaKaydet1(FILE *dosya,DERS *headd);
void DosyayaKaydet2(FILE *dosya,STUDENT *heads);
void DosyayaKaydet3(FILE *dosya,KAYIT *headk);
STUDENT *OgrenciBul(STUDENT *heads,int );
DERS *DersBul(DERS *headd,char kod[]);
void OgrenciDersKayit(DERS **headd,STUDENT **heads, KAYIT **headk,int maxders,int kredi,char tarih[]);
int ListeyeEkle(DERS **ders,STUDENT **ogr,int no);
void SinifListesiOlustur(DERS **headd);
void SinifListesiYazdir(DERS **headd);
void OgrenciKayitSil(DERS **headd,STUDENT **heads, KAYIT **headk,char tarih[]);
void ListedenSil(DERS **ders,STUDENT **ogr,int no);
void DersProgrami(DERS *headd,STUDENT *heads);
void free1(DERS *headd);
void free2(STUDENT *heads);
void free3(KAYIT *headk);

int main(){
	KAYIT *headk=NULL;
	DERS *headd=NULL;
	STUDENT *heads=NULL;
	OgrenciListeAl(&heads);
	DersKayitListeAl(&headk);
	DersListeAl(&headd,&headk);
	int islem,maxders,maxkredi;
	char tarih[20];
	
	printf("\n\tTarih giriniz (GG.AA.YYYY) : ");
	scanf("%s",tarih);
	printf("\n\tOgrenci ders kayit islemleri girdiginiz degerlere gore yapilacaktir.\n");
	printf("\n\tOgrencinin alabilecegi maksimum ders sayisini giriniz : ");
	scanf("%d",&maxders);
	printf("\tOgrencinin alabilecegi maksimum kredi sayisini giriniz : ");
	scanf("%d",&maxkredi);
	
	system("cls");
	do{
	printf("\n\n                           MENU                        \n");
	printf("\t--------------------------------------------\n");
	printf("\t	1.Ogrencileri listele \n");
	printf("\t	2.Ogrenci Ekle \n");
	printf("\t	3.Ogrenci Sil \n");
	printf("\t	4.Dersleri Listele \n");
	printf("\t	5.Ders Ekle \n");
	printf("\t	6.Ders Kapat \n");
	printf("\t        7.Ogrenciyi derse kaydet\n");
	printf("\t        8.Ogrencinin dersten kaydini sil\n");
	printf("\t        9.Sinif listesi yazdir\n");
	printf("\t        10.Ogrencinin ders programini yazdir\n");
	printf("\t	11.CIKIS \n");
	printf("\t--------------------------------------------\n");
	printf("	Bir islem seciniz : ");
	scanf("%d",&islem);
	
	switch(islem){
		case 1: 
			system("cls");
			OgrenciListeYaz(heads);
		break;
		case 2:
			system("cls");
			OgrenciEkle(&heads);
		break;
		case 3:
			system("cls");
			OgrenciSil(&heads,&headd,&headk,tarih);	
		break;
		case 4:
			system("cls");
			DersListeYaz(headd);
		break;
		case 5:
			system("cls");
			DersEkle(&headd,tarih);
		break;
		case 6:
			system("cls");
			DersKapat(&headd,&headk,&heads,tarih);
		break;
		case 7:
			system("cls");
  			OgrenciDersKayit(&headd,&heads,&headk,maxders,maxkredi,tarih);
		break;
		case 8:
			system("cls");
			OgrenciKayitSil(&headd,&heads,&headk,tarih);
		break;
		case 9:
			system("cls");
			SinifListesiYazdir(&headd);
		break;
		case 10:
			system("cls");
			DersProgrami(headd,heads);
		break;
	}
	}while(islem!=11);
	
	free1(headd);
	free2(heads);
	free(headk);
	
	return 0;
}

void DersListeAl(DERS **headd, KAYIT **headk){
	int size;
	int i;
	KAYIT *temp;
	DERS *p=(DERS*)malloc(sizeof(DERS));
	if(p==NULL)  exit(-1);
	DERS *a=(DERS*)malloc(sizeof(DERS));
	if(a==NULL) exit(-1);
	FILE *dosya=fopen("dersler.txt","r");
	if(dosya == NULL){          //dosya var m� kontrol�
  	//	printf("Dosya bulunamadi...");
  		FILE *dosya=fopen("dersler.txt","w");
 	}else{
 		fseek(dosya,0,SEEK_END);  //dosyan�n i�i dolu mu kontrol�
 		size=ftell(dosya);
	}
	if(size != 0){
		fseek(dosya,0,SEEK_SET); 
		while(!feof(dosya)){
 			fscanf(dosya,"%[^,],%[^,],%d,%d\n",a->kod,a->ad,&(a->kredi),&(a->kontenjan));
			if(*headd==NULL){
				*headd=p;          //link bo�sa ba�a yer a��l�r
			}else{
				p->next=(DERS*)malloc(sizeof(DERS));     //link doluysa nextine yer a��l�r
				p=p->next;
			}
			strcpy(p->ad,a->ad);
			strcpy(p->kod,a->kod);
			p->kontenjan=a->kontenjan;
			p->kredi=a->kredi;
			p->next=NULL;		
	
		p->kayitlikisi=0; //derslerin mevcutlar�n� ba�lang��ta s�f�rl�yoruz
		i=0;
		
		if((*headk) != NULL){
			temp=*headk;
			while(temp != NULL){   //��renci ders kay�t dosyas�nda var olan kay�tlara g�re mevcutlar� art�r�p derslerin ��renci dizisini dolduruyoruz
			if((strcmp((temp->derskodu),(p->kod))) == 0 && (strcmp((temp->bilgi),"kayitli"))==0){
				if(p->kayitlikisi == 0){
					(p->kayitlikisi)++;
					p->list=(int*)malloc((p->kayitlikisi)*sizeof(int));  //diziye ilk kez eleman eklenecekse malloc
				}else{
					(p->kayitlikisi)++; 
					p->list=realloc((p->list),(p->kayitlikisi)*sizeof(int));    //ilk de�ilse realloc
				}
				p->list[i]=temp->ogr;
				i++;
			}
			temp=temp->next; 
			}
		}
	}
	}
	free(a);
	fclose(dosya);
	}
	

void OgrenciListeAl(STUDENT **heads){
	STUDENT *tmp=(STUDENT*)malloc(sizeof(STUDENT));
	STUDENT *a=(STUDENT*)malloc(sizeof(STUDENT));
	int size;
	FILE *dosya=fopen("ogrenciler.txt","r");
	if(dosya == NULL){    //dosya var m�
  	//	printf("Dosya bulunamadi...");
  		FILE *dosya=fopen("ogrenciler.txt","w");
 	}else{
 		fseek(dosya,0,SEEK_END);
 		size=ftell(dosya);
	}
	if(size!=0){      //dosya var ama i�i bo� mu
		fseek(dosya,0,SEEK_SET);
		while(!feof(dosya)){
			if(*heads == NULL){
				(*heads)=(STUDENT*)malloc(sizeof(STUDENT));
				(*heads)->next=NULL;
				(*heads)->prev=NULL;
				fscanf(dosya,"%d,%[^,],%[^,],%d,%d\n",&((*heads)->no),(*heads)->ad,(*heads)->soyad,&((*heads)->toplamkredi),&((*heads)->derssayisi));
			}else{
				tmp=(*heads);
				while(tmp->next!=NULL){
					tmp=tmp->next;
				}
				tmp->next=(STUDENT*)malloc(sizeof(STUDENT));
				tmp->next->prev=tmp;
				tmp->next->next=NULL;
				fscanf(dosya,"%d,%[^,],%[^,],%d,%d\n",&(tmp->next->no),tmp->next->ad,tmp->next->soyad,&(tmp->next->toplamkredi),&(tmp->next->derssayisi));
			}
		}
		
	}	
	fclose(dosya);
}
void DersKayitListeAl(KAYIT **headk){   //ders liste almayla ayn� i�lemler
	KAYIT *p=(KAYIT*)malloc(sizeof(KAYIT));
   if(p==NULL)  exit(-1);
	KAYIT *a=(KAYIT*)malloc(sizeof(KAYIT));
 	if(a==NULL) exit(-1);
	int size;
	FILE *dosya=fopen("OgrenciDersKayit.txt","r");
	if(dosya == NULL){
  		//printf("Dosya bulunamadi.");
  		FILE *dosya=fopen("OgrenciDersKayit.txt","w");
 	}else{
 		fseek(dosya,0,SEEK_END);
 		size=ftell(dosya);
	}
	if(size != 0){
		fseek(dosya,0,SEEK_SET);
		while(!feof(dosya)){
 	 	fscanf(dosya,"%d,%[^,],%d,%[^,],%[^\n]\n",&(a->numara),a->derskodu,&(a->ogr),a->tarih,a->bilgi);
		if(*headk == NULL){
			*headk=p;
		}else{
			p->next=(KAYIT*)malloc(sizeof(KAYIT));
			p=p->next;
		}
		p->numara=a->numara;
		strcpy(p->derskodu,a->derskodu);
		p->ogr=a->ogr;
		strcpy(p->tarih,a->tarih);
		strcpy(p->bilgi,a->bilgi);
		p->next=NULL;
		}
	}
	free(a);
	fclose(dosya);
}

void DersEkle(DERS **headd,char tarih[]){
	int var=0;
	DERS *temp=(*headd);
	DERS *ders;
	DERS *d=(DERS*)malloc(sizeof(DERS));
	printf("\n\tDersin kodu : ");
	scanf(" %s",d->kod);	
	ders=DersBul(*headd,(d->kod));   // fonksiyon �a��rark b�yle bir ders var m� diye kontro ediyoruz
	if(ders!=NULL){
		printf("\n\tBu ders zaten ekli...\n");
	}else{	
		while(temp->next !=NULL && strcmp((d->kod),(temp->next->kod))>=0){   //dersi hangi konuma yerle�tirmemiz gerekti�ini buluyoruz
			temp=temp->next;         
		}
		printf("\tDersin adi : ");
		scanf(" %[^\n]s",d->ad);	
		printf("\tDersin kredisi : ");
		scanf("%d",&(d->kredi));
		printf("\tDersin kontenjani : ");		
		scanf("%d",&(d->kontenjan));

		if(temp==(*headd)){   //en ba�a ekleme
			d->next=(*headd);
			(*headd)=d; 
		}else if(temp->next==NULL){  //en sona ekleme
			temp->next=d;
		}else{ 
			d->next=temp->next;  //ortaya ekleme
			temp->next=d;
		}
		printf("\n\tDers basariyla eklendi...\n");
	}
	free(d);
	FILE *dosya=fopen("dersler.txt","w");
	DosyayaKaydet1(dosya,(*headd));
	fclose(dosya);
}
void DersKapat(DERS **headd, KAYIT **headk,STUDENT **heads,char tarih[]){
	char x[10];
	char off[15]="ders kapandi";
	DERS *temp=(*headd);
	DERS *b=(DERS*)malloc(sizeof(DERS));
	STUDENT *ogr;
	int i;
	if(temp != NULL){
	printf("\n\tKapatilacak dersin kodu :");
	scanf("%s",x);
	if((strcmp(x,(temp->kod)))==0){  //kapat�lacak ders linkin en ba��ndaysa
		for(i=0;i<(temp->kayitlikisi);i++){  //dersin ��renci dizisin de eleman varsa
		ogr=OgrenciBul(*heads,(temp->list[i]));  //dersi alan ��rencileri fonksiyon yard�m�yla ��renci linkinde buluyoruz
		(ogr->derssayisi)--; //ders kapand��� i�in ��rencinin ders say�s�n� ve
		(ogr->toplamkredi) = (ogr->toplamkredi) - (temp->kredi);  //kredisini azalt�yoruz
		}
		free(temp->list);  
		b=(*headd)->next;
		free((*headd));
		(*headd)=b;
		printf("\n\tDers basarili bir sekilde kapandi...\n");
	}else{
		while(temp->next!=NULL && strcmp((temp->next->kod),x)!=0){  //dersin konumunu ar�yoruz 
		temp=temp->next;
		}
		if(temp->next == NULL){  //sona kadar geldiysek ders yok demektir
			printf("\n\t%s kodlu ders bulunamadi...\n",x);
		}else{
			for(i=0;i<(temp->next->kayitlikisi);i++){      
			//dersi bulursak yukar�daki i�lemlerin ayn�s�n� yap�yoruz
				ogr=OgrenciBul(*heads,(temp->next->list[i]));
				(ogr->derssayisi)--;
				(ogr->toplamkredi) = (ogr->toplamkredi) - (temp->kredi);
			} 
			free(temp->list); //dersin ��renci listesini bo�alt�yoruz
			b=temp->next;
			temp->next=temp->next->next;		
			free(b);
			b=NULL;
			printf("\n\tDers basarili bir sekilde kapandi...\n");
		}
	}
	}else{
		printf("\n\tDosyada silinecek ders yoktur.Once kayit yapiniz...\n");
	}
	
	FILE *dosya=fopen("dersler.txt","w");
	DosyayaKaydet1(dosya,(*headd));
	fclose(dosya);
	
	FILE *dosya1=fopen("ogrenciler.txt","w");
	DosyayaKaydet2(dosya1,(*heads));
	fclose(dosya1);
	
	KAYIT *temp2=(*headk);
	if(temp2 != NULL){
		while(temp2 != NULL ){
			if((strcmp((temp2->derskodu),x))==0){   //dersi kapatt�ktan sonra o ders kay�t dosyas�nda o derse derse dair bir kay�t 
				strcpy((temp2->bilgi),off);  //varsa durum bilgisini ders kapand� yap�yoruz
				strcpy(temp2->tarih,tarih);	
			}
			temp2=temp2->next;
		}
		FILE *dosya2=fopen("OgrenciDersKayit.txt","w");
		DosyayaKaydet3(dosya2,*headk);
		fclose(dosya2);
	}
	char kod2[20];
	strcpy(kod2,x);
	strcat(kod2, ".txt");  //dersin s�n�f listesi dosyas� e�er olu�turulduysa siliyoruz.
	remove(kod2);
  	free(b);	
}

void OgrenciEkle(STUDENT **heads){
	int sira=0,var=0;
	STUDENT *temp=(*heads);
	STUDENT *ogr;
	STUDENT *a=(STUDENT*)malloc(sizeof(STUDENT));
	printf("\n\tOgrencinin numarasi : ");
	scanf(" %d",&(a->no));
	ogr=OgrenciBul(*heads,(a->no));  //fonksiyon yard�m�yla ��renci var m� diye kontrol ediyoyoruz
	if(ogr!= NULL){
		printf("\n\t%d kodlu ogrenci zaten ekli...\n",(a->no));
	}else{
		while(temp->next!=NULL && a->no >= temp->next->no){
	 		temp=temp->next;
		}
		printf("\tOgrencinin adi : ");
		scanf(" %[^\n]s",a->ad);
		printf("\tOgrencinin soyadi : ");
		scanf("%s",a->soyad); 
		printf("\tOgrencinin ders sayisi : ");
		scanf("%d",&a->derssayisi);
		printf("\tOgrencinin toplam kredisi : ");
		scanf("%d",&a->toplamkredi);
		if((*heads)==NULL){
			(*heads)=a;
			(*heads)->next=NULL;
		}else if(temp==(*heads) && a->no < (*heads)->no){ //ba�a ekleme
		 	a->next=*heads;
		 	(*heads)->prev=a;
		 	*heads=a;
		}else if(temp->next == NULL && a->no > temp->no){  //sona ekleme
			temp->next=a;
			a->prev=temp;
			a->next=NULL;
		}else{
			a->next=temp->next; //ortaya ekleme
			temp->next->prev=a;
			temp->next=a;
			a->prev=temp;
		} 
		 	printf("\n\tOgrenci basariyla eklendi...");
	}

	FILE *dosya=fopen("ogrenciler.txt","w");
	DosyayaKaydet2(dosya,(*heads));
	fclose(dosya);
}
void OgrenciSil(STUDENT **heads,DERS ** headd,KAYIT **headk,char tarih[]){
	int t;
	char birakti[20]="birakti";
	STUDENT *x=(STUDENT*)malloc(sizeof(STUDENT));
	STUDENT *temp=(*heads);
	KAYIT *temp2=*headk;
	DERS *ders;
	if(temp != NULL){
		printf("\n\tKaydi silinecek ogrencinin numarasi : ");
		scanf("%d",&t);
		if(temp->no == t){  //en ba�ta 22011001 numaral� ��renci oldu�unda silmeye �al��t���m�zda bazen uzun s�r�yor nedenini ��zemedim.
		//	printf("\n\tBu islem biraz uzun surebilir...(10 sn civari)");
			while(temp2!=NULL){
				
				if(temp2->ogr == t && strcmp(temp2->bilgi,"kayitli")==0){  // silinen ��rencinin herhangi bir derse kayd� varsa 
						ders=DersBul(*headd,temp2->derskodu);				//kay�t bilgisini "b�rakt� olarak de�i�tiriyoruz
						ListedenSil(&ders,&temp,t);   //listeden silme foNksiyonu ile ��renciyi ald��� derslerin ��renci dizisinden siliyoruz.
						strcpy(temp2->bilgi,birakti);
						strcpy(temp2->tarih,tarih);
				}
				temp2=temp2->next;
			}
		
			x=(*heads)->next;
			x->prev=(*heads);
			free(*heads);
			(*heads)=x;
			printf("\n\tOgrenci basariyla silindi...\n");
		}else{
			while(temp->next!=NULL && temp->next->no != t){
			temp=temp->next;
			}
			if(temp->next == NULL){
				printf("\t%d numarali ogrenci bulunamadi...",t);
			}else{
				while(temp2!=NULL){
					if(temp2->ogr==t && strcmp(temp2->bilgi,"kayitli")==0){
						ders=DersBul(*headd,temp2->derskodu);
						ListedenSil(&ders,&(temp->next),t);
						strcpy(temp2->bilgi,birakti);
						strcpy(temp2->tarih,tarih);	
					}
					temp2=temp2->next;
				}
				x=temp->next;
				temp->next=temp->next->next;	
				free(x);	
				x=NULL;
				printf("\n\tOgrenci basariyla silindi...");
			}
		}
	}else{
		printf("\n\tDosyada silinecek ogrenci yoktur.Once kayit yapiniz...\n");
	}

	FILE *dosya1=fopen("OgrenciDersKayit.txt","w");
	DosyayaKaydet3(dosya1,*headk);
	fclose(dosya1);
	FILE *dosya=fopen("ogrenciler.txt","w");
	DosyayaKaydet2(dosya,(*heads));
	fclose(dosya);
	char no2[50];
	itoa(t, no2, 10);
	strcat(no2,"_DERSPROGRAMI.txt");   
	if(remove(no2)==0){
		printf("\n\t%s adli dosya silinmistir.",no2);
	}
	
}
void OgrenciDersKayit(DERS **headd,STUDENT **heads, KAYIT **headk,int maxders,int maxkredi,char tarih[]){
	char kod[15];
	char bilgi[15]="kayitli";
	int flag=0;
	int no, numara;
	DERS *ders;
	KAYIT *tmp,*prev;
	STUDENT *ogr;
	FILE *dosya,*dosya1;
	int kredi=0,islem=1;
	printf("\n\tDers kaydi yapmak istediginiz ogrencinin numarasini giriniz : ");
	scanf("%d",&no);
	ogr=OgrenciBul(*heads,no);  //��renci var m� kontrol�
	if(ogr==NULL){
		printf("\n\tOgrenci bulunamadi...");
	}else{
		while((ogr->derssayisi < maxders) && islem==1){  //maksimum ders s�n�r� kontrol�
			printf("\tOgrenciyi kaydetmek istediginiz dersin kodunu giriniz : "); 
			scanf("%s",kod);
			ders=DersBul(*headd,kod);  //kay�t yapmak istedi�imiz der var m� kontrol�
			if(ders==NULL){
				printf("\n\tDers bulunamadi...");
			}else if(ogr->toplamkredi + ders->kredi <= maxkredi){  //eklenecek dersle kredi s�n�r� a��l�yor mu
				flag=ListeyeEkle(&ders,&ogr,no);  
				if(flag!=2){  //��renci zaten listenin i�inde bulunuyorsa �a�r�lan fonksiyon 2 return eder yeniden ekleme i�lemi yap�lmaz
					if((*headk)==NULL){  //kay�t dosyas� bo�sa
					(*headk)=(KAYIT*)malloc(sizeof(KAYIT));
					numara=10000;
					(*headk)->numara=numara;
					strcpy((*headk)->derskodu,kod);
					(*headk)->ogr=no;
					strcpy((*headk)->tarih,tarih);
					strcpy((*headk)->bilgi,bilgi);
				}else{
				tmp=*headk;
				if((strcmp((tmp->derskodu),kod)) == 0 && tmp->ogr == no ){   //ogrencinin "ders b�rakt�" veya "sildi" olarak bir kay�t logu varsa 
					strcpy(tmp->bilgi,bilgi);												//o sat�rdaki bilgi ve tarih de�i�tirilir
					strcpy(tmp->tarih,tarih);	
					flag=1;
				}else{
					while(tmp->next!= NULL ){
						if((strcmp((tmp->next->derskodu),kod)) == 0 && tmp->next->ogr == no ){
							strcpy(tmp->next->bilgi,bilgi);	
							strcpy(tmp->tarih,tarih);	
							flag=1;
						}
						tmp=tmp->next;
					}
				}
				if(flag != 1 && tmp->next==NULL){    //��renci ve derse dair herhangi bir kay�t logu yoksa yenisi olu�turulur
					numara=(tmp->numara)+1;
					tmp->next=(KAYIT*)malloc(sizeof(KAYIT));
					tmp=tmp->next;	
					tmp->numara=numara;
					strcpy(tmp->derskodu,kod);
					tmp->ogr=no;
					strcpy((tmp->tarih),tarih);
					strcpy((tmp->bilgi),bilgi);						
				}
			}
			}else{
				printf("\n\tBu ogrenci bu derse zaten kayitli. Yeniden kaydedemezsiniz...");
			}

			}else{
				printf("\n\tMaksimum kredi sinirini asiyorsunuz..."); 
			}
			printf("\n\tSecilen ogrenciye yeniden ders eklemek icin 1, ders kayit islemini tamamlamak icin 2 giriniz : ");
			scanf("%d",&islem);
			printf("\n");
		}
		if((ogr->derssayisi) >= maxders){  //whiledan ogrencinin ders say�s� maksimum dersi ge�ti�i i�in ��kt�ysak
				printf("\n\tMaksimum ders sayisina ulastiniz.Secilen ogrenciye yeni ders ekleyemezsiniz...");
		}
	}
	/*dosya=fopen("dersler.txt","w");
	DosyayaKaydet1(dosya,*headd);
	fclose(dosya);*/
	dosya=fopen("ogrenciler.txt","w");
	DosyayaKaydet2(dosya,*heads);
	fclose(dosya);
	dosya1=fopen("OgrenciDersKayit.txt","w");
	DosyayaKaydet3(dosya1,*headk);
	fclose(dosya1);
}
void ListedenSil(DERS **ders,STUDENT **ogr,int no){
	((*ders)->kayitlikisi)--; //mevcutu 1 azalt�yoruz
	int i=0;
	while(i < ((*ders)->kayitlikisi) && (*ders)->list[i] != no){  //silinecek ��rencinin konumunu buluyoruz
		i++;
	}
	int j;
	for(j=i;j<((*ders)->kayitlikisi);j++){  
		(*ders)->list[i]=(*ders)->list[i+1]; // ��rencileri bir kayd�r�yoruz silinen ��rencinin �st�ne do�ru
	}
	(*ders)->list=realloc(((*ders)->list),(((*ders)->kayitlikisi)*sizeof(int)));  //dizinin boyutunu k���lt�yoruz
	((*ogr)->derssayisi)--;  //ogrencinin der say�s�n� ve kredisini azalt�yoruz
	(*ogr)->toplamkredi -= (*ders)->kredi;
	
}
int ListeyeEkle(DERS **ders,STUDENT **ogr,int no){
	int flag=0; 
	int i =0;
	while(i != ((*ders)->kayitlikisi) && (*ders)->list[i] <= no){  //��renci zaten listedeyse flag 2 yap�p return ediyoruz
		if((*ders)->list[i] == no){
			flag=2;
			return flag;
		}
		i++;  //��rencinin eklenece�i konumu bulduk
	}
	((*ders)->kayitlikisi)++; //mevcutu art�yoruz 
	if((*ders)->kayitlikisi<=(*ders)->kontenjan){ 
		if((*ders)->kayitlikisi == 1){ 
			(*ders)->list=(int*)malloc(((*ders)->kayitlikisi)*sizeof(int)); //ilk kay�tsa malloc
		}else{
			(*ders)->list=realloc(((*ders)->list),(((*ders)->kayitlikisi)*sizeof(int))); //ilk kay�t de�ilse realloc
		}
		int j;
		for(j=(((*ders)->kayitlikisi)-1);j>i;j--){  //t�m ekemanlar� bir geriye kayd�r�yoruz
			(*ders)->list[j]=(*ders)->list[j-1];
		}
		(*ders)->list[i]=no;  //araya ��renciyi yerle�tiriyoruz
		((*ogr)->derssayisi)++;  //��rencinin ders ve kredisini art�r�yoruz
		(*ogr)->toplamkredi += (*ders)->kredi;		
	}else{
		printf("\n\tBu dersin kontenjani dolmustur...");
	}
	return flag;
}

void OgrenciKayitSil(DERS **headd,STUDENT **heads, KAYIT **headk,char tarih[]){
	char off[15]="sildi";
	int no;
	FILE *dosya;
	DERS *ders;
	STUDENT *ogr;
	char kod[15];
	printf("\n\tDersten kaydini silmek istediginiz ogrencinin numarasini giriniz : ");
	scanf("%d",&no);
	ogr=OgrenciBul(*heads,no); //��renci var m�
	if(ogr==NULL){
		printf("\n\tOgrenci bulunamadi...");
	}else{
		printf("\tOgrenciyi kaydetmek istediginiz dersin kodunu giriniz : ");
		scanf("%s",kod);
		ders=DersBul(*headd,kod);  //ders var m�
		if(ders==NULL){
			printf("\n\tDers bulunamadi...");
		}else{
			KAYIT *tmp=*headk;
			if(tmp->ogr == no && strcmp(tmp->derskodu,kod) == 0 ){
				strcpy(tmp->bilgi,off);	
				strcpy(tmp->tarih,tarih);
			}else{
				while(tmp->next->ogr != no && (strcmp((tmp->next->derskodu),kod)) != 0  ){
				tmp=tmp->next;
				}
			}
			if(tmp->next == NULL || (strcmp((tmp->next->bilgi),off))==0){
				printf("\n\t%d numarali ogrenci %s kodlu derse kayitli degildir.",no,kod);
			}else{
				ListedenSil(&ders,&ogr,no); //kayd� ilinen ��renciyi dersin ��renci listesinden siliyoruz
				strcpy(tmp->next->bilgi,off);
				strcpy(tmp->next->tarih,tarih);
				printf("\n\t%d numarali ogrenci %s kodlu dersten kaydi basariyla silinmistir.",no,kod);
			
			
				dosya=fopen("ogrenciler.txt","w");
				DosyayaKaydet2(dosya,*heads);
				fclose(dosya);
				dosya=fopen("OgrenciDersKayit.txt","w");
				DosyayaKaydet3(dosya,*headk);
				fclose(dosya);
			}
		}
	}
}

void SinifListesiOlustur(DERS **headd){
	DERS *temp=*headd;
	FILE *fp;
	int i;
	char kod[15];
	while(temp!=NULL){
		strcpy(kod,temp->kod);  ;//dosya ad�n� olu�turuyoruz
		strcat(kod,".txt");
		fp=fopen(kod,"w");
		if((temp->kayitlikisi)>0){  //derse kay�tl� ki�i varsa diziyi dola��p ��rencileri yazd�r�yoruz
			for(i=0;i<(temp->kayitlikisi);i++){
				fprintf(fp,"%d\n",temp->list[i]);
			}
		}
		fclose(fp);
		temp=temp->next;
	}
}
void SinifListesiYazdir(DERS **headd){
	SinifListesiOlustur(headd);
	char kod[15];
	int no;
	DERS *ders;
	printf("\n\tOgrenci listesini goruntulemek istediginiz dersin kodunu giriniz : ");
	scanf("%s",kod);
	ders=DersBul(*headd,kod); //ders var m� kontrol�
	if(ders != NULL){
		DERS *temp=*headd;
		while(temp!=NULL && (strcmp(temp->kod,kod))!=0){
			temp=temp->next;
		}
		if(temp==NULL){
			printf("\n\tDers bulunamadi...");
		}else if(temp->kayitlikisi != 0){  //dersin mevcudu varsa listeyi yazd�r�yoruz
			printf("\n\t%s kodlu dersin sinif listesi : \n",kod);
			strcpy(kod,temp->kod);   //dosya ismi olu�turma
			strcat(kod,".txt");
			FILE *dosya=fopen(kod,"r");
			while(!feof(dosya)){
				fscanf(dosya,"%d\n",&no);
				printf("\n\t%d\n",no);
			}
			fclose(dosya);
		}else{
			printf("\n\tBu derse kayitli ogrenci bulunmamaktadir...");
		}
	}else{
		printf("\n\t%s kodlu ders bulunmamaktadir",kod);
	}
}

void DersProgrami(DERS *headd,STUDENT *heads){
	DERS *temp=headd;
	int i,flag,x=0,no;
	char dosyaismi[40];
	STUDENT *ogr;
	printf("\n\tDers programini gormek istediginiz ogrencinin numarasini giriniz : ");
	scanf("%d",&no);
	ogr=OgrenciBul(heads,no);  //ogrenci var m�
	
	if(ogr != NULL){
		printf("\n\t%d numarali ogrencinin ders programi :\n");
		itoa(no,dosyaismi,10);   //dosya ismi olu�turma
		strcat(dosyaismi,"_DERSPROGRAMI.txt");
		FILE *dosya=fopen(dosyaismi,"w");
		while(temp!=NULL){  //t�m dersleri geziyoruz
			flag=0;
			for(i=0;i<(temp->kayitlikisi);i++){  //dersi alan ��rencilerin listesini geziyoruz
				if(temp->list[i] == no){  //e�er arad���m�z ��renci varsa flag 1 yap�yoruz
					flag=1;
					x++;
				}
			}
			if(flag==1){  //flag 1 se dersin ad�n� ders program�na ekliyoruz
				fprintf(dosya,"%s\n",temp->kod);
				printf("\n\t%s",temp->kod);
			}
			temp=temp->next;
		}
		fclose(dosya);
		if(x==0){
			printf("\n\tOgrencinin aldigi ders bulunmamaktadir...");
		}
	}else{
		printf("\n\t%d numarali ogrenci bulunmamaktadir.",no);
	}

}

STUDENT *OgrenciBul(STUDENT *heads,int no){  
	STUDENT *temp=heads;
	while(temp != NULL && temp->no != no){
		temp=temp->next;
		//printf("%d",temp->no);
	}
	return temp;
}
DERS *DersBul(DERS *headd,char kod[]){
	DERS *temp=headd;
	while(temp != NULL && strcmp((temp->kod),kod)!=0){
		temp=temp->next;
	}
	return temp;
}
void OgrenciListeYaz(STUDENT *heads){
	STUDENT *p=heads;
	printf("\n\tOgrenci Listesi:\n\n");
	if(p==NULL){
		printf("\n\tSisteme kayitli ogrenci yoktur...");
	}
	while(p!=NULL){
		printf("\t%10d, %10s, %10s, %4d, %4d \n",p->no,p->ad,p->soyad,p->derssayisi,p->toplamkredi);
		p=p->next;
	}
	free(p);
}
void DersListeYaz(DERS *headd){
	DERS *p=headd;
	printf("\n\tDers Listesi:\n\n");
	if(p==NULL){
		printf("\n\tSisteme kayitli ders yoktur...");
	}
	while(p!=NULL){
		printf("\t%10s,  %40s,  %4d,  %4d\n",p->kod,p->ad,p->kredi,p->kontenjan);
		p=p->next;
	}
	free(p);	
}
void OgrenciDersKayitYazdir(KAYIT *headk){
	KAYIT *p=headk;
	printf("\n\tOgrenci Ders Kay�t :\n\n");
	while(p!=NULL){
		printf("\t%d,  %s,  %s,  %s, %s\n",p->numara,p->derskodu,p->ogr,p->tarih,p->bilgi);
		p=p->next;
	}
	free(p);	
}
void DosyayaKaydet1(FILE *dosya,DERS *headd){
	while(headd !=NULL){
		fprintf(dosya,"%s,%s,%d,%d\n",headd->kod,headd->ad,headd->kredi,headd->kontenjan);
		headd=headd->next;
	}
}
void DosyayaKaydet2(FILE *dosya,STUDENT *heads){
	while(heads!=NULL){
		fprintf(dosya,"%d,%s,%s,%d,%d\n",heads->no,heads->ad,heads->soyad,(heads->toplamkredi),(heads->derssayisi));
		heads=heads->next;	
	}
} 
void DosyayaKaydet3(FILE *dosya,KAYIT *headk){
	while(headk !=NULL){
		fprintf(dosya,"%d,%s,%d,%s,%s\n",headk->numara,headk->derskodu,headk->ogr,headk->tarih,headk->bilgi);
		headk=headk->next;
	}
}
void free1(DERS *headd){
	DERS *temp;
		while(headd!=NULL){
		temp=headd;
		headd=headd->next;
		free(temp);
	}
}
void free2(STUDENT *heads){
	STUDENT *temp;
		while(heads!=NULL){
		temp=heads;
		heads=heads->next;
		free(temp);
	}
}
void free3(KAYIT *headk){
	KAYIT *temp;
		while(headk!=NULL){
		temp=headk;
		headk=headk->next;
		free(temp);
	}
}

