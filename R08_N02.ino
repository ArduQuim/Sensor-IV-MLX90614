//Sensor de Temperatura Infravermelho - Modelo: MLX90614

// Incluir as bibliotecas necessárias 
#include <Adafruit_MLX90614.h>// Responsável por receber os dados do sensor e os interpretar
#include <LiquidCrystal_I2C.h>// Gere o display LCD
#include <Wire.h>// Responsavél por gerir a comunicação I2C

Adafruit_MLX90614 mlx = Adafruit_MLX90614();//Recebe os dados e armazena na variável mlx

//Variáveis
double temp_amb;//Define a variável de temperatura ambiente
double temp_obj;//Defina a variável de temperatura do objeto
const int LCD_linhas = 2; // Número de linhas do seu display LCD
const int LCD_colunas = 16; // Número de colunas do seu display LCD
const int numeroPiscadas = 3; // Número de vezes que o dado pisca
// As próximas 3 variáveis descrevem os intervalos de tempo empregados no display LCD e podem ser editados conforme o desejo do usuário
const float LCD_tempoAceso = 2.5; // Tempo, em segundos, em que o dado é exibido
const float LCD_tempoPiscando = 1.5; // Tempo, em segundos, em que o dado permanece piscando
const float LCD_tempoApagado = 0.5; // Intervalo, em segundos, entre a exibição dos dados

LiquidCrystal_I2C lcd(0x27,LCD_colunas,LCD_linhas); // Declara o display como um objeto chamado "lcd"

void setup()// Comandos executados ao inicializar o Arduino 
{
  Serial.begin(9600);//Inicia a comunicação com a serial
  mlx.begin();//Inicia a comunicação com o sensor MLX90614
  lcd.init(); // Inicia o display lcd(x, y), de x colunas e y linhas; Nesse caso, lcd(16,2);  
  
  Serial.println("Display LCD ligado"); // Informa, na porta serial, que o display esta ligado
  Serial.println("Sensor de temperatura MLX90614");//Imprime um tópico "Sensor de temperatura MLX90614" com quebra de linha(ln)
}

void loop()// Comandos que serão executados repetidamente (loop)
{
  temp_amb = mlx.readAmbientTempC();// Recebe o dado de temperatura ambiente, o converte para graus Celsius e armazena na variável "temp_amb"
  temp_obj = mlx.readObjectTempC();// Recebe o dado de temperatura do objeto, o converte para graus Celsius e armazena na variável "temp_obj"
  
if (!mlx.begin()) {// Caso o sensor não funcione corretamente
    Serial.println("Erro ao ler temperatura!");//Imprime uma mensagem de erro
    lcd.backlight();// Liga a luz de fundo do display
    lcd.setCursor(0,0);// Posiciona o cursor na primeira coluna (0) e na primeira linha (0)
    lcd.print("Erro ao ler temp");//Imprime uma mensagem de erro no display LCD
    delay(1000);//Estabelece um intervalo em milisegundos entre as medições (1000 ms = 1 s)
}
    
else{// Caso o sensor funcione corretamente

  lcd.backlight(); // Liga a luz de fundo do display

  // Os próximos comandos imprimem a temperatura na porta serial
  Serial.print("Temp Ambiente = ");
  Serial.print(temp_amb);//Imprime a temperatura ambiente
  Serial.print("°C;");// Imprime o simbolo de grau, a letra “C” e um ponto e vírgula
  Serial.print("   Temp Objeto = ");
  Serial.print(temp_obj);//Imprime a temperatura do objeto na mira do sensor
  Serial.println("°C");// Imprime o simbolo de grau, a letra “C” com quebra de linha(ln)

 // O resultado fica como: 
    /* 
    Temp Ambiente = 25.64°C;   Temp Objeto = 28.23°C
    */ 

    // Os próximos comandos imprimem a temperatura no display LCD
    lcd.setCursor(0,0); // Posiciona o cursor na primeira coluna (0) e na primeira linha (0)
    lcd.print("Amb(");// Imprime o texto “Amb" e abre um parêntese
    lcd.print(char(223)); // Imprime o símbolo de grau
    lcd.print("C)"); // Imprime a letra “C” e fecha o parêntese
    lcd.print("||"); // Adiciona duas linha para separar as leituras
    lcd.print("Obj(");// Imprime o texto “Obj" e abre um parêntese
    lcd.print(char(223)); // Imprime o símbolo de grau
    lcd.print("C)"); // Imprime a letra “C”
}   
     // Apaga e reescreve o valor no display, fazendo o valor piscar
     for (int i = 0; i < numeroPiscadas; i++) {
     lcd.setCursor(0, 1);
     for (int j = 0; j < LCD_colunas; j++) {
     lcd.print(" ");
}
    delay((LCD_tempoPiscando * 1000)/(numeroPiscadas * 2)); // Gera uma pausa entre os processos
    lcd.setCursor(0,1); // Posiciona o cursor na primeira coluna (0) e na segunda linha (1)
    lcd.print(temp_amb); // Imprime o valor da temperatura ambiente coletada
    lcd.setCursor(7,1); // Posiciona o cursor na sétima coluna (7) e na segunda linha (1)
    lcd.print("||");// Adiciona duas linha para separar as leituras
    lcd.setCursor(9,1); // Posiciona o cursor na nona coluna (9) e na segunda linha (1)
    lcd.print(temp_obj); // Imprime o valor da temperatura do objeto apontado
    delay((LCD_tempoPiscando * 1000)/(numeroPiscadas * 2)); // Gera uma pausa entre os processos
}
    delay(LCD_tempoAceso*1000);//Faz com que a luz de fundo permaneça um período acesa(sem piscar)
    lcd.noBacklight(); // Desliga a luz de fundo do display
    delay(LCD_tempoApagado*1000);//Faz com que a luz de fundo permaneça um período apagada

    // O resultado fica como: 
    /* 
    Amb(°C)||Obj(°C)
    28.63  ||32.81
           ou
    Amb(°C)||Obj(°C)
    28.63  ||-02.81
           ou
    Amb(°C)||Obj(°C)
    28.63  ||102.81
           ou
    (Com a temp ambiente abaixo de 0)
     Amb(°C)||Obj(°C)
    -02.63  ||32.81
    */ 
    //Pode-se olhar o led tx na placa do Arduino para confirmar o funcionamento
}
