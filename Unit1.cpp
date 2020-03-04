//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
        #define DO_WYGRANEJ 13;
        int x=-7;
        int y=-7;
        int do_wygranej=DO_WYGRANEJ;
        TImage* WskPaleta;


        class CPoziom
        {
        private:
        int poziom;
        TLabel* wsk;
        bool wygrana;


        public:
        CPoziom():poziom(1),wygrana(false){}
        ~CPoziom() {}
        void ustanow_relacje(TLabel* wska) {wsk=wska;}
        void pokaz () {wsk->Caption=poziom;}
        void inkrementuj () {poziom++;}
        int wartosc() {return poziom;}
        bool stan() const {return wygrana;}
        void informuj_stan(bool wyg) {wygrana=wyg;}
        };

        CPoziom POZIOM;


        bool kolizja(TImage* pilka, TImage* box)
        {
         // Lewa strona uderzenie
         if(x>0&&y<0&&pilka->Top+pilka->Height/2<=box->Top+box->Height &&
                pilka->Top+pilka->Height/2>=box->Top&&pilka->Left+pilka->Width>=box->Left &&
                pilka->Left+pilka->Width<=box->Left+19) {x=-x;return true;}
         if(x>0&&y>0&&pilka->Top+pilka->Height/2<=box->Top+box->Height &&
                pilka->Top+pilka->Height/2>=box->Top&&pilka->Left+pilka->Width>=box->Left &&
                pilka->Left+pilka->Width<=box->Left+19) {x=-x;return true;}
         //Góra uderzenie
         if(x>0&&y>0&&pilka->Left>=box->Left-pilka->Width/2 &&
                pilka->Left+pilka->Width/2<=box->Left+box->Width && pilka->Top+pilka->Height>=box->Top &&
                pilka->Top+pilka->Height<=box->Top+19) {y=-y; return true;}
         if(x<0&&y>0&&pilka->Left>=box->Left-pilka->Width/2 &&
                pilka->Left+pilka->Width/2<=box->Left+box->Width && pilka->Top+pilka->Height>=box->Top &&
                pilka->Top+pilka->Height<=box->Top+19) {y=-y; return true;}
         //Prawa strona uderzenie
         if(x<0&&y>0&&pilka->Top+pilka->Height/2<=box->Top+box->Height &&
                pilka->Top+pilka->Height/2>=box->Top&&pilka->Left<=box->Left+box->Width &&
                pilka->Left>=box->Left+box->Width-19) {x=-x; return true;}
         if(x<0&&y<0&&pilka->Top+pilka->Height/2<=box->Top+box->Height &&
                pilka->Top+pilka->Height/2>=box->Top&&pilka->Left<=box->Left+box->Width &&
                pilka->Left>=box->Left+box->Width-19) {x=-x; return true;}
         //Dó³ uderzenie
         if(x>0&&y<0&&pilka->Left>=box->Left-pilka->Width/2 &&
                pilka->Left+pilka->Width/2<=box->Left+box->Width && pilka->Top<=box->Top+box->Height &&
                pilka->Top>=box->Top+box->Height-19) {y=-y; return true;}
         if(x<0&&y<0&&pilka->Left>=box->Left-pilka->Width/2 &&
                pilka->Left+pilka->Width/2<=box->Left+box->Width && pilka->Top<=box->Top+box->Height &&
                pilka->Top>=box->Top+box->Height-19) {y=-y; return true;}
         return false;
        }
        void LosujPolozenie(TImage* wskaznik,TShape* wskTlo)
        {
       srand(time(NULL));
       int width,height;
       height=rand()%wskTlo->Height/2+wskTlo->Height/3;
       width=rand()%wskTlo->Width;
       wskaznik->Left=width;
       wskaznik->Top=height;
       wskaznik->Visible=true;
        }
        void LosujPilke(TShape* tlo,TImage* ball)
        {
       srand(time(NULL));
       int width,height;
       height=rand()%tlo->Height/2+tlo->Height/2;
       width=rand()%tlo->Width;
       ball->Left=width;
       ball->Top=height;
       ball->Visible=true;
        }

        class CDMoc
        {
          private:
          int licznik;
          int CzasTrwaniaMocy;
          TImage* wsk1;
          TImage* wsk2;
          TShape* wskTlo;
          TImage* pilka;
          TImage* paleta;
          bool los;
          bool NastapilaKolizja;
          bool NastapilaKolizja1;
          bool NastapilaKolizja2;

          public:
          void UstanowRelacje(TImage* wskaznik1, TImage* wskaznik2, TShape* wskaznikTlo,TImage* pileczka,TImage* wskp)
           {wsk1=wskaznik1;wsk2=wskaznik2;wskTlo=wskaznikTlo; pilka=pileczka;paleta=wskp;}
          void wylosuj () {
             srand(time(NULL));
             int m=rand()%2;
             switch(m)
             {
             case 0: LosujPolozenie(wsk1,wskTlo); los=true; break;
             case 1: LosujPolozenie(wsk2,wskTlo); los=true; break;
             default: break;
             }
             }
          void inkrementuj() {licznik++;}
          void inkrementuj1() {CzasTrwaniaMocy++;}
          void UstawZero() {CzasTrwaniaMocy=0;}
          int ile_licznik() const {return licznik;}
          int ile_CzasTrwaniaMocy() const {return CzasTrwaniaMocy;}
          bool CzyKolizja() const {return NastapilaKolizja;}
          bool CzyKolizja1() const {return NastapilaKolizja1;}
          bool CzyKolizja2() const {return NastapilaKolizja2;}
          void UstawKolizja() {NastapilaKolizja=0;}
          void UstawKolizja1() {NastapilaKolizja1=0;}
          void UstawKolizja2() {NastapilaKolizja2=0;}
          bool CzyMocObecna() const {return los;}
          void UstawLosFALSZ() {los=false; licznik=0; wsk1->Visible=false;wsk2->Visible=false;}
          bool kolizja()
          {
           if (wsk1->Visible==true && pilka->Left >= wsk1->Left-pilka->Width &&
                pilka->Left <= wsk1->Left+wsk1->Width &&
                pilka->Top >= wsk1->Top-pilka->Height &&
                pilka->Top <= wsk1->Top+wsk1->Height )
           {
                if(x<0)x-=2;
                if(x>0)x+=2;
                if(y>0)y+=2;
                if(y<0)y-=2;
                CzasTrwaniaMocy=0;
                wsk1->Visible=false;
                NastapilaKolizja=true;
                NastapilaKolizja1=true;
                return true;
           }
           else if (wsk2->Visible==true && pilka->Left >= wsk2->Left-pilka->Width &&
                pilka->Left <= wsk2->Left+wsk2->Width &&
                pilka->Top >= wsk2->Top-pilka->Height &&
                pilka->Top <= wsk2->Top+wsk2->Height)
           {
                WskPaleta=paleta;
                WskPaleta->Visible=true;
                CzasTrwaniaMocy=0;
                wsk2->Visible=false;
                NastapilaKolizja=true;
                NastapilaKolizja2=true;
           return true;
           }
           else return false;
          }

        //friend bool LosujPolozenie(TImage* wskaznik);
        };
        CDMoc MOC;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::balltimerTimer(TObject *Sender)
{
        //przypisanie wskaznika jesli nie ma kolizji i ustawienie widocznosci palet
     if(!MOC.CzyKolizja2())
     {
       WskPaleta=paleta;
       paleta->Visible=true;
       paleta1->Visible=false;
     }
     else {paleta->Visible=false;}

     POZIOM.ustanow_relacje(Label2);
     POZIOM.pokaz();
     ball->Left+=x;
     ball->Top+=y;
     // pojawinie siê mocy
     MOC.inkrementuj();
     MOC.UstanowRelacje(moc1,moc2,tlo,ball,paleta1);
     if(MOC.ile_licznik()>=250 && !MOC.CzyMocObecna())
     { MOC.wylosuj();}
     //znikniêcie mocy po zbyt d³ugim czasie
     if(MOC.ile_licznik()>=500)
     {

     MOC.UstawLosFALSZ();
     }
     //tlo->Height-=1;
     if(ball->Left+5<=tlo->Left)x=-x;
     if(ball->Top+5<=tlo->Top) y=-y;
     if(ball->Left+ball->Width+5>=tlo->Width) x=-x;
     //przegrana
     if(ball->Top+ball->Height>=tlo->Height)
     {
      ball->Visible=false;
      balltimer->Enabled=false;
      //int level=POZIOM.wartosc();
      Label1->Caption="Przegrana!";
      Label1->Visible=true;
      Button1->Visible=true;
      Button2->Visible=true;
      POZIOM.informuj_stan(false);
     }
     //Odbicie pi³eczki
     else if  (ball->Left > WskPaleta->Left-ball->Width/2 && ball->Left < WskPaleta->Left+WskPaleta->Width-ball->Width/2 &&
                ball->Top+ball->Height>WskPaleta->Top-5 && ball->Top+ball->Height<WskPaleta->Top+WskPaleta->Height)
     /*else if  (ball->Left > paleta->Left-ball->Width/2 && ball->Left < paleta->Left+paleta->Width-ball->Width/2 &&
                ball->Top+ball->Height>paleta->Top-5 && ball->Top+ball->Height<paleta->Top+paleta->Height)*/
     {
       if(y>0) y*=-1;
     }

     //WYGRANA
     if(do_wygranej<=0) { balltimer->Enabled=false;  Label1->Caption="WYGRANA!";
      Label1->Visible=true;
      Button1->Visible=true;
      Button2->Visible=true;
      POZIOM.informuj_stan(true);
      }

     // kolizja z moc¹
     MOC.kolizja();
     if(MOC.CzyKolizja())
     {
       MOC.inkrementuj1();
       if(MOC.ile_CzasTrwaniaMocy()>=300)
       {
                MOC.UstawZero();
                MOC.UstawKolizja();
                if(MOC.CzyKolizja1())
                {
                if(x<0)x+=2;
                if(x>0)x-=2;
                if(y>0)y-=2;
                if(y<0)y+=2;
                MOC.UstawKolizja1();
                }
                MOC.UstawKolizja2();
                MOC.UstawLosFALSZ();
       }
     }

     //blok 1
     if(Image1->Visible==true && kolizja(ball,Image1))
     {Image1->Visible=false; do_wygranej--; }
     //blok 2
     if(Image2->Visible==true && kolizja(ball,Image2))
     {Image2->Visible=false; do_wygranej--; }
     //blok 3
     if(Image3->Visible==true && kolizja(ball,Image3))
     {Image3->Visible=false; do_wygranej--; }
     //blok 4
     if(Image4->Visible==true && kolizja(ball,Image4))
     {Image4->Visible=false; do_wygranej--; }
     //blok 5
     if(Image5->Visible==true && kolizja(ball,Image5))
     {Image5->Visible=false; do_wygranej--; }
     //blok 6
     if(Image6->Visible==true && kolizja(ball,Image6))
     {Image6->Visible=false; do_wygranej--; }
     //blok 7
     if(Image7->Visible==true && kolizja(ball,Image7))
     {Image7->Visible=false; do_wygranej--; }
     //blok 8
     if(Image8->Visible==true && kolizja(ball,Image8))
     {Image8->Visible=false; do_wygranej--; }
     //blok 9
     if(Image9->Visible==true && kolizja(ball,Image9))
     {Image9->Visible=false; do_wygranej--; }
     //blok 10
     if(Image10->Visible==true && kolizja(ball,Image10))
     {Image10->Visible=false; do_wygranej--; }
     //blok 11
     if(Image11->Visible==true && kolizja(ball,Image11))
     {Image11->Visible=false; do_wygranej--; }
     //blok 12
     if(Image12->Visible==true && kolizja(ball,Image12))
     {Image12->Visible=false; do_wygranej--; }
     //blok 13
     if(Image13->Visible==true && kolizja(ball,Image13))
     {Image13->Visible=false; do_wygranej--; }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LewoTimer(TObject *Sender)
{
        if(WskPaleta->Left-10>tlo->Left)
        {
         WskPaleta->Left-=10;
        }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

        if(Key==VK_LEFT)  Lewo->Enabled=true;
        if(Key==VK_RIGHT) Prawo->Enabled=true;
        if(Key==VK_UP) Gora->Enabled=true;
        if(Key==VK_DOWN) Dol->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PrawoTimer(TObject *Sender)
{
                 if(WskPaleta->Left+WskPaleta->Width+10<tlo->Width)
                {
                WskPaleta->Left+=10;
                }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key==VK_LEFT)  Lewo->Enabled=false;
        if(Key==VK_RIGHT) Prawo->Enabled=false;
        if(Key==VK_UP) Gora->Enabled=false;
        if(Key==VK_DOWN) Dol->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GoraTimer(TObject *Sender)
{
  if(WskPaleta->Top>tlo->Height/2)
  {
  WskPaleta->Top-=10;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DolTimer(TObject *Sender)
{
        if(WskPaleta->Top+WskPaleta->Height<tlo->Height)
        {
         WskPaleta->Top+=10;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
       if(POZIOM.stan())
       {
       POZIOM.inkrementuj();
       tlo->Height-=25;
       // Losowane po³o¿enia pi³ki
       LosujPilke(tlo,ball);
       //Inkrementacja o wartosc 1;
       if(x<0)x-=1;
       if(x>0)x+=1;
       if(y>0)y=-y;
       if(y<0)y-=1;

       WskPaleta=paleta;
       paleta->Visible=true;
       paleta1->Visible=false;
       Label1->Visible=false;
       balltimer->Enabled=true;
       Button1->Visible=false;
       Button2->Visible=false;
       do_wygranej=DO_WYGRANEJ;
       Image1->Visible=true;    Image2->Visible=true;   Image3->Visible=true;
       Image4->Visible=true;    Image5->Visible=true;   Image6->Visible=true;
       Image7->Visible=true;    Image8->Visible=true;   Image9->Visible=true;
       Image10->Visible=true;   Image11->Visible=true;  Image12->Visible=true;
       Image13->Visible=true;
       }
       else
       Application->MessageBox("Aby móc zagrac w nastêpnym poziomie nale¿y przejsc obecny",
				"KOMUNIKAT",MB_YESNO |  MB_ICONSTOP);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
       // Losowane po³o¿enia pi³ki
       LosujPilke(tlo,ball);
       //gwarancja poruszania sie pi³ki w górê
       if(y>0)y=-y;
       Label1->Visible=false;
       balltimer->Enabled=true;
       Button1->Visible=false;
       Button2->Visible=false;
       do_wygranej=DO_WYGRANEJ;
       WskPaleta=paleta;
       paleta->Visible=true;
       paleta1->Visible=false;
       Image1->Visible=true;    Image2->Visible=true;   Image3->Visible=true;
       Image4->Visible=true;    Image5->Visible=true;   Image6->Visible=true;
       Image7->Visible=true;    Image8->Visible=true;   Image9->Visible=true;
       Image10->Visible=true;   Image11->Visible=true;  Image12->Visible=true;
       Image13->Visible=true;
}
//---------------------------------------------------------------------------


