#include "stm32_spi_sd.h"
#include "main.h"
#include "spi.h"

#define SD_DUMMY_BYTE 0xFF

#define SD_CS_LOW() HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET)
#define SD_CS_HIGH() HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_SET)

uint32_t SpixTimeout = 1000; /*<! Value of Timeout when SPI communication fails */

/**
  * @brief  SPI error treatment function.
  */
static void SPIx_Error(void)
{
	/* De-initialize the SPI communication BUS */
	HAL_SPI_DeInit(&hspi1);

	/* Re-Initiaize the SPI communication BUS */
	MX_SPI1_Init();
}

/* Link functions for SD Card peripheral*/
void SD_IO_Init(void)
{
	/* spi and gpio configured in cube @see spi.c and gpio.c*/

	/* SD chip select high */
	SD_CS_HIGH();

	/* Send dummy byte 0xFF, 10 times with CS high */
	/* Rise CS and MOSI for 80 clocks cycles */
	for (uint8_t counter = 0; counter <= 9; counter++)
	{
		/* Send dummy byte 0xFF */
		SD_IO_WriteByte(SD_DUMMY_BYTE);
	}
}

void SD_IO_CSState(uint8_t state)
{
	if (state == 1)
	{
		SD_CS_HIGH();
	}
	else
	{
		SD_CS_LOW();
	}
}

void SD_IO_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength)
{
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_SPI_TransmitReceive(&hspi1, (uint8_t *)DataIn, DataOut, DataLength, SpixTimeout);

	/* Check the communication status */
	if (status != HAL_OK)
	{
		/* Execute user timeout callback */
		SPIx_Error();
	}
}

uint8_t SD_IO_WriteByte(uint8_t Data)
{
	uint8_t tmp;
	/* Send the byte */
	SD_IO_WriteReadData(&Data, &tmp, 1);
	return tmp;
}
