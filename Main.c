#include "stm32f4xx.h"
char dma_buffer[] = "Hello from DMA!\r\n";
void USART2_Init(void);
void DMA1_Stream6_Init(uint32_t srcAddr, uint16_t len);
void GPIO_Init(void);
int main(void)
{
    GPIO_Init();
    USART2_Init();
    DMA1_Stream6_Init((uint32_t)dma_buffer, sizeof(dma_buffer) - 1);
    USART2->CR3 |= USART_CR3_DMAT;  // Enable USART DMA transmit
    DMA1_Stream6->CR |= DMA_SxCR_EN;  // Start DMA stream
    while (!(DMA1->HISR & DMA_HISR_TCIF6)); // Wait for TCIF6 flag
    DMA1->HIFCR |= DMA_HIFCR_CTCIF6; // Clear the transfer complete flag
    while (1); // Infinite loop
}
void GPIO_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER &= ~(3 << (2 * 2));      // Clear mode
    GPIOA->MODER |= (2 << (2 * 2));       // Alternate function
    GPIOA->AFR[0] |= (7 << (4 * 2));      // AF7 for USART2
}
void USART2_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    USART2->BRR = (uint16_t)(16000000 / 115200); // Assuming 16 MHz
    USART2->CR1 |= USART_CR1_TE;     // Enable transmitter
    USART2->CR1 |= USART_CR1_UE;     // Enable USART
}

// Configure DMA1 Stream6 for USART2_TX
void DMA1_Stream6_Init(uint32_t srcAddr, uint16_t len)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    DMA1_Stream6->CR &= ~DMA_SxCR_EN;
    while (DMA1_Stream6->CR & DMA_SxCR_EN); // Wait for it to disable
    DMA1->HIFCR |= DMA_HIFCR_CTCIF6;
    DMA1_Stream6->PAR = (uint32_t)&USART2->DR;
    DMA1_Stream6->M0AR = srcAddr;
    DMA1_Stream6->NDTR = len;
    DMA1_Stream6->CR = 0;
    DMA1_Stream6->CR |= (4 << DMA_SxCR_CHSEL_Pos);  // Channel 4 for USART2_TX
    DMA1_Stream6->CR |= DMA_SxCR_DIR_0;             // Memory to Peripheral
    DMA1_Stream6->CR |= DMA_SxCR_MINC;              // Memory increment
    DMA1_Stream6->CR |= DMA_SxCR_TCIE;              // Transfer complete interrupt (optional)
    DMA1_Stream6->CR |= DMA_SxCR_PL_1;              // Priority high
}
