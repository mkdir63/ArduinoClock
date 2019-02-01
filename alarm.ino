#define LED 7

#include <SoftwareSerial.h>

/* questa libreria ci permette di creare delle connessioni seriali 
su Pin digitali, inoltre ci permette di creare più connessioni con 
un baud di 115200.
Proseguiamo con andare a dichiarare la funzione costruttrice e come
parametro gli passiamo 2 valori, che sono rispettivamente RX e il 
TX della nostra comunicazione. */

SoftwareSerial mySerial(52,53);

void setup()
{
  pinMode(key,OUTPUT);   //key per il bluetooth serve per configuralo
  digitalWrite(key,HIGH);//attiva key ma serve solo in fase iniziale
  pinMode(LED, OUTPUT);	 //notifica la ricezione di qualcosa
  
  /* Nel setup andiamo semplicemente a dichiarare dei Pin per la 
  key(o Wakeup) e il btLed. Il Pin key serve generalmente per 
  entrare in AT mode (entrare in AT mode e i comandi) così da 
  poter configurare il nostro modulo bluetooth. Invece il Pin 
  assegnato alla variabile btLed è un Pin che verrà collegato a 
  un led che si accenderà ogni qualvolta che la nostra scheda 
  riceverà delle informazioni tramite bluetooth. 
  Inoltre creiamo una comunicazione seriale a un baud 38400 
  (ma la si può creare a differenti baud), sia per il monitor 
  seriale che per la comunicazione bluetooth. */
  
  //inizializzazione porta seriale definendo il baud
   Serial.begin(38400);
   Serial.println("Type AT commands!");
   // SoftwareSerial "com port"
   mySerial.begin(38400); 
}

void loop()
{
  
  /* Viene fatto un controllo sulla variabile myserial ovvero sul
  bluetooth controllando se è disponibile.
  Se il bluetooth risulta disponibile significa che sta ricevendo
  delle informazioni, di seguito Arduino accende il led sopra ci-
  tato ed entra in un ciclo while per acquisire il valore ricevuto,
  questo succede perché il nostro bluetooth riceve byte per byte 
  l’ informazione, di seguito ricostruisce il comando (o stringa)
  ricevuta facendo una somma di caratteri. */

if (mySerial.available()) 
  { 
    digitalWrite(LED,HIGH);
    while(mySerial.available()){
      //leggo i valori ricevuti dal bluetooth
      command += (char)mySerial.read();
    }
  
  /* Per inviare dei comandi tramite la nostra scheda. Questa if
  viene utilizzata principalmente per mandare comandi AT per con-
  figurare il modulo , ma può essere utilizzata anche per mandare
  dei parametri al nostro dispositivo. */

  // manda linput scritto dall' utente
  if (Serial.available()){
    delay(10); // The DELAY!
    mySerial.write(Serial.read());
  }
  
}
