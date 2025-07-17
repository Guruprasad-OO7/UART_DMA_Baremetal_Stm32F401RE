#include "stm32f4xx.h"
char dma_buffer[] = "Hello from DMA via Virtual COM Port!\r\n";
void GPIO_Init(void);
void USART2_Init(void);
void DMA1_Stream6_Init(uint32_t srcAddr, uint16_t len);
void LED_Init(void);
void delay_ms(uint32_t ms);

int main(void)
{
    GPIO_Init();
    USART2_Init();
    USART2->CR3 |= USART_CR3_DMAT;  // Enable DMA for USART2 TX
    while (1)
    {
        DMA1_Stream6_Init((uint32_t)dma_buffer, sizeof(dma_buffer) - 1);
        DMA1_Stream6->CR |= DMA_SxCR_EN;         // Enable DMA stream
        while (!(DMA1->HISR & DMA_HISR_TCIF6));  // Wait for transfer complete
        DMA1->HIFCR |= DMA_HIFCR_CTCIF6;         // Clear TC flag
        GPIOA->ODR ^= (1 << 5);  // Toggle LED
        delay_ms(1000);          // Wait 1 second
    }
}
void GPIO_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER &= ~(3 << (2 * 2));
    GPIOA->MODER |=  (2 << (2 * 2));
    GPIOA->AFR[0] &= ~(0xF << (4 * 2));
    GPIOA->AFR[0] |=  (7 << (4 * 2));
    GPIOA->OSPEEDR |= (3 << (2 * 2));  
    GPIOA->MODER &= ~(3 << (5 * 2));
    GPIOA->MODER |=  (1 << (5 * 2));  
}
void USART2_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    USART2->BRR = (16000000 / 115200);  //16MHz
    USART2->CR1 |= USART_CR1_TE;
    USART2->CR1 |= USART_CR1_UE;
}
void DMA1_Stream6_Init(uint32_t srcAddr, uint16_t len)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    DMA1_Stream6->CR &= ~DMA_SxCR_EN;
    while (DMA1_Stream6->CR & DMA_SxCR_EN);  // Wait until disabled
    DMA1->HIFCR |=DMA_HIFCR_CTCIF6;  // Clear TC flag

    DMA1_Stream6->PAR  =(uint32_t)&USART2->DR;
    DMA1_Stream6->M0AR =srcAddr;
    DMA1_Stream6->NDTR =len;
    DMA1_Stream6->CR =0;
    DMA1_Stream6->CR |=(4 << DMA_SxCR_CHSEL_Pos);  // Channel 4
    DMA1_Stream6->CR |=DMA_SxCR_DIR_0;             // Mem-to-Periph
    DMA1_Stream6->CR |=DMA_SxCR_MINC;              // Mem increment
    DMA1_Stream6->CR |=DMA_SxCR_PL_1;              // High priority
}
void delay_ms(uint32_t ms)
{
    SysTick->LOAD=16000-1;  // 1 ms tick (for 16 MHz)
    SysTick->VAL=0;
    SysTick->CTRL=5;  // Enable SysTick with processor clock
    for (uint32_t i=0; i<ms; i++)
    {
        while (!(SysTick->CTRL&(1<<16)));  // Wait for COUNTFLAG
    }

    SysTick->CTRL=0;  // Disable SysTick
}
