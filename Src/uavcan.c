#include <stdio.h>
#include <stdlib.h>
#include "canard.h"
#include "canard_stm32.h"
#include "uavcan.h"
#include "stm32f1xx_hal.h"
#include "main.h"

#define CANARD_SPIN_PERIOD   500
#define PUBLISHER_PERIOD_mS     25
            
static CanardInstance g_canard;                //The library instance
static uint8_t g_canard_memory_pool[1024];     //Arena for memory allocation, used by the library
static uint32_t  g_uptime = 0;
uint16_t rc_pwm[6] = {0,0,0,0,0,0};



 

//////////////////////////////////////////////////////////////////////////////////////

bool shouldAcceptTransfer(const CanardInstance* ins,
                          uint64_t* out_data_type_signature,
                          uint16_t data_type_id,
                          CanardTransferType transfer_type,
                          uint8_t source_node_id)
{
    if ((transfer_type == CanardTransferTypeRequest) &&(data_type_id == UAVCAN_GET_NODE_INFO_DATA_TYPE_ID))
    {
        *out_data_type_signature = UAVCAN_GET_NODE_INFO_DATA_TYPE_SIGNATURE;
        return true;
    }
    if (data_type_id == UAVCAN_EQUIPMENT_ESC_RAWCOMMAND_ID)
    {
        *out_data_type_signature = UAVCAN_EQUIPMENT_ESC_RAWCOMMAND_SIGNATURE;
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////

void onTransferReceived(CanardInstance* ins, CanardRxTransfer* transfer)
{
    if ((transfer->transfer_type == CanardTransferTypeRequest) &&
        (transfer->data_type_id == UAVCAN_GET_NODE_INFO_DATA_TYPE_ID))
    {
        getNodeInfoHandleCanard(transfer);
    } 

    if (transfer->data_type_id == UAVCAN_EQUIPMENT_ESC_RAWCOMMAND_ID)
    {
        rawcmdHandleCanard(transfer);
    }
    
}

void getNodeInfoHandleCanard(CanardRxTransfer* transfer)
{
        uint8_t buffer[UAVCAN_GET_NODE_INFO_RESPONSE_MAX_SIZE];
        memset(buffer,0,UAVCAN_GET_NODE_INFO_RESPONSE_MAX_SIZE);
        uint16_t len = makeNodeInfoMessage(buffer);
        int result = canardRequestOrRespond(&g_canard,
                                            transfer->source_node_id,
                                            UAVCAN_GET_NODE_INFO_DATA_TYPE_SIGNATURE,
                                            UAVCAN_GET_NODE_INFO_DATA_TYPE_ID,
                                            &transfer->transfer_id,
                                            transfer->priority,
                                            CanardResponse,
                                            &buffer[0],
                                            (uint16_t)len);
}





void uavcanInit(void)
{
    CanardSTM32CANTimings timings;
    int result = canardSTM32ComputeCANTimings(HAL_RCC_GetPCLK1Freq(), 1000000, &timings);
    if (result)
    {
        __ASM volatile("BKPT #01");
    }
    result = canardSTM32Init(&timings, CanardSTM32IfaceModeNormal);
    if (result)
    {
        __ASM volatile("BKPT #01");
    }
 
    canardInit(&g_canard,                         // Uninitialized library instance
               g_canard_memory_pool,              // Raw memory chunk used for dynamic allocation
               sizeof(g_canard_memory_pool),      // Size of the above, in bytes
               onTransferReceived,                // Callback, see CanardOnTransferReception
               shouldAcceptTransfer,              // Callback, see CanardShouldAcceptTransfer
               NULL);
 
    canardSetLocalNodeID(&g_canard, 10);
}

void sendCanard(void)
{
  const CanardCANFrame* txf = canardPeekTxQueue(&g_canard); 
  while(txf)
    {
        const int tx_res = canardSTM32Transmit(txf);
        if (tx_res < 0)                  // Failure - drop the frame and report
        {
            __ASM volatile("BKPT #01");  // TODO: handle the error properly
        }
        if(tx_res > 0)
        {
            canardPopTxQueue(&g_canard);
        }
        txf = canardPeekTxQueue(&g_canard); 
    }
}

void receiveCanard(void)
{
    CanardCANFrame rx_frame;
    int res = canardSTM32Receive(&rx_frame);
    if(res)
    {
        canardHandleRxFrame(&g_canard, &rx_frame, HAL_GetTick() * 1000);
    }    
}
void spinCanard(void)
{  
    static uint32_t spin_time = 0;
    if(HAL_GetTick() < spin_time + CANARD_SPIN_PERIOD) return;  // rate limiting
    spin_time = HAL_GetTick();
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);   
    
    uint8_t buffer[UAVCAN_NODE_STATUS_MESSAGE_SIZE];    
    static uint8_t transfer_id = 0;                           // This variable MUST BE STATIC; refer to the libcanard documentation for the background
    makeNodeStatusMessage(buffer);  
    canardBroadcast(&g_canard, 
                    UAVCAN_NODE_STATUS_DATA_TYPE_SIGNATURE,
                    UAVCAN_NODE_STATUS_DATA_TYPE_ID,
                    &transfer_id,
                    CANARD_TRANSFER_PRIORITY_LOW,
                    buffer, 
                    UAVCAN_NODE_STATUS_MESSAGE_SIZE);                         //some indication
    
}



void publishCanard(void)
{  
    static uint32_t publish_time = 0;
    static int step = 0;
    if(HAL_GetTick() < publish_time + PUBLISHER_PERIOD_mS) {return;} // rate limiting
    publish_time = HAL_GetTick();
  
    uint8_t buffer[UAVCAN_PROTOCOL_DEBUG_KEYVALUE_MESSAGE_SIZE];
    memset(buffer,0x00,UAVCAN_PROTOCOL_DEBUG_KEYVALUE_MESSAGE_SIZE);
    step++;
    if(step == 256) 
    {
        step = 0;
    }
  
    float val = sine_wave[step];
    static uint8_t transfer_id = 0;
    canardEncodeScalar(buffer, 0, 32, &val);
    memcpy(&buffer[4], "sin", 3);    
    canardBroadcast(&g_canard, 
                    UAVCAN_PROTOCOL_DEBUG_KEYVALUE_SIGNATURE,
                    UAVCAN_PROTOCOL_DEBUG_KEYVALUE_ID,
                    &transfer_id,
                    CANARD_TRANSFER_PRIORITY_LOW,
                    &buffer[0], 
                    7);
    memset(buffer,0x00,UAVCAN_PROTOCOL_DEBUG_KEYVALUE_MESSAGE_SIZE);
  
    val = step;
    canardEncodeScalar(buffer, 0, 32, &val);
    memcpy(&buffer[4], "stp", 3);  
    canardBroadcast(&g_canard, 
                    UAVCAN_PROTOCOL_DEBUG_KEYVALUE_SIGNATURE,
                    UAVCAN_PROTOCOL_DEBUG_KEYVALUE_ID,
                    &transfer_id,
                    CANARD_TRANSFER_PRIORITY_LOW,
                    &buffer[0], 
                    7);
}

void makeNodeStatusMessage(uint8_t buffer[UAVCAN_NODE_STATUS_MESSAGE_SIZE])
{
    uint8_t node_health = UAVCAN_NODE_HEALTH_OK;
    uint8_t node_mode   = UAVCAN_NODE_MODE_OPERATIONAL;
    memset(buffer, 0, UAVCAN_NODE_STATUS_MESSAGE_SIZE);
    uint32_t uptime_sec = (HAL_GetTick() / 1000);
    canardEncodeScalar(buffer,  0, 32, &uptime_sec);
    canardEncodeScalar(buffer, 32,  2, &node_health);
    canardEncodeScalar(buffer, 34,  3, &node_mode);
}

uint16_t makeNodeInfoMessage(uint8_t buffer[UAVCAN_GET_NODE_INFO_RESPONSE_MAX_SIZE])
{
    memset(buffer, 0, UAVCAN_GET_NODE_INFO_RESPONSE_MAX_SIZE);
    makeNodeStatusMessage(buffer);
   
    buffer[7] = APP_VERSION_MAJOR;
    buffer[8] = APP_VERSION_MINOR;
    buffer[9] = 1;                          // Optional field flags, VCS commit is set
    uint32_t u32 = GIT_HASH;
    canardEncodeScalar(buffer, 80, 32, &u32); 
    
    readUniqueID(&buffer[24]);
    const size_t name_len = strlen(APP_NODE_NAME);
    memcpy(&buffer[41], APP_NODE_NAME, name_len);
    return 41 + name_len ;
}

void readUniqueID(uint8_t* out_uid)
{
    for (uint8_t i = 0; i < UNIQUE_ID_LENGTH_BYTES; i++)
    {
        out_uid[i] = i;
    }
}


void rawcmdHandleCanard(CanardRxTransfer* transfer)
{
    
    int offset = 0;
    for (int i = 0; i<6; i++)
    {
        if (canardDecodeScalar(transfer, offset, 14, true, &rc_pwm[i])<14) { break; }
        offset += 14;
    }
   // rcpwmUpdate(ar);
}
void showRcpwmonUart()
{
    char str[5];
    itoa(rc_pwm[0],str,10);
    HAL_UART_Transmit(&huart1,str,5,0xffff);
    HAL_UART_Transmit(&huart1,"\n",2,0xffff);
}