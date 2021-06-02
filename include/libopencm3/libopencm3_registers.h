#ifndef  LIBOPENCM3_REGISTERS_H
#define  LIBOPENCM3_REGISTERS_H

#define MMIO32(addr)		            (*(volatile uint32_t *)(addr))

#define PERIPH_BASE			            (0x40000000U)
#define PERIPH_BASE_APB2	            (PERIPH_BASE + 0x10000)
#define PERIPH_BASE_APB1		        (PERIPH_BASE + 0x00000)
#define PERIPH_BASE_AHB			        (PERIPH_BASE + 0x18000)
#define PPBI_BASE                       (0xE0000000U)
#define SCS_BASE                        (PPBI_BASE + 0xE000)
// NVIC //////////////////////////////////////////////////////////////////////////////////
#define NVIC_BASE                       (SCS_BASE + 0x0100)

#define NVIC_ISER(iser_id)		        MMIO32(NVIC_BASE + 0x00 + ((iser_id) * 4))

#define NVIC_TIM2_IRQ                   15
// RCC //////////////////////////////////////////////////////////////////////////////////
#define RCC_BASE			            (PERIPH_BASE_AHB + 0x09000)

#define RCC_CFGR				        MMIO32(RCC_BASE + 0x04)

#define RCC_CR					        MMIO32(RCC_BASE + 0x00)

#define RCC_AHBENR				        MMIO32(RCC_BASE + 0x14)

#define RCC_APB2ENR				        MMIO32(RCC_BASE + 0x18)

#define RCC_APB1ENR				        MMIO32(RCC_BASE + 0x1c)
// GPIO ////////////////////////////////////////////////////////////////////////////////
#define GPIO_CRL(port)		            MMIO32((port) + 0x00)

#define GPIO_BSRR(port)			        MMIO32((port) + 0x10)

#define GPIO_IDR(port)			        MMIO32((port) + 0x08)

#define GPIO_CRH(port)			        MMIO32((port) + 0x04)
    // GPIOA
#define GPIO_PORT_A_BASE                (PERIPH_BASE_APB2 + 0x0800)
#define GPIOA				            GPIO_PORT_A_BASE

#define GPIOA_CRH			            GPIO_CRH(GPIOA)

#define GPIOA_CRL			            GPIO_CRL(GPIOA)

#define GPIOA_BSRR			            GPIO_BSRR(GPIOA)

#define GPIOA_IDR			            GPIO_IDR(GPIOA)
// GPIOB
#define GPIO_PORT_B_BASE		        (PERIPH_BASE_APB2 + 0x0c00)
#define GPIOB				            GPIO_PORT_B_BASE

#define GPIOB_CRH			            GPIO_CRH(GPIOB)
// ADC /////////////////////////////////////////////////////////////////////////////////
#define ADC_CR1(block)                  MMIO32((block) + 0x04)
#define ADC_CR2(block)                  MMIO32((block) + 0x08)

#define ADC_DR(block)			        MMIO32((block) + 0x4c)

#define ADC_SMPR1(block)                MMIO32((block) + 0x0c)
#define ADC_SMPR2(block)                MMIO32((block) + 0x10)

#define ADC_SQR1(block)			        MMIO32((block) + 0x2c)
#define ADC_SQR2(block)			        MMIO32((block) + 0x30)
#define ADC_SQR3(block)			        MMIO32((block) + 0x34)
// ADC1
#define ADC1_BASE			            (PERIPH_BASE_APB2 + 0x2400)
#define ADC1				            ADC1_BASE

#define ADC1_CR1                        ADC_CR1(ADC1)
#define ADC1_CR2                        ADC_CR2(ADC1)

#define ADC1_DR                         ADC_DR(ADC1)

#define ADC1_SMPR1                      ADC_SMPR1(ADC1)
#define ADC1_SMPR2                      ADC_SMPR2(ADC1)

#define ADC1_SQR1                       ADC_SQR1(ADC1)
#define ADC1_SQR2                       ADC_SQR2(ADC1)
#define ADC1_SQR3                       ADC_SQR3(ADC1)
// USART ///////////////////////////////////////////////////////////////////////////////
#define USART_BRR(usart_base)		    MMIO32((usart_base) + 0x08)

#define USART_CR1(usart_base)		    MMIO32((usart_base) + 0x0c)
#define USART_CR2(usart_base)		    MMIO32((usart_base) + 0x10)
#define USART_CR3(usart_base)		    MMIO32((usart_base) + 0x14)

#define USART_SR(usart_base)		    MMIO32((usart_base) + 0x00)

#define USART_DR(usart_base)		    MMIO32((usart_base) + 0x04)
// USART1
#define USART1_BASE			            (PERIPH_BASE_APB2 + 0x3800)

#define USART1_BRR			            USART_BRR(USART1_BASE)

#define USART1_CR1			            USART_CR1(USART1_BASE)
#define USART1_CR2			            USART_CR2(USART1_BASE)
#define USART1_CR3			            USART_CR3(USART1_BASE)

#define USART1_SR			            USART_SR(USART1_BASE)

#define USART1_DR			            USART_DR(USART1_BASE)
// DMA /////////////////////////////////////////////////////////////////////////////////
#define DMA_CPAR(dma_base, channel)	    MMIO32((dma_base) + 0x10 + (0x14 * ((channel) - 1)))

#define DMA_CMAR(dma_base, channel)	    MMIO32((dma_base) + 0x14 + (0x14 * ((channel) - 1)))

#define DMA_CNDTR(dma_base, channel)	MMIO32((dma_base) + 0x0C + (0x14 * ((channel) - 1)))

#define DMA_CCR(dma_base, channel)	    MMIO32((dma_base) + 0x08 + (0x14 * ((channel) - 1)))
// DMA1
#define DMA1_BASE			            (PERIPH_BASE_AHB + 0x08000)
#define DMA1				            DMA1_BASE

#define DMA_CHANNEL1			        1

#define DMA1_CPAR(channel)		        DMA_CPAR(DMA1, channel)
#define DMA1_CPAR1			            DMA1_CPAR(DMA_CHANNEL1)
    

#define DMA1_CMAR(channel)		        DMA_CMAR(DMA1, channel)
#define DMA1_CMAR1			            DMA1_CMAR(DMA_CHANNEL1)

#define DMA1_CNDTR(channel)		        DMA_CNDTR(DMA1, channel)
#define DMA1_CNDTR1			            DMA1_CNDTR(DMA_CHANNEL1)

#define DMA1_CCR(channel)		        DMA_CCR(DMA1, channel)
#define DMA1_CCR1			            DMA1_CCR(DMA_CHANNEL1)
// TIMERS ///////////////////////////////////////////////////////////////////////////////
#define TIM_CNT(tim_base)		        MMIO32((tim_base) + 0x24)

#define TIM_CCER(tim_base)		        MMIO32((tim_base) + 0x20)

#define TIM_CR1(tim_base)               MMIO32((tim_base) + 0x00)

#define TIM_CCMR2(tim_base)		        MMIO32((tim_base) + 0x1C)

#define TIM_PSC(tim_base)		        MMIO32((tim_base) + 0x28)

#define TIM_ARR(tim_base)		        MMIO32((tim_base) + 0x2C)

#define TIM_CCR2(tim_base)		        MMIO32((tim_base) + 0x38)

#define TIM_EGR(tim_base)		        MMIO32((tim_base) + 0x14)

#define TIM_CCR4(tim_base)		        MMIO32((tim_base) + 0x40)

#define TIM_DIER(tim_base)		        MMIO32((tim_base) + 0x0C)

#define TIM_SR(tim_base)		        MMIO32((tim_base) + 0x10)
// TIMER2
#define TIM2_BASE			            (PERIPH_BASE_APB1 + 0x0000)
#define TIM2				            TIM2_BASE

#define TIM2_CNT			            TIM_CNT(TIM2)

#define TIM2_CCER			            TIM_CCER(TIM2)

#define TIM2_CR1			            TIM_CR1(TIM2)

#define TIM2_CCMR2			            TIM_CCMR2(TIM2)

#define TIM2_PSC			            TIM_PSC(TIM2)

#define TIM2_ARR			            TIM_ARR(TIM2)

#define TIM2_CCR2			            TIM_CCR2(TIM2)

#define TIM2_EGR			            TIM_EGR(TIM2)

#define TIM2_CCR4			            TIM_CCR4(TIM2)

#define TIM2_DIER			            TIM_DIER(TIM2)

#define TIM2_SR				            TIM_SR(TIM2)
// TIMER 4
#define TIM4_BASE			            (PERIPH_BASE_APB1 + 0x0800)
#define TIM4				            TIM4_BASE

#define TIM4_CCER			            TIM_CCER(TIM4)

#define TIM4_CR1			            TIM_CR1(TIM4)

#define TIM4_CCMR2			            TIM_CCMR2(TIM4)

#define TIM4_PSC			            TIM_PSC(TIM4)

#define TIM4_ARR			            TIM_ARR(TIM4)

#define TIM4_CCR2			            TIM_CCR2(TIM4)

#define TIM4_EGR			            TIM_EGR(TIM4)

#define TIM4_CCR4			            TIM_CCR4(TIM4)
// FLASH ////////////////////////////////////////////////////////////////////////////////
#define FLASH_MEM_INTERFACE_BASE	    (PERIPH_BASE_AHB + 0x0a000)

#define FLASH_ACR			            MMIO32(FLASH_MEM_INTERFACE_BASE + 0x00)

#endif //LIBOPENCM3_REGISTERS_H