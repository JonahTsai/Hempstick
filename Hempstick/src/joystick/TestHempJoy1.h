// C:\workspace\Atmel Studio\6.1\FreeRTOSArduino-Test\HempsteadJoystick\src\joystick\TestHempJoy1.h


char ReportDescriptor[61] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x04,                    // USAGE (Joystick)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x09,                    //   USAGE_PAGE (Button)
    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
    0x29, 0x3f,                    //   USAGE_MAXIMUM (Button 63)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x35, 0x00,                    //   PHYSICAL_MINIMUM (0)
    0x45, 0x01,                    //   PHYSICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x3f,                    //   REPORT_COUNT (63)
    0x81, 0x21,                    //   INPUT (Cnst,Ary,Abs,NPrf)
    0x0b, 0x04, 0x00, 0x01, 0x00,  //   USAGE (Generic Desktop:Joystick)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x0b, 0x30, 0x00, 0x01, 0x00,  //     USAGE (Generic Desktop:X)
    0x0b, 0x31, 0x00, 0x01, 0x00,  //     USAGE (Generic Desktop:Y)
    0x0b, 0x32, 0x00, 0x01, 0x00,  //     USAGE (Generic Desktop:Z)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x0f,              //     LOGICAL_MAXIMUM (4095)
    0x75, 0x10,                    //     REPORT_SIZE (16)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x81, 0x22,                    //     INPUT (Data,Var,Abs,NPrf)
    0xc0,                          //         END_COLLECTION
    0xc0                           //     END_COLLECTION
};

