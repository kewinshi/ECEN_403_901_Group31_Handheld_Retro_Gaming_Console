Kyle Liu main.c
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "fonts.h"
#include <string.h>
#include "stm32f1xx_hal_conf.h"

//#include "st7789v2.h"
/* Private includes ----------------------------------------------------------*/

#define LCD_WIDTH    320
#define LCD_HEIGHT   170
#define MENU_ITEMS     2
#define LCD_CS_Pin GPIO_PIN_6
#define LCD_CS_GPIO_Port GPIOB
#define LCD_DC_Pin GPIO_PIN_8
#define LCD_DC_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_9
#define LCD_RST_GPIO_Port GPIOA
//button defines
#define BUTTON_UP_PIN       GPIOA
#define BUTTON_UP_PIN_Port       GPIO_PIN_11

#define BUTTON_DOWN_PIN     GPIOA
#define BUTTON_DOWN_PIN_Port     GPIO_PIN_12

#define BUTTON_SELECT_PIN   GPIOA
#define BUTTON_SELECT_PIN_Port   GPIO_PIN_10


// Initialize pins as input in your GPIO configuration function

//color defines
#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED   0xFC00  // Adjusted for 6-bit red
#define GREEN 0x07E0  // Adjusted for 6-bit green
#define BLUE  0x001F  // Adjusted for 6-bit blue


/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
void LCD_Init(void);
void LCD_WriteCommand(uint8_t cmd);
void LCD_WriteData(uint8_t data);
void LCD_FillScreen(uint32_t color);
void LCD_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void LCD_Clear(uint16_t color);
void clear_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_DrawChar(uint16_t x, uint16_t y, char c, uint32_t color, uint32_t bgcolor);
void LCD_Drawpixel(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawString(uint16_t x, uint16_t y, const char *str, uint32_t color, uint32_t bgcolor);

//void Draw_Menu(void);
//void Handle_Input(void);
//void StartGame(uint8_t gameIndex);

/* Private user code ---------------------------------------------------------*/
/*
uint8_t currentMenuItem = 0;
const char* menuItems[MENU_ITEMS] = {
    "PACMAN",
    "SNAKE"
};
uint16_t menuColors[MENU_ITEMS] = {
    ST7789V2_YELLOW,
    ST7789V2_GREEN
};
*/


typedef enum {
    MENU_ITEM_1,
    MENU_ITEM_2,
    MENU_ITEM_COUNT // Always define this to keep track of the total number of items
} MenuItem;

MenuItem currentMenuItem = MENU_ITEM_1;

#define NUM_MENU_ITEMS MENU_ITEM_COUNT

SPI_HandleTypeDef hspi1;
uint8_t selected_item = 0;
int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  HAL_Delay(100);
  LCD_Init();
  HAL_Delay(100);
  //green
  LCD_Clear(GREEN);
  HAL_Delay(100);

  displayMenu();
  clear_area(100, 100, 110, 110, GREEN);
  

  while (1)
  {
	  //HAL_UART_Transmit(&huart2, (uint8_t *)"test\r\n", strlen("test\r\n"), HAL_MAX_DELAY);

	  if (HAL_GPIO_ReadPin(GPIOA, BUTTON_UP_PIN) == GPIO_PIN_SET) {
		 HAL_UART_Transmit(&huart2, (uint8_t *)"up\r\n", strlen("up\r\n"), HAL_MAX_DELAY);
	     navigateMenuUp();
	     HAL_Delay(200); // Debounce delay
	  }else if (HAL_GPIO_ReadPin(GPIOA, BUTTON_DOWN_PIN) == GPIO_PIN_SET) {
		 HAL_UART_Transmit(&huart2, (uint8_t *)"down\r\n", strlen("down\r\n"), HAL_MAX_DELAY);
	     navigateMenuDown();
	     HAL_Delay(200);
	  }else if (HAL_GPIO_ReadPin(GPIOA, BUTTON_SELECT_PIN) == GPIO_PIN_SET) {
	     selectMenuItem();
	     HAL_Delay(200);
	  }
  }
  /* USER CODE END 3 */
}
//up button
void navigateMenuUp() {
    if (currentMenuItem > 0) {
        currentMenuItem--;
    }
    displayMenu();
}
//down button
void navigateMenuDown() {
    if (currentMenuItem < MENU_ITEM_COUNT - 1) {
        currentMenuItem++;
    }
    displayMenu();
}
//select button
void selectMenuItem() {
    switch (currentMenuItem) {
        case MENU_ITEM_1:
            //loadGame1Screen(); //for integration later
            break;
        case MENU_ITEM_2:
            //loadGame2Screen(); // for integration later
            break;
    }
}

void displayMenu() {
    LCD_Clear(BLACK);  // Clear the screen

    // Always display the header
    LCD_DrawString(50, 50, "main menu", WHITE, BLACK);
    LCD_DrawString(50, 60, "select games", WHITE, BLACK);

    // Display menu items with selection indicator
    if (currentMenuItem == MENU_ITEM_1) {
        LCD_DrawString(50, 70, ">> snake", WHITE, BLACK);
        LCD_DrawString(50, 80, "   pacman", WHITE, BLACK);
    } else if (currentMenuItem == MENU_ITEM_2) {
        LCD_DrawString(50, 70, "   snake", WHITE, BLACK);
        LCD_DrawString(50, 80, ">> pacman", WHITE, BLACK);
    }
}
//lcd commands
void LCD_WriteCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET); // Command mode
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

}
//lcd  send datas
void LCD_WriteData(uint8_t data) {
    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET); // Data mode
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}
//set the boundary of the lcd
void LCD_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    LCD_WriteCommand(0x2A);
    LCD_WriteData(x0 >> 8);
    LCD_WriteData(x0 & 0xFF);
    LCD_WriteData(x1 >> 8);
    LCD_WriteData(x1 & 0xFF);

    LCD_WriteCommand(0x2B);
    LCD_WriteData(y0 >> 8);
    LCD_WriteData(y0 & 0xFF);
    LCD_WriteData(y1 >> 8);
    LCD_WriteData(y1 & 0xFF);

    LCD_WriteCommand(0x2C);
}
//initialize the lcd
void LCD_Init(void)
{
    // Hardware Reset
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(100);

    // Basic initialization sequence

    LCD_WriteCommand(0x11);    // Sleep out
    HAL_Delay(120);           // Required delay

    LCD_WriteCommand(0x36);    // Memory Access Control
    LCD_WriteData(0x00);      // Normal orientation

    LCD_WriteCommand(0x3A);    // Interface Pixel Format
    LCD_WriteData(0x05);      // 16-bit color

    LCD_WriteCommand(0x21);    // Display Inversion On

    LCD_WriteCommand(0x13);    // Normal Display Mode On

    LCD_WriteCommand(0x29);    // Display On
    HAL_Delay(120);

}
//one of the main driver function, clears the lcd screen
void LCD_Clear(uint16_t color) {
	LCD_WriteCommand(0x2A); // Column Address Set
	LCD_WriteData(0x00); // Start column high byte
	LCD_WriteData(0x00); // Start column low byte
	LCD_WriteData(0x00); // End column high byte
	LCD_WriteData(0xEF); // End column low byte (239 for 240px width)

	LCD_WriteCommand(0x2B); // Row Address Set
    LCD_WriteData(0x00); // Start row high byte
    LCD_WriteData(0x00); // Start row low byte
    LCD_WriteData(0x01); // End row high byte
    LCD_WriteData(0x3F); // End row low byte (319 for 320px height)

    LCD_WriteCommand(0x2C); // Memory Write

    for (uint32_t i = 0; i < 240 * 320; i++) {
    	LCD_WriteData(color >> 8);   // Send high byte
    	LCD_WriteData(color & 0xFF); // Send low byte
    }
}
void clear_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    // Ensure the coordinates are within bounds
    if (x1 >= LCD_WIDTH || y1 >= LCD_HEIGHT || x2 >= LCD_WIDTH || y2 >= LCD_HEIGHT) {
        return; // Out of bounds, do nothing
    }

    // Set the column address range
    LCD_WriteCommand(0x2A); // Column Address Set
    LCD_WriteData(x1 >> 8); // Start column high byte
    LCD_WriteData(x1 & 0xFF); // Start column low byte
    LCD_WriteData(x2 >> 8); // End column high byte
    LCD_WriteData(x2 & 0xFF); // End column low byte

    // Set the row address range
    LCD_WriteCommand(0x2B); // Row Address Set
    LCD_WriteData(y1 >> 8); // Start row high byte
    LCD_WriteData(y1 & 0xFF); // Start row low byte
    LCD_WriteData(y2 >> 8); // End row high byte
    LCD_WriteData(y2 & 0xFF); // End row low byte

    // Start writing to memory
    LCD_WriteCommand(0x2C); // Memory Write

    // Fill the specified area with the color
    for (uint32_t i = 0; i < (x2 - x1 + 1) * (y2 - y1 + 1); i++) {
        LCD_WriteData(color >> 8);    // Send high byte of the color
        LCD_WriteData(color & 0xFF); // Send low byte of the color
    }
}


//testing function
void LCD_FillScreen(uint32_t color) {
    LCD_WriteCommand(0x2C); // RAM write command
    for (uint16_t i = 0; i < 320 * 170; i++) {
        LCD_WriteData(color >> 16); // Red
        LCD_WriteData((color >> 8) & 0xFF); // Green
        LCD_WriteData(color & 0xFF); // Blue
    }
}
//characters a-z
    uint8_t font_a[7] = {
	    0b00000,
	    0b01110,
	    0b00001,
	    0b01111,
	    0b10001,
	    0b01111,
	    0b00000
	};

	uint8_t font_b[7] = {
	    0b10000,
	    0b10000,
	    0b11110,
	    0b10001,
	    0b10001,
	    0b11110,
	    0b00000
	};

	uint8_t font_c[7] = {
	    0b00000,
	    0b01111,
	    0b10000,
	    0b10000,
	    0b10000,
	    0b01111,
	    0b00000
	};

	uint8_t font_d[7] = {
	    0b00001,
	    0b00001,
	    0b01111,
	    0b10001,
	    0b10001,
	    0b01111,
	    0b00000
	};

	uint8_t font_e[7] = {
	    0b00000,
	    0b01110,
	    0b10001,
	    0b11111,
	    0b10000,
	    0b01111,
	    0b00000
	};

	uint8_t font_f[7] = {
	    0b00111,
	    0b01000,
	    0b11110,
	    0b01000,
	    0b01000,
	    0b01000,
	    0b00000
	};

	uint8_t font_g[7] = {
	    0b00000,
	    0b01111,
	    0b10001,
	    0b10001,
	    0b01111,
	    0b00001,
	    0b11110
	};

	uint8_t font_h[7] = {
	    0b10000,
	    0b10000,
	    0b11110,
	    0b10001,
	    0b10001,
	    0b10001,
	    0b00000
	};

	uint8_t font_i[7] = {
	    0b00000,
	    0b00100,
	    0b00000,
	    0b01100,
	    0b00100,
	    0b01110,
	    0b00000
	};

	uint8_t font_j[7] = {
	    0b00000,
	    0b00001,
	    0b00001,
	    0b00001,
	    0b10001,
	    0b01110,
	    0b00000
	};

	uint8_t font_k[7] = {
	    0b10000,
	    0b10010,
	    0b10100,
	    0b11000,
	    0b10100,
	    0b10010,
	    0b00000
	};

	uint8_t font_l[7] = {
	    0b01100,
	    0b00100,
	    0b00100,
	    0b00100,
	    0b00100,
	    0b01110,
	    0b00000
	};

	uint8_t font_m[7] = {
	    0b00000,
	    0b11010,
	    0b10101,
	    0b10101,
	    0b10101,
	    0b10101,
	    0b00000
	};

	uint8_t font_n[7] = {
	    0b00000,
	    0b11110,
	    0b10001,
	    0b10001,
	    0b10001,
	    0b10001,
	    0b00000
	};

	uint8_t font_o[7] = {
	    0b00000,
	    0b01110,
	    0b10001,
	    0b10001,
	    0b10001,
	    0b01110,
	    0b00000
	};

	uint8_t font_p[7] = {
	    0b00000,
	    0b11110,
	    0b10001,
	    0b11110,
	    0b10000,
	    0b10000,
	    0b00000
	};

	uint8_t font_q[7] = {
	    0b00000,
	    0b01111,
	    0b10001,
	    0b01111,
	    0b00001,
	    0b00001,
	    0b00000
	};

	uint8_t font_r[7] = {
	    0b00000,
	    0b11110,
	    0b10001,
	    0b10000,
	    0b10000,
	    0b10000,
	    0b00000
	};

	uint8_t font_s[7] = {
	    0b00000,
	    0b01111,
	    0b10000,
	    0b01110,
	    0b00001,
	    0b11110,
	    0b00000
	};

	uint8_t font_t[7] = {
	    0b01000,
	    0b11111,
	    0b01000,
	    0b01000,
	    0b01000,
	    0b00111,
	    0b00000
	};

	uint8_t font_u[7] = {
	    0b00000,
	    0b10001,
	    0b10001,
	    0b10001,
	    0b10001,
	    0b01111,
	    0b00000
	};

	uint8_t font_v[7] = {
	    0b00000,
	    0b10001,
	    0b10001,
	    0b10001,
	    0b01010,
	    0b00100,
	    0b00000
	};

	uint8_t font_w[7] = {
	    0b00000,
	    0b10001,
	    0b10001,
	    0b10101,
	    0b10101,
	    0b01010,
	    0b00000
	};

	uint8_t font_x[7] = {
	    0b00000,
	    0b10001,
	    0b01010,
	    0b00100,
	    0b01010,
	    0b10001,
	    0b00000
	};

	uint8_t font_y[7] = {
	    0b00000,
	    0b10001,
	    0b10001,
	    0b01111,
	    0b00001,
	    0b01110,
	    0b00000
	};

	uint8_t font_z[7] = {
	    0b00000,
	    0b11111,
	    0b00010,
	    0b00100,
	    0b01000,
	    0b11111,
	    0b00000
	};
	// Character '>'
	uint8_t font_greater_than[7] = {
	    0b10000,
	    0b01000,
	    0b00100,
	    0b00010,
	    0b00100,
	    0b01000,
	    0b10000
	};


//constant for all of the characters
	const uint8_t* font_data[27] = {font_a, font_b,font_c,font_d,font_e,font_f,font_g,font_h,font_i,font_j,font_k,font_l,font_m,font_n,font_o,font_p,font_q,font_r,font_s,font_t,font_u,font_v,font_w,font_x,font_y,font_z,font_greater_than};

//more characters to be added as the game needs
void LCD_DrawChar(uint16_t x, uint16_t y, char c, uint32_t color, uint32_t bgcolor) {

	if ((c < 'a' || c > 'z') && c != '>') {
       return; // Do nothing if character is outside 'a'-'z' range
    }

    // Find the font array for the character
	 const uint8_t* char_data;
	 if (c >= 'a' && c <= 'z') {
       char_data = font_data[c - 'a']; // Use existing lowercase letters
     } else if (c == '>') {
       char_data = font_data[26]; // Use the index for the '>' character
     }

    // Draw the character in a 5x7 grid
    for (int row = 0; row < 7; row++) {
       uint8_t row_data = char_data[row]; // Get the row data for the current character
       for (int col = 0; col < 5; col++) {
            if (row_data & (1 << (4 - col))) { // Check if the specific bit is set (1)
                LCD_Drawpixel(x + col, y + row, color); // Draw pixel if bit is set
            }
       }
    }
}

void LCD_Drawpixel(uint16_t x, uint16_t y, uint16_t color) {
    // Set the column address
    LCD_WriteCommand(0x2A); // Column address set command (ST7789)
    LCD_WriteData(x >> 8);  // Send the higher 8 bits of the x-coordinate
    LCD_WriteData(x & 0xFF); // Send the lower 8 bits of the x-coordinate

    // Set the row address
    LCD_WriteCommand(0x2B); // Row address set command (ST7789)
    LCD_WriteData(y >> 8);  // Send the higher 8 bits of the y-coordinate
    LCD_WriteData(y & 0xFF); // Send the lower 8 bits of the y-coordinate

    // Write the pixel color data
    LCD_WriteCommand(0x2C); // Memory write command (ST7789)
    LCD_WriteData(color >> 8);  // Send the higher 8 bits of the color
    LCD_WriteData(color & 0xFF); // Send the lower 8 bits of the color
}


// Draw a string on the display
void LCD_DrawString(uint16_t x, uint16_t y, const char *str, uint32_t color, uint32_t bgcolor) {
    while (*str) {
        LCD_DrawChar(x, y, *str, color, bgcolor);
        x += 6; // Move x for the next character
        str++;
    }
}

// Draw a single pixel on the display
void LCD_SetPixel(uint16_t x, uint16_t y, uint32_t color) {
    LCD_WriteCommand(0x2A); // Column address set
    LCD_WriteData(x >> 8);
    LCD_WriteData(x & 0xFF);
    LCD_WriteCommand(0x2B); // Row address set
    LCD_WriteData(y >> 8);
    LCD_WriteData(y & 0xFF);
    LCD_WriteCommand(0x2C); // RAM write
    LCD_WriteData(color >> 16); // Red
    LCD_WriteData((color >> 8) & 0xFF); // Green
    LCD_WriteData(color & 0xFF); // Blue
}




/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DC_Pin|RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : DC_Pin RST_Pin */
  GPIO_InitStruct.Pin = DC_Pin|RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : CS_Pin */
  GPIO_InitStruct.Pin = CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;  // Set to pull-up for stable input
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
