/*********************************************************************************************************************
 * TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
 * Copyright (c) 2022 SEEKFREE ��ɿƼ�
 *
 * ���ļ��� TC264 ��Դ���һ����
 *
 * TC264 ��Դ�� ��������
 * �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
 * �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
 *
 * ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
 * ����û�������������Ի��ʺ��ض���;�ı�֤
 * ����ϸ����μ� GPL
 *
 * ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
 * ���û�У������<https://www.gnu.org/licenses/>
 *
 * ����ע����
 * ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
 * �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
 * ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
 * ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
 *
 * �ļ�����          cpu0_main
 * ��˾����          �ɶ���ɿƼ����޹�˾
 * �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
 * ��������          ADS v1.9.4
 * ����ƽ̨          TC264D
 * ��������          https://seekfree.taobao.com/
 *
 * �޸ļ�¼
 * ����              ����                ��ע
 * 2022-09-15       pudding            first version
 ********************************************************************************************************************/
#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"

// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������

// **************************** �������� ****************************
int core0_main(void)
{
    clock_init(); // ��ȡʱ��Ƶ��<��ر���>
    debug_init(); // ��ʼ��Ĭ�ϵ��Դ���
    /*****************************///��ʼ��
    ips200_init(IPS200_TYPE_PARALLEL8); // ��Ļ��ʼ��
    mt9v03x_init();

    PidInit(&LSpeed_PID);
    PidInit(&RSpeed_PID);
    Pid_Value();

    encoder_init();
    servo_init();
    motor_init();

    pit_ms_init(CCU60_CH0, 5);

    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_DEBUG_UART);
    seekfree_assistant_oscilloscope_struct oscilloscope_data;
    oscilloscope_data.data[0] =0;
    oscilloscope_data.channel_num = 2;
    // �ȴ����к��ĳ�ʼ�����
    cpu_wait_event_ready();
    while (TRUE)
    {
        Show_Camera_Info();

        MotorDuty1 = (sint32)PidIncCtrl(&LSpeed_PID, (float)(500 - encoder_L)); // �ٶȱջ�
        MotorDuty2 = (sint32)PidIncCtrl(&RSpeed_PID, (float)(500 - encoder_R)); // �ٶȱջ�

        seekfree_assistant_oscilloscope_send(&oscilloscope_data);

        if (MotorDuty1 > 9999)
                MotorDuty1 = 9999;
        else if (MotorDuty1 < -9999)
                MotorDuty1 = 9999;
        if (LSpeed_PID.out > 9999)
            LSpeed_PID.out = 9999;
        else if (LSpeed_PID.out < -9999)
            LSpeed_PID.out = -9999;


        if (MotorDuty2 > 9999)
            MotorDuty2 = 9999;
        else if (MotorDuty2 < -9999)
            MotorDuty2 = -9999;
        if (RSpeed_PID.out > 9999)
            RSpeed_PID.out = 9999;
        else if (RSpeed_PID.out < -9999)
            RSpeed_PID.out = -9999;

        motor_control_dir(MotorDuty2,  MotorDuty1 );
        system_delay_ms(5);
    }
}

#pragma section all restore

// **************************** �������� ****************************
//      encoder_R = encoder_get_count(ENCODER_DIR);
//      encoder_L = -encoder_get_count(ENCODER_QUADDEC);
/*
        MotorDuty1 = (int)PidIncCtrl(&LSpeed_PID, (float)(((sint16)400) - encoder_L  ));
        motor_control_dir(0,(sint32)MotorDuty1);

        seekfree_assistant_oscilloscope_send(&oscilloscope_data);

        oscilloscope_data.data[0]=encoder_L;
        printf("encoder_R=%d\n ",encoder_R);*/

//        system_delay_ms (100);
//        encoder_R = encoder_get_count(ENCODER_DIR);
//         encoder_clear_count(ENCODER_DIR); // ��ձ���������
