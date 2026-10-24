// ATENÇÃO! O código considera o circuito com o sensor na alimentação 5V e o resistor fixo no terra

// Definição dos pinos e constantes
const int PINO_LDR = A0;

// Resistência padrão do resistor (ohms)
const float RESISTOR_FIXO = 10000;

// Fator de calibração aproximado:
// Quando a resistência do LDR for 12000Ω, tem 10 de lux
const float RESISTENCIA_REF = 12000;  // resistência do LDR quando há 10 lux
const float LUMINOSIDADE_REF = 10;   // a luz dessa referência (10 lux)
const float GAMA = 0.8; // Valor padrão dos sensores VT90N1

// Em média, 1 W/m² equivale a 120 Lux de referência
const float FATOR_LUX_POR_WATTS_M2 = 120;

// Valor padrão da potência da placa em usinas solares
const float POTENCIA_PADRAO = 550;

// Valor padrão de perda de perfomance no mercado, pois a placa nunca chega em 100%
const float PERFORMANCE_RATIO = 0.8;

void setup() {
  Serial.begin(9600);
  pinMode(PINO_LDR, INPUT);
}

void loop() {
  // 1. Leitura do valor analógico (0 a 1023)
  int valorAnalogico = analogRead(PINO_LDR);
  valorAnalogico = constrain(valorAnalogico, 1, 1022); // Limita os extremos para evitar divisão por 0
  
  // 2. Conversão do valor lido para resistência (ohms)
  float resistenciaLdr = RESISTOR_FIXO * (1023 - valorAnalogico) / valorAnalogico;

  // 3. Estimativa de Lux baseada na resistência do LDR
  float luminosidade = LUMINOSIDADE_REF * pow(RESISTENCIA_REF / resistenciaLdr, 1.0 / GAMA);

  // 4. Estimativa de Irradiância baseada no Lux estimado
  float irradianciaEstimada = luminosidade / FATOR_LUX_POR_WATTS_M2;

  // 5. Estimativa de Potência Gerada Ideal baseada na potência padrão e perfomance ratio padrão
  float potenciaEstimada = POTENCIA_PADRAO * (irradianciaEstimada / 1000) * PERFORMANCE_RATIO;

  // Exibição dos dados no Monitor Serial
  Serial.print(irradianciaEstimada);
  Serial.print(";");
  Serial.println(potenciaEstimada);

  delay(2000); // Aguarda 2 segundos para a próxima leitura
}