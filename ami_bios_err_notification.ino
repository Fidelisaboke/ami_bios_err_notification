// AMI BIOS notification simulation(American Megatrends)
// By Fidel Agade Isaboke
/* Reference:
https://habr.com/en/companies/hetmansoftware/articles/548204/
*/

const int buzzer1 = 2;
const int led1 = 3;

/* Function that activates the buzzer and LED
based on beep count */
void notify(int no_of_beeps, int delay_value, int freq = 500){
  for(int i = 0; i < no_of_beeps; i++){
    digitalWrite(led1, HIGH);
    tone(buzzer1, freq, 200);
    delay(delay_value);
    digitalWrite(led1, LOW);
    noTone(buzzer1);
    delay(delay_value);
  }
}

// Short beeps
void notify_short(int no_of_beeps){
  notify(no_of_beeps, 200);
}

// Long beeps
void notify_long(int no_of_beeps){
  notify(no_of_beeps, 500);
}

//Siren
// Check YT Video for how it sounds (Credit: BootLoxes)
// https://youtu.be/8O38fqv4ohI?feature=shared
void notify_siren(int count){
  for(int i = 0; i < count; i++){
    digitalWrite(led1, HIGH);
    tone(buzzer1, 500, 500);
    delay(500);
    digitalWrite(led1, LOW);
    tone(buzzer1, 250, 500);
    delay(500);
  }
}

void setup()
{
  pinMode(buzzer1, OUTPUT);
  pinMode(led1, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  
  if(Serial.available()>0){
    
    // Get the status number - represents number of beeps
    int status_no = Serial.parseInt();
    Serial.print("Status number: ");
    Serial.println(status_no, DEC);
    
    // The fun part - simulation of beeps
    switch(status_no){
      // Short Only
      // 1 Beep
      case 1:
      Serial.println("No errors detected");
      notify_short(1);
      break;
      
      // 2 Beeps
      case 2:
      Serial.println("Parity circuit failure");
      notify_short(2);
      break;
      
      // 3 Beeps
      case 3:
      Serial.println("Base 64 K RAM failure");
      notify_short(3);
      break;
      
      // 4 Beeps
      case 4:
      Serial.println("System timer failure");
      notify_short(4);
      break;
      
      // 5 Beeps
      case 5:
      Serial.println("Process failure - CPU");
      notify_short(5);
      break;
      
      // 6 Beeps
      case 6:
      Serial.println("Keyboard controller A20 Gate Error");
      notify_short(6);
      break;
      
      // n beeps
      // ...
      
      // Long + short
      // (13) 1 long, 3 short - Extended memory failure
      case 13:
      Serial.println("Extended memory failure");
      notify_long(1);
      notify_short(3);
      break;
      
      // (22) Two-tone siren - CPU Fan Speed, Voltage Issue
      case 22:
      Serial.println("CPU Fan Speed, Voltage Issue");
      notify_siren(50);
      break;
      
      default:
      Serial.println("Status unknown");
      break;
    }
  }
}