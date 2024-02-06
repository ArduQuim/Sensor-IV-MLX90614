//Sensor de Temperatura Infravermelho - Modelo: MLX90614

// Incluir a biblioteca necessária 
#include <Adafruit_MLX90614.h>// Responsável por receber os dados do sensor e os interpretar

Adafruit_MLX90614 mlx = Adafruit_MLX90614();//Recebe os dados e armazena na variável mlx

//Variáveis
double temp_amb;//Define a variável de temperatura ambiente
double temp_obj;//Defina a variável de temperatura do objeto

void setup()// Comandos executados ao inicializar o Arduino 
{
  Serial.begin(9600);//Inicia a comunicação com a serial
  Serial.println("Sensor de temperatura MLX90614");//Imprime um tópico "Sensor de temperatura MLX90614" com quebra de linha(ln)
  mlx.begin();//Inicia a comunicação com o sensor MLX90614
}

void loop()// Comandos que serão executados repetidamente (loop)
{
  temp_amb = mlx.readAmbientTempC();// Recebe o dado de temperatura ambiente, o converte para graus Celsius e armazena na variável "temp_amb"
  temp_obj = mlx.readObjectTempC();// Recebe o dado de temperatura do objeto, o converte para graus Celsius e armazena na variável "temp_obj"
  
if (!mlx.begin()) {// Caso o sensor não funcione corretamente
    Serial.println("Erro ao ler temperatura!");//Imprime uma mensagem de erro
    delay(1000);//Estabelece um intervalo em milisegundos entre as medições (1000 ms = 1 s)
    }
    
else{// Caso o sensor funcione corretamente
  //Mostra as informações no Serial Monitor
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
    
  delay(1000);} // Estabelece um intervalo em milisegundos entre as medições (1000 ms = 1 s)
}
//Pode-se olhar o led tx na placa do Arduino para confirmar o funcionamento
