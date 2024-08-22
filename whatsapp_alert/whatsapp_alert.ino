#include<WiFi.h>
#include<HTTPClient.h>

int echopin= 22;//input
int trigerpin=23;//output
int a = 15;

HTTPClient http;

void setup() {
  Serial.begin(9600);
  
  pinMode(echopin,INPUT);
  pinMode(trigerpin,OUTPUT);
  pinMode(a,OUTPUT);
  
  connectToWiFi();

}

void loop() {

  water();
}


String water()
{
  // put your main code here, to run repeatedly:
  long distance;
  long duration;
  digitalWrite(trigerpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigerpin,HIGH);
  delayMicroseconds(10);
   digitalWrite(trigerpin,LOW);
  duration=pulseIn(echopin,HIGH);
  distance= duration*0.034/2;                           //(duration/2)/29.1;  //duration*0.034/2

    Serial.print("distance ");
    Serial.println(String(distance)+ "cm");
    
   int v = 100-((100/15)*distance);
   Serial.println("Percentage: "+String(v)+" %");
   send_data(String(v));

   if (distance<4)
      digitalWrite(a,0);
   else if(distance>11)
      digitalWrite(a,1);
    else
       Serial.print("");  
    
    delay(50);


}

void send_data(String y)
{
//  https://blynk.cloud/external/api/update?token=IX6ng7gfTfq1ZQ-qoY0MpoP8xDId_t_O&v2=19
  String key = "IX6ng7gfTfq1ZQ-qoY0MpoP8xDId_t_O";
  String api = "https://blynk.cloud/external/api/update?token="+key+"&v3=";
//  String x = ntp_time();
  
  String newapi = api+String(y);
  http.begin(newapi); // calling the api
  int httpCode = http.GET();
  Serial.println("HTTPCODE: "+String(httpCode));
  

}

//*******connect to the WiFi*******
void connectToWiFi(){

    String ssid ="LIMITED2";
    String password = "123.ILUV";
    WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
    delay(1000);
    WiFi.mode(WIFI_STA);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);


    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("Connected");
    
    
    
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //IP address assigned to your ESP
    
    delay(1000);
}