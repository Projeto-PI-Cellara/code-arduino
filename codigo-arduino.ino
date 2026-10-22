// Definição dos pinos e constantes
const int PINO_FOTOVOLTAICO = A0;

// Tensão de referência do Arduino (geralmente 5.0V ou 3.3V)
const float TENSAO_REFERENCIA = 5.0;

// Fator de calibração aproximado:
// Em média, para pequenas células solares, 1 Volt equivale a cerca de 1000 a 2000 Lux sob luz visível direta.
const float FATOR_LUX_POR_VOLT = 1500.0;

// Em média, 1 W/m² equivale a 120 Lux de referência
const float FATOR_LUX_POR_WATTS_M2 = 120;

// Valor padrão da potência da placa em usinas solares
const int POTENCIA_PADRAO = 550;

// Valor padrão de perda de perfomance no mercado, pois a placa nunca chega em 100%
const float PERFORMANCE_RATIO = 0.8;

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