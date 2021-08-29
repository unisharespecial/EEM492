/******************************************************
      PIC16F877 ile Tuþ Takýmý Uygulamasý-2 (74C922 Ýle)
*******************************************************/
#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk                 // dosyasý tanýtýlýyor.
// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.
#use fast_io(b) //Port yönlendirme komutlarý B portu için geçerli
#use fast_io(c) //Port yönlendirme komutlarý C portu için geçerli

#byte   portc=0x07   // C portu "portc" ismine eþitleniyor.

char const keys[] ={1,2,3,0,   // Gelen bilgilere göre gösterilmesi
                    4,5,6,0,    // istenen karakterler
                    7,8,9,0,
                    0xF,0,0xF,0 };

//*********** Dýþ Kesme Fonksiyonu Tanýmlanýyor ********
#int_ext            // Dýþ kesme fonksiyonu
void dis_kesme ()
{
   portc=keys[portc>>4];  // C portuna C portunun okunan yüksek deðerlikli 4 biti aktarýlýyor
}


//********** ANA PROGRAM FONKSÝYONU*******
void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý

   set_tris_b(0x01);   // B portu komple çýkýþ
   set_tris_c(0xF0);   // C portunun Yüksek deðerlikli 4 bit çýkýþ, düþük deðerlikli 4 bit giriþ

   ext_int_edge(L_TO_H);  // INT_EXT dýþ kesmesinin yükselen kenarda aktif olacaðýný belirtir

   enable_interrupts(INT_EXT);  // Dýþ kesme aktif
   enable_interrupts(GLOBAL);   // Aktif edilen kesmelere izin ver

   portc=0;  // Baþlangýçta C portu çýkýþý sýfýrlanýyor

   while(1);  // Sonsuz döngü
}

