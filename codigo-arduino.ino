// Definição dos pinos e constantes
const int PINO_FOTOVOLTAICO = A0;

// Tensão de referência do Arduino (geralmente 5.0V ou 3.3V)
const float TENSAO_REFERENCIA = 5.0;

// Fator de calibração aproximado:
// Em média, para pequenas células solares, 1 Volt equivale a cerca de 1000 a 2000 Lux sob luz visível direta.
const float FATOR_LUX_POR_VOLT = 1500.0;

void setup() {
  Serial.begin(9600);
  pinMode(PINO_FOTOVOLTAICO, INPUT);
  
}

void loop() {
  // 1. Leitura do valor analógico (0 a 1023)
  int valorAnalogico = analogRead(PINO_FOTOVOLTAICO);

  // 2. Conversão do valor lido para Tensão (Volts)
  float tensaoGerada = (valorAnalogico * TENSAO_REFERENCIA) / 1023.0;

  // 3. Estimativa de Lux baseada na tensão gerada
  float luxEstimado = tensaoGerada * FATOR_LUX_POR_VOLT;

  // Exibição dos dados no Monitor Serial

  Serial.println(luxEstimado);
 

  delay(2000); // Aguarda 2 segundos para a próxima leitura
}