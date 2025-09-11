#define PIN_LED 13
unsigned int count;
int toggle;

void setup() {
    pinMode(PIN_LED, OUTPUT);        
    Serial.begin(115200);           

    while (!Serial) {
        ; // wait for serial port to connect
    }

    Serial.println("Hello World!");  
    count = 0;
    toggle = 0;
    digitalWrite(PIN_LED, toggle);   
}

void loop() {
    Serial.println("Hello World!");   

    toggle = !toggle;                
    digitalWrite(PIN_LED, toggle);   

    delay(1000);                    
}
