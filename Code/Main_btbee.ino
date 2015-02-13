#include <IRremote.h>
IRsend irsend;
//The durations if raw
unsigned int AC_ON1[51]={
  8500,4150,550,500,600,450,550,500,550,1550,550,500,550,500,550,500,550,1550,600,450,600,450,550,500,550,500,550,500,600,450,550,500,550,1550,550,1550,550,1550,550,1550,550,500,550,1550,550,1550,550,1550,550,500,550};
unsigned int fav1[36]={
  400,300,150,250,200,600,200,400,200,550,200,250,150,300,150,300,200,250,200,250,150,600,150,450,200,750,200,550,200,250,200,400,200,300,150};
unsigned int chUp1[36]={
  500,200,200,250,200,550,250,400,200,550,200,250,200,250,200,250,200,200,250,200,200,600,200,400,200,750,200,250,200,550,200,250,200,250,200};
unsigned int source1[67]={
  4550,4500,600,1650,650,1600,650,1600,650,500,600,500,650,500,600,550,600,500,600,1650,650,1600,650,1600,650,500,600,500,650,500,600,550,600,500,650,1600,650,500,600,500,650,500,600,500,650,500,600,500,600,550,600,550,600,1650,600,1650,600,1650,600,1650,650,1600,600,1650,650,1600,650};
unsigned int centre1[67]={
  4550,4500,600,1650,600,1650,650,1600,650,500,600,500,600,550,600,500,650,500,650,1600,650,1600,650,1600,650,500,600,500,650,500,600,550,600,500,650,500,600,500,600,550,600,1650,600,550,600,1650,600,1650,600,500,650,1600,600,1650,650,1650,600,500,650,1600,600,550,600,500,600,1700,600};
unsigned int chDown1[35]={
  450,250,200,200,200,600,150,450,200,600,200,200,200,250,200,250,200,250,200,550,200,600,150,450,150,800,150,300,200,550,200,250,150,450,200};
int q[16];
int pop=15; //sets population limit     
boolean a=0;// light
boolean b=0;// fan   1
boolean c=0;// fan   2
boolean d=0; //TV
boolean e=0,f=0;

//progmem

void chDown(){
  for(int i = 0; i < 5; i++) {
    irsend.sendRaw(chDown1,36,38);
    delay(20);
  }
}

void fadeDown()
{
  irsend.sendNEC(0x10EF38C7, 32);
}


void fav()
{
  for (int i = 0; i < 5; i++) {
    irsend.sendRaw(fav1,35,38);
    delay(20);
  }
}
void centre()
{
  irsend.sendRaw(centre1,67,38);
  delay(100);
  irsend.sendRaw(centre1,67,38);
}

void mute()
{
  irsend.sendNEC(0x10EF58A7, 32);
}
void source()
{
  irsend.sendRaw(source1,67,38);
  delay(100);
  irsend.sendRaw(source1,67,38);
}

void chUp()
{
  for (int i = 0; i < 5; i++)
  {
    irsend.sendRaw(chUp1,36,38);
    delay(20);
  }
}


void volDown()
{ 
  irsend.sendNEC(0x10EFA857, 32); // Philips Volume Up
}

void reduceBass()
{
  irsend.sendNEC(0x10EFE817, 32); //Philips reduce bass
}
void volUp()
{
  irsend.sendNEC(0x10EF28D7, 32); // Philips Volume Up
}
void ACPower()
{
  for (int i = 0; i <2; i++) {
    irsend.sendRaw(AC_ON1,51,38);
    delay(500);
  }
}




void setVol()
{
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(0x10EF00FF, 32); //Philips '1' code
    delay(40);
  }
  for (int i = 0; i < 6; i++) {
    reduceBass();
    delay(200);
  }
  for(int i=0;i<10;i++)
  {
    volUp();
    delay(200);
  }
}

















void setup()  
{ 
  Serial.begin(9600);
  pinMode(15,OUTPUT);//LIGHT
  pinMode(16,OUTPUT);//FAN1
  pinMode(17,OUTPUT);//FAN2
  pinMode(18,OUTPUT);//TV
}  


void loop()  
{  
  if(Serial.available())  
  {  
    int  val = Serial.read();
    Serial.println(val);

    if(val==65)//A LIGHT
    {
      if(a==0)
      {
        digitalWrite(15,HIGH);
        a=1;
      }
      else{
        digitalWrite(15,LOW);
        a=0;
      }
    }
    else if(val==66)//B FAN
    {
      if(b==0)
      {
        digitalWrite(16,HIGH);
        b=1;
      }
      else{
        digitalWrite(16,LOW);
        b=0;
      }
    }
    else if(val==67) //C FAN2
    {
      if (c==0){
        digitalWrite(17,HIGH);
        c=1;
      }
      else
      {
        digitalWrite(17,LOW);
        c=0;
      }
    }

    else if(val==68) //D TV
    {
      if(d==0){
        digitalWrite(18,HIGH);
        d=1;
      }
      else{
        digitalWrite(18,LOW);
        d=0;
      }
    }

    else if(val==70) //FAV
    {
      fav();

    }

    else if(val==72) // H cycle AV modes
    {
      source();
      delay(700);
      source();
      delay(500);
      centre();
    }




    else if(val==77) //Movie MODE - M
    {
      digitalWrite(18,HIGH);
      delay(2000);
      digitalWrite(15,LOW);
      delay(2000);
      digitalWrite(16,LOW);
      delay(2000);
      digitalWrite(17,LOW);
      a=0;
      b=0;
      c=0;
      d=1;
      delay(500);
      setVol();
      delay(2000);
      for(short int i=0;i<2;i++)
      {
        source();
        delay(800);
      }
      centre();

    }
    else if(val==83) //Sleep or OFF -S
    {

      digitalWrite(15,LOW);
      delay(1000);
      digitalWrite(16,LOW);
      delay(1000);
      digitalWrite(17,LOW);
      delay(1000);
      digitalWrite(18,LOW);
      a=0;
      b=0;
      c=0;
      d=0;

    } 

    else if(val==84) //TV MODE -T
    {
      a=1;
      d=1;
      digitalWrite(18,HIGH);
      delay(6000);
      digitalWrite(15,HIGH);
      delay(10000);
      setVol();
      delay(5000);
      for(short int i=0;i<4;i++)
      {
        source();
        delay(800);
      }
      delay(2000);
      centre();
      delay(13000);
      fav();
      delay(1000);
      for(short int i=0;i<13;i++)
      {
        chUp();
        delay(3500);
      }
    }


    else if(val==78) //Normal MODE -N
    {
      a=1;
      b=1;
      c=1;
      d=0;
      digitalWrite(15,HIGH);
      delay(1000);
      digitalWrite(16,HIGH);
      delay(1000);
      digitalWrite(17,HIGH);
      delay(1000);
      digitalWrite(18,LOW);
    }
    else if(val==82) // R MODE 
    {
      ACPower();
    }

    else if(val==85) //U chUp
    {
      chUp();

    }
    else if(val==86) //V chDown
    {
      chDown();
    }
    else if(val==90) // Z fad reverse
    {
      for(int j=0;j<5;j++){
        fadeDown();
        delay(400);
      }
    }
    else if(val==88) //X reset Audio
    {
      setVol();
    }
    else if (val>31)
    {
      for(int i=0;i<pop;i++)
        q[i]=q[i+1];

      q[15]=val; //write the unrecognised letter to the end of the queue  eg {0,0,0,l,i,g,h,t,0,0,o,n}






      if((q[11]==108) && (q[12]==105) && (q[13]==103) && (q[14]==104) && (q[15]==116)) //light
      {
        if(a==0)
        {
          digitalWrite(15,HIGH);
          a=1;
        }
      }


      if((q[11]==113) && q[12]==117 && q[13]==105 && q[14]==101 && q[15]==116)   //quiet   
      {
        mute();
        q[16]=(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
      }
      if((q[13]==102) && (q[14]==97) && (q[15]==110)) //fan
      {
        if(b==0)
        {
          digitalWrite(16,HIGH);
          delay(300);
          digitalWrite(17,HIGH);
          b=1;
          c=1;

        }
      }

      if((q[14]==116) && (q[15]==118)) //tv
      {
        if(d==0){
          digitalWrite(18,HIGH);
          d=1;
        }
      }

      if((q[14]==118) &&(q[15]==117))
      {
        volUp();
      }

      if((q[14]==118) && (q[15]==100))
      {
        volDown();
      }

      if((q[12]==99) && (q[13]==111) && (q[14]==111) && (q[15]==108)) //cool
      {
        ACPower();
      }


      if(((q[13])==97) && (q[14]==32) && (q[15]==99)) // a c
      {
        ACPower();
      }



      if((q[11]==115) && (q[12]==108) && (q[13]==101) && (q[14]==101) && (q[15]==112)) //sleep
      {
        digitalWrite(15,LOW);
        delay(600);
        digitalWrite(16,LOW);
        delay(600);
        digitalWrite(17,LOW);
        delay(600);
        digitalWrite(18,LOW);
        a=0;
        b=0;
        c=0;
        d=0;

      }



      if((q[11]== 97 )&& (q[12]==117) && (q[13]==100) && (q[14]==105) && (q[15]==111))
      {
        setVol();
      }  

      if((q[11]== 115 )&& (q[12]==111) && (q[13]==117) && (q[14]==110) && (q[15]==100))
      {
        setVol();
      }

    } 

  }
}



