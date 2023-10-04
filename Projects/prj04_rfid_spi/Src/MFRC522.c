/**************************************************************************/
/*!

  @file    MFRC522.c
  @author  Bjarte Johansen
  @licence ljos.mit-license.org

  SPI Driver for MFRC522 NFC/13.56 RFID Transceiver.

  Based on code by Dr.Leong ( WWW.B2CQSHOP.COM ) and
  Miguel Balboa (https://github.com/miguelbalboa/rfid).

 */
/**************************************************************************/


#include "MFRC522.h"


MFRC522_SPI_Config_t mfrc522_spi_config = {
  .cs = {
    .port = GPIOB,
    .pin = GPIO_PIN_12
  },
  .mosi = {
    .port = GPIOC,
    .pin = GPIO_PIN_1
  },
  .miso = {
    .port = GPIOC,
    .pin = GPIO_PIN_2
  },
  .clk = {
    .port = GPIOB,
    .pin = GPIO_PIN_10
  }
};

extern SPI_HandleTypeDef hspi2;

// int _reset;


void MFRC522_SPI_PinsConfig() {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();


    /**SPI2 GPIO Configuration
    PC1     ------> SPI2_MOSI
    PC2     ------> SPI2_MISO
    PB10     ------> SPI2_SCK
    PB12     ------> SPI2_NSS
    */
    GPIO_InitStruct.Pin = mfrc522_spi_config.mosi.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_SPI2;
    HAL_GPIO_Init(mfrc522_spi_config.mosi.port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = mfrc522_spi_config.miso.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(mfrc522_spi_config.miso.port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = mfrc522_spi_config.clk.pin;//GPIO_PIN_10|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(mfrc522_spi_config.clk.port, &GPIO_InitStruct);
}


void MFRC522_SPI_Init()
{

  GPIO_InitTypeDef gpio_cs = {
      .Pin = mfrc522_spi_config.cs.pin,
      .Mode = GPIO_MODE_OUTPUT_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_HIGH,
      .Alternate = 0};

  HAL_GPIO_Init(mfrc522_spi_config.cs.port, &gpio_cs);

  hspi2 = (SPI_HandleTypeDef) {
    .Instance = SPI2,
    .Init = {
      .Mode = SPI_MODE_MASTER,
      .Direction = SPI_DIRECTION_2LINES,
      .DataSize = SPI_DATASIZE_8BIT,
      .CLKPolarity = SPI_POLARITY_LOW,
      .CLKPhase = SPI_PHASE_2EDGE,
      .NSS = SPI_NSS_HARD_OUTPUT,
      .BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128,
      .FirstBit = SPI_FIRSTBIT_MSB,
      .TIMode = SPI_TIMODE_DISABLE,
      .CRCCalculation = SPI_CRCCALCULATION_DISABLE,
      .CRCPolynomial = 10
    }
  };

  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  
}

HAL_StatusTypeDef MFRC522_SPI_TransmitReceive(byte *pTxData, byte *pRxData, uint32_t Timeout)
{
  HAL_StatusTypeDef status;
  
  status = HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)pTxData, (uint8_t *)pRxData, 1, Timeout);
  
  return status;
}

/**************************************************************************/
/*!

  @brief Instantiates a new MFRC522 class.

  @param sad    SPI chip select pin (CS/SS/SSEL)
  @param reset  Not reset and power-down pin.

 */
/**************************************************************************/
void MFRC522_init() {
    MFRC522_SPI_Init();
}

/**************************************************************************/
/*!

  @brief   Writes value to a register.

  @param   addr  The address a register.
  @param   val   The value to write to a register.

 */
/**************************************************************************/
void MFRC522_writeToRegister(byte addr, byte val) {

    byte frame1_tx = (addr<<1)&0x7E;
    byte frame_rx = 0;

    HAL_GPIO_WritePin(mfrc522_spi_config.cs.port, mfrc522_spi_config.cs.pin, GPIO_PIN_RESET);
    MFRC522_SPI_TransmitReceive(&frame1_tx, &frame_rx, MFRC522_SPI_TIMEOUT_MS);

    MFRC522_SPI_TransmitReceive(&val, &frame_rx, MFRC522_SPI_TIMEOUT_MS);

    HAL_GPIO_WritePin(mfrc522_spi_config.cs.port, mfrc522_spi_config.cs.pin, GPIO_PIN_SET);
}

/**************************************************************************/
/*!

  @brief   Reads the value at a register.

  @param   addr  The address a register.

  @returns The byte at the register.

 */
/**************************************************************************/
byte MFRC522_readFromRegister(byte addr) {
  byte frame1_tx = ((addr<<1)&0x7E) | 0x80;
  byte frame_rx = 0;

  HAL_GPIO_WritePin(mfrc522_spi_config.cs.port, mfrc522_spi_config.cs.pin, GPIO_PIN_RESET);
  MFRC522_SPI_TransmitReceive(&frame1_tx, &frame_rx, MFRC522_SPI_TIMEOUT_MS);
  frame1_tx = 0;
  MFRC522_SPI_TransmitReceive(&frame1_tx, &frame_rx, MFRC522_SPI_TIMEOUT_MS);
  HAL_GPIO_WritePin(mfrc522_spi_config.cs.port, mfrc522_spi_config.cs.pin, GPIO_PIN_SET);
  return frame_rx;
}

/**************************************************************************/
/*!

  @brief   Adds a bitmask to a register.

  @param   addr   The address a register.
  @param   mask  The mask to update the register with.

 */
/**************************************************************************/
void MFRC522_setBitMask(byte addr, byte mask) {
  byte current;
  current = MFRC522_readFromRegister(addr);
  MFRC522_writeToRegister(addr, current | mask);
}

/**************************************************************************/
/*!

  @brief   Removes a bitmask from the register.

  @param   reg   The address a register.
  @param   mask  The mask to update the register with.

 */
/**************************************************************************/
void MFRC522_clearBitMask(byte addr, byte mask) {
  byte current;
  current = MFRC522_readFromRegister(addr);
  MFRC522_writeToRegister(addr, current & (~mask));
}

/**************************************************************************/
/*!

  @brief   Does the setup for the MFRC522.

 */
/**************************************************************************/
void MFRC522_begin() {

  MFRC522_reset();

  //Timer: TPrescaler*TreloadVal/6.78MHz = 24ms
  MFRC522_writeToRegister(TModeReg, 0x8D);       // Tauto=1; f(Timer) = 6.78MHz/TPreScaler
  MFRC522_writeToRegister(TPrescalerReg, 0x3E);  // TModeReg[3..0] + TPrescalerReg
  MFRC522_writeToRegister(TReloadRegL, 30);
  MFRC522_writeToRegister(TReloadRegH, 0);

  MFRC522_writeToRegister(TxAutoReg, 0x40);      // 100%ASK
  MFRC522_writeToRegister(ModeReg, 0x3D);        // CRC initial value 0x6363

  MFRC522_setBitMask(TxControlReg, 0x03);        // Turn antenna on.
}

/**************************************************************************/
/*!

  @brief   Sends a SOFTRESET command to the MFRC522 chip.

 */
/**************************************************************************/
void MFRC522_reset() {
  MFRC522_writeToRegister(CommandReg, MFRC522_SOFTRESET);
}

/**************************************************************************/
/*!

  @brief   Checks the firmware version of the chip.

  @returns The firmware version of the MFRC522 chip.

 */
/**************************************************************************/
byte MFRC522_getFirmwareVersion() {
  byte response;
  response = MFRC522_readFromRegister(VersionReg);
  return response;
}

/**************************************************************************/
/*!

  @brief   Runs the digital self test.

  @returns True if the self test passes, false otherwise.

 */
/**************************************************************************/
boolean MFRC522_digitalSelfTestPass() {
  int i;
  byte n;

  byte selfTestResultV1[] = {0x00, 0xC6, 0x37, 0xD5, 0x32, 0xB7, 0x57, 0x5C,
                          0xC2, 0xD8, 0x7C, 0x4D, 0xD9, 0x70, 0xC7, 0x73,
                          0x10, 0xE6, 0xD2, 0xAA, 0x5E, 0xA1, 0x3E, 0x5A,
                          0x14, 0xAF, 0x30, 0x61, 0xC9, 0x70, 0xDB, 0x2E,
                          0x64, 0x22, 0x72, 0xB5, 0xBD, 0x65, 0xF4, 0xEC,
                          0x22, 0xBC, 0xD3, 0x72, 0x35, 0xCD, 0xAA, 0x41,
                          0x1F, 0xA7, 0xF3, 0x53, 0x14, 0xDE, 0x7E, 0x02,
                          0xD9, 0x0F, 0xB5, 0x5E, 0x25, 0x1D, 0x29, 0x79};
  byte selfTestResultV2[] = {0x00, 0xEB, 0x66, 0xBA, 0x57, 0xBF, 0x23, 0x95,
                          0xD0, 0xE3, 0x0D, 0x3D, 0x27, 0x89, 0x5C, 0xDE,
                          0x9D, 0x3B, 0xA7, 0x00, 0x21, 0x5B, 0x89, 0x82,
                          0x51, 0x3A, 0xEB, 0x02, 0x0C, 0xA5, 0x00, 0x49,
                          0x7C, 0x84, 0x4D, 0xB3, 0xCC, 0xD2, 0x1B, 0x81,
                          0x5D, 0x48, 0x76, 0xD5, 0x71, 0x61, 0x21, 0xA9,
                          0x86, 0x96, 0x83, 0x38, 0xCF, 0x9D, 0x5B, 0x6D,
                          0xDC, 0x15, 0xBA, 0x3E, 0x7D, 0x95, 0x3B, 0x2F};
  byte *selfTestResult;
  switch(MFRC522_getFirmwareVersion()) {
    case 0x91 :
      selfTestResult = selfTestResultV1;
      break;
    case 0x92 :
      selfTestResult = selfTestResultV2;
      break;
    default:
      return false;
  }

  MFRC522_reset();
  MFRC522_writeToRegister(FIFODataReg, 0x00);
  MFRC522_writeToRegister(CommandReg, MFRC522_MEM);
  MFRC522_writeToRegister(AutoTestReg, 0x09);
  MFRC522_writeToRegister(FIFODataReg, 0x00);
  MFRC522_writeToRegister(CommandReg, MFRC522_CALCCRC);

  // Wait for the self test to complete.
  i = 0xFF;
  do {
    n = MFRC522_readFromRegister(DivIrqReg);
    i--;
  } while ((i != 0) && !(n & 0x04));

  for (i=0; i < 64; i++) {
    if (MFRC522_readFromRegister(FIFODataReg) != selfTestResult[i]) {
      //printf(i);
      return false;
    }
  }
  return true;
}

/**************************************************************************/
/*!

  @brief   Sends a command to a tag.

  @param   cmd     The command to the MFRC522 to send a command to the tag.
  @param   data    The data that is needed to complete the command.
  @param   dlen    The length of the data.
  @param   result  The result returned by the tag.
  @param   rlen    The number of valid bits in the resulting value.

  @returns Returns the status of the calculation.
           MI_ERR        if something went wrong,
           MI_NOTAGERR   if there was no tag to send the command to.
           MI_OK         if everything went OK.

 */
/**************************************************************************/
int MFRC522_commandTag(byte cmd, byte *data, int dlen, byte *result, int *rlen) {
  int status = MI_ERR;
  byte irqEn = 0x00;
  byte waitIRq = 0x00;
  byte lastBits, n;
  int i;

  switch (cmd) {
  case MFRC522_AUTHENT:
    irqEn = 0x12;
    waitIRq = 0x10;
    break;
  case MFRC522_TRANSCEIVE:
    irqEn = 0x77;
    waitIRq = 0x30;
    break;
  default:
    break;
  }

  MFRC522_writeToRegister(CommIEnReg, irqEn|0x80);    // interrupt request
  MFRC522_clearBitMask(CommIrqReg, 0x80);             // Clear all interrupt requests bits.
  MFRC522_setBitMask(FIFOLevelReg, 0x80);             // FlushBuffer=1, FIFO initialization.

  MFRC522_writeToRegister(CommandReg, MFRC522_IDLE);  // No action, cancel the current command.

  // Write to FIFO
  for (i=0; i < dlen; i++) {
    MFRC522_writeToRegister(FIFODataReg, data[i]);
  }

  // Execute the command.
  MFRC522_writeToRegister(CommandReg, cmd);
  if (cmd == MFRC522_TRANSCEIVE) {
    MFRC522_setBitMask(BitFramingReg, 0x80);  // StartSend=1, transmission of data starts
  }

  // Waiting for the command to complete so we can receive data.
  i = 25; // Max wait time is 25ms.
  do {
    HAL_Delay(1); //HAL_Delay
    // CommIRqReg[7..0]
    // Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
    n = MFRC522_readFromRegister(CommIrqReg);
    i--;
  } while ((i!=0) && !(n&0x01) && !(n&waitIRq));

  MFRC522_clearBitMask(BitFramingReg, 0x80);  // StartSend=0

  if (i != 0) { // Request did not time out.
    if(!(MFRC522_readFromRegister(ErrorReg) & 0x1B)) {  // BufferOvfl Collerr CRCErr ProtocolErr
      status = MI_OK;
      if (n & irqEn & 0x01) {
        status = MI_NOTAGERR;
      }

      if (cmd == MFRC522_TRANSCEIVE) {
        n = MFRC522_readFromRegister(FIFOLevelReg);
        lastBits = MFRC522_readFromRegister(ControlReg) & 0x07;
        if (lastBits) {
          *rlen = (n-1)*8 + lastBits;
        } else {
          *rlen = n*8;
        }

        if (n == 0) {
          n = 1;
        }

        if (n > MAX_LEN) {
          n = MAX_LEN;
        }

        // Reading the recieved data from FIFO.
        for (i=0; i<n; i++) {
          result[i] = MFRC522_readFromRegister(FIFODataReg);
        }
      }
    } else {
      status = MI_ERR;
    }
  }
  return status;
}

/**************************************************************************/
/*!

  @brief   Checks to see if there is a tag in the vicinity.

  @param   mode  The mode we are requsting in.
  @param   type  If we find a tag, this will be the type of that tag.
                 0x4400 = Mifare_UltraLight
                 0x0400 = Mifare_One(S50)
                 0x0200 = Mifare_One(S70)
                 0x0800 = Mifare_Pro(X)
                 0x4403 = Mifare_DESFire

  @returns Returns the status of the request.
           MI_ERR        if something went wrong,
           MI_NOTAGERR   if there was no tag to send the command to.
           MI_OK         if everything went OK.

 */
/**************************************************************************/
int MFRC522_requestTag(byte mode, byte *data) {
  int status, len;
  MFRC522_writeToRegister(BitFramingReg, 0x07);  // TxLastBists = BitFramingReg[2..0]

  data[0] = mode;
  status = MFRC522_commandTag(MFRC522_TRANSCEIVE, data, 1, data, &len);

  if ((status != MI_OK) || (len != 0x10)) {
    status = MI_ERR;
  }

  return status;
}

/**************************************************************************/
/*!

  @brief   Handles collisions that might occur if there are multiple
           tags available.

  @param   serial  The serial nb of the tag.

  @returns Returns the status of the collision detection.
           MI_ERR        if something went wrong,
           MI_NOTAGERR   if there was no tag to send the command to.
           MI_OK         if everything went OK.

 */
/**************************************************************************/
int MFRC522_antiCollision(byte *serial) {
  int status, i, len;
  byte check = 0x00;

  MFRC522_writeToRegister(BitFramingReg, 0x00);  // TxLastBits = BitFramingReg[2..0]

  serial[0] = MF1_ANTICOLL;
  serial[1] = 0x20;
  status = MFRC522_commandTag(MFRC522_TRANSCEIVE, serial, 2, serial, &len);
  len = len / 8; // len is in bits, and we want each byte.
  if (status == MI_OK) {
    // The checksum of the tag is the ^ of all the values.
    for (i = 0; i < len-1; i++) {
      check ^= serial[i];
    }
    // The checksum should be the same as the one provided from the
    // tag (serial[4]).
    if (check != serial[i]) {
      status = MI_ERR;
    }
  }

  return status;
}

/**************************************************************************/
/*!

  @brief   Calculates the CRC value for some data that should be sent to
           a tag.

  @param   data    The data to calculate the value for.
  @param   len     The length of the data.
  @param   result  The result of the CRC calculation.

 */
/**************************************************************************/
void MFRC522_calculateCRC(byte *data, int len, byte *result) {
  int i;
  byte n;

  MFRC522_clearBitMask(DivIrqReg, 0x04);   // CRCIrq = 0
  MFRC522_setBitMask(FIFOLevelReg, 0x80);  // Clear the FIFO pointer

  //Writing data to the FIFO.
  for (i = 0; i < len; i++) {
    MFRC522_writeToRegister(FIFODataReg, data[i]);
  }
  MFRC522_writeToRegister(CommandReg, MFRC522_CALCCRC);

  // Wait for the CRC calculation to complete.
  i = 0xFF;
  do {
    n = MFRC522_readFromRegister(DivIrqReg);
    i--;
  } while ((i != 0) && !(n & 0x04));  //CRCIrq = 1

  // Read the result from the CRC calculation.
  result[0] = MFRC522_readFromRegister(CRCResultRegL);
  result[1] = MFRC522_readFromRegister(CRCResultRegM);
}

/**************************************************************************/
/*!

  @brief   Selects a tag for processing.

  @param   serial  The serial number of the tag that is to be selected.

  @returns The SAK response from the tag.

 */
/**************************************************************************/
byte MFRC522_selectTag(byte *serial) {
  int i, status, len;
  byte sak;
  byte buffer[9];

  buffer[0] = MF1_SELECTTAG;
  buffer[1] = 0x70;
  for (i = 0; i < 5; i++) {
    buffer[i+2] = serial[i];
  }
  MFRC522_calculateCRC(buffer, 7, &buffer[7]);

  status = MFRC522_commandTag(MFRC522_TRANSCEIVE, buffer, 9, buffer, &len);

  if ((status == MI_OK) && (len == 0x18)) {
    sak = buffer[0];
  }
  else {
    sak = 0;
  }

  return sak;
}

/**************************************************************************/
/*!

  @brief   Handles the authentication between the tag and the reader.

  @param   mode    What authentication key to use.
  @param   block   The block that we want to read.
  @param   key     The authentication key.
  @param   serial  The serial of the tag.

  @returns Returns the status of the collision detection.
           MI_ERR        if something went wrong,
           MI_OK         if everything went OK.

 */
/**************************************************************************/
int MFRC522_authenticate(byte mode, byte block, byte *key, byte *serial) {
  int i, status, len;
  byte buffer[12];

  //Verify the command block address + sector + password + tag serial number
  buffer[0] = mode;          // 0th byte is the mode
  buffer[1] = block;         // 1st byte is the block to address.
  for (i = 0; i < 6; i++) {  // 2nd to 7th byte is the authentication key.
    buffer[i+2] = key[i];
  }
  for (i = 0; i < 4; i++) {  // 8th to 11th byte is the serial of the tag.
    buffer[i+8] = serial[i];
  }

  status = MFRC522_commandTag(MFRC522_AUTHENT, buffer, 12, buffer, &len);

  if ((status != MI_OK) || (!(MFRC522_readFromRegister(Status2Reg) & 0x08))) {
    status = MI_ERR;
  }

  return status;
}

/**************************************************************************/
/*!

  @brief   Tries to read from the current (authenticated) tag.

  @param   block   The block that we want to read.
  @param   result  The resulting value returned from the tag.

  @returns Returns the status of the collision detection.
           MI_ERR        if something went wrong,
           MI_OK         if everything went OK.

 */
/**************************************************************************/
int MFRC522_readFromTag(byte block, byte *result) {
  int status, len;

  result[0] = MF1_READ;
  result[1] = block;
  MFRC522_calculateCRC(result, 2, &result[2]);
  status = MFRC522_commandTag(MFRC522_TRANSCEIVE, result, 4, result, &len);

  if ((status != MI_OK) || (len != 0x90)) {
    status = MI_ERR;
  }

  return status;
}

/**************************************************************************/
/*!

  @brief   Tries to write to a block on the current tag.

  @param   block  The block that we want to write to.
  @param   data   The data that we shoudl write to the block.

  @returns Returns the status of the collision detection.
           MI_ERR        if something went wrong,
           MI_OK         if everything went OK.

 */
/**************************************************************************/
int MFRC522_writeToTag(byte block, byte *data) {
  int status, i, len;
  byte buffer[18];

  buffer[0] = MF1_WRITE;
  buffer[1] = block;
  MFRC522_calculateCRC(buffer, 2, &buffer[2]);
  status = MFRC522_commandTag(MFRC522_TRANSCEIVE, buffer, 4, buffer, &len);

  if ((status != MI_OK) || (len != 4) || ((buffer[0] & 0x0F) != 0x0A)) {
    status = MI_ERR;
  }

  if (status == MI_OK) {
    for (i = 0; i < 16; i++) {
      buffer[i] = data[i];
    }
    MFRC522_calculateCRC(buffer, 16, &buffer[16]);
    status = MFRC522_commandTag(MFRC522_TRANSCEIVE, buffer, 18, buffer, &len);

    if ((status != MI_OK) || (len != 4) || ((buffer[0] & 0x0F) != 0x0A)) {
      status = MI_ERR;
    }
  }

  return status;
}

/**************************************************************************/
/*!

  @brief   Sends a halt command to the current tag.

  @returns Returns the result of the halt.
           MI_ERR        If the command didn't complete properly.
           MI_OK         If the command completed.
 */
/**************************************************************************/
int MFRC522_haltTag() {
  int status, len;
  byte buffer[4];

  buffer[0] = MF1_HALT;
  buffer[1] = 0;
  MFRC522_calculateCRC(buffer, 2, &buffer[2]);
  MFRC522_clearBitMask(Status2Reg, 0x08);  // turn off encryption
  status = MFRC522_commandTag(MFRC522_TRANSCEIVE, buffer, 4, buffer, &len);

  return status;
}