// Definição dos pinos e constantes
const int PINO_LDR = A0;

// Tensão de referência do Arduino (geralmente 5.0V ou 3.3V)
const float TENSAO_REFERENCIA = 5.0;

// Resistência padrão do resistor
const float RESISTOR_FIXO = 10000;

// Fator de calibração aproximado:
// Quando a resistência do LDR for 12000Ω, tem 10 de lux
const float RESISTENCIA_REF = 12000.0;  // resistência do LDR quando há 10 lux
const float LUX_REF = 10.0;   // a luz dessa referência (10 lux)
const float GAMMA = 0.80;

// Em média, 1 W/m² equivale a 120 Lux de referência
const float FATOR_LUX_POR_WATTS_M2 = 120;

// Valor padrão da potência da placa em usinas solares
const int POTENCIA_PADRAO = 550;

// Valor padrão de perda de perfomance no mercado, pois a placa nunca chega em 100%
const float PERFORMANCE_RATIO = 0.8;

void setup() {
  Serial.begin(9600);
  pinMode(PINO_LDR, INPUT);
}

void loop() {
  // 1. Leitura do valor analógico (0 a 1023)
  int valorAnalogico = analogRead(PINO_LDR);

  // 2. Resistência do LDR
  float tensaoFixo = (valorAnalogico * TENSAO_REFERENCIA) / 1023.0; // Captura a tensão do resistor
  float tensaoLdr = TENSAO_REFERENCIA - tensaoFixo; // Subtraindo a tensao de 5V pela tensao do resistor, você tem a tensão do LDR
  float resistenciaLdr = tensaoLdr / (tensaoFixo / RESISTOR_FIXO); // Resistência é igual tensao ÷ corrente. Por isso dividimos a tensão do LDR pela corrente do resistor

  // 3. Estimativa de Lux baseada na resistência do LDR
  float luxEstimado = LUX_REF * pow(RESISTENCIA_REF / resistenciaLdr, 1.0 / GAMMA);

  // 4. Estimativa de Irradiância baseada no Lux estimado
  float irradianciaEstimada = luxEstimado / FATOR_LUX_POR_WATTS_M2;

  // 5. Estimativa de Potência Gerada Ideal baseada na potência padrão e perfomance ratio padrão
  float potenciaEstimada = POTENCIA_PADRAO * (irradianciaEstimada / 1000) * PERFORMANCE_RATIO;

  // Exibição dos dados no Monitor Serial
  Serial.print(irradianciaEstimada);
  Serial.print(";");
  Serial.println(potenciaEstimada);


  delay(2000); // Aguarda 2 segundos para a próxima leitura
}