#include  <msp430x14x.h>  
//��Ӧ�ĺ�������  
void Init_Keypad(void);//���̳�ʼ��  
void Check_Key(void);  
void delay();  
void Key_Event(void);//��ȡ���̺�������ʹ��ʱͨ���˺������м���ɨ��  
  
//ѡ���Ӧ�Ķ˿�  
#define KEYOUT P1OUT  
#define KEYIN P1IN  
#define KEYDIR P1DIR  
  
#define uchar unsigned char
#define uint  unsigned int
  
/***************ȫ�ֱ���***************/  
uchar key_Pressed;      //�����Ƿ񱻰���:1--�ǣ�0--��  
uchar key_val;          //��ż�ֵ  
uchar key_Flag;         //�����Ƿ��ѷſ���1--�ǣ�0--��  
//���ü����߼���ֵ���������ֵ��ӳ��  
uchar key_Map[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};  
  
/******************************************* 
�������ƣ�Init_Keypad 
��    �ܣ���ʼ��ɨ����̵�IO�˿� 
��    ������ 
����ֵ  ���� 
********************************************/  
void Init_Keypad(void)  
{       
    KEYDIR = 0xf0;       //KEY.0~KEY.3����Ϊ����״̬, KEY.4~KEY.7����Ϊ���״̬  
    KEYOUT |= 0xf0;      // KEY.4~KEY.7����ߵ�ƽ  
    key_Flag = 0;         
    key_Pressed = 0;     
    key_val = 0;  
}  
/********************************************* 
* Check_Key(),��鰴����ȷ�ϼ�ֵ 
*********************************************/  
/******************************************* 
�������ƣ�Check_Key 
��    �ܣ�ɨ����̵�IO�˿ڣ���ü�ֵ 
��    ������ 
����ֵ  ���� 
********************************************/  
void Check_Key(void)  
{  
    uchar row ,col,tmp1,tmp2;  
      
    tmp1 = 0x80;  
    for(row = 0;row < 4;row++)              //��ɨ��  
    {  
        KEYOUT = 0xf0;                      //KEY.4~KEY.7���ȫ1  
        KEYOUT -= tmp1;                      //KEY.4~p1.7�����λ����һ��Ϊ0  
        tmp1 >>=1;                                
        if ((KEYIN & 0x0f) < 0x0f)           //�Ƿ�KEYIN��KEY.0~KEY.3����һλΪ0  
        {                         
            tmp2 = 0x01;                         // tmp2���ڼ�����һλΪ0    
            for(col = 0;col < 4;col++)              // �м��   
            {            
                if((KEYIN & tmp2) == 0x00)           // �Ƿ��Ǹ���,����0Ϊ��  
                {            
                    key_val = key_Map[row * 4 + col];  // ��ȡ��ֵ  
                    return;                         // �˳�ѭ��  
                }  
                tmp2 <<= 1;                        // tmp2����1λ   
            }  
        }  
    }        
}  
/******************************************* 
�������ƣ�delay 
��    �ܣ���ʱԼ15ms������������� 
��    ������ 
����ֵ  ���� 
********************************************/  
void delay()  
{  
    uint tmp;  
       
    for(tmp = 12000;tmp > 0;tmp--);  
}  
/******************************************* 
�������ƣ�Key_Event 
��    �ܣ���ⰴ��������ȡ��ֵ 
��    ������ 
����ֵ  ���� 
********************************************/  
void Key_Event(void)  
{       
    uchar tmp;  
       
    KEYOUT &= 0x00;              // ����KEYOUTȫΪ0���ȴ���������  
    tmp = KEYIN;                 // ��ȡ p1IN  
    if ((key_Pressed == 0x00)&&((tmp & 0x0f) < 0x0f)) //����м�����  
    {                       
        key_Pressed = 1;        // ����а������£�����key_Pressed��ʶ  
        delay();                //��������  
        Check_Key();            // ����check_Key(),��ȡ��ֵ   
    }       
    else if ((key_Pressed == 1)&&((tmp & 0x0f) == 0x0f)) //��������Ѿ��ͷ�  
    {                       
        key_Pressed = 0;        // ���key_Pressed��ʶ  
        key_Flag    = 1;        // ����key_Flag��ʶ  
    }  
    else   
    {  
        _NOP();  
    }       
}  