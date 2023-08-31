/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mateusz Salamon
 * @brief          : STM32 na Rejestrach
 ******************************************************************************
 ******************************************************************************

 	 	 	 	 https://msalamon.pl
 	 	 	 	 https://sklep.msalamon.pl
 	 	 	 	 https://kursstm32.pl
 	 	 	 	 https://stm32narejestrach.pl

 */
#include "main.h"

// LEDs control macros
#define LD4_ON GPIOA->BSRR = GPIO_BSRR_BS5
#define LD4_OFF GPIOA->BSRR = GPIO_BSRR_BR5
#define LD4_TOGGLE GPIOA->ODR ^= GPIO_ODR_OD5

#define LD5_ON GPIOA->BSRR = GPIO_BSRR_BS6
#define LD5_OFF GPIOA->BSRR = GPIO_BSRR_BR6
#define LD5_TOGGLE GPIOA->ODR ^= GPIO_ODR_OD6

#define LD6_ON GPIOA->BSRR = GPIO_BSRR_BS7
#define LD6_OFF GPIOA->BSRR = GPIO_BSRR_BR7
#define LD6_TOGGLE GPIOA->ODR ^= GPIO_ODR_OD7

// Constants for Software Timer's actions
#define LD4_TIMER 500
#define LD5_TIMER 222
#define LD6_TIMER 147

// Tick for System Time
__IO uint32_t Tick;

// LEDs Configuration
void ConfigureLD4(void);
void ConfigureLD5(void);
void ConfigureLD6(void);

// Get current System Time
uint32_t GetSystemTick(void);

// Software Timers variables
uint32_t Timer_LD4;
uint32_t Timer_LD5;
uint32_t Timer_LD6;

int main(void)
{

	// 1s = 12 000 000
	// 0,001 = X
	SysTick_Config(12000000 / 1000);

	// Configure LEDs
	ConfigureLD4();
	ConfigureLD5();
	ConfigureLD6();

	// Software Timers - first fill
	Timer_LD4 = GetSystemTick();
	Timer_LD5 = GetSystemTick();
	Timer_LD6 = GetSystemTick();

    /* Loop forever */
	while(1)
	{
		// LD4
		if((GetSystemTick() - Timer_LD4) > LD4_TIMER) // Check if is time to make  action
		{
			Timer_LD4 = GetSystemTick(); // Refill action's timer
			LD4_TOGGLE; // ACTION!
		}

		// LD5
		if((GetSystemTick() - Timer_LD5) > LD5_TIMER)
		{
			Timer_LD5 = GetSystemTick();
			LD5_TOGGLE;
		}

		// LD6
		if((GetSystemTick() - Timer_LD6) > LD6_TIMER)
		{
			Timer_LD6 = GetSystemTick();
			LD6_TOGGLE;
		}


	}
}

void ConfigureLD4(void)
{
	// Enable Clock for PORTA
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

	// Configure GPIO Mode - Output
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
	GPIOA->MODER &= ~(GPIO_MODER_MODE5_1);

	// Configure Output Mode - Push-pull
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);

	// Configure GPIO Speed - Low
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED5);

	// Configure Pull-up/Pull-down - no PU/PD
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5);
}

void ConfigureLD5(void) // PA6
{
	// Enable Clock for PORTA
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

	// Configure GPIO Mode - Output
	GPIOA->MODER |= GPIO_MODER_MODE6_0;
	GPIOA->MODER &= ~(GPIO_MODER_MODE6_1);

	// Configure Output Mode - Push-pull
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT6);

	// Configure GPIO Speed - Low
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED6);

	// Configure Pull-up/Pull-down - no PU/PD
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD6);
}

void ConfigureLD6(void) // PA7
{
	// Enable Clock for PORTA
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

	// Configure GPIO Mode - Output
	GPIOA->MODER |= GPIO_MODER_MODE7_0;
	GPIOA->MODER &= ~(GPIO_MODER_MODE7_1);

	// Configure Output Mode - Push-pull
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT7);

	// Configure GPIO Speed - Low
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED7);

	// Configure Pull-up/Pull-down - no PU/PD
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD7);
}

void SysTick_Handler(void)
{
	Tick++; // Increase system timer
}

uint32_t GetSystemTick(void)
{
	return Tick; // Return current System Time
}




