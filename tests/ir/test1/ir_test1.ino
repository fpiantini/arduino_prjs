void setup() {
  // put your setup code here, to run once:
  pinMode(11,INPUT); // TSOP is connected on the 11th pin  
  Serial.begin(9600);  

}

void loop() {
  // put your main code here, to run repeatedly:
  int remote_val = remote();  
  if(remote_val>0)  
  {  
   Serial.println(remote_val);  
   delay(150); // A remote press will normally generate 3 signal trains. This is to avoid reading duplicates  
  }
}

int remote()  
{  
 int value = 0;  
 int time = pulseIn(11,LOW);  
 if(time>2000) // Checking if the Start Bit has been received. Start Bit Duration is 2.4ms  
 {  
  for(int counter1=0;counter1<12;counter1++) // A loop to receive the next 12 bits  
  {  
   if(pulseIn(11,LOW)>1000) // checking the duration of each pulse, if it is a '1' then we use it in our binary to decimal conversion, '0's can be ignored.  
   {  
    value = value + (1<< counter1);// binary to decimail conversion. 1<< i is nothing but 2 raised to the power of i  
   }  
  }  
 }  
 return value;  
}  
