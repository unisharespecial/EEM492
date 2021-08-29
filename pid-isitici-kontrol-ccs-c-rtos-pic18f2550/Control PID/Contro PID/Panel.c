#include <18F2550.h>
#device adc=10

#FUSES NOWDT,WDT128,HS,NOPROTECT,NOBROWNOUT,BORV20,PUT,NOCPD,STVREN,NODEBUG,LVP                   
#FUSES NOWRT,NOWRTD,IESO,FCMEN,PBADEN,NOWRTC,NOWRTB,NOEBTR,NOEBTRB,NOCPB,MCLR  
#FUSES LPT1OSC,NOXINST,PLL12,CPUDIV1,USBDIV,NOVREGEN   

#use delay(clock=40000000)
#use rs232(baud=38400,xmit=PIN_A5,rcv=PIN_A4,FORCE_SW)
#use rtos(timer=0,minor_cycle=1ms)
#use fast_io(b)
#include <flex_lcd.c>
#include <string.h>

#define Led_On_Off PIN_C0
#define Led_PID PIN_C1

char BufferLCD1[16];                // Buffer para escribir 1º linea del LCD
char BufferLCD2[16];                // Buffer para escribir 1º linea del LCD
int LengthMsj1, LengthMsj2;         // Largo de los string
int1 Print;                         // Indicador de Borrado de LCD
char String[6];                     // Buffer para almacenar conversion a imprimir
int Tecla,ControlMenu,SubMenu;      // Variables usadas en el control de Menu.-
float Kp,Ti,Td,q0,q1,q2,p0,p00;     // Variables para control PID
float eT,eT_1,eT_2,uT,rT,uT_1;      // Variables para control PID
float TempRef,TempReal;             // Variables para el control realimentado
float ValorMod;                     // Variable para ir guardando valor modificado y posterior reemplazo.
int16 Medida, ControlPWM;           // Medida obtenida del A/D, y variable de setoe de PWM.
int1 Panel;                         // Control de estado de panel, 0= Panel apagado, 1= Panel encendido.-
int1 SistControl;                   // Indica el sistema de control utilizado, 0= On-Off, 1=PID.-
int1 SistControlSelec;              // Indica que sistema de control se ha de seleccionar al presionar Enter.-
int Enter;                          // Variable utilizada para indicar en que menu se ha realizado enter.-
int PosMod;                         // Variable que indica la posicion de la cifra a modificar.
int1 Datalogger;                    // Envio de data por serial activado/desactivado (1/0).


/* **** Definicion de tareas **** */
#task(rate=1ms,max=10us)
void InicializacionTareas();

#task(rate=20ms,max=1ms)
void ControlSistema();

#task(rate=1ms,max=1ms,queue=2)
void VisualizacionLCD();

#task(rate=1ms,max=1ms)
void ImprimirLCD();

#task(rate=100ms,max=1ms)
void ActualizaDisplay(void);

/* **** defincion de funciones **** */
void Incializacion_variables(void);
int TestTeclado(void);
void SeleccionMenu(int Tecla);
void ImpresionMenu(void);
void ControlEnter(void);
void Actualizar_parametros(void);

/* **** Programa principal **** */
void main()
{
lcd_init();
   set_tris_b(0xF0);          
   setup_adc_ports(AN0|VSS_VDD);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   
   Kp=0.8142; Ti=0.761; Td=0.19;    // valores iniciales del control PID.-
   TempRef=200.0;                   // Temperatura inicial deseada.-
   Incializacion_variables();       // incialización de las variables del sistema.-
   
   setup_timer_2(t2_div_by_16,249,1);  //PWM
   setup_ccp1(ccp_pwm);
   
   /*printf(lcd_putc,"Sistema Control\n+ Panel. CCSRTOS ");
   printf("Sistema Control + Panel. CCSRTOS\r\n");
   delay_ms(1000);
   lcd_putc("\f");*/
   set_adc_channel(0);
   enable_interrupts(INT_RB);
   enable_interrupts(GLOBAL);
   
   output_low(Led_On_Off); // led Indicadores de sistema de control.-
   output_high(Led_PID);
   
   rtos_run();
}
//******************************************************************************
/* Interrupcion por cambio de estado RB4-RB7

 Se utiliza esta interrupcion para detectar si se ha pulsado alguna tecla. Al
 activarse la interrupcion se pasa a detectar la tecla pulsada, se envia la
 tecla a la cola de mensajes de una tarea que se encargará de trabajar con la 
 variable. Y se habilta dicha tarea.-
 
*/
#int_RB
void  RB_isr(void) 
{
   Tecla=TestTeclado();                            //Testea la Tecla Pulsada.-
   if(Tecla!=16){                                  //Tecla y no falsa alarma?.-
         rtos_msg_send(VisualizacionLCD,Tecla);    
         rtos_enable(VisualizacionLCD);
   }
}

//******************************************************************************
/* Tarea que se encarga de incializar las demás tareas.
   
 Esta tarea se utiliza dado que el RTOS de CCS no permite comenzar con las tareas
 deshabiltadas.-

*/
void InicializacionTareas(void){
   rtos_disable(ImprimirLCD);
   rtos_disable(VisualizacionLCD);
   rtos_disable(ActualizaDisplay);
   rtos_disable(InicializacionTareas);
}


/* Tarea que se ejecuta cada 20 ms para determinar la señal de control del sistema*/
void ControlSistema(void){
   Medida=read_adc();               // Lectura del valor analogico.-
   TempReal=Medida;                 
   TempReal=(TempReal*500)/1024;   // Se aplica la escala adecuada para obtener
                                    // el valor en ºC.-
   
   eT=TempRef-TempReal;                     //Cálculo error
   
   if(SistControl==1){                      // Control PID?
      uT=q0*eT - q1*eT_1 + q2*eT_2 + uT_1;  //Cálculo de la salida PID (uT=[Volt])
      rT=(uT*1000)/5;                       //duty cycle maximo 1000 -> 5V.-
      /* <<<<< AntiWindup  >>>>>*/
      if (rT>1000){                         //Salida PID si es mayor que el 1000.-
         uT=(uT + 5*p0)*p00;      
         rT=1000;
      }
      if (rT<0){                            //Salida PID si es menor que el 0
         uT=uT*p00;  
         rT=0;
      }
      /* <<<<< Transferencia de salida PID a señal PWM >>>>>*/
      ControlPWM=rT;                            
      set_pwm1_duty(ControlPWM);
      /*  <<<<< Guardar variables para proximo estado >>>>>*/
      eT_2=eT_1;
      eT_1=eT;
      uT_1=uT;
   }else{                                    // Control On-Off.-
      if(eT>0){output_high(PIN_C2);}
      else{output_low(PIN_C2);}
   }
   if(Datalogger==1){
      putc(make8(Medida,1));
      putc(make8(Medida,0));   
   }
}

/* 

 Tarea que se encarga de procesar la tecla presionada, para moverse dentro del
 menu de control y ejecutar el enter.-
 Esta tarea se ejecuta una sola vez al recibir un dato, lo trata y luego se 
 desactiva.
 
*/
void VisualizacionLCD(void){
   if(rtos_msg_poll()>0){
      SeleccionMenu(rtos_msg_read());  //Dependiendo la Tecla recibida se ubica 
                                       //dentro del Menu.-
      if(Panel==1){                    //Si no se a pedido apagar...
         if(Enter==0){                 //Y si no se ha presionado Enter...
            ImpresionMenu();           //Cargamos los buffer segun la posicion 
                                       //en el menu para impresion en LCD.-
         }
         rtos_enable(ImprimirLCD);     //Habilitamos tarea para impresion en LCD.-
      }
   }
   rtos_disable(VisualizacionLCD);
}


/* 
 Esta tarea se encarga de enviar de un caracter a la vez (Por cada ejecucion de
 tarea) al LCD de cada uno de los buffer y luego se desactiva.-
*/
void ImprimirLCD(void){
int j;

   if(Print==1){                 // Borramos display?
      lcd_comand(1);    
      Print=0;
      rtos_yield();              // Se "duerme" hasta el proximo ciclo.-
   }
   for(j=0;j<LengthMsj1;j++){    // Si hay caracteres en Primer linea envia al LCD.-
     lcd_putc(BufferLCD1[j]);
     rtos_yield();               
   }
   if(LengthMsj2!=0){            // Si hay caracteres a imprimir en la segunda linea..
      lcd_gotoxy(1,2);           // ..salta a la siguiente a la linea 2.
      rtos_yield();
   }
   for(j=0;j<LengthMsj2;j++){    // Si hay caracteres en Segunda linea envia al LCD.-
      lcd_putc(BufferLCD2[j]);
      rtos_yield();
   }
   if(PosMod!=0){                // Utilizado para correr el cursor cuando se modifican
                                 // los parametros.-
      lcd_gotoxy(PosMod,1);      // Vuelve cursor para modificar valores.-
      rtos_yield();
   }
   rtos_disable(ImprimirLCD);
}


/*
 Esta tarea se encarga de actualizar el Buffer de impresión del LCD cada 100ms 
 para mostrar temperatura real del sistema.-
*/
void ActualizaDisplay(void){
   if(Panel==1){                          // Evitamos que se ejecute al iniciar
      strcpy(BufferLCD1,"Temp. Real:");
      sprintf(String,"%3.1f",TempReal);
      strcpy(BufferLCD2,String);
      LengthMsj1=strlen(BufferLCD1);
      LengthMsj2=strlen(BufferLCD2); 
      Print=1;                            // Requiere borrar LCD.
      rtos_enable(ImprimirLCD);
   }
}
//******************************************************************************

/* Inicializacion de las variables del sistema */
void Incializacion_variables(void){
   eT_1=0.0; eT_2=0.0; uT_1=0.0; 
   
   q0=Kp*(1+(0.02/Ti)+(Td*50));
   q1=Kp*(1+(Td*100));
   q2=Kp*Td*50;
   p0=0.02/Ti;
   p00=1/(1+p0);
   
   Panel=0;             // Panel apagado.-
   PosMod=0;            // Si es cero no hace nada.-
   Enter=0;             // No se ha presionado Enter.-
   SistControl=1;       // Comienza con sistema de control PID.-
   datalogger=0;        // Datalogger apagado.-
   output_b(0x00);      // Para inicialización Teclado.-
}

/* 
 En caso de modificar alguno de las contantes del control PID se debe actualizar
 las constates de la funcion PID
*/
void Actualizar_parametros(void){
   q0=Kp*(1+(0.02/Ti)+(Td*50));
   q1=Kp*(1+(Td*100));
   q2=Kp*Td*50;
   p0=0.02/Ti;
   p00=1/(1+p0);
}


/* 
 Rutina de testeo de Tecla presionada, devuelve posicion de tecla presionada
 [0 a 16, (16= falsa alarma)]
*/
int TestTeclado(void){
   int i,j,Filas;
   Filas=0x0E;                      //xxxx1110.
   output_b(Filas);
   i=0;
   for(j=0;j<4;j++){
      if(input(PIN_B4)==0){break;}
      i++;
      if(input(PIN_B5)==0){break;}
      i++;
      if(input(PIN_B6)==0){break;}
      i++;
      if(input(PIN_B7)==0){break;}
      i++;
      shift_left(&Filas,1,1);
      output_b(Filas);              //Trasladamos el 0 a siguiente Pin.
   }
   output_b(0x00);                  //Para detectar proxima pulsacion.-
   return(i);
}

/*
 Esta funcion se encarga de actualizar las variables que controlan posicion dentro
 del Menu visualizado en el LCD. Además se encarga de realizar la tarea al pulsar
 Enter.-
                              Menu Principal
 ControlMenu->                      0
 SubMenu->                          0
 -------------------------------------------------------------------------------
                  Datos      Configuraciones      Datalogger
                    10             11                 12
                                    1
 -------------------------------------------------------------------------------
                  Temp.Real | Selec.Control     |   Comenzar
                     20     |      21           |     22               
                     2      |       3           |      4
                  Temp.Ref. | Modificar Temp.Ref|   Terminar
                     23     |       24          |     25
                     2      |       3           |      4
                  Kp        | Modificar Kp      |
                     26     |       27          |
                     2      |       3           |
                  Td        |Modificar Td       |
                     29     |       30          | 
                     2      |       3           |
                  Ti        | Modificar Ti      |
                     32     |       33          |
                     2      |       3           |
*/
void SeleccionMenu(int Tecla){
   if(Tecla==2){           // tecla de encendido de Panel?
      if(Panel==0){        // El panel esta apagado?
         ControlMenu=0;
         SubMenu=0;
         lcd_comand(0x0C); // Encendemos Display.-
         Panel=1;
      }else{
         lcd_comand(0x08); // Papagamos Display.-
         Panel=0;
         Enter=0;
         PosMod=0;
      }
   }else{
   switch(Tecla){
      case 7:                                // Derecha
         if(Enter==0){                       // Si no se ha presionado enter.-
         if(SubMenu==0 | SubMenu==1){
            ControlMenu+=10;
            switch(ControlMenu){
               case 10:
                  SubMenu=1;
               break;
               case 20:
                  Submenu=2;
               break;
               case 21:
                  SubMenu=3;
               break;
               case 22:
                  SubMenu=4;
               break;
            }
         }
         }else{
            switch(Enter){     // Si se a presionado enter modifica posicion del 
                               //cursor en la cifra a modicicar
               case 1:
                  PosMod++;
                  if(PosMod==7){PosMod=6;}
                  if(PosMod==2){PosMod=3;}
               break;
               case 2:
                  PosMod++;
                  if(PosMod==6){PosMod=5;}
                  if(PosMod==4){PosMod=5;}
               break;           
            }
            ControlEnter();
         }
         
      break;
      case 6:                       // Arriba
         if(Enter==0){              // Si no se a presionado enter, nos movemos 
         if(SubMenu!=0){            // dentro del menu.-
            switch(ControlMenu){
               case 10:
                  ControlMenu=12;
               break;
               case 20:
                  ControlMenu=32;
               break;
               case 21:
                  ControlMenu=33;
               break;
               case 22:
                  ControlMenu=25;
               break; 
               default:
                  switch(SubMenu){
                     case 1:
                        ControlMenu--;
                     break;
                     default:
                        ControlMenu-=3;   
                  }
            }            
         }
         }else{                           // En caso que se haya presionado enter
                                          // se pasa a incrementar la variable
                                          // segun la cifra seleccionada, o a
                                          // Seleccionar el tipo de control.
            switch(Enter){
               case 1:
                  switch(PosMod){
                     case 1:
                        ValorMod+=1;
                     break;
                     case 3:
                        ValorMod+=0.1;
                     break;
                     case 4:
                        ValorMod+=0.01;
                     break;
                     case 5:
                        ValorMod+=0.001;
                     break;
                     case 6:
                        ValorMod+=0.0001;
                     break;                  
                  }
               break;
               case 2:
                  switch(PosMod){
                     case 1:
                        ValorMod+=100;
                     break;
                     case 2:
                        ValorMod+=10;
                     break;
                     case 3:
                        ValorMod+=1;
                     break;
                  }
                  if(ValorMod>=1000){ValorMod=999.9;}
               break; 
               case 3:
                  if(SistControlSelec==0){
                     SistControlSelec=1;
                  }else{
                     SistControlSelec=0;
                  }
               break;
            }
            ControlEnter();
         }
      break;
      case 5:                             // Abajo
         if(Enter==0){                    // Si no se ha presionado enter, se
                                          // mueve dentro del menu.-
         if(SubMenu!=0){
            switch(ControlMenu){
               case 12:
                  ControlMenu=10;
               break;
               case 32:
                  ControlMenu=20;
               break;
               case 33:
                  ControlMenu=21;
               break;
               case 25:
                  ControlMenu=22;
               break; 
               default:
                  switch(SubMenu){
                     case 1:
                        ControlMenu++;
                     break;
                     default:
                        ControlMenu+=3;  
                  }
            }            
         }
         }else{                           // En caso que se haya presionado enter
                                          // se pasa a decrementar la variable
                                          // segun la cifra seleccionada, o a
                                          // Seleccionar el tipo de control.
            switch(Enter){
               case 1:
                  switch(PosMod){
                     case 1:
                        ValorMod-=1;
                     break;
                     case 3:
                        ValorMod-=0.1;
                     break;
                     case 4:
                        ValorMod-=0.01;
                     break;
                     case 5:
                        ValorMod-=0.001;
                     break;
                     case 6:
                        ValorMod-=0.0001;
                     break;                  
                  }
               break;
               case 2:
                  switch(PosMod){
                     case 1:
                        ValorMod-=100;
                     break;
                     case 2:
                        ValorMod-=10;
                     break;
                     case 3:
                        ValorMod-=1;
                     break;
                  }
                  if(ValorMod<0){ValorMod=0;}
               break;
               case 3:
                  if(SistControlSelec==0){
                     SistControlSelec=1;
                  }else{
                     SistControlSelec=0;
                  }
               break;
            }
            ControlEnter();
         }
      break;
      case 4:                          // Izquierda
         if(Enter==0){
         switch(SubMenu){
            case 1:
               ControlMenu=0;
               SubMenu=0;
            break;
            case 2:
               ControlMenu=10;
               SubMenu=1;
            break;
            case 3:
               ControlMenu=11;
               SubMenu=1;
            break;
            case 4:
               ControlMenu=12;
               SubMenu=1;
            break;
         }
         }else{
            switch(Enter){
               case 1:
                  PosMod--;
                  if(PosMod==0){PosMod=1;}
                  if(PosMod==2){PosMod=1;}
               break;
               case 2:
                  PosMod--;
                  if(PosMod==0){PosMod=1;}
               break;           
            }
            ControlEnter();
         }
      break;
      case 0:  // Enter
         switch(SubMenu){
            case 2:
               if(Enter==0 & ControlMenu==20){
                  rtos_enable(ActualizaDisplay);
                  Enter=4;
               }
            break;
            case 3:
               if(Enter==0){
                  switch(ControlMenu){
                     case 21:
                        Enter=3;
                        SistControlSelec=0;
                     break;
                     case 24:
                        lcd_comand(0x0D); // Cursor Parpadeando.-
                        Enter=2;
                        PosMod=3;
                        ValorMod=TempRef;
                     break;
                     case 27:
                        ValorMod=Kp;
                        lcd_comand(0x0D); // Cursor Parpadeando.-
                        Enter=1;
                        PosMod=6;
                     break;
                     case 30:
                        ValorMod=Td;
                        lcd_comand(0x0D); // Cursor Parpadeando.-
                        Enter=1;
                        PosMod=6;
                     break;
                     case 33:
                        ValorMod=Ti;
                        lcd_comand(0x0D); // Cursor Parpadeando.-
                        Enter=1;
                        PosMod=6;
                     break;
                  }
               }else{
                  switch(ControlMenu){
                     case 21:
                        if(SistControlSelec==0){
                           SistControl=0;
                           output_high(Led_On_Off);
                           output_low(Led_PID);
                           setup_ccp1(CCP_OFF);
                        }else{
                           SistControl=1;
                           output_low(Led_On_Off);
                           output_high(Led_PID);
                           setup_ccp1(ccp_pwm);          //Módulo CCP a modo PWM
                        }
                     break;
                     case 27:
                        Kp=ValorMod;
                        Actualizar_parametros();
                     break;
                     case 30:
                        Td=ValorMod;
                        Actualizar_parametros();
                     break;
                     case 33:
                        Ti=ValorMod;
                        Actualizar_parametros();
                     break;
                     case 24:
                        TempRef=ValorMod;
                     break;
                  }
                  Enter=0; PosMod=0;
                  lcd_comand(0x0C);
               }
               ControlEnter();
            break;
            case 4:
               switch(ControlMenu){
                  case 22:
                     Datalogger=1;
                  break;
                  case 25:
                     Datalogger=0;
                  break;
               }
            break;
         }
      break;
      case 3:                                   // Escape
         if(Enter==4){
            rtos_disable(ActualizaDisplay);     // Se sale de opcion visualizar 
            Enter=0;                            // temperatura real.-
         }else{
            Enter=0; PosMod=0;                  // Se sale de opcion de modificar
            lcd_comand(0x0C);                   // algun paramentro
         }
      break;
   }
   }
}

/*
 Rutina que se encarga de cargar en los buffer la cadena de string a ser 
 enviados al LCD segun la posicion dentro del menu.
*/
void ImpresionMenu(void){
   switch(ControlMenu){
      case 0:
         strcpy(BufferLCD1,"Menu Principal");
         strcpy(BufferLCD2,"     --->>");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 10:
         strcpy(BufferLCD1,">Datos");
         strcpy(BufferLCD2,"Configuracion");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 11:
         strcpy(BufferLCD1,">Configuracion");
         strcpy(BufferLCD2,"Datalogger");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 12:
         strcpy(BufferLCD1,">Datalogger");
         strcpy(BufferLCD2,"Datos");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 20:
         strcpy(BufferLCD1,"Mostrar");
         strcpy(BufferLCD2,"Temperatura Real");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 23:
         strcpy(BufferLCD1,"Temp. Ref.:");
         sprintf(String,"%3.0f",TempRef);
         strcpy(BufferLCD2,String);
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 26:
         strcpy(BufferLCD1,"Cte. Kp:");
         sprintf(String,"%1.4f",Kp);
         strcpy(BufferLCD2,String);
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 29:
         strcpy(BufferLCD1,"Cte. Td:");
         sprintf(String,"%1.4f",Td);
         strcpy(BufferLCD2,String);
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 32:
         strcpy(BufferLCD1,"Cte. Ti:");
         sprintf(String,"%1.4f",Ti);
         strcpy(BufferLCD2,String);
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 21:
         strcpy(BufferLCD1,"Seleccion de");
         strcpy(BufferLCD2,"Control");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 24:
         strcpy(BufferLCD1,"Modificar");
         strcpy(BufferLCD2,"Temp. Referencia");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 27:
         strcpy(BufferLCD1,"Modificar Cte Kp");
         strcpy(BufferLCD2,"");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 30:
         strcpy(BufferLCD1,"Modificar Cte Td");
         strcpy(BufferLCD2,"");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 33:
         strcpy(BufferLCD1,"Modificar Cte Ti");
         strcpy(BufferLCD2,"");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 22:
         strcpy(BufferLCD1,"Comenzar Logger");
         strcpy(BufferLCD2,"");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 25:
         strcpy(BufferLCD1,"Detener Logger");
         strcpy(BufferLCD2,"");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;   
   }
}


/*
 Rutina que carga los Buffer en el caso de que se haya presionado enter.-
*/
void ControlEnter(void){
   switch(Enter){
      case 1:
         sprintf(String,"%1.4f",ValorMod);
         strcpy(BufferLCD1,String);
         strcpy(BufferLCD2,"");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;
      case 2:
         sprintf(String,"%03.0f",ValorMod);
         strcpy(BufferLCD1,String);
         strcpy(BufferLCD2,"");
         LengthMsj1=strlen(BufferLCD1);
         LengthMsj2=strlen(BufferLCD2); 
         Print=1; // -1 Requiere borrar LCD.
      break;  
      case 3:
         if(SistControlSelec==0){
            strcpy(BufferLCD1,">>Control ON/OFF");
            strcpy(BufferLCD2,"  Control PID");
            LengthMsj1=strlen(BufferLCD1);
            LengthMsj2=strlen(BufferLCD2); 
            Print=1; // -1 Requiere borrar LCD.
         }else{
            strcpy(BufferLCD1,"  Control ON/OFF");
            strcpy(BufferLCD2,">>Control PID");
            LengthMsj1=strlen(BufferLCD1);
            LengthMsj2=strlen(BufferLCD2); 
            Print=1; // -1 Requiere borrar LCD.
         }
      break;
   }
}
