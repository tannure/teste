int voltas=0;//estamos contando o dobro de voltas 
int limetehorario=160;//valor a ser definido pelo usuario 
int limeteantihorario=320;//valor deste é a soma do de horario com o de anti horario
bool ligado=true;
int padrao=0;
int salvapadrao;
int pos = 0; // variable to store the servo position

#include <Servo.h>
 
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int verifica();

int contavoltas(int normal);

void setup() 
{
  // put your setup code here, to run once:
 pinMode(2, OUTPUT); // uso este pino para acionar o buzzer
 digitalWrite(2, LOW);

 pinMode(3, INPUT); // leio da tensão no receptor IR
 
 myservo.attach(9);  // attaches the servo on pin 9 to the servo object
 
 Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  if (voltas<limetehorario){
  if (pos==0){
  pos=myservo.read();
  }
  myservo.write(pos);// tell servo to go to position in variable 'pos'
  pos++;                    
  ligado=digitalRead(3);
  if (digitalRead(3) == LOW)
    digitalWrite(2, LOW);
  else if (digitalRead(3) == HIGH){
    digitalWrite(2, HIGH);
    salvapadrao=padrao;
    padrao=contavoltas(padrao);
    Serial.println(padrao);
    if (padrao!=0)voltas++; 
    else padrao=salvapadrao; 
  }
   Serial.println(digitalRead(3));
   Serial.println("voltas");
   Serial.println(voltas); 
   //Serial.println("posicao");
   //Serial.println(pos); 
   if(pos==360){
    pos=0;
    delay(10);
   }
  delay(10);
}

else if(limeteantihorario>voltas){
  //roda para o lado oposto ou encerra o eletrodo vamos cv sobre isso 
  if (voltas==limetehorario){
    myservo.write(90);
  }
  if (pos==360){
  pos=myservo.read();
  }
  myservo.write(pos);// tell servo to go to position in variable 'pos'
  pos--;       
  ligado=digitalRead(3);
  if (digitalRead(3) == LOW)
    digitalWrite(2, LOW);
  else if (digitalRead(3) == HIGH){
    digitalWrite(2, HIGH);
    salvapadrao=padrao;
    padrao=contavoltas(padrao);
    Serial.println(padrao);
    if (padrao!=0)voltas++; 
    else padrao=salvapadrao; 
  }
  Serial.println(digitalRead(3));
  Serial.println("voltas");
  Serial.println(voltas); 
   //Serial.println("posicao");
   //Serial.println(pos); 
  if(pos==0){
    pos=360;
    delay(10);
  }
  delay(10); 
}
else if(limeteantihorario==voltas){
  myservo.write(90);
}
}

int contavoltas (int normal){//so esperar o sensor voltar ao normal
   int cont=0;
   int teste=0;
   //cont=normal;
   //if (padrao == 0){
    while(teste==0){
    while(ligado!=0){
      cont++;
      ligado=digitalRead(3);
      Serial.println(ligado);
      delay(10);
    }
    teste=verifica();
    }
    return cont;
  }

int verifica (){
  int cont2=0;
  Serial.println("verificaaaa");
  for(cont2=0;cont2<5;cont2){
      cont2++;
      ligado=digitalRead(3);     
      Serial.println(ligado);
      if (ligado!=0){
        return 0;
      }
      delay(10);
  }
  return 1;
}

